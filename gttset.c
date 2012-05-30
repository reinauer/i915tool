#include "video.h"

int cangencode = 0;
extern u32 gsmphys;
extern u32 aperture, aperturesize;

int main(int argc, char *argv[])
{
	int i;
	int num = 32768;

	init(&argc, &argv);

	for(i = 0; i < 32; i += 4){
		u32 word = io_I915_READ32(i|1);
		u32 base = word;
		u32 lowbits = word;
		printf("%d: [%#x]%#x, %s, %s, %s, %s\n", i, word, base, 
			lowbits & 8 ? "GFDT": "~GFDT", 
			lowbits & 4 ? ";Cached in LLC": ";from gttentry", 
			lowbits & 2 ? ";cacheable L3": "~;cacheable in L3", 
			lowbits & 1 ? ";V": ";~V");
	}

	printf("# PTEs is %d\n", aperturesize / 4096);
	printf("Start of graphics pages would be %#p\n", gsmphys + 2*1024*1024);
	for(i = 0; i < aperturesize/1024; i += 4){
		u32 word = gsmphys + 2*1024*1024 + i*4096;
		io_I915_WRITE32(i|1,word);
	}

	
}
