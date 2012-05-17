#include "video.h"

extern u32 gsmphys;
int cangencode = 0;
extern u8 *gfx;

int main(int argc, char *argv[])
{
	int i, j, k;

	init(&argc, &argv);

	print_hex_dump_bytes("", DUMP_PREFIX_ADDRESS, gfx, 256);

	for(i = 0; i < 1048576; i++)
		gfx[i] = i;
	print_hex_dump_bytes("", DUMP_PREFIX_ADDRESS, gfx, 256);

}
