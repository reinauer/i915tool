#include <stdio.h>

main(int argc, char *argv[])
{
	int compress = 1;
	unsigned char bus, dev, fn, reg;
	unsigned long indir = 0, _cf8=0xcf8;
	unsigned long indiraddr = 0x50a0, indirdata = 0x50a4;
	int indirremoved = 0,_cf8removed = 0;
	char cmd, size;
	unsigned long data, address;
	int lineno = 0;
	char line[80];
	if (argc > 1)
		indir = strtoul(argv[1], 0, 0);
	if (argc > 2)
		indirdata = strtoul(argv[2], 0, 0);
		
	while (gets(line)){
		lineno++;
		sscanf(line, "%c%c%lx%lx", &cmd, &size, &data, &address);
		if (! compress) {
			printf("{%c%c, 1, \"\",0x%08lx, 0x%08lx, 0},\n", cmd, size, data, address);
			continue;
		}

		if (address == indiraddr){
			indirremoved++;
			indir = data;
			continue;
		}

		if (address == 0xcf8){
			_cf8removed++;
			_cf8 = data;
			bus = data >> 16;
			dev = ((unsigned short)data) >> 11;
			fn = (data>>8)&7;
			reg = ((unsigned char)data)>>2;
			continue;
		}
		if ((address & (~3)) == 0xcfc){
			printf("{M, 1, \"pci dev(0x%x,0x%x,0x%x,0x%x)\"},\n", bus, dev, fn, reg);
			printf("{%cPC, 0x%08lx, \"\", 0x%08lx, 0x%08lx},\n", cmd, _cf8, address, data);
			continue;
		}

		if (address == indirdata) {
			if (size != 'l')
				fprintf(stderr, "BOTCH at line %d: 1804, but not 'l', skipping\n", lineno);
			else
				printf("{G%c%c, 1, \"\", 0x%08lx, 0x%08lx, 0},\n", cmd, size, indir, data);
			continue;
		}
		printf("{%c%c, 1, \"\", 0x%08lx, 0x%08lx, 0},\n", cmd, size, address, data);
			
	}

	fprintf(stderr, "//Removed %d indirect IOs to %08lx\n", indirremoved, indiraddr);
	fprintf(stderr, "//Removed %d IOs to cf8\n", _cf8removed);
	/* never trust anything */
	fflush(stdout);
	exit(0);
}
// cc -g -o translatewtm2  translatewtm2.c 
// ./translatewtm2 < MTV2IOAPR022013 | wc
// ./translatewtm2 <MTV2IOAPR022013  > MTV2IOAPR022013.c
// wc MTV2IOAPR022013
// wc MTV2IOAPR022013.c
//140635  421913 2966609 MTV2IOAPR022013
// 107453  537265 3868308 MTV2IOAPR022013.c
// now, with compress enabled.  17808   89040  641088
