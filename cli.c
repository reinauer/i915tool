#include "video.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

extern int verbose;
extern struct drm_device *i915;
int cangencode = 0;

int main(int argc, char *argv[])
{
	unsigned long long start, end;
	unsigned long usec;
	bool drm_crtc_helper_set_mode(struct drm_crtc *crtc,
                              struct drm_display_mode *mode,
                              int x, int y,
                              struct drm_framebuffer *old_fb);
	int lvds = 0;
	struct drm_encoder *encoder;
	struct intel_connector *ic;
	struct drm_i915_private *dp;
	struct drm_connector *connector = NULL;
	struct drm_display_mode *mode = NULL;
	int level = 0;
	struct drm_crtc *crtc;
	struct intel_load_detect_pipe pipe;
	char *cmd;
	void geneld(char *, u8 *);
	init(&argc, &argv);
	printf("suggest b,i,m,c,p,d8,f, then d0 (lo off and lO on)\n");
	while ((cmd = readline(">")) != NULL){
		start = rdtsc();
		switch(cmd[0]) {
			case 'i': devinit(); break;
			case 'b':
				intel_setup_bios(i915);
				if (i915->bios_bin)
					intel_parse_bios(i915);
				break;
			case 'l':
				if (cmd[1] == 'O')
					intel_panel_enable_backlight(i915);
				else if (cmd[1] == 'o')
					intel_panel_disable_backlight(i915);
				else fprintf(stderr,
						"Usage: l<o|O> (off or On)\n");
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
				
				if (! connector) {
					warnx(1, "No connector, maybe do a b, l0, m commands?");
					break;
				}
				if (connector->display_info.raw_edid)
					dumpeld("LVDS Raw: ", 
					connector->display_info.raw_edid);
				if (mode) drm_mode_debug_printmodeline(mode);
				
				break;
		case 'g':
			/* generate code for edid init */

			if (connector)
				geneld("edid", connector->display_info.raw_edid);
			break;
			
#if 0
		case 'd':
			level = strtoul(&cmd[1], 0, 0);
			if (connector)
				ic = to_intel_connector(connector);
			else {
				fprintf(stderr, "no connector! Did you do a 'c' command?\n");
				break;
			}
			
			if (verbose)
				fprintf(stderr, 
					"We have connector:%p intel connector %p, ice %p\n", 
					connector, ic, 
					ic ? ic->encoder : NULL);
			if (ic->encoder) 
				encoder = (struct drm_encoder *)(ic->encoder);
			else {
				fprintf(stderr, "no encoder!\n");
				break;
			}
			if (verbose)
				fprintf(stderr, "Encoder is %p\n", encoder);
        		list_for_each_entry(mode, &connector->modes, head) {
                		if (mode->status == MODE_OK)
                        		break;
			}
			if (! mode || mode->status != MODE_OK)
			  mode = drm_mode_create(i915);
			if (! mode){
				fprintf(stderr, "FUCK! no mode\n");
				break;
			}
			/* at this point backpanel is lit or should be. Get a pipe. */
			/* too soon? Consider not doing this yet. */
			/* we need to do this or a dpms(0) hangs. */
			if (! level)
				intel_get_load_detect_pipe(to_intel_encoder(encoder), connector, mode,&pipe);
			crtc = encoder->crtc;
			if (crtc)
				drm_crtc_helper_set_mode(crtc,
							 mode,  0, 0, NULL);
			else {
				fprintf(stderr, "no crtc!\n");
			}
			if (lvds)
				intel_lvds_dpms(encoder, level);
			else
				intel_dp_dpms(encoder, level);
			/* at this point backpanel is lit or should be. Get a pipe. */
			//intel_get_load_detect_pipe(to_intel_encoder(encoder), connector, mode,&pipe);
			//void gen6_fdi_link_train(struct drm_crtc *crtc) ;
			crtc = encoder->crtc;
			break;
			if (crtc)
				intel_crt_load_detect(to_intel_crtc(crtc));
			else
				fprintf(stderr, "NO crtc on encoder\n");
			break;
#endif
		case 'f':
			drm_helper_resume_force_mode(i915);
			intel_fbdev_init(i915);
			break;
		case 'p':
			if (! connector){
				fprintf(stderr, "NO connector? 'c' command?\n");
				break;
			}
			drm_helper_probe_single_connector_modes(connector, 8192, 8192);
			break;
		case 'v':
			verbose = strtoul(&cmd[1], 0, 0);
			break;
			
		default: 
			fprintf(stderr, "This program sucks too much to tell you the commands you can do\n");
			break;
			
			}
		end = rdtsc();
		usec = microseconds(start, end);
		fprintf(stderr, "Command took %ld microseconds\n", usec);
		}
}
