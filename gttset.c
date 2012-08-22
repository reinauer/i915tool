#include "video.h"

int cangencode = 0;
extern u32 gsmphys;
extern u32 aperture, aperturesize;

int main(int argc, char *argv[])
{
	int i;
	unsigned long baseM;

	init(&argc, &argv);

	for(i = 0; i < 32; i++){
		u32 word = io_I915_READ32((i*4)|1);
		u32 base = word;
		u32 lowbits = word;
		printf("%d: [%#x]%#x, %s, %s, %s, %s\n", i, word, base, 
			lowbits & 8 ? "GFDT": "~GFDT", 
			lowbits & 4 ? ";Cached in LLC": ";from gttentry", 
			lowbits & 2 ? ";cacheable L3": "~;cacheable in L3", 
			lowbits & 1 ? ";V": ";~V");
	}

	baseM = gsmphys + 2*1024*1024;
	if (argc)
		baseM = 1048576*strtoul(argv[0], 0, 0);
	printf("# PTEs is %d\n", gfxpages);
	printf("Start of graphics pages would be %#p\n", baseM);
	for(i = 0; i < gfxpages; i++){
		u32 word = baseM + i*4096;
		io_I915_WRITE32((i*4)|1,word|1);
	}

	
}
