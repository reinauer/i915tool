/* variables comon to all tools. 
 */
int verbose = 1;
unsigned short addrport, dataport;
struct drm_device *i915;
unsigned short vendor=0x8086, device=0x0116;
struct pci_dev fake = {.vendor_id=0x8086, .device_id = 0x0116}, *dev0;
int dofake = 0;
u8 *bios_image = NULL;
void *mmiobase;
u32 mmiophys;
u32 gsmphys;
u32 gsmgfx;
u32 aperture, aperturesize;
u8 *gfx;
int mmiosize;
size_t bios_image_size;
int gencode = 0;
extern int cangencode;

int gfxsize = (2560 * 1700);
int gfxpages = ((2560 * 1700 * 4) + 4095)/* bytes */ / 4096 /* bytes per gtt */;
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

	/* owie. Just be crude about it. */
bool intel_choose_pipe_bpp_dither(struct drm_crtc *crtc,
					 unsigned int *pipe_bpp)
{

	fprintf(stderr, "(HARD-WIRED: setting pipe bpc to %d (max display bpc %d)\n",
			 6, 6);

	*pipe_bpp = 6 * 3;

	return 1;
}

void BUG(void)
{
	fprintf(stderr, "BUG!\n");
}

void
getrawmonotonic(struct timespec *t)
{
	clock_getres(CLOCK_MONOTONIC, t);
}

/* for now ... we'll keep it simple */
/* I'm almost certain we don't need these IDs but we'll see */
static int idr = 1;

void
idr_init(void *v)
{
}

int
idr_pre_get(void *x)
{
	return 1;
}

int
idr_get_new_above(void *v, void *o, int unused, int *new_id)
{
	*new_id = idr++;
}

void
printio(bool write, u32 reg, u64 val, u32 size)
{
        unsigned int small = (unsigned int) val;
        fprintf(stderr, "%s %s: ", write ? "W" : "R", regname(reg));
        switch(size){
	case 1: fprintf(stderr, "%02x\n", small);
		break;
	case 2: fprintf(stderr, "%04x\n", small);
		break;
	case 4: fprintf(stderr, "%08x\n", small);
		break;
	case 8: fprintf(stderr, "%016llx\n", (unsigned long long) val);
		break;
        }
}

unsigned long io_I915_READ32(unsigned long addr)
{
       unsigned long val;
       if (dofake)
               return 0xcafebabe;
       outl(addr, addrport);
       val = inl(dataport);
       if (verbose > 4)
               printio(0, addr, val, 4);
       return val;
}

void io_I915_WRITE32(unsigned long addr, unsigned long val)
{
       if (dofake)
               return;
       outl(addr, addrport);
       outl(val, dataport);
       if (verbose > 4)
               printio(1, addr, val, 4);
}

/* not sure how we want to do this so let's guess */
/* to make it easy, we start at zero and assume 250 hz. */
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
	if (verbose > 10)
		fprintf(stderr, "MS: %d\n", j);
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

void
hexdump(u32 *base, int size)
{
	int i, j;
	for(i = 0; i < size/sizeof(u32); i += 8) {
		fprintf(stderr, "%#x: ", i);
		for(j = 0; j < 8; j++)
			fprintf(stderr, "%08x", base[i+j]);
		fprintf(stderr,"\n");
	}
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

	if (verbose > 3)
		fprintf(stderr, "UDELAY %d!\n", i);
	end = rdtsc() + i * tickspermicrosecond;
	while (rdtsc() < end)
		;
}

unsigned long I915_READ(unsigned long addr)
{
	volatile u32 *ptr = (u32 *)(mmiobase + addr);
	unsigned long val;
	if (dofake)
		return 0xcafebabe;
	val = *ptr;
	if (verbose > 4)
		printio(0, addr, val, 4);
	return val;
}

void I915_WRITE(unsigned long addr, unsigned long val)
{
	volatile u32 *ptr = (u32 *)(mmiobase + addr);
	if (dofake)
		return;
	*ptr = val;
	if (verbose > 4)
		printio(1, addr, val, 4);
}

u16 I915_READ16(unsigned long addr)
{
	volatile u16 *ptr = (u16 *)(mmiobase + addr);
	unsigned long val;
	if (dofake)
		return 0xbabe;
	val = *ptr;
	if (verbose > 4)
		printio(0, addr, val, 2);
	return val;
}

