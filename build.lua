-- lua5.1/luajit
function run(cmd)
	print("$ "..cmd)
	return os.execute(cmd)
end

local files = table.concat({"cllua.cpp"}," ")
local obj = "cllua.o"
local exe = "cllua"
local cpp = os.getenv("CPP") or "g++"
local libs = "-l"..table.concat({"OpenCL","lua5.1"}," -l")
local cppflags = "-c -std=c++11"

run(cpp.." "..files.." "..cppflags.." -o "..obj)
run(cpp.." "..obj.." "..libs.." -o "..exe)
