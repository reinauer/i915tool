#include "video.h"

extern int verbose;
extern unsigned short addrport, dataport;
extern struct drm_device *i915;
extern unsigned short vendor, device;
extern struct pci_dev fake;
extern int dofake;
extern u8 *bios_image;
extern void *mmiobase;
extern u32 mmiophys;
extern int mmiosize;
extern size_t bios_image_size;
int cangencode = 0;

int main(int argc, char *argv[])
{
	struct pci_dev *pci_dev_find(struct drm_device *dev);

	init(&argc, &argv);
	devinit();
	
	intel_setup_bios(i915);
	if (i915->bios_bin)
		intel_parse_bios(i915);
}
