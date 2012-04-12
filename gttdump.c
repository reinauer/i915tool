#include "video.h"

int cangencode = 0;

int main(int argc, char *argv[])
{
	int i;

	init(argc, argv);

	for(i = 0; i < 32768; i += 4){
		u32 word = io_I915_READ32(i|1);
		u32 base = word;
		u32 lowbits = word;
		fprintf(stderr, "%d: [%#x]%#x, %s, %s, %s, %s\n", i, word, base, 
			lowbits & 8 ? "GFDT": "~GFDT", 
			lowbits & 4 ? ";Cached in LLC": ";from gttentry", 
			lowbits & 2 ? ";cacheable L3": "~;cacheable in L3", 
			lowbits & 1 ? ";V": ";~V");
	}
}
