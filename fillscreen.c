#include "video.h"

extern u32 gsmphys;
int cangencode = 0;
extern u8 *gfx;

int main(int argc, char *argv[])
{
	int i, j, k;
	int size = gfxsize;
	int loopcount;
	char bits[] = {0x3f, 0x1f, 0xf, 0x7, 0x3, 0x1, 020, 0x30, 0x38, 0x3c, 
		0x3e};
	unsigned char cycle = 0;
	unsigned int shift = 8;
	unsigned long fill = 0xaa5599;

	init(&argc, &argv);

	if (argc)
		size = strtoul(argv[0], 0, 0);
	if (argc > 1)
		fill = strtoul(argv[1], 0, 0);

	print_hex_dump_bytes("", DUMP_PREFIX_ADDRESS, gfx, 256);

	/* we do 32M in coreboot */
	unsigned long *x = (unsigned long *)gfx;
	printf("Change %d things\n", size);
	for(i = 0; i < size; i++){
		x[i] = fill;
	}
	print_hex_dump_bytes("", DUMP_PREFIX_ADDRESS, gfx, 256);

}
