void puts(const constant unsigned char* str) {
	printf("%s",str);
}

void kernel lua_vm(global const unsigned char* code) {
	if (code[0] != 27 || code[1] != 'L' || code[2] != 'u' || code[3] != 'a') {
		puts("INVALID LUA HEADER. QUITTING\n");
		return;
	}
	if (code[4] != 0x51) {
		puts("Only Lua 5.1 compiled code supported. Sorry.\n");
		return;
	}
}
