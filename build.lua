-- lua5.1/luajit
function run(cmd)
	print("$ "..cmd)
	return os.execute(cmd)/256
end
local file = "cllua.c"
local out = "cllua"
local libs = {"OpenCl"}
local cmdline = os.getenv("CC") or "clang"
cmdline = cmdline .. " -std=c++ "..file.." -o "..out 
for _,v in pairs(libs) do
	cmdline = cmdline .. " -l"..v
end
run(cmdline)
