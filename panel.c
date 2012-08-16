#include "video.h"

extern int verbose;
extern struct drm_device *i915;
int cangencode = 0;

int main(int argc, char *argv[])
{
	struct drm_i915_private *dp;

	init(&argc, &argv);
	devinit();
	intel_setup_bios(i915);
	if (i915->bios_bin)
		intel_parse_bios(i915);
#if defined(VERSION) && VERSION == 36
	intel_panel_enable_backlight(i915, 0);
#else
	intel_panel_enable_backlight(i915);
#endif
	i915_driver_load(i915, (unsigned long)i915->dev_private->info);

	/* now walk the connector list, dumping connector type 
	 * and EDID
	 */
	dp = i915->dev_private;

	if (dp->int_lvds_connector) {
		if (verbose){
			fprintf(stderr, "We have an lvds: \n");
		}
	}
	
	if (dp->int_edp_connector) {
		if (verbose)
			fprintf(stderr, "We have an edp: \n");
	}

	u32 pwm = intel_panel_get_backlight(i915);
	printf("pwm %d\n", pwm);

	if (argc)
		pwm = strtol(argv[0], 0, 0);
	printf("new pwm %d\n", pwm);
#if defined(VERSION) && VERSION == 36
	intel_panel_enable_backlight(i915, 0);
#else
	intel_panel_enable_backlight(i915);
#endif
	intel_panel_set_backlight(i915, pwm);
	pwm = intel_panel_get_backlight(i915);
	printf("pwm at end is %d\n", pwm);
}
