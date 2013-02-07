

#include "final/i915_reg.h"

int verbose = 0;

enum {
	vmsg = 1, vio = 2, vspin = 4,
};

unsigned short addrport = 0x1000;
unsigned short dataport = 0x1000 +4;

char *regname(unsigned long addr)
{
	sprintk(BIOS_SPEW, name, "0x%lx", addr);
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

static unsigned long tickspermicrosecond = 1795;
static unsigned long long globalstart;

static unsigned long
microseconds(unsigned long long start, unsigned long long end)
{
	unsigned long ret;
	ret = ((end - start)/tickspermicrosecond);
	return ret;
}

static unsigned long globalmicroseconds(void)
{
	return microseconds(globalstart, rdtsc());
}

static void udelay(int i)
{
	unsigned long long end;

	if (verbose & vio)
		fprintk(BIOS_SPEW, stderr, "UDELAY %d!\n", i);
	end = rdtsc() + i * tickspermicrosecond;
	while (rdtsc() < end)
		;
}

static unsigned long io_i915_READ32(unsigned long addr)
{
       unsigned long val;
       outl(addr, addrport);
       val = inl(dataport);
       return val;
}

static void io_i915_WRITE32(unsigned long val, unsigned long addr)
{
       outl(addr, addrport);
       outl(val, dataport);
}

#define M 1
#define R 2
#define W 3
#define V 4
#define I 8

struct iodef {
	unsigned char op;
	unsigned int count;
	char *msg;
	unsigned long addr;
	unsigned long data;
	unsigned long udelay;
} iodefs[] = {
#include "i915io.c"
};

int i915lightup(void)
{
	int i, prev = 0;
	unsigned long lastreadindex;
	struct iodef *id = iodefs, *lastidread;
	unsigned long u, t;
	globalstart = rdtsc();

	/* state machine! */
	for(i = 0; i < sizeof(iodefs)/sizeof(iodefs[0]); i++, id++){
		switch(id->op){
		case M:
			if (verbose & vmsg) printk(BIOS_SPEW, "%ld: %s\n", globalmicroseconds(), id->msg);
			break;
		case R:
			u = i915_READ32(id->addr);
			if (verbose & vio)printk(BIOS_SPEW, "%s: Got %08lx, expect %08lx\n", 
				regname(id->addr), u, id->data);
			/* we're looking for something. */
			if (lastidread->addr == id->addr){
				/* they're going to be polling. 
				 * just do it 1000 times
				 */
				for(t = 0; t < 1000 && id->data != u; t++){
					u = io_i915_READ32(id->addr);
				}
				if (verbose & vspin) printk(BIOS_SPEW, "%s: # loops %ld got %08lx want %08lx\n",	
						regname(id->addr),
						t, u, id->data);
			}
			lastidread = id;
			break;
		case W:
			if (verbose & vio)printk(BIOS_SPEW, "%s: outl %08lx\n", regname(id->addr), id->data);
			io_i915_WRITE32(id->data, id->addr);
			if (id->addr == PCH_PP_CONTROL)
				udelay(100000);
			break;
		case V:
			if (id->count < 8){
				prev = verbose;
				verbose = id->count;
			} else {
				verbose = prev;
			}
			break;
		case I:
			break;
		default:
			printk(BIOS_SPEW, "BAD TABLE, opcode %d @ %d\n", id->op, i);
			exit(1);
		}
		if (id->udelay)
			udelay(id->udelay);
	}

	printk(BIOS_SPEW, "%ld microseconds\n", globalmicroseconds());
}