void I915_WRITE16(unsigned long addr, u16 val)
{
	volatile u16 *ptr = (u16 *)(mmiobase + addr);
	if (dofake)
		return;
	*ptr = val;
	if (verbose > 4)
		printio(1, addr, val, 2);
}

u8 I915_READ8(unsigned long addr)
{
	volatile u8 *ptr = (u8 *)(mmiobase + addr);
	u8 val;
	if (dofake)
		return 0xba;
	val = *ptr;
	if (verbose > 4)
		printio(0, addr, val, 1);
	return val;
}

void I915_WRITE8(unsigned long addr, u8 val)
{
	volatile u8 *ptr = (u8 *)(mmiobase + addr);
	if (dofake)
		return;
	*ptr = val;
	if (verbose > 4)
		printio(1, addr, val, 1);
}

static int gtt_poll_interval(u32 reg, u32 mask, u32 value, int trytry)
{
	int try = trytry;
        u32 data;

        while (try--) {
                data = I915_READ(reg);
		if (verbose > 4)
			fprintf(stderr, "gtt_poll: %#x <- %#x\n", data, reg);
                if ((data & mask) == value){
			fprintf(stderr, "succeeds after %d tries\n", trytry-try);
                        return 1;
		}
                udelay(10);
        }

        fprintf(stderr, "GT init timeout\n");
        return 0;
}

#define GTT_RETRY 1000
static int gtt_poll(u32 reg, u32 mask, u32 value)
{
	return gtt_poll_interval(reg, mask, value, GTT_RETRY);
}
void *pci_map_rom(struct pci_dev *dev, size_t *size)
{
	*size = bios_image_size;
	return bios_image;
}

void *pci_unmap_rom(struct pci_dev *dev, void *bios)
{
	return NULL;
}

void *dmi_check_system(unsigned long ignore)
{
	return NULL;
}

void *
mapit(u32 phys, u32 size)
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

/* keep it here. */
static inline unsigned int cpuid_eax(unsigned int op)
{
        unsigned int eax;

        __asm__("mov %%ebx, %%edi;"
                "cpuid;"
                "mov %%edi, %%ebx;"
                : "=a" (eax)
                : "0" (op)
                : "ecx", "edx", "edi");
        return eax;
}
/* from coreboot. We're willing to do this as we're going into coreboot someday */
static int bridge_revision_id = -1;

int bridge_silicon_revision(void)
{
	struct pci_dev *bridge;
	if (bridge_revision_id < 0) {
		bridge = pci_get_bus_and_slot(0, 0);

		uint8_t stepping = cpuid_eax(1) & 0xf;
		uint8_t bridge_id = pci_read_byte(bridge, PCI_DEVICE_ID) & 0xf0;
		bridge_revision_id = bridge_id | stepping;
		printf("bridge revision %x\n", bridge_revision_id);
	}
	return bridge_revision_id;
}

void
devinit()
{
	if (bridge_silicon_revision() < IVB_STEP_C0) {
		/* 1: Enable force wake */
		I915_WRITE(0xa18c, 0x00000001);
		if (!gtt_poll(0x130090, (1 << 0), (1 << 0)))
			return;
	} else {
		I915_WRITE(0xa180, 1 << 5);
		I915_WRITE(0xa188, 0xffff0001);
		if (!gtt_poll_interval(0x130040, (1 << 0), (1 << 0), 100000))
			return;
	}
}

char *commandname = NULL;
void usage(void)
{
	printf("Usage: %s [-b biosfile] [-f (fake hardware)]"
			"[-C (gen code if applicable)"
			"[-v (increase verbosity for each -v)]", commandname);
	exit(1);
}

