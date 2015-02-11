#!/usr/bin/env lua
function run(cmd)
	print("$ "..cmd)
	return os.execute(cmd)
end

local files = table.concat({"cllua.cpp"}," ")
local obj = "cllua.o"
local exe = "cllua"
local cpp = os.getenv("CXX") or "g++"
local libs = "-l"..table.concat({"OpenCL","lua5.1"}," -l")
local cppflags = "-c -std=c++11"

run("xxd -i kernel.cl > kernel_cl.h")
run(cpp.." "..files.." "..cppflags.." -o "..obj)
run(cpp.." "..obj.." "..libs.." -o "..exe)
