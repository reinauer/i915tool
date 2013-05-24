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
#include "i915_reg.h"

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
			sprintf(name,"%s+0x%x", names[truncaddr], offset);
			return name;
		}
	}
	/* oh well ... */
	sprintf(name, "0x%lx", addr);
	return name;
}

#include "opcodes.c"

struct iodef {
	unsigned char op;
	unsigned long option; /* count or PCI config space */
	char *msg;
	unsigned long addr;
	unsigned long data;
	unsigned long udelay;
} iodefs[] = {
#include "wtm2io_step2.c"
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

	/* !@#$#@ compiler */
	value = (u32)id->data;

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
		cp+=sprintf(cp,"/*[%ldbytes]*/",(id->data>>20)&0x1f);
	}
	if (((id->addr & ~0x300) == DPA_AUX_CH_DATA1) && (id->op == Wl)){
		cp += sprintf(cp, "/*%04lx:%s %s %s*/",
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
	int dedup = 0;
	int pass = 0;
	int i;
	int pch_pp_control_seen = 0;
	struct iodef *id = iodefs;
	/* state machine! */
	for(i = 0; i < sizeof(iodefs)/sizeof(iodefs[0]); i++, id++){
		/* timers: 0x40 is timer 0, 41 1, 42 2, 43 a contro register. 
		 * 0x61 is pc speaker. Ignore them.
		 */
		if (id->addr > 0x40 && id->addr < 0x62)
			continue;

		if (id->op < GWl) {
			printf("{%s, 0x%08lx, \"%s\", 0x%lx, 0x%lx, %ld},\n", 
			opnames[id->op], id->option, id->msg, id->addr, id->data, id->udelay);
		} else {
			/* take the opportunity to do some cleanup */
			
			/* skip the gtt. */
			/* works */
			if (id->addr < 0x3fffd)
				continue;
			/* no need to do any PCH_PP_CONTROL stuff */
			/* works. */
			if (id->addr == PCH_PP_CONTROL){
				fprintf(stderr, "WARNING: NOT IGNORING PCH_PP_CONTROL\n");
				continue;
				if (pch_pp_control_seen++ == 0){
				}
			}
			/* the final test. Is this a dup?
			 * last op is ALWAYS an I; no need to check 
			 * array bounds
			 */
			if (id->op == GRl &&
				id[1].op == GRl &&
				id->addr == id[1].addr &&
				id->data == id[1].data){
				id[1].option++;
				dedup++;
				continue;
			}
			printf("{%s, %ld, \"%s\", %s, %s, %ld},\n", 
			opnames[id->op], id->option, id->msg, regname(id->addr),symname(id), id->udelay);
		}
	}
	printf("{I,},\n");
	fflush(stdout);
	fprintf(stderr, "%d dups deleted\n", dedup);
	exit(0);
}
// cc -g -o prettywtm2regs prettywtm2regs.c
