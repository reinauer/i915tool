#include <stdio.h>
#include <stdlib.h>
#include <sys/io.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "video.h"
#include "final/i915_reg.h"

int verbose = 0;

enum {
	vmsg = 1, vio = 2, vspin = 4,
};

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
		sprintf(name, "0x%lx", addr);
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
	sprintf(name, "0x%lx", addr);
	return name;
}

#define M 1
#define R 2
#define W 3
#define V 4
#define I 8
char *opnames[] = {
	[M] "M",
	[R] "R",
	[W] "W",
	[V] "V",
	[I] "I",
};

struct iodef {
	unsigned char op;
	unsigned int count;
	char *msg;
	unsigned long addr;
	unsigned long data;
	unsigned long udelay;
} iodefs[] = {
#include "WTM2IO.c"
};

#include "buildregs.c"

int
morethanonebit(unsigned long x)
{
	return x & (x-1);
}
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0])) 
char *symname(struct iodef *id)
{
	static char name[512];
	char *cp;
	struct registers *r = NULL;
	unsigned long value;
	int i;
	name[0] = 0;
	/* chew up the bits. Each time you find one that works, then suck it out and replace it with a symbol. */
	if (id->addr < ARRAY_SIZE(reglist))
		r = reglist[id->addr];
	if (!r){
		sprintf(name, "0x%08lx", id->data);
		return name;
	}

	value = id->data;

	/* walk the list. Rip the bits out of addr. If something is left, print it. */
	for(i = 0, cp = name; r[i].name; i++){
		if (! (r[i].value & value))
			continue;
		if (! morethanonebit(r[i].value)){
			cp += sprintf(cp, "%s|", r[i].name);
		} else {
			cp += sprintf(cp, "(%s&0x%lx)|", r[i].name, value & r[i].value);
		}
		value &= ~r[i].value;
	}

	/* special cases! */
	if ((id->addr & ~0x300) == DPA_AUX_CH_CTL){
		cp+=sprintf(cp,"/*[%dbytes]*/",(id->data>>20)&0x1f);
	}
	if (((id->addr & ~0x300) == DPA_AUX_CH_DATA1) && (id->op == W)){
		cp += sprintf(cp, "/*%04x:%s %s %s*/",
			      id->data>>16,
			      id->data&I2C_M_TEN ? "10 bits" : "",
			      id->data&I2C_M_RD ? "Read":"Write",
			      id->data&I2C_M_RECV_LEN ? "Recv len": "");
	}
	/* just print out hte original value. Useful for knowing what it was AND any bits we could not figure out. */
	sprintf(cp, "0x%08lx", id->data);
	return name;
	
}

int main(int argc, char *argv[])
{
	int i;
	struct iodef *id = iodefs;
	/* state machine! */
	for(i = 0; i < sizeof(iodefs)/sizeof(iodefs[0]); i++, id++){
		if ((id->op != W) && (id->op != R)){
			printf("{%s, %d, \"%s\", %s, 0x%lx, %ld},\n", 
			opnames[id->op], id->count, id->msg, regname(id->addr), id->data, id->udelay);
		} else {
			printf("{%s, %d, \"%s\", %s, %s, %ld},\n", 
			opnames[id->op], id->count, id->msg, regname(id->addr),symname(id), id->udelay);
		}
	}

}
// cc -g prettywtm2regs.c
