#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <err.h>

#include <sys/io.h>
#include <sys/time.h>
#include <linux/types.h>
#include <errno.h>
#include <unistd.h>

#include "google.c"
unsigned int *gfx = NULL;
unsigned int membase = 0xd0000000;
unsigned int memsize = 32 * 1024 * 1024;
unsigned int physbase;
int gfxpages = 4250;
/* pagesize in longs */
int pagesize = 1024;
int fakeit = 0;

/* do everything -- page size computations, all that stuff --
 * in terms of longs. It's easier.
 */
void *
mapit(unsigned int phys, unsigned int size)
{
	void *virt;
	int kfd;
	kfd = open("/dev/mem", O_RDWR);
	if (kfd < 0)
		errx(1, "/dev/mem");
	virt = mmap(NULL, size, PROT_WRITE|PROT_READ, MAP_SHARED, kfd, phys);
	close(kfd);
	if ((void *)-1 == virt)
		errx(1, "mmap");
	return virt;
}

int addrport = 0x1000;
int dataport = 0x1004;
unsigned int io_I915_READ32(unsigned int addr)
{
       unsigned int val;
	if (fakeit){
		printf("READ %08x\n", addr);
		return 0;
	}

       outl(addr, addrport);
       val = inl(dataport);
       return val;
}

void io_I915_WRITE32(unsigned int addr, unsigned int val)
{
	if (fakeit){
		printf("WRITE %08x, val %08x\n", addr, val);
		return;
	}
       outl(addr, addrport);
       outl(val, dataport);
}

/* the address is assumed to point to the start of the page */
void onepage(unsigned int *address, unsigned int *data, int xsize)
{
	unsigned int offset;
	unsigned int page;
	unsigned int pageoffset;
	int i, size;

	/* we need to remap this page. Figure out which page it is
	 * and set it up
	 */
	/* get a BYTE offset */
	offset = (unsigned long)address - (unsigned long)gfx;
	/* this one thing has to be in units of bytes  -- so use byte pagesize*/
	page = offset >> 12;
	/* our target is pointing to the common page area. 
	 * make it point to the separate page area
	 */
	io_I915_WRITE32((page*4)|1,(physbase + offset)|1);
	/* OK, now, figure out how far we are into the page
	 * and fill the space with white. 
	 */
	offset = ((unsigned long)address)&0xfff;
	/* that's a byte offset. Make it a long index. */
	pageoffset = offset >>2;
	/* and make our address a page-aligned address */
	address = (unsigned int *) (((unsigned long)address>>12)<<12);
	for(i = 0; i < pageoffset; i++){
		if (fakeit)
			printf("%p = 0xffffff\n", &address[i]);
		else
			address[i] = 0xffffff;
	}
	for(size = 0; size < xsize; size++, i++){
		if (fakeit)
			printf("%p = %08x\n", &address[i], *data++);
		else
			address[i] = *data++;
	}
	/* fill out the rest of the page with white */
	for(;size < 1024; size++, i++){
		if (fakeit)
			printf("%p = 0xffffff\n", &address[i]);
		else
			address[i] = 0xffffff;
	}
}


/* goal: grab bits of the image that we're almost always
 * ripping off page-sized bits
 * hint: we assume xsize is > 0. Don't be dumb. 
 */
void oneline(unsigned int *address, unsigned int *data, int xsize)
{
	int size, amt;
	unsigned int start, end;
	for(size = 0; size < xsize;){
		/* figure out how much remains */
		start = (unsigned long) address;
		/* set round to end of this page at most */
		/* end is a BYTE address */
		/* end will have at most the value of the start of the
		 * NEXT page
		 */
		end = (((start + 4096)>>12)<<12);
		/* compute amount in bytes */
		amt = end - start;
		/* convert to words */
		amt >>= 2;
		/* maybe it's too much */
		amt = (xsize - size) < 1024 ? (xsize - size) : amt;
		
		onepage(address, data, amt);

		/* the goal is that we've rounded up to a page 
		 * and now tear off page-sized chunks
		 */
		size += amt;
		address += amt;
		data += amt;
	}
}
	
void image(unsigned int *address, unsigned int *data, int x, int y, int xsize, int ysize)
{
  int yamt;
	address = &address[y*2560];
	for(yamt = 0; yamt < ysize; yamt++){
		oneline(&address[x], data, xsize);
		address += 2560;
		data += xsize;
	}
}
	
int main(int argc, char *argv[])
{
	int x = imgx, y = imgy, xsize = imgxsize, ysize=imgysize;

	if (argc == 1){} else 
	if (argc == 2){
		printf("=====================WARNING: FAKING IT\n");
		fakeit++;
	} else
	if (argc == 5 || argc == 6){
		x = strtoul(argv[1], 0, 0);
		y = strtoul(argv[2], 0, 0);
		xsize = strtoul(argv[3], 0, 0);
		ysize = strtoul(argv[4], 0, 0);
		if (argc == 6) fakeit++;
	} else {printf("no args or one arg or 4 args\n");}
	if (! fakeit){
		iopl(3);
	} 
	gfx = mapit(membase, memsize);

	physbase = 0xada00000;
	printf(", gfx is %p, # PTEs is %d\n", gfx, gfxpages);
	printf("Start of graphics pages would be %p\n", (void *)(unsigned long)physbase);
	printf("Put it at [%d,%d]-[%d,%d]\n", x, y, xsize, ysize);

	/* The black rect. */
#if 0
	printf("image(gfx, black, 0, 0, 512, 1);\n");image(gfx, black, 0, 0, 512, 1);
	printf("NEXT %d\n", i++);
	printf("image(gfx, black, 1024, 1024, 1026, 1);\n");image(gfx, black, 1024, 1024, 1026, 1);
	printf("NEXT %d\n", i++);
	printf("image(gfx, black, 511, 1024, 1, 5);\n");image(gfx, black, 511, 1024, 1, 5);
	printf("NEXT %d\n", i++);
	printf("image(gfx, black, 1024, 1024, 1, 1);\n");image(gfx, black, 1024, 1024, 1, 1);
	printf("NEXT %d\n", i++);
	printf("image(gfx, black, 1024, 1024, 3, 1);\n");image(gfx, black, 1024, 1024, 3, 1);
	printf("NEXT %d\n", i++);
	printf("image(gfx, black, 1027, 1024, 3, 1);\n");image(gfx, black, 1027, 1024, 3, 1);
	printf("NEXT %d\n", i++);
	printf("image(gfx, black, 1024, 1024, 2000, 15);\n");image(gfx, black, 1024, 1024, 2000, 15);
#endif
	image(gfx, img, x, y, xsize, ysize);
	return 0;
}
