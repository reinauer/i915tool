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
	intel_setup_bios(i915);
	if (i915->bios_bin)
		intel_parse_bios(i915);
	devinit();
	i915_driver_load(i915, (unsigned long)i915->dev_private->info);
	dp = i915->dev_private;
				
	if (dp->int_edp_connector) {
		encoder = dp->int_edp_connector->encoder;
		if (verbose){
			fprintf(stderr, "We have an edp: \n");
		}
		connector = dp->int_edp_connector;
	}
				
	if (! connector) {
		errx(1, "No connector, maybe do a b, l0, m commands?");
	}
	if (connector)
		ic = to_intel_connector(connector);
	else {
		errx( "no connector! \n");
	}
	
	fprintf(stderr, 
		"We have connector:%p intel connector %p, ice %p\n", 
		connector, ic, 
		ic ? ic->encoder : NULL);
	if (ic->encoder) 
		encoder = (struct drm_encoder *)(ic->encoder);
	else {
		errx("no encoder!\n");
	}
	if (verbose)
		fprintf(stderr, "Encoder is %p\n", encoder);
	/* at this point backpanel is lit or should be. Get a pipe. */
	intel_get_load_detect_pipe(to_intel_encoder(encoder), connector, mode,&pipe);
	intel_panel_enable_backlight(i915, 0);
	intel_panel_set_backlight(i915, 4882);
	end = rdtsc();
	usec = microseconds(start, end);
}
