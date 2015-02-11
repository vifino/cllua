#include main.h

int header_validate(char* chunk) {
	// signature
	for (int i=0;i<4;i++) {
		if (chunk[i]!=ch_signature[i]) {
			return 0;
		}
	}
	if (
		chunk[4]!=ch_version || // version
		chunk[5]!=0 ||          // format version
		chunk[6]!=1 ||          // little endian
		chunk[7]!=4 ||          // size of int
		chunk[8]!=4 ||          // size of size_t
		chunk[9]!=4 ||          // size of instruction
		chunk[10]!=8 ||         // size of lua number
		chunk[11]!=0            // integral
	) {
		return 0;
	}
	return 1;
}