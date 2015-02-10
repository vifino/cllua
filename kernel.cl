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
	if (code[5] != 0x00) {
		puts("Format not supported!\n");
		return;
	}
	if (code[6] != 0x01) {
		puts("Only Little Endian is supported at this time! Sorry!\n");
	}
	if (code[7] != 0x04) {
		puts("Only 4 byte integers supported!\n");
	}
	if (code[8] != 0x08) {
		puts("Only 4 byte integers supported!\n");
	}
}
