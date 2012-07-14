#include "video.h"

extern u32 gsmphys;
int cangencode = 0;
extern u8 *gfx;

int main(int argc, char *argv[])
{
	int i, j, k;

	init(&argc, &argv);

	print_hex_dump_bytes("", DUMP_PREFIX_ADDRESS, gfx, 256);

	/* we do 32M in coreboot */
	unsigned long long *x = (unsigned long long *)gfx;
	for(i = 0; i < 32*1024*1024/sizeof(unsigned long long); i += sizeof(unsigned long long))
		x[i] = i;
	print_hex_dump_bytes("", DUMP_PREFIX_ADDRESS, gfx, 256);

}
