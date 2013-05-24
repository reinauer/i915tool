/* This code is intended to produce a mixed table-driven/code-driven
 * IO. So it sttill has a poke register with magic values but also has
 * intermixed that with code.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/io.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "drmdefines.h"
#include "video.h"
#include "i915_reg.h"


/* stuff we need that was not here. */
#include "undef.h"

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
	unsigned int count;
	char *msg;
	unsigned long addr;
	unsigned long data;
	unsigned long udelay;
} iodefs[] = {
#include "wtm2io_step4.c"
};

#include "buildregs.c"
#include "builddrmregs.c"

int
morethanonebit(unsigned long x)
{
	return x & (x-1);
}
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0])) 
char *symname(struct registers *regs[], int nregs, int op, unsigned long addr, unsigned long data)
{
	static char name[512];
	char *cp;
	struct registers *r = NULL;
	unsigned long value;
	int i;
	name[0] = 0;
	/* chew up the bits. Each time you find one that works, then
	 * suck it out and replace it with a symbol.
	 */
	if (addr < nregs)
		r = regs[addr];
	if (!r){
		sprintf(name, "0x%08lx", data);
		return name;
	}

	value = data;

	/* walk the list. Rip the bits out of addr. If something is left, print it. */
	for(i = 0, cp = name; r[i].name; i++){
		/* very new. If it has an extract you're supposed to just take it. */
		if (r[i].extract){
			unsigned long printval = r[i].mask & value;
			printval >>= r[i].shift;
			cp += sprintf(cp, "(/*%s*/0x%lx<<%ld)|", r[i].name,printval, r[i].shift);
			value &= ~r[i].value;
		}
		/* old school; no mask set. */
		if ((! r[i].mask) && (! (r[i].value & value)))
			continue;
		/* new school. Mask non-zero, check for a match */
		if (r[i].mask && ((r[i].mask & value) != r[i].value))
			continue;
		if (! morethanonebit(r[i].value)){
			cp += sprintf(cp, "%s|", r[i].name);
		} else {
			cp += sprintf(cp, "(%s&0x%lx)|", r[i].name, value & r[i].value);
		}
		if (!r[i].mask)
			value &= ~r[i].value;
		else
			value &= ~r[i].mask;
	}

/* special cases! */
	if ((addr & ~0x300) == DPA_AUX_CH_CTL){
		cp+=sprintf(cp,"/*[%ldbytes]*/",(data>>20)&0x1f);
	}
	if (((addr & ~0x300) == DPA_AUX_CH_DATA1) && (op == GWl)){
		cp += sprintf(cp, "/*%04lx:%s %s %s*/",
			      data>>16,
			      data&I2C_M_TEN ? "10 bits" : "",
			      data&I2C_M_RD ? "Read":"Write",
			      data&I2C_M_RECV_LEN ? "Recv len": "");
	}
	/* just print out hte original value. Useful for knowing what it was AND any bits we could not figure out. */
	sprintf(cp, "0x%08lx", data);
	return name;
	
}


char functions[1048576], *current = functions;


/* aux function. Create the call to the function which does IO on the aux channel
 * we pretty much ignore all writes to CTL after the first one. 
 * The writes to the data registers turn into stores into an array of u32. 
 * The data is read into an array of u8. 
 * After this, you get to modify it by hand. But at least it's a bit easier.
 */
#if 0
#define	DP_LINK_BW_SET		            0x100
# define DP_LINK_BW_1_62		    0x06
# define DP_LINK_BW_2_7			    0x0a
# define DP_LINK_BW_5_4			    0x14

#define DP_LANE_COUNT_SET	            0x101
# define DP_LANE_COUNT_MASK		    0x0f
# define DP_LANE_COUNT_ENHANCED_FRAME_EN    (1 << 7)

#define DP_TRAINING_PATTERN_SET	            0x102
# define DP_TRAINING_PATTERN_DISABLE	    0
# define DP_TRAINING_PATTERN_1		    1
# define DP_TRAINING_PATTERN_2		    2
# define DP_TRAINING_PATTERN_3		    3
# define DP_TRAINING_PATTERN_MASK	    0x3

