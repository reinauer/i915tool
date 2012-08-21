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
	struct drm_display_mode *mode;
	int level = 0;
	struct drm_crtc *crtc;
	struct intel_load_detect_pipe pipe;

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

	/* at this point backpanel is lit or should be. Get a pipe. */
	intel_get_load_detect_pipe(to_intel_encoder(encoder), connector, mode,&pipe);
	/* now we have a framebuffer. Let's try to enable it. */
	intel_fbdev_init(i915);

#if 0
	enum drm_connector_status intel_crt_load_detect(struct intel_crt *crt);
	crtc = encoder->crtc;
	if (crtc)
		intel_crt_load_detect(to_intel_crtc(crtc));
	else
		fprintf(stderr, "NO crtc on encoder\n");
	dumpmodeconfig();
	uint32_t bclrpat_reg;
	bclrpat_reg = BCLRPAT(PIPE_A);
	I915_WRITE(bclrpat_reg, 0x500050);

	uint32_t vsync_reg;
	uint32_t vsync = I915_READ(vsync_reg);
	uint32_t vsync_start = (vsync & 0xffff) + 1;
	uint32_t vblank, vblank_start, vblank_end;
	uint32_t vblank_reg;
	vblank_reg = VBLANK(PIPE_A);
	vblank = I915_READ(vblank_reg);
	vblank_start = (vblank & 0xfff) + 1;
	vblank_end = ((vblank >> 16) & 0xfff) + 1;
	vsync_reg = VSYNC(PIPE_A);	
	vblank_start = vsync_start;
	I915_WRITE(vblank_reg,
		   (vblank_start - 1) |
		   ((vblank_end - 1) << 16));
#endif
	

}
