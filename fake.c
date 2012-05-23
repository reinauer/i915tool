
/* these are fake functions to get something to run. 
 * over time, they get replaced by real functions
 * extracted by our ladybug friend. 
 */
//void intel_crt_init(struct drm_device *dev) { fprintf(stderr, "%s called\n", "intel_crt_init");}
void intel_dvo_init(struct drm_device *dev) { fprintf(stderr, "%s called\n", "intel_dvo_init");}
void intel_hdmi_init(struct drm_device *dev, int sdvox_reg) { fprintf(stderr, "%s called\n", "intel_hdmi_init");}
bool intel_sdvo_init(struct drm_device *dev, int output_device) { fprintf(stderr, "%s called\n", "intel_sdvo_init");}
void intel_tv_init(struct drm_device *dev) { fprintf(stderr, "%s called\n", "intel_tv_init");}