# define DP_LINK_QUAL_PATTERN_DISABLE	    (0 << 2)
# define DP_LINK_QUAL_PATTERN_D10_2	    (1 << 2)
# define DP_LINK_QUAL_PATTERN_ERROR_RATE    (2 << 2)
# define DP_LINK_QUAL_PATTERN_PRBS7	    (3 << 2)
# define DP_LINK_QUAL_PATTERN_MASK	    (3 << 2)

# define DP_RECOVERED_CLOCK_OUT_EN	    (1 << 4)
# define DP_LINK_SCRAMBLING_DISABLE	    (1 << 5)

# define DP_SYMBOL_ERROR_COUNT_BOTH	    (0 << 6)
# define DP_SYMBOL_ERROR_COUNT_DISPARITY    (1 << 6)
# define DP_SYMBOL_ERROR_COUNT_SYMBOL	    (2 << 6)
# define DP_SYMBOL_ERROR_COUNT_MASK	    (3 << 6)

#define DP_TRAINING_LANE0_SET		    0x103
#define DP_TRAINING_LANE1_SET		    0x104
#define DP_TRAINING_LANE2_SET		    0x105
#define DP_TRAINING_LANE3_SET		    0x106
#define DP_SET_POWER                        0x600
# define DP_SET_POWER_D0                    0x1
# define DP_SET_POWER_D3                    0x2

#endif

char *auxdest[] = {
[0x600] "DP_SET_POWER",
	[0x202] "DP_LANE0_1_STATUS",
	[0x203] "DP_LANE2_3_STATUS",
	[0x204] "DP_LANE_ALIGN_STATUS_UPDATED",
	[0x103] "DP_TRAINING_LANE0_SET",
	[0x102] "DP_TRAINING_PATTERN_SET",
	[0x101] "DP_LANE_COUNT_SET",
	[0x100] "DP_LINK_BW_SET",
	[DP_DPCD_REV] "DP_DPCD_REV",
	[DP_MAX_LINK_RATE] "DP_MAX_LINK_RATE",
	[DP_MAX_LANE_COUNT] "DP_MAX_LANE_COUNT",
	[DP_MAX_DOWNSPREAD] "DP_MAX_DOWNSPREAD",
	[DP_NORP] "DP_NORP",
	[DP_DOWNSTREAMPORT_PRESENT] "DP_DOWNSTREAMPORT_PRESENT",
	[DP_MAIN_LINK_CHANNEL_CODING] "DP_MAIN_LINK_CHANNEL_CODING",
	[DP_EDP_CONFIGURATION_CAP] "DP_EDP_CONFIGURATION_CAP",
	[DP_TRAINING_AUX_RD_INTERVAL] "DP_TRAINING_AUX_RD_INTERVAL",
	[DP_PSR_SUPPORT] "DP_PSR_SUPPORT",
	[DP_PSR_CAPS] "DP_PSR_CAPS",
	[DP_LANE_COUNT_SET] "DP_LANE_COUNT_SET",
	[DP_TRAINING_PATTERN_SET] "DP_TRAINING_PATTERN_SET",
	[DP_TRAINING_LANE0_SET] "DP_TRAINING_LANE0_SET",
	[DP_TRAINING_LANE1_SET] "DP_TRAINING_LANE1_SET",
	[DP_TRAINING_LANE2_SET] "DP_TRAINING_LANE2_SET",
	[DP_TRAINING_LANE3_SET] "DP_TRAINING_LANE3_SET",
	[DP_DOWNSPREAD_CTRL] "DP_DOWNSPREAD_CTRL",
	[DP_MAIN_LINK_CHANNEL_CODING_SET] "DP_MAIN_LINK_CHANNEL_CODING_SET",
	[DP_PSR_EN_CFG] "DP_PSR_EN_CFG",
	[DP_DEVICE_SERVICE_IRQ_VECTOR] "DP_DEVICE_SERVICE_IRQ_VECTOR",
	[DP_EDP_CONFIGURATION_SET] "DP_EDP_CONFIGURATION_SET",
	[DP_LANE0_1_STATUS] "DP_LANE0_1_STATUS",
	[DP_LANE2_3_STATUS] "DP_LANE2_3_STATUS",
	[DP_LANE_ALIGN_STATUS_UPDATED] "DP_LANE_ALIGN_STATUS_UPDATED",
	[DP_SINK_STATUS] "DP_SINK_STATUS",
	[DP_ADJUST_REQUEST_LANE0_1] "DP_ADJUST_REQUEST_LANE0_1",
	[DP_ADJUST_REQUEST_LANE2_3] "DP_ADJUST_REQUEST_LANE2_3",
	[DP_TEST_REQUEST] "DP_TEST_REQUEST",
	[DP_TEST_LINK_RATE] "DP_TEST_LINK_RATE",
	[DP_TEST_LANE_COUNT] "DP_TEST_LANE_COUNT",
	[DP_TEST_PATTERN] "DP_TEST_PATTERN",
	[DP_TEST_RESPONSE] "DP_TEST_RESPONSE",
	[DP_SET_POWER] "DP_SET_POWER",
	[DP_PSR_ERROR_STATUS] "DP_PSR_ERROR_STATUS",
	[DP_PSR_ESI] "DP_PSR_ESI",
	[DP_PSR_STATUS] "DP_PSR_STATUS",
};

