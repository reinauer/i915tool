#include "video.h"

int cangencode = 0;

int main(int argc, char *argv[])
{
	int i;

	init(argc, argv);

	for(i = 0; i < 32768; i++){
		u32 word = io_I915_READ32(i|1);
		u32 base = word;
		u32 lowbits = word;
		fprintf(stderr, "%d: [%#x]%#x, %s, %s, %s, %s\n", i, word, base, 
			lowbits & 8 ? "GFDT": "NO GFDT", 
			lowbits & 4 ? "Cached in LLC": "use cacheability controls from gtt entry", 
			lowbits & 2 ? "cacheable in L3": "NOT  cacheable in L3", 
			lowbits & 1 ? "valid": "NOT valid");
	}
}
