#include <stdio.h>
#include <sys/io.h>
#include <time.h>
#include <sys/time.h>
#include "final/i915_reg.h"

int vmsg = 0;
int vio = 0;
int vspin = 0;
unsigned short addrport = 0x1000;
unsigned short dataport = 0x1000 +4;
char *names[] = {
#include "names.c"
};

int nnames = sizeof(names)/sizeof(names[0]);

char *regname(unsigned long addr)
{
	static char name[128];
	int i;
	int offset;
	unsigned long truncaddr;

	if (addr > nnames){
		sprintf(name, "0x%x", addr);
		return name;
	}
	if (names[addr])
		return names[addr];
	/* for now we'll take up to 6 bits of offset */
	for(i = 1, truncaddr = addr; i < 0x80; i = (i << 1) | 1){
		offset = addr & i;
		truncaddr = addr & (~i);
		if (names[truncaddr]){
			sprintf(name,"%s+%x", names[truncaddr], offset);
			return name;
		}
	}
	/* oh well ... */
	sprintf(name, "0x%x", addr);
	return name;
}
/* not sure how we want to do this so let's guess */
/* to make it easy, we start at zero and assume 250 hz. */
static __inline__ unsigned long long rdtsc(void)
{
  unsigned hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
  return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

unsigned long msecs(void)
{
	static struct timeval start;
	struct timeval now;
	static int first = 0;
	unsigned long j;
	if (! first++)
		gettimeofday(&start, NULL);
	gettimeofday(&now, NULL);
	j = (now.tv_sec - start.tv_sec)*1000 + (now.tv_usec-start.tv_usec)/1000;
	if (vio > 0)
		fprintf(stderr, "MS: %ld\n", j);
	return j;
}

void
mdelay(unsigned long ms)
{
	unsigned long start;
	start = msecs();
	while (msecs() < (start + ms))
		;
}

static unsigned long tickspermicrosecond = 1000;

void
calibratetsc(void)
{
	unsigned long long start, end;
	fprintf(stderr, "Delay for 10 seconds to calibrate tsc...");
	start = rdtsc();
	mdelay(10000);
	end = rdtsc();
	/* convert to ticks per microsecond -- 10M microseconds */
	tickspermicrosecond = (end - start) / 10000000;
	fprintf(stderr, "Done: tickspermicrosecond = %ld\n", tickspermicrosecond);
}

unsigned long
microseconds(unsigned long long start, unsigned long long end)
{
	unsigned long ret;
	ret = ((end - start)/tickspermicrosecond);
	return ret;
}

void udelay(int i)
{
	unsigned long long end;

	if (vio > 0)
		fprintf(stderr, "UDELAY %d!\n", i);
	end = rdtsc() + i * tickspermicrosecond;
	while (rdtsc() < end)
		;
}

unsigned long io_i915_READ32(unsigned long addr)
{
       unsigned long val;
       outl(addr, addrport);
       val = inl(dataport);
       return val;
}

void io_i915_WRITE32(unsigned long val, unsigned long addr)
{
       outl(addr, addrport);
       outl(val, dataport);
}

#define M 1
#define R 2
#define W 3

struct iodef {
	unsigned char op;
	unsigned int count;
	char *msg;
	unsigned long addr;
	unsigned long data;
	unsigned long udelay;
} iodefs[] = {
#include "newIO.c"
};

#if 0

	cc -g -static -o IO IO.c

Edit ,|grep '^[\[RUW]'
Edit ,s///g
Edit ,s/^We.*\n//g
Edit ,s/\nU/ ;;;U/g
Edit ,|uniq -c
Edit ,s/\[000000.0\]/M/g 
Edit ,s/^  *//g
Edit ,s/(^[0-9]+) ([MRW])/\2 \1/g
Edit ,s/"/\\"/g
Edit ,s/^M (.*) (\[.*)/{M, \1, "\2"},/g
Edit ,s/:  */:/g
Edit ,s/^([RW]) ([0-9]+) (.*):([0-9a-f]+)(.*)/{\1, \2, "", \3, 0x\4, \5},/g
Edit ,s/;;;UDELAY *([0-9]+)!/\1/g
Edit ,s/\+ */+0x/g

#endif
int main(int argc, char *argv[])
{
	int i;
	unsigned long lastreadindex;
	struct iodef *id = iodefs, *lastidread;
	unsigned long u, t;
	argc--,argv++;
	while (argc){
		if (*argv[0] == 'm') vmsg++;
		if (*argv[0] == 'i') vio++;
		if (*argv[0] == 's') vspin++;
		argc--,argv++;
	}
	iopl(3);

	/* state machine! */
	for(i = 0; i < sizeof(iodefs)/sizeof(iodefs[0]); i++, id++){
		switch(id->op){
		case M:
			if (vmsg) printf("%s\n", id->msg);
			break;
		case R:
			u = io_i915_READ32(id->addr);
			if (vio)printf("%s: Got %08x, expect %08x\n", 
				regname(id->addr), u, id->data);
			/* we're looking for something. */
			if (lastidread->addr == id->addr){
				/* they're going to be polling. 
				 * just do it 1000 times
				 */
				for(t = 0; t < 1000 && id->data != u; t++){
					u = io_i915_READ32(id->addr);
				}
				if (vspin) printf("%s: # loops %d got %08x want %08x\n",	
						regname(id->addr),
						t, u, id->data);
			}
			lastidread = id;
			break;
		case W:
			if (vio)printf("%s: outl %08x\n", regname(id->addr), id->data);
			io_i915_WRITE32(id->data, id->addr);
			break;
		default:
			printf("BAD TABLE, opcode %d @ %d\n", id->op, i);
			exit(1);
		}
		if (id->udelay)
			udelay(id->udelay);
	}
}