char text[1024];
char *msgtxt(char *msg)
{
	char *t = text;
	*t = 0;
	if (! msg)
		return;
	while (*msg){
		if (*msg == '"')
			*t++ = '\\';
		*t++ = *msg++;
	}
	*t++ = 0;
	return text;
}
int aux(int index)
{
	static int count = 0;
	struct iodef *id = &iodefs[index];
	/* iterate through the *data* items, accumulating into the in array. 
	 * then call intel_dp_aux_ch_32 with the pointer to the outarray. 
	 * to make things easier, we take subsequent IOs into other arrays.
	 */
	int msglen = 0, senddatalen = 0;
	int dp_or_i2c = 0,  mot = 0, dpcmd = 0, i2ccmd = 0;
	int cmd = 0;
	int rw = 0;
	int dest = 0;
	unsigned char len = 0;
	int chwritecount = 0;
	int sentbusy = 0;
	unsigned long host;
	/* loop until we hit the write to the CTL. Accumulate writes
	 * to the data registers. Ignore reads. The VBIOS usage of the
	 * AUX is very different from the kernel.
	 */
	/* Ah, the VBIOS. It's crap. It does a very non-standard
	 * set of ops on the first aux op. Must remember that.
	 */
	for(;;id++, index++){
		switch(id->addr){
		case DPA_AUX_CH_CTL:
			if (id->op == GWl)
				chwritecount++;
			if (chwritecount  > 1){
				fprintf(stderr, "aux(): more than one write to ch@%i\n", index);
			fprintf(stderr, "{%s, %d, \"%s\", %s, %s, %ld},\n", 
					opnames[id->op], id->count, msgtxt(id->msg), 
					regname(id->addr),symname(reglist, 
								  ARRAY_SIZE(reglist), 
								  id->op, id->addr, 
								  id->data), id->udelay);

			}
			if (id->op == GWl &&
				id->data & DP_AUX_CH_CTL_SEND_BUSY){
				msglen = (id->data>>20)&0x1f;
				senddatalen = msglen -1;
				if (count++ == 0)
					goto done;
				sentbusy++;
				continue;
			}
			if (id->op == GRl && id->data & DP_AUX_CH_CTL_DONE){
				if (sentbusy)
					goto done;
			}
			break;
		case DPA_AUX_CH_DATA1:
			if (id->op == GRl)
				break;
			/* defined in the aux standard, e.g. 
			 * http://hackipedia.org/Hardware/video/connectors/DisplayPort/VESA%20DisplayPort%20Standard%20v1.1a.pdf
			 */
			dp_or_i2c = id->data>>31;
			printf("\tauxout = %s",
			     dp_or_i2c ? "1<<31 /* dp */" : "0<<31 /* i2c */");
			if (dp_or_i2c) { /* dp */
				cmd = (id->data>>28)&7;
				rw = cmd == 0 ? 0 : 1;
				dest = (id->data>>8) & 0xfffff;
				len = id->data;
				printf("|0x%x<<28/*%s*/|%s<<8|0x%x|0x%08lx;\n", cmd, rw ? "R" : "W",auxdest[dest], len, id->data);
				printf("printk(BIOS_SPEW, \"%s\");\n", auxdest[dest]);
			} else {
				mot = (id->data>>30)&1;
				i2ccmd = (id->data>>28)&3;
				rw = i2ccmd == 0 ? 0 : 1;
				dest = (id->data>>8) & 0xfffff;
				len = id->data;
				printf("|%d<<30|0x%x<<28/*%s*/|0x%x<<8|0x%x|0x%08lx;\n", mot, i2ccmd, rw ? "R" : "W",dest, len, id->data);
			}
			printf("\tunpack_aux(auxout, &msg[0], 4);\n");
			break;
		case DPA_AUX_CH_DATA2:
		if (id->op == GRl)
			break;
			printf("\tauxout = 0x%08lx;\n", id->data);
			if (dp_or_i2c){
				host = ntohl(id->data);
				printf("\t/*%s*/\n", symname(drmreglist, sizeof(drmreglist), GWl, dest, host));
			}
			printf("\tunpack_aux(auxout, &msg[4], 4);\n");
			break;
		case DPA_AUX_CH_DATA3:
		if (id->op == GRl)
			break;
			printf("\tauxout = 0x%08lx;\n", id->data);
			printf("\tunpack_aux(auxout, &msg[8], 4);\n");
			break;
		case DPA_AUX_CH_DATA4:
		if (id->op == GRl)
			break;
			printf("\tauxout = 0x%08lx;\n", id->data);
			printf("\tunpack_aux(auxout, &msg[0xc], 4);\n");
			break;
		case DPA_AUX_CH_DATA5:
		if (id->op == GRl)
			break;
			printf("\tauxout = 0x%08lx;\n", id->data);
			printf("\tunpack_aux(auxout, &msg[0x10], 4);\n");
			break;
		default:
			fprintf(stderr, "unexpected in the middle of an AUX CH sequence@%d\n",
				index);
			fprintf(stderr, "{%s, %d, \"%s\", %s, %s, %ld},\n", 
					opnames[id->op], id->count, msgtxt(id->msg), 
					regname(id->addr),symname(reglist, 
								  ARRAY_SIZE(reglist), 
								  id->op, id->addr, 
								  id->data), id->udelay);

			break;
		}
	}
	done:
	/* note; Must always check that abcd0008 applies *i.e. aux dp chan is up */
	printf("\tintel_dp_aux_ch(dp, msg, %d, auxin, %d);\n", msglen, rw ? len : 0);
	//printf("udelay(100000);\n");
	return index;
}
char *prefix = 
"/*\n"
"* This file is part of the coreboot project.\n"
"*\n"
"* Copyright 2013 Google Inc.\n"
"*\n"
"* This program is free software; you can redistribute it and/or modify\n"
"* it under the terms of the GNU General Public License as published by\n"
"* the Free Software Foundation; version 2 of the License.\n"
"*\n"
"* This program is distributed in the hope that it will be useful,\n"
"* but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"* GNU General Public License for more details.\n"
"*\n"
"* You should have received a copy of the GNU General Public License\n"
"* along with this program; if not, write to the Free Software\n"
"* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA\n"
"*/\n"
"/* generated code; do not edit*/\n"
"#include <stdint.h>\n"
"#include <console/console.h>\n"
"#include <delay.h>\n"
"#include <drivers/intel/gma/i915.h>\n"
"#include <arch/io.h>\n"
"\tint index;\tu32 auxout;\n\tu8 auxin[20];\nu8 msg[32];"
"void runio(struct intel_dp *dp,  int verbose);\n"
"void runio(struct intel_dp *dp,  int verbose)\n{\n"
;

