#include "video.h"

extern int verbose;
extern struct drm_device *i915;
int cangencode = 0;

int main(int argc, char *argv[])
{
	struct drm_i915_private *dp;
	struct drm_connector *connector = NULL;
	int level = 0;

	init(&argc, &argv);
	devinit();
	intel_setup_bios(i915);
	if (i915->bios_bin)
		intel_parse_bios(i915);
	intel_panel_enable_backlight(i915);
	i915_driver_load(i915, (unsigned long)i915->dev_private->info);

	/* now walk the connector list, dumping connector type 
	 * and EDID
	 */
	dp = i915->dev_private;

	if (dp->int_lvds_connector) {
		if (verbose){
			fprintf(stderr, "We have an lvds: \n");
		}
		connector = dp->int_lvds_connector;
	}
	
	if (dp->int_edp_connector) {
		if (verbose)
			fprintf(stderr, "We have an edp: \n");
		connector = dp->int_edp_connector;
	}
	if (! connector)
		errx(1, "No connector, all done here");
	printf("dpms: current level is %d\n", connector->dpms);

	printf("%d levels to set\n", argc);
	while(argc) {
		level = strtol(argv[0], 0, 0);
		printf("dpms: going to level %d\n", level);
		drm_helper_connector_dpms(connector, level);
		argc--;
		argv++;
	}

}
