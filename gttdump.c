#include "video.h"

int cangencode = 0;

int main(int argc, char *argv[])
{
	int i;
	int num = 32768;

	init(&argc, &argv);

	for(i = 0; i < num; i += 4){
		u32 word = io_I915_READ32(i|1);
		u32 base = word & (~0xfff);
		u16 low12bits = word & 0xfff;
		printf("%d: [%#x]%#x, %s, %s, %s, %s\n", i, word, base, 
			low12bits & 8 ? "GFDT": "~GFDT", 
			low12bits & 4 ? ";Cached in LLC": ";from gttentry", 
			low12bits & 2 ? ";cacheable L3": ";~cacheable in L3", 
			low12bits & 1 ? ";Valid": ";~Valid");
	}
}