void init(int *ac, char ***av)
{
	int argc; char **argv;
	char *filename = NULL;
	argc = *ac; argv = *av;
	commandname = argv[0];
	for(argc--, argv++; argc; argc--, argv++) {
		if (argv[0][0] != '-')
			break;
		if (!strcmp(argv[0], "-b")) {
			filename = argv[1];
			if (! filename)
				usage();
			argc--, argv++;
		}
		if (!strcmp(argv[0], "-f"))
			dofake++;
		if (!strcmp(argv[0], "-v"))
			verbose++;
		if (!strcmp(argv[0], "-C"))
			if (cangencode)
				gencode++;
			else
				errx(1, "You asked for gencode but this program doesn't do that");
	}

	*ac = argc;
	*av = argv;


	i915 = calloc(1, sizeof(*i915));
	i915->dev_private = calloc(1, sizeof(*i915->dev_private));
	/* until we do a bit more w/ coccinelle */
	i915->dev_private->dev = i915;

	if (dofake) {
		i915->pdev = &fake;
		if (! find_idlist(i915, vendor, device))
			errx(1, "can't find fake device in pciidlist");
	} else {
		if (! pci_dev_find(i915))
			errx(1, "No VGA device of any kind found\n");
	}

	if (filename) {
		FILE *fd;
		int amt;
		/* size it later */
		bios_image = malloc(8*1048576);
		fd = fopen(filename, "r");
		amt = fread(bios_image, 65536, 128, fd);
		if (amt < 1) {
			free(bios_image);
		} else {
			i915->bios_bin = bios_image;
			i915->dev_private->opregion.vbt = bios_image;
			bios_image_size = amt * 65536;
			fclose(fd);
		}
	}
	/* get the base address for the mmio indirection registers -- BAR 4 */
	addrport = i915->pdev->base_addr[4] & ~3;
	dataport = addrport + 4;
	iopl(3);
	addrport = i915->pdev->base_addr[4] & ~3;
	dataport = addrport + 4;
	if (verbose > 2)
		fprintf(stderr, "Addrport is at %x, dataport at %x\n", 
				addrport, dataport);
	/* get the base of the mmio space */
	mmiophys = i915->pdev->base_addr[0] & ~0xf;
	mmiosize = i915->pdev->size[0];
	if (verbose > 2)
		fprintf(stderr, "phys base is %#x, size %d\n", mmiophys, mmiosize);
	mmiobase = mapit(mmiophys, mmiosize);
	aperture = i915->pdev->base_addr[2] & ~0xf;
	aperturesize = i915->pdev->size[2];
	if (verbose > 2)
		fprintf(stderr, "aperture base is %#x, size %d: ", 
			aperture, aperturesize);
	gfx = mapit(aperture, aperturesize);
	if (verbose > 2)
		fprintf(stderr, "mapped at %#x\n", gfx);
	dev0 = pci_get_bus_and_slot(0,0);
	printf("WARNING: using ivy specific read of for gsm: reg 0x5c\n");
	gsmphys = pci_read_long(dev0, 0x5c);
	/* adjust for TSEG */
	gsmphys += 8*1024*1024;
	gsmgfx = gsmphys + 2 * 1024 * 1024;
	if (verbose > 2)
		fprintf(stderr, "gsmphys is %#x\n", gsmphys);
}

void
dumpeld(char *name, u8 *eld)
{
  print_hex_dump_bytes(name, DUMP_PREFIX_OFFSET, eld, MAX_ELD_BYTES);
}
void
geneld(char *name, u8 *eld)
{
  printf("unsigned char %s[MAX_ELD_BYTES] = {\n", name);
  int i, j;
  for(i = j = 0; i + j < MAX_ELD_BYTES; i += 16, j = 0) {
	  for(j = 0; i + j < MAX_ELD_BYTES && j < 16; j++)
		  printf("0x%02x, ", eld[i+j]);
	  printf("\n");
  }
  printf("};\n");
}

void
dumpmodeconfig(void)
{
	extern struct drm_device *i915;
	struct drm_device *dev = i915;

	struct drm_connector *connector;
	struct drm_encoder *tmp_encoder;
	struct drm_crtc *crtc;
	printf("num_fb %d\n", i915->mode_config.num_fb);

        list_for_each_entry(connector, &dev->mode_config.connector_list, head)
		printf("connector %p\n", connector);

	printf("num_crtc %d\n", i915->mode_config.num_crtc);
	list_for_each_entry(crtc, &dev->mode_config.crtc_list, head) {
		printf("crtc %p enabled %d, x %d y %d\n", crtc, crtc->enabled, crtc->x, crtc->y);
	}
	printf("num_encoder %d\n", i915->mode_config.num_encoder);
	list_for_each_entry(tmp_encoder, &dev->mode_config.encoder_list, head) {
		printf("encoder %p crtc %p\n", tmp_encoder, tmp_encoder->crtc);
	}
}

void *allocz(int size)
{
	/* obsolete or not, it's convenient */
	u8 *cp = valloc(size);
	if (! cp)
		errx(1, "%d bytes\n", size);
	memset(cp, 0, size);
	if (verbose > 4)
		printf("allocz %d bytes\n", size);
	return cp;
}