char *postfix ="}\n"
;

int main(int argc, char *argv[])
{
	int i;
	/* no need for this right now. */
	int num_to_change = 1000;
	int num_changed = 0;
	struct iodef *id = iodefs;
	/* state machine! */
	printf("%s\n",prefix);
	for(i = 0; i < sizeof(iodefs)/sizeof(iodefs[0]); i++, id++){
		if (id->op == I)
			continue;
		if ((id->op != GWl) && (id->op != GRl)){
			if (id->msg && strlen(id->msg))
				printf("\tprintk(BIOS_SPEW, \"\%s\");\n", msgtxt(id->msg));
			if (id->op <= Wl && id->op >= Wb)
				printf("\tout%s(0x%08lx, 0x%08lx);\n", func[id->op], id->data, id->addr);
			if (id->op <= Rl && id->op >= Rb){
				printf("\tif (verbose&vio){in%s(0x%08lx);", func[id->op], id->addr);
				printf("\tprintk(BIOS_SPEW,\"\t%08lx\\n\");}\n", id->data);
			}
		} else {
			/* drive state machines, if nothing to do,
			 * then resume.  if write to DPA_AUX_CH_CTL &&
			 * DP_AUX_CH_CTL_SEND_BUSY is set, that starts
			 * an aux cycle. If write to DPA_AUX_CH_DATA1,
			 * that starts and aux cycle.  The VBIOS seems
			 * to be driving the AUX channel in a strange
			 * way.
			 */
			if (id->op == GWl && id->addr == DPA_AUX_CH_CTL &&
			    (id->data & DP_AUX_CH_CTL_SEND_BUSY &&
			     num_changed < num_to_change)){
				num_changed++;
				fprintf(stderr, "AUX at %d\n", i);
				fprintf(stderr, "{%s, %d, \"%s\", %s, %s, %ld},\n", 
					opnames[id->op], id->count, msgtxt(id->msg), 
					regname(id->addr),symname(reglist, 
								  ARRAY_SIZE(reglist), 
								  id->op, id->addr, 
								  id->data), id->udelay);
				i = aux(i);
				id = &iodefs[i];
				continue;
			}
			if (id->op == GWl && id->addr == DPA_AUX_CH_DATA1 &&
			    num_changed < num_to_change) {
				num_changed++;
				fprintf(stderr, "AUX at %d\n", i);
				
				fprintf(stderr, "{%s, %d, \"%s\", %s, %s, %ld},\n", 
			       	opnames[id->op], id->count, msgtxt(id->msg), regname(id->addr),symname(reglist, ARRAY_SIZE(reglist), id->op, id->addr, id->data), id->udelay);
				i = aux(i);
				id = &iodefs[i];
				continue;
			}
			/* only ignore these writes if we're still transforming
			 * aux io
			 */
			if (id->addr >= DPA_AUX_CH_CTL
			    && id->addr <= DPA_AUX_CH_DATA5 &&
			     num_changed < num_to_change)
				continue;
			if (id->op == GWl && id->addr == _LGC_PALETTE_A){
				while ((id->addr & ~0x3ff) == _LGC_PALETTE_A){
					id++,i++;
				}
				printf("\tpalette();\n");
			}
			/* detect a spin */
			/* GWl followed by GWr or GRl followed by GRl */
			if (id->addr == id[-1].addr && id->op == GRl && 
			    id->addr != id[1].addr) {
				printf("\tspin(0x%08lx, 0x%08lx);\n", id->data, id->addr);
				fprintf(stderr, "Spinning on %08lx\n", id->addr);
			}
			if (i < sizeof(iodefs)/sizeof(iodefs[0])){
				if (id->op == GWl){
					printf("\tio_i915_write32(%s,%s);\n",
					       symname(reglist, ARRAY_SIZE(reglist), id->op, id->addr, id->data),regname(id->addr));
					if (id->addr == PCH_PP_CONTROL) printf("\tudelay(600000);\n");
				} else {
					//printf("\tif (verbose & vio) io_i915_read32(%s, %08lx);\n",regname(id->addr), id->data);
					printf("\tif (verbose & vio) {io_i915_read32(%s);printk(BIOS_SPEW, \"  %08lx\\n\");}\n",
					       regname(id->addr), id->data);
				}
			}
			if (id->udelay)
				printf("\tudelay(%ld)\n", id->udelay);

		}
	}
	printf("%s\n", postfix);
	/* this should not be needed. valgrind sees no errors. !# */
	fflush(stdout);
	exit(0);
}

