#include "video.h"

extern u32 gsmphys;
int cangencode = 0;
extern u8 *gfx;

int main(int argc, char *argv[])
{
	int i, j, k;
	int size = gfxsize;
	unsigned long fill;

	init(&argc, &argv);

	print_hex_dump_bytes("", DUMP_PREFIX_ADDRESS, gfx, 256);

	/* we do 32M in coreboot */
	unsigned long *x = (unsigned long *)gfx;
	while (read(0, &fill, 4) > 3){
		x[i] = fill;
	}
	print_hex_dump_bytes("", DUMP_PREFIX_ADDRESS, gfx, 256);

}