void freez(void *p)
{
	if (verbose > 4)
		printf("Free %p\n", p);
}
/*
LVDS Raw: 00000000: 00 ff ff ff ff ff ff 00 4c a3 42 31 00 00 00 00  ........L.B1....
LVDS Raw: 00000010: 00 15 01 03 80 1a 10 78 0a d3 e5 95 5c 60 90 27  .......x....\`.'
LVDS Raw: 00000020: 19 50 54 00 00 00 01 01 01 01 01 01 01 01 01 01  .PT.............
LVDS Raw: 00000030: 01 01 01 01 01 01 9e 1b 00 a0 50 20 12 30 10 30  ..........P .0.0
LVDS Raw: 00000040: 13 00 05 a3 10 00 00 19 00 00 00 0f 00 00 00 00  ................
LVDS Raw: 00000050: 00 00 00 00 00 23 87 02 64 00 00 00 00 fe 00 53  .....#..d......S
LVDS Raw: 00000060: 41 4d 53 55 4e 47 0a 20 20 20 20 20 00 00 00 fe  AMSUNG.     ....
LVDS Raw: 00000070: 00 31 32 31 41 54 31 31 2d 38 30 31 0a 20 00 45  .121AT11-801. .E
*/
unsigned char lumpyedid[MAX_ELD_BYTES] = {
0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x4c, 0xa3, 0x42, 0x31, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x15, 0x01, 0x03, 0x80, 0x1a, 0x10, 0x78, 0x0a, 0xd3, 0xe5, 0x95, 0x5c, 0x60, 0x90, 0x27, 
0x19, 0x50, 0x54, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x9e, 0x1b, 0x00, 0xa0, 0x50, 0x20, 0x12, 0x30, 0x10, 0x30, 
0x13, 0x00, 0x05, 0xa3, 0x10, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x87, 0x02, 0x64, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x53, 
0x41, 0x4d, 0x53, 0x55, 0x4e, 0x47, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xfe, 
0x00, 0x31, 0x32, 0x31, 0x41, 0x54, 0x31, 0x31, 0x2d, 0x38, 0x30, 0x31, 0x0a, 0x20, 0x00, 0x45, 
};
/* more stuff coccinelle can't always get :-( */
void *kcalloc(int num, int size, int ignored)
{
	return allocz(num * size);
}

#if 0
 .,$g/^R/s/..\(.*\):.*/v = I915_READ(\1);
 .,$g/^W/s/..\(.*\):\(.*\)/I915_WRITE(\1, 0x\2);
#endif
/* snooped IO */
void hackattack(void)
{
	unsigned long v;
	v = I915_READ(PP_ON_DELAYS);
	v = I915_READ(PP_OFF_DELAYS);
	I915_WRITE(PP_ON_DELAYS,  0x019007d0);
	I915_WRITE(PP_OFF_DELAYS,  0x015e07d0);
	I915_WRITE(0x100000,  0x0000000000000000);
	I915_WRITE(0x100008,  0x0000000000000000);
	I915_WRITE(0x100010,  0x0000000000000000);
	I915_WRITE(0x100018,  0x0000000000000000);
	I915_WRITE(0x100020,  0x0000000000000000);
	I915_WRITE(0x100028,  0x0000000000000000);
	I915_WRITE(0x100030,  0x0000000000000000);
	I915_WRITE(0x100038,  0x0000000000000000);
	I915_WRITE(0x100040,  0x0000000000000000);
	I915_WRITE(0x100048,  0x0000000000000000);
	I915_WRITE(0x100050,  0x0000000000000000);
	I915_WRITE(0x100058,  0x0000000000000000);
	I915_WRITE(0x100060,  0x0000000000000000);
	I915_WRITE(0x100068,  0x0000000000000000);
	I915_WRITE(0x100070,  0x0000000000000000);
	I915_WRITE(0x100078,  0x0000000000000000);
	v = I915_READ(0x145004);
	v = I915_READ(0x145008);
}

void
setgtt(unsigned long base, int inc)
{
  	int i;

/*
	printf("# PTEs is %d\n", num);
	printf("Start of graphics pages would be %#p\n", base);
 */
	for(i = 0; i < gfxpages; i++){
		u32 word = base + i*inc;
		io_I915_WRITE32((i*4)|1,word|1);
	}


}
