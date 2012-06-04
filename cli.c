#include "video.h"

extern int verbose;
extern struct drm_device *i915;
int cangencode = 0;

int main(int argc, char *argv[])
{
	bool drm_crtc_helper_set_mode(struct drm_crtc *crtc,
                              struct drm_display_mode *mode,
                              int x, int y,
                              struct drm_framebuffer *old_fb);
	int lvds = 0;
	struct drm_encoder *encoder;
	struct intel_connector *ic;
	struct drm_i915_private *dp;
	struct drm_connector *connector = NULL;
	struct drm_display_mode *mode;
	int level = 0;
	struct drm_crtc *crtc;
	struct intel_load_detect_pipe pipe;
	char cmd[128];

	init(&argc, &argv);
	while (gets(cmd) != EOF) {
		switch(cmd[0]) {
			case 'i': devinit(); break;
			case 'b':
				intel_setup_bios(i915);
				if (i915->bios_bin)
					intel_parse_bios(i915);
				break;
			case 'l':
				if (cmd[1] == 'o')
					intel_panel_enable_backlight(i915);
				break;
			case 'm': 
				i915_driver_load(i915, (unsigned long)i915->dev_private->info);
				break;
			case 'c':

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
					mode = dp->lfp_lvds_vbt_mode;
				}
				
				if (dp->int_edp_connector) {
					encoder = dp->int_edp_connector->encoder;
					if (verbose){
						fprintf(stderr, "We have an edp: \n");
					}
					connector = dp->int_edp_connector;
				}
			
				if (! connector)
					warnx(1, "No connector, all done here");
				break;

			case 'd':
				if (connector)
				  ic = to_intel_connector(connector);
				
				if (verbose)
					fprintf(stderr, "We have connector:%p intel connector %p, ice %p\n", connector, ic, 
						ic ? ic->encoder : NULL);
				if (ic->encoder) 
					encoder = (struct drm_encoder *)(ic->encoder);
				if (verbose)
					fprintf(stderr, "Encoder is %p\n", encoder);
				/* at this point backpanel is lit or should be. Get a pipe. */
				intel_get_load_detect_pipe(to_intel_encoder(encoder), connector, mode,&pipe);
				mode = drm_mode_create(i915);
				if (! mode)
					fprintf(stderr, "FUCK! no mode\n");
				crtc = encoder->crtc;
				if (crtc)
			        	drm_crtc_helper_set_mode(crtc,
			                              mode,  0, 0, NULL);
				break;
				/* at this point backpanel is lit or should be. Get a pipe. */
				intel_get_load_detect_pipe(to_intel_encoder(encoder), connector, mode,&pipe);
				void gen6_fdi_link_train(struct drm_crtc *crtc) ;
				crtc = encoder->crtc;
				if (crtc)
					intel_crt_load_detect(to_intel_crtc(crtc));
				else
					fprintf(stderr, "NO crtc on encoder\n");
				break;
			case 'f':
				fprintf(stderr, "NOT YET!\n");
				//intel_fbdev_init(i915);
				break;
			}
		}
}
