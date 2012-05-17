#include "video.h"

extern int verbose;
extern struct drm_device *i915;
int cangencode = 0;

int main(int argc, char *argv[])
{
	struct drm_i915_private *dp;
	bool dpd_is_edp = false;

	init(&argc, &argv);
	devinit();
	intel_setup_bios(i915);
	if (i915->bios_bin)
		intel_parse_bios(i915);
	intel_panel_enable_backlight(i915);
	i915_driver_load(i915, (unsigned long)i915->dev_private->info);

	dp = i915->dev_private;

	dpd_is_edp = intel_dpd_is_edp(i915);
	
	if (has_edp_a(i915))
		printf("DP_A,");
	
	if (dp->int_lvds_connector)
		printf("LVDS,");

	if (I915_READ(HDMIC) & PORT_DETECTED)
		printf("HDMIC,");

	if (I915_READ(HDMID) & PORT_DETECTED)
		printf("HDMID,");

	if (I915_READ(PCH_DP_C) & DP_DETECTED)
		printf("DPC,");

	if (!dpd_is_edp && (I915_READ(PCH_DP_D) & DP_DETECTED))
		printf("DPD,");
	printf("\n");

}
