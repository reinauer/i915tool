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
u32 aperture, aperturesize;
void *gfx;
int mmiosize;
size_t bios_image_size;
int gencode = 0;
extern int cangencode;

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

unsigned long io_I915_READ32(unsigned long addr)
{
       unsigned long val;
       if (dofake)
               return 0xcafebabe;
       outl(addr, addrport);
       val = inl(dataport);
       if (verbose > 1)
               fprintf(stderr, "%s: %x <- %x\n", __func__, val, addr);
       return val;
}

void io_I915_WRITE32(unsigned long addr, unsigned long val)
{
       if (dofake)
               return;
       outl(addr, addrport);
       outl(val, dataport);
       if (verbose > 1)
               fprintf(stderr, "%s: %x -> %x\n", __func__, val, addr);
}

/* not sure how we want to do this so let's guess */
/* to make it easy, we start at zero and assume 250 hz. */
unsigned long msecs(void)
{
	struct timeval start, now;
	static int first = 0;
	unsigned long j;
	if (! first++)
		gettimeofday(&start, NULL);
	gettimeofday(&now, NULL);
	j = (now.tv_sec - start.tv_sec)*1000 + (now.tv_usec-start.tv_usec)/1000;
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

void
hexdump(u32 *base, int size)
{
	int i, j;
	for(i = 0; i < size/sizeof(u32); i += 8) {
		printf("%#x: ", i);
		for(j = 0; j < 8; j++)
			printf("%08x", base[i+j]);
		printf("\n");
	}
}
void udelay(int i)
{
	printf("UDELAY %d!\n", i);
}

unsigned long I915_READ(unsigned long addr)
{
	volatile u32 *ptr = (u32 *)(mmiobase + addr);
	unsigned long val;
	if (dofake)
		return 0xcafebabe;
	val = *ptr;
	if (verbose > 1)
		fprintf(stderr, "%s: %x <- %x\n", __func__, val, addr);
	return val;
}

void I915_WRITE(unsigned long addr, unsigned long val)
{
	volatile u32 *ptr = (u32 *)(mmiobase + addr);
	if (dofake)
		return;
	*ptr = val;
	if (verbose > 1)
		fprintf(stderr, "%s: %x -> %x\n", __func__, val, addr);
}

u16 I915_READ16(unsigned long addr)
{
	volatile u16 *ptr = (u16 *)(mmiobase + addr);
	unsigned long val;
	if (dofake)
		return 0xbabe;
	val = *ptr;
	if (verbose > 1)
		fprintf(stderr, "%s: %x <- %x\n", __func__, val, addr);
	return val;
}

void I915_WRITE16(unsigned long addr, u16 val)
{
	volatile u16 *ptr = (u16 *)(mmiobase + addr);
	if (dofake)
		return;
	*ptr = val;
	if (verbose > 1)
		fprintf(stderr, "%s: %x -> %x\n", __func__, val, addr);
}

#define GTT_RETRY 1000
static int gtt_poll(u32 reg, u32 mask, u32 value)
{
        unsigned try = GTT_RETRY;
        u32 data;

        while (try--) {
                data = I915_READ(reg);
                if ((data & mask) == value){
			printf("succeeds after %d tries\n", GTT_RETRY-try);
                        return 1;
		}
                udelay(10);
        }

        fprintf(stderr, "GT init timeout\n");
        return 0;
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

void
devinit()
{
	u32 val;
	/* force wake. */
	I915_WRITE(0xa18c, 1);
	gtt_poll(0x130090, 1, 1);
	
}

void init(int argc, char *argv[])
{
	for(argc--, argv++; argc; argc--, argv++) {
		if (argv[0][0] != '-')
			break;
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

	if (argc) {
		FILE *fd;
		int amt;
		/* size it later */
		bios_image = malloc(8*1048576);
		fd = fopen(argv[0], "r");
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
	/* get the base address for the mmio indirection registers -- BAR 2 */
	addrport = i915->pdev->base_addr[4] & ~3;
	dataport = addrport + 4;
	iopl(3);
	addrport = i915->pdev->base_addr[4] & ~3;
	dataport = addrport + 4;
	printf("Addrport is at %x, dataport at %x\n", addrport, dataport);
	/* get the base of the mmio space */
	mmiophys = i915->pdev->base_addr[0] & ~0xf;
	mmiosize = i915->pdev->size[0];
	printf("phys base is %#x, size %d\n", mmiophys, mmiosize);
	mmiobase = mapit(mmiophys, mmiosize);
	aperture = i915->pdev->base_addr[2] & ~0xf;
	aperturesize = i915->pdev->size[2];
	printf("aperture base is %#x, size %d\n", aperture, aperturesize);
	gfx = mapit(aperture, aperturesize);
	dev0 = pci_get_bus_and_slot(0,0);
	gsmphys = pci_read_long(dev0, 0xb8);
	/* adjust for TSEG */
	gsmphys += 8*1024*1024;
	printf("gsmphys is %#x\n", gsmphys);
}
