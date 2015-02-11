#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

#include <CL/cl.hpp>

#include "kernel_cl.h"

extern "C" {
	#include <lua5.1/lua.h>
	#include <lua5.1/lauxlib.h>
}

typedef struct {
    size_t *len;
    char **data;
} BS_DESCRIP;

int scriptMemoryWriter(lua_State* ls, const void* p, size_t sz, void* ud)
{
    BS_DESCRIP* bd = (BS_DESCRIP*)ud;
    char* newData = (char*)realloc(*(bd->data), (*(bd->len)) + sz);

    if(newData)
    {
        memcpy(newData + (*(bd->len)), p, sz);
        *(bd->data) = newData;
        *(bd->len) += sz;

    } else {
        free(newData);

        return 1;
    }

    return 0;
}

unsigned char outputBuffer[0x8000];

int main() {
	memset(outputBuffer,0,0x8000);

	std::vector<cl::Platform> all_platforms;
	cl::Platform::get(&all_platforms);
	if(all_platforms.size()==0){
		std::cout<<" No platforms found. Check OpenCL installation!\n"; // No Vendor ICD's installed.
		exit(1);
	}
	cl::Platform default_platform=all_platforms[0];
	std::cout << "Using platform: "<<default_platform.getInfo<CL_PLATFORM_NAME>()<<"\n";

	//get default device of the default platform
	std::vector<cl::Device> all_devices;
	default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices); // No Vendor ICD's installed.
	if(all_devices.size()==0){
		std::cout<<" No devices found. Check OpenCL installation!\n";
		exit(1);
	}
	cl::Device default_device=all_devices[0];
	std::cout<< "Using device: "<<default_device.getInfo<CL_DEVICE_NAME>()<<"\n"; // Print the device we are using.

	cl::Context context({default_device});

	cl::Program::Sources sources;

	// Load kernel.cl
	/*std::ifstream t("kernel.cl");
	std::string kernel_code((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());*/

	sources.push_back({(const char*)kernel_cl,(size_t)kernel_cl_len}); // Push over the kernel code

	cl::Program program(context,sources);
	if(program.build({default_device})!=CL_SUCCESS){
		std::cout<<"Error building: "<<program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device)<<"\n"; // Build failure.
		exit(1);
	}
	std::cout<< "Built without errors"<<"\n";
	// load source into here
	std::ifstream s("source.lua");
	std::string luasource((std::istreambuf_iterator<char>(s)), std::istreambuf_iterator<char>());
	int luasource_size;

	lua_State *state = luaL_newstate(); // New lua state
	luaL_loadbuffer(state, luasource.c_str(), luasource.length(), "cl_lua");
	char* bytecode = 0L;
	size_t bytecode_len = 0;
	BS_DESCRIP bd = {&bytecode_len, &bytecode};
	lua_dump(state,scriptMemoryWriter,&bd); // Dump bytecode from script

	cl::Buffer buffer_luacode(context,CL_MEM_READ_WRITE,sizeof(char)*bytecode_len); // Create bytecode buffer

	cl::CommandQueue queue(context,default_device);
	queue.enqueueWriteBuffer(buffer_luacode,CL_TRUE,0,sizeof(char)*bytecode_len,bytecode);

	cl::make_kernel<cl::Buffer> lua_vm(cl::Kernel(program,"lua_vm"));
	cl::EnqueueArgs eargs(queue,cl::NDRange(1),cl::NullRange);
	lua_vm(eargs,buffer_luacode).wait(); // Run and wait until done.

	return 0;
}
