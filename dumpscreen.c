#include "video.h"

extern u32 gsmphys;
int cangencode = 0;

int main(int argc, char *argv[])
{
	int i, j, k;

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
		if (lowbits & 1){
			for(j = 0; j < 4096; j += 8) {
				fprintf(stderr, "%#x:", base+j);
				for(k = 0; k < 8; k++){
					u32 mem = (base-gsmphys)+j+k|1;
					u32 val = io_I915_READ32(mem);
					fprintf(stderr, "%#x ", val);
				}
				fprintf(stderr, "\n");
			}
		}
	}
}
