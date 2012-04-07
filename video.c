#include "video.h"

int verbose = 1;
static unsigned short addrport, dataport;
struct drm_device *i915;
unsigned short vendor=0x8086, device=0x0116;
struct pci_dev fake = {.vendor_id=0x8086, .device_id = 0x0116};
int dofake = 0;
u8 *bios_image = NULL;
u8 *mmiobase;
u32 mmiophys;
int mmiosize;
size_t bios_image_size;

/* */

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
hexdump(u8 *base, int size)
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
	printf("UDELAY!\n");
}

unsigned long io_I915_READ(unsigned long addr)
{
	unsigned long val;
	if (dofake)
		return 0xcafebabe;
	outl(addr, addrport);
	val = inl(dataport);
	if (verbose)
		fprintf(stderr, "%s: %x <- %x\n", __func__, val, addr);
	return val;
}

void io_I915_WRITE(unsigned long addr, unsigned long val)
{
	if (dofake)
		return;
	outl(addr, addrport);
	outl(val, dataport);
	if (verbose)
		fprintf(stderr, "%s: %x -> %x\n", __func__, val, addr);
}

unsigned long I915_READ(unsigned long addr)
{
	volatile u32 *ptr = (u32 *)(mmiobase + addr);
	unsigned long val;
	if (dofake)
		return 0xcafebabe;
	val = *ptr;
	if (verbose)
		fprintf(stderr, "%s: %x <- %x\n", __func__, val, addr);
	return val;
}

void I915_WRITE(unsigned long addr, unsigned long val)
{
	volatile u32 *ptr = (u32 *)(mmiobase + addr);
	if (dofake)
		return;
	*ptr = val;
	if (verbose)
		fprintf(stderr, "%s: %x -> %x\n", __func__, val, addr);
}

u16 I915_READ16(unsigned long addr)
{
	volatile u16 *ptr = (u16 *)(mmiobase + addr);
	unsigned long val;
	if (dofake)
		return 0xbabe;
	val = *ptr;
	if (verbose)
		fprintf(stderr, "%s: %x <- %x\n", __func__, val, addr);
	return val;
}

void I915_WRITE16(unsigned long addr, u16 val)
{
	volatile u16 *ptr = (u16 *)(mmiobase + addr);
	if (dofake)
		return;
	*ptr = val;
	if (verbose)
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

void
mapit(void)
{
	int kfd;
	kfd = open("/dev/mem", O_RDWR);
	if (kfd < 0)
		errx(1, "/dev/mem");
	mmiobase = mmap(NULL, mmiosize, PROT_WRITE|PROT_READ, MAP_SHARED, kfd, mmiophys);
	if ((void *)-1 == mmiobase)
		errx(1, "mmap");
}

void
devinit()
{
	u32 val;
	/* force wake. */
	I915_WRITE(0xa18c, 1);
	gtt_poll(0x130090, 1, 1);
	
}
int main(int argc, char *argv[])
{
	struct pci_dev *pci_dev_find(struct drm_device *dev);
	for(argc--, argv++; argc; argc--, argv++) {
		if (argv[0][0] != '-')
			break;
		if (!strcmp(argv[0], "-f"))
			dofake++;
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
	printf("Addrport is at %x, dataport at %x\n", addrport, dataport);
	/* get the base of the mmio space */
	mmiophys = i915->pdev->base_addr[0] & ~0xf;
	mmiosize = i915->pdev->size[0];
	printf("phys base is %#x, size %d\n", mmiophys, mmiosize);
	mapit();
	devinit();
	//hexdump(mmiobase, mmiosize);
	
	/* we should use ioperm but hey ... it's had troubles */
	iopl(3);
	intel_setup_bios(i915);
	if (i915->bios_bin)
		intel_parse_bios(i915);
	printf("Has PCH split: %d\n", HAS_PCH_SPLIT(i915));
	printf("is mobile: %d\n", IS_MOBILE(i915));
	printf("is edp: %d\n", intel_dpd_is_edp(i915));


	u8 pin;
	pin = GMBUS_PORT_PANEL;
	printf("lvds_is_present_in_vbt returns %d\n", 
		lvds_is_present_in_vbt(i915, &pin));
	i915_driver_load(i915, i915->dev_private->info);
	/* where we want to be someday ... */
	intel_setup_outputs(i915);
}
