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

unsigned long *gfx = NULL;
unsigned long membase = 0xd0000000;
unsigned long memsize = 32 * 1024 * 1024;
unsigned long physbase;
int gfxpages = 4250;
/* pagesize in longs */
int pagesize = 1024;

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
       outl(addr, addrport);
       val = inl(dataport);
       return val;
}

void io_I915_WRITE32(unsigned long addr, unsigned long val)
{
       outl(addr, addrport);
       outl(val, dataport);
}

/* the address is assumed to point to the start of the page */
void onepage(unsigned long *address, unsigned long *data, int xsize)
{
	unsigned long offset;
	unsigned long page;
	unsigned long pageoffset;
	int i, amt, size;
	/* get an offset */
	offset = address - gfx;
	/* this one thing has to be in units of bytes  -- so use byte pagesize*/
	page = offset >> 12;
	/* our target is pointing to the common page area. 
	 * make it point to the separate page area
	 */
	io_I915_WRITE32((page)|1,(physbase + offset)|1);
	/* OK, now, figure out how far we are into the page
	 * and fill the space with white. 
	 */
	pageoffset = offset & (1024-1);
	for(i = 0; i < pageoffset; i++)
		address[i] = 0xffffff;
	for(size = 0; size < xsize; size++)
		address[i] = *data++;
	for(;size < 1024; size++)
		address[i] = 0xffffff;
}

void oneline(unsigned long *address, unsigned long *data, int xsize)
{
	int size, amt;
	for(size = 0; size < xsize;){
		/* figure out how much remains */
		if (xsize - size < pagesize)
			amt = xsize - size;
		else
			amt = pagesize;
		onepage(address, data, amt);
		size += amt;
		address += amt;
		data += amt;
	}
}
	
void image(unsigned long *address, unsigned long *data, int x, int y, int xsize, int ysize)
{
	int yamt, xamt;
	for(; yamt < ysize; yamt++){
		oneline(&address[x], data, xsize);
		address += 2560;
		data += xsize;
	}
}
	
int main(int argc, char *argv[])
{
	int i;

	static unsigned long black[1048576];
	iopl(3);
	gfx = mapit(membase, memsize);

	physbase = 0xada00000;
	printf("# PTEs is %d\n", gfxpages);
	printf("Start of graphics pages would be %#p\n", physbase);

	/* The black rect. */
	image(gfx, black, 512, 512, 512, 512);
}
