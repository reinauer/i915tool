#include <stdio.h>

main()
{
	int compress = 1;
	unsigned char bus, dev, fn, reg;
	unsigned long _1800 = 0, _cf8=0;
	int _1800removed = 0,_cf8removed = 0;
	char cmd, size;
	unsigned long data, address;
	char line[80];
	while (gets(line)){
		sscanf(line, "%c%c%lx%lx", &cmd, &size, &data, &address);
		if (! compress) {
			printf("{%c%c, 1, 0x%08lx, 0x%08lx, 0},\n", cmd, size, data, address);
			continue;
		}

		if (address == 0x1800){
			if (data == _1800){
				_1800removed++;
				continue;
			}
			printf("{%c%c, 1, 0x%08lx, 0x%08lx, 0},\n", cmd, size, address, data);
			_1800 = data;
			continue;
		}

		if (address == 0xcf8){
			if (data == _cf8){
				_cf8removed++;
				continue;
			}
			_cf8 = data;
			bus = data >> 16;
			dev = ((unsigned short)data) >> 11;
			fn = (data>>8)&7;
			reg = ((unsigned char)data)>>2;
			printf("/* pci dev(0x%x,0x%x,0x%x,0x%x)*/\n", bus, dev, fn, reg);
			continue;
		}

		printf("{%c%c, 1, 0x%08lx, 0x%08lx, 0},\n", cmd, size, address, data);
			
	}

	fprintf(stderr, "//Removed %d IOs to 1800\n", _1800removed);
	fprintf(stderr, "//Removed %d IOs to cf8\n", _cf8removed);
}
// cc -g -o translatewtm2  translatewtm2.c 
// ./translatewtm2 < MTV2IOAPR022013 | wc
// ./translatewtm2 <MTV2IOAPR022013  > MTV2IOAPR022013.c
// wc MTV2IOAPR022013
// wc MTV2IOAPR022013.c
