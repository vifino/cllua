#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <CL/cl.hpp>

int main() {
	std::vector<cl::Platform> all_platforms;
	cl::Platform::get(&all_platforms);
	if(all_platforms.size()==0){
		std::cout<<" No platforms found. Check OpenCL installation!\n";
		exit(1);
	}
	cl::Platform default_platform=all_platforms[0];
	std::cout << "Using platform: "<<default_platform.getInfo<CL_PLATFORM_NAME>()<<"\n";

	//get default device of the default platform
	std::vector<cl::Device> all_devices;
	default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
	if(all_devices.size()==0){
		std::cout<<" No devices found. Check OpenCL installation!\n";
		exit(1);
	}
	cl::Device default_device=all_devices[0];
	std::cout<< "Using device: "<<default_device.getInfo<CL_DEVICE_NAME>()<<"\n";

	cl::Context context({default_device});

	cl::Program::Sources sources;

	// Load kernel.cl
	std::ifstream t("kernel.cl");
	std::string kernel_code((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

	sources.push_back({kernel_code.c_str(),kernel_code.length()});

	cl::Program program(context,sources);
	if(program.build({default_device})!=CL_SUCCESS){
		std::cout<<" Error building: "<<program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device)<<"\n"; // Build failure.
		exit(1);
	}
	// load source into here
	std::ifstream s("source.lua");
	std::string luacode((std::istreambuf_iterator<char>(s)), std::istreambuf_iterator<char>());
	std::int luasource_size;


	cl::Buffer buffer_luacode(context,CL_MEM_READ_WRITE,sizeof(char)*luasource_size);

	cl::CommandQueue queue(context,default_device);
	queue.enqueueWriteBuffer(buffer_luacode,CL_TRUE,0,sizeof(char)*luasource_size,luasource);

	return 0;
}
