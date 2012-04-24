#include "video.h"

extern int verbose;
extern unsigned short addrport, dataport;
extern struct drm_device *i915;
extern unsigned short vendor, device;
extern struct pci_dev fake;
extern int dofake;
extern u8 *bios_image;
extern u32 *mmiobase;
extern u32 mmiophys;
extern int mmiosize;
extern size_t bios_image_size;
int cangencode = 0;

/*
DRM_MODE_CONNECTOR_LVDS
and set the mode to 0, and hope we're not already in that mode. 
*/
int main(int argc, char *argv[])
{
	struct drm_i915_private *dp;
	init(argc, argv);
	devinit();
	//hexdump(mmiobase, mmiosize);
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
	intel_panel_enable_backlight(i915);
	i915_driver_load(i915, (unsigned long)i915->dev_private->info);
	hexdump(mmiobase, 128);
	dp = i915->dev_private;

	if (dp->int_lvds_connector) {
		if (verbose){
			fprintf(stderr, "We have an lvds: \n");
		}
		drm_helper_connector_dpms(dp->int_lvds_connector, 0);
	}


}
