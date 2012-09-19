#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#include <sys/io.h>
#include <sys/time.h>
#include <linux/types.h>
#include <errno.h>

unsigned int *gfx = NULL;
unsigned long membase = 0xd0000000;
unsigned long memsize = 32 * 1024 * 1024;
unsigned long physbase;
int gfxpages = 4250;
/* pagesize in longs */
int pagesize = 1024;
int fakeit = 1;

/* do everything -- page size computations, all that stuff --
 * in terms of longs. It's easier.
 */
void *
mapit(unsigned long phys, unsigned long size)
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
unsigned long io_I915_READ32(unsigned long addr)
{
       unsigned long val;
	if (fakeit){
		printf("READ %08lx\n", addr);
		return;
	}

       outl(addr, addrport);
       val = inl(dataport);
       return val;
}

void io_I915_WRITE32(unsigned long addr, unsigned long val)
{
	if (fakeit){
		printf("WRITE %08lx, val %08lx\n", addr, val);
		return;
	}
       outl(addr, addrport);
       outl(val, dataport);
}

/* the address is assumed to point to the start of the page */
void onepage(unsigned int *address, unsigned int *data, int xsize)
{
	unsigned long offset;
	unsigned long page;
	unsigned long pageoffset;
	int i, amt, size;

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
			printf("%p = %08lx\n", &address[i], *data++);
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
 */
void oneline(unsigned int *address, unsigned int *data, int xsize)
{
	int size, amt;
	unsigned long start, end;
	for(size = 0; size < xsize;){
		/* figure out how much remains */
		start = (unsigned long) address;
		/* set round to end of this page at most */
		/* end is a BYTE address */
		/* end will have at most the value of the start of the
		 * NEXT page
		 */
		end = (((start + 4095 + xsize*4)>>12)<<12);
		/* compute amount in bytes */
		amt = end - start;
		/* convert to words */
		amt >>= 2;
		/* maybe it's too much */
		amt = amt > xsize ? xsize : amt;
		
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
	int yamt, xamt;
	for(yamt = 0; yamt < ysize; yamt++){
		oneline(&address[y*2560 + x], data, xsize);
		address += 2560;
		data += xsize;
	}
}
	
int main(int argc, char *argv[])
{
	int i = 0;

	static unsigned int black[1048576];

	if (argc > 1)
		fakeit++;
	if (! fakeit){
		iopl(3);
		gfx = mapit(membase, memsize);
	} 
	gfx = mapit(membase, memsize);

	physbase = 0xada00000;
	printf("# PTEs is %d\n", gfxpages);
	printf("Start of graphics pages would be %#p\n", physbase);

	/* The black rect. */
	printf("image(gfx, black, 511, 1024, 1, 1);\n");image(gfx, black, 511, 1024, 1, 1);
	printf("NEXT %d\n", i++);
	printf("image(gfx, black, 1024, 1024, 1, 1);\n");image(gfx, black, 1024, 1024, 1, 1);
	printf("NEXT %d\n", i++);
	printf("image(gfx, black, 1024, 1024, 3, 1);\n");image(gfx, black, 1024, 1024, 3, 1);
	printf("NEXT %d\n", i++);
	printf("image(gfx, black, 1027, 1024, 3, 1);\n");image(gfx, black, 1027, 1024, 3, 1);
	printf("NEXT %d\n", i++);
	printf("image(gfx, black, 1024, 1024, 2000, 1);\n");image(gfx, black, 1024, 1024, 2000, 1);
	printf("NEXT %d\n", i++);
	printf("image(gfx, black, 1024, 1024, 2000, 15);\n");image(gfx, black, 1024, 1024, 2000, 15);
}
