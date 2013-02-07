#include <stdio.h>
#include "final/i915_reg.h"

#define M 1
#define R 2
#define W 3
#define V 4
#define I 8

char *opnames[] = {
	[M] "M",
	[R] "R",
	[W] "W"
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
struct {
	int op, count;
	char *mesg;
	unsigned long reg, val;
	int delay;
} regs[] = {
#include "stoutRW.c"
};
main()
{
	int i;
	for(i = 0; i < sizeof(regs)/sizeof(regs[0]); i++){
		if ((regs[i].op == W) || (regs[i].op == R))
			printf("{%s, %d, \"%s\", %s, 0x%lx, %d},\n", 
			opnames[regs[i].op], regs[i].count, regs[i].mesg, regname(regs[i].reg), regs[i].val, regs[i].delay);
		else
			printf("{%s, %d, \"%s\", },\n", 
			opnames[regs[i].op], regs[i].count, regs[i].mesg);

	}
}

 /* cc -o stoutgraphics stoutgraphics.c */
