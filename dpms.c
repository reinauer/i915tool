#include "video.h"

extern int verbose;
extern struct drm_device *i915;
int cangencode = 0;

int main(int argc, char *argv[])
{
	struct drm_i915_private *dp;
	struct drm_connector *connector = NULL;
	int level = 0;
	struct drm_encoder *encoder;
	struct drm_crtc *crtc;

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

	dumpmodeconfig();
	printf("%d levels to set\n", argc);
	connector->encoder = list_first_entry(&i915->mode_config.encoder_list, struct drm_encoder , head);
	connector->encoder->crtc = list_first_entry(&i915->mode_config.crtc_list, struct drm_crtc , head);
	while(argc) {
		level = strtol(argv[0], 0, 0);
		printf("dpms: going to level %d\n", level);
		drm_helper_connector_dpms(connector, level);
		argc--;
		argv++;
	}

}
