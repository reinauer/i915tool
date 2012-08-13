
/* these are fake functions to get something to run. 
 * over time, they get replaced by real functions
 * extracted by our ladybug friend. 
 */
extern void intel_hdmi_init(struct drm_device *dev,
			    int sdvox_reg, enum port port){ fprintf(stderr, "%s called\n", "intel_hdmi_init");}
//void intel_crt_init(struct drm_device *dev) { fprintf(stderr, "%s called\n", "intel_crt_init");}
void intel_tv_init(struct drm_device *dev) { fprintf(stderr, "%s called\n", "intel_tv_init");}

bool intel_sdvo_init(struct drm_device *dev, uint32_t sdvo_reg,
			    bool is_sdvob){ fprintf(stderr, "%s called\n", "intel_sdvo_init");}

/* I doubt we need this but ... jsut checking */
void intel_crtc_disable(struct drm_crtc *crtc)
{
	fprintf(stderr, "INTEL_CRTC_DISABLE CALLED ... YOU WERE WRONG!\n");
}

