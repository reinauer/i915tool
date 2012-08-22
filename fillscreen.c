#include "video.h"

extern u32 gsmphys;
int cangencode = 0;
extern u8 *gfx;

int main(int argc, char *argv[])
{
	int i, j, k;
	int size = 32 * 1024 * 1024;
	int loopcount;
	char bits[] = {0x3f, 0x1f, 0xf, 0x7, 0x3, 0x1, 020, 0x30, 0x38, 0x3c, 
		0x3e};
	unsigned char cycle = 0;
	unsigned int shift = 8;
	unsigned long fill = 0xaa559900;

	init(&argc, &argv);

	if (argc)
		size = strtoul(argv[0], 0, 0);
	if (argc > 0)
		fill = strtoul(argv[1], 0, 0);

	print_hex_dump_bytes("", DUMP_PREFIX_ADDRESS, gfx, 256);

	/* we do 32M in coreboot */
	unsigned long *x = (unsigned long *)gfx;
	loopcount = size*1024/sizeof(*x);
	printf("Change %d things\n", loopcount);
	for(i = 0; i < loopcount; i++){
		x[i] = fill;
	}
	print_hex_dump_bytes("", DUMP_PREFIX_ADDRESS, gfx, 256);

}
