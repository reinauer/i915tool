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
	int gen6_do_reset(struct drm_device *dev, u8 flags);

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

	gen6_do_reset(i915, 0);

}
