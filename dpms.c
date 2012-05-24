#include "video.h"

extern int verbose;
extern struct drm_device *i915;
int cangencode = 0;

int main(int argc, char *argv[])
{
	void intel_dp_dpms(struct drm_encoder *encoder, int mode);
	void intel_lvds_dpms(struct drm_encoder *encoder, int mode);
	int lvds = 0;
	struct drm_encoder *encoder;
	struct intel_connector *ic;
	struct drm_i915_private *dp;
	struct drm_connector *connector = NULL;
	int level = 0;
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
		lvds = 1;
		encoder = dp->int_lvds_connector->encoder;
		if (verbose){
			fprintf(stderr, "We have an lvds: \n");
		}
		connector = dp->int_lvds_connector;
	}
	
	if (dp->int_edp_connector) {
		encoder = dp->int_edp_connector->encoder;
		if (verbose){
			fprintf(stderr, "We have an edp: \n");
		}
		connector = dp->int_edp_connector;
	}

	if (! connector)
		errx(1, "No connector, all done here");
	printf("dpms: current level is %d\n", connector->dpms);
	
	if (connector)
	  ic = to_intel_connector(connector);
	
	if (verbose)
		fprintf(stderr, "We have connector:%p intel connector %p, ice %p\n", connector, ic, 
			ic ? ic->encoder : NULL);
	if (ic->encoder) 
		encoder = (struct drm_encoder *)(ic->encoder);
	if (verbose)
		fprintf(stderr, "Encoder is %p\n", encoder);
	while(argc && encoder) {
		level = strtol(argv[0], 0, 0);
		printf("dpms: going to level %d\n", level);
		if (lvds)
			intel_lvds_dpms(encoder, level);
		else
			intel_dp_dpms(encoder, level);
		argc--;
		argv++;
	}

	dumpmodeconfig();

}
