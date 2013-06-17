

static  struct cxsr_latency cxsr_latency_table[] = {
	{1, 0, 800, 400, 3382, 33382, 3983, 33983},    /* DDR2-400 SC */
	{1, 0, 800, 667, 3354, 33354, 3807, 33807},    /* DDR2-667 SC */
	{1, 0, 800, 800, 3347, 33347, 3763, 33763},    /* DDR2-800 SC */
	{1, 1, 800, 667, 6420, 36420, 6873, 36873},    /* DDR3-667 SC */
	{1, 1, 800, 800, 5902, 35902, 6318, 36318},    /* DDR3-800 SC */

	{1, 0, 667, 400, 3400, 33400, 4021, 34021},    /* DDR2-400 SC */
	{1, 0, 667, 667, 3372, 33372, 3845, 33845},    /* DDR2-667 SC */
	{1, 0, 667, 800, 3386, 33386, 3822, 33822},    /* DDR2-800 SC */
	{1, 1, 667, 667, 6438, 36438, 6911, 36911},    /* DDR3-667 SC */
	{1, 1, 667, 800, 5941, 35941, 6377, 36377},    /* DDR3-800 SC */

	{1, 0, 400, 400, 3472, 33472, 4173, 34173},    /* DDR2-400 SC */
	{1, 0, 400, 667, 3443, 33443, 3996, 33996},    /* DDR2-667 SC */
	{1, 0, 400, 800, 3430, 33430, 3946, 33946},    /* DDR2-800 SC */
	{1, 1, 400, 667, 6509, 36509, 7062, 37062},    /* DDR3-667 SC */
	{1, 1, 400, 800, 5985, 35985, 6501, 36501},    /* DDR3-800 SC */

	{0, 0, 800, 400, 3438, 33438, 4065, 34065},    /* DDR2-400 SC */
	{0, 0, 800, 667, 3410, 33410, 3889, 33889},    /* DDR2-667 SC */
	{0, 0, 800, 800, 3403, 33403, 3845, 33845},    /* DDR2-800 SC */
	{0, 1, 800, 667, 6476, 36476, 6955, 36955},    /* DDR3-667 SC */
	{0, 1, 800, 800, 5958, 35958, 6400, 36400},    /* DDR3-800 SC */

	{0, 0, 667, 400, 3456, 33456, 4103, 34106},    /* DDR2-400 SC */
	{0, 0, 667, 667, 3428, 33428, 3927, 33927},    /* DDR2-667 SC */
	{0, 0, 667, 800, 3443, 33443, 3905, 33905},    /* DDR2-800 SC */
	{0, 1, 667, 667, 6494, 36494, 6993, 36993},    /* DDR3-667 SC */
	{0, 1, 667, 800, 5998, 35998, 6460, 36460},    /* DDR3-800 SC */

	{0, 0, 400, 400, 3528, 33528, 4255, 34255},    /* DDR2-400 SC */
	{0, 0, 400, 667, 3500, 33500, 4079, 34079},    /* DDR2-667 SC */
	{0, 0, 400, 800, 3487, 33487, 4029, 34029},    /* DDR2-800 SC */
	{0, 1, 400, 667, 6566, 36566, 7145, 37145},    /* DDR3-667 SC */
	{0, 1, 400, 800, 6042, 36042, 6584, 36584},    /* DDR3-800 SC */
};

/*
 * Latency for FIFO fetches is dependent on several factors:
 *   - memory configuration (speed, channels)
 *   - chipset
 *   - current MCH state
 * It can be fairly high in some situations, so here we assume a fairly
 * pessimal value.  It's a tradeoff between extra memory fetches (if we
 * set this value too high, the FIFO will fetch frequently to stay full)
 * and power consumption (set it too low to save power and we might see
 * FIFO underruns and display "flicker").
 *
 * A value of 5us seems to be a good balance; safe for very low end
 * platforms but not overly aggressive on lower latency configs.
 */
static  int latency_ns = 5000;

/* Pineview has different values for various configs */
static  struct intel_watermark_params pineview_display_wm = {
	PINEVIEW_DISPLAY_FIFO,
	PINEVIEW_MAX_WM,
	PINEVIEW_DFT_WM,
	PINEVIEW_GUARD_WM,
	PINEVIEW_FIFO_LINE_SIZE
};
static  struct intel_watermark_params pineview_display_hplloff_wm = {
	PINEVIEW_DISPLAY_FIFO,
	PINEVIEW_MAX_WM,
	PINEVIEW_DFT_HPLLOFF_WM,
	PINEVIEW_GUARD_WM,
	PINEVIEW_FIFO_LINE_SIZE
};
static  struct intel_watermark_params pineview_cursor_wm = {
	PINEVIEW_CURSOR_FIFO,
	PINEVIEW_CURSOR_MAX_WM,
	PINEVIEW_CURSOR_DFT_WM,
	PINEVIEW_CURSOR_GUARD_WM,
	PINEVIEW_FIFO_LINE_SIZE,
};
static  struct intel_watermark_params pineview_cursor_hplloff_wm = {
	PINEVIEW_CURSOR_FIFO,
	PINEVIEW_CURSOR_MAX_WM,
	PINEVIEW_CURSOR_DFT_WM,
	PINEVIEW_CURSOR_GUARD_WM,
	PINEVIEW_FIFO_LINE_SIZE
};
static  struct intel_watermark_params g4x_wm_info = {
	G4X_FIFO_SIZE,
	G4X_MAX_WM,
	G4X_MAX_WM,
	2,
	G4X_FIFO_LINE_SIZE,
};
static  struct intel_watermark_params g4x_cursor_wm_info = {
	I965_CURSOR_FIFO,
	I965_CURSOR_MAX_WM,
	I965_CURSOR_DFT_WM,
	2,
	G4X_FIFO_LINE_SIZE,
};
static  struct intel_watermark_params valleyview_wm_info = {
	VALLEYVIEW_FIFO_SIZE,
	VALLEYVIEW_MAX_WM,
	VALLEYVIEW_MAX_WM,
	2,
	G4X_FIFO_LINE_SIZE,
};
static  struct intel_watermark_params valleyview_cursor_wm_info = {
	I965_CURSOR_FIFO,
	VALLEYVIEW_CURSOR_MAX_WM,
	I965_CURSOR_DFT_WM,
	2,
	G4X_FIFO_LINE_SIZE,
};
static  struct intel_watermark_params i965_cursor_wm_info = {
	I965_CURSOR_FIFO,
	I965_CURSOR_MAX_WM,
	I965_CURSOR_DFT_WM,
	2,
	I915_FIFO_LINE_SIZE,
};
static  struct intel_watermark_params i945_wm_info = {
	I945_FIFO_SIZE,
	I915_MAX_WM,
	1,
	2,
	I915_FIFO_LINE_SIZE
};
static  struct intel_watermark_params i915_wm_info = {
	I915_FIFO_SIZE,
	I915_MAX_WM,
	1,
	2,
	I915_FIFO_LINE_SIZE
};
static  struct intel_watermark_params i855_wm_info = {
	I855GM_FIFO_SIZE,
	I915_MAX_WM,
	1,
	2,
	I830_FIFO_LINE_SIZE
};
static  struct intel_watermark_params i830_wm_info = {
	I830_FIFO_SIZE,
	I915_MAX_WM,
	1,
	2,
	I830_FIFO_LINE_SIZE
};

static  struct intel_watermark_params ironlake_display_wm_info = {
	ILK_DISPLAY_FIFO,
	ILK_DISPLAY_MAXWM,
	ILK_DISPLAY_DFTWM,
	2,
	ILK_FIFO_LINE_SIZE
};
static  struct intel_watermark_params ironlake_cursor_wm_info = {
	ILK_CURSOR_FIFO,
	ILK_CURSOR_MAXWM,
	ILK_CURSOR_DFTWM,
	2,
	ILK_FIFO_LINE_SIZE
};
static  struct intel_watermark_params ironlake_display_srwm_info = {
	ILK_DISPLAY_SR_FIFO,
	ILK_DISPLAY_MAX_SRWM,
	ILK_DISPLAY_DFT_SRWM,
	2,
	ILK_FIFO_LINE_SIZE
};
static  struct intel_watermark_params ironlake_cursor_srwm_info = {
	ILK_CURSOR_SR_FIFO,
	ILK_CURSOR_MAX_SRWM,
	ILK_CURSOR_DFT_SRWM,
	2,
	ILK_FIFO_LINE_SIZE
};

static  struct intel_watermark_params sandybridge_display_wm_info = {
	SNB_DISPLAY_FIFO,
	SNB_DISPLAY_MAXWM,
	SNB_DISPLAY_DFTWM,
	2,
	SNB_FIFO_LINE_SIZE
};
static  struct intel_watermark_params sandybridge_cursor_wm_info = {
	SNB_CURSOR_FIFO,
	SNB_CURSOR_MAXWM,
	SNB_CURSOR_DFTWM,
	2,
	SNB_FIFO_LINE_SIZE
};
static  struct intel_watermark_params sandybridge_display_srwm_info = {
	SNB_DISPLAY_SR_FIFO,
	SNB_DISPLAY_MAX_SRWM,
	SNB_DISPLAY_DFT_SRWM,
	2,
	SNB_FIFO_LINE_SIZE
};
static  struct intel_watermark_params sandybridge_cursor_srwm_info = {
	SNB_CURSOR_SR_FIFO,
	SNB_CURSOR_MAX_SRWM,
	SNB_CURSOR_DFT_SRWM,
	2,
	SNB_FIFO_LINE_SIZE
};

static bool g4x_compute_wm0(struct drm_device *dev,
			    int plane,
			     struct intel_watermark_params *display,
			    int display_latency_ns,
			     struct intel_watermark_params *cursor,
			    int cursor_latency_ns,
			    int *plane_wm,
			    int *cursor_wm)
{
	struct drm_crtc *crtc;
	int htotal, hdisplay, clock, pixel_size;
	int line_time_us, line_count;
	int entries, tlb_miss;

	crtc = intel_get_crtc_for_plane(dev, plane);
	if (crtc->fb == NULL || !crtc->enabled) {
		*cursor_wm = cursor->guard_size;
		*plane_wm = display->guard_size;
		return false;
	}

	htotal = crtc->mode.htotal;
	hdisplay = crtc->mode.hdisplay;
	clock = crtc->mode.clock;
	pixel_size = crtc->fb->bits_per_pixel / 8;

	/* Use the small buffer method to calculate plane watermark */
	entries = ((clock * pixel_size / 1000) * display_latency_ns) / 1000;
	tlb_miss = display->fifo_size*display->cacheline_size - hdisplay * 8;
	if (tlb_miss > 0)
		entries += tlb_miss;
	entries = DIV_ROUND_UP(entries, display->cacheline_size);
	*plane_wm = entries + display->guard_size;
	if (*plane_wm > (int)display->max_wm)
		*plane_wm = display->max_wm;

	/* Use the large buffer method to calculate cursor watermark */
	line_time_us = ((htotal * 1000) / clock);
	line_count = (cursor_latency_ns / line_time_us + 1000) / 1000;
	entries = line_count * 64 * pixel_size;
	tlb_miss = cursor->fifo_size*cursor->cacheline_size - hdisplay * 8;
	if (tlb_miss > 0)
		entries += tlb_miss;
	entries = DIV_ROUND_UP(entries, cursor->cacheline_size);
	*cursor_wm = entries + cursor->guard_size;
	if (*cursor_wm > (int)cursor->max_wm)
		*cursor_wm = (int)cursor->max_wm;

	return true;
}

#define single_plane_enabled(mask) is_power_of_2(mask)

#define ILK_LP0_PLANE_LATENCY		700
#define ILK_LP0_CURSOR_LATENCY		1300

/*
 * Check the wm result.
 *
 * If any calculated watermark values is larger than the maximum value that
 * can be programmed into the associated watermark register, that watermark
 * must be disabled.
 */
static bool ironlake_check_srwm(struct drm_device *dev, int level,
				int fbc_wm, int display_wm, int cursor_wm,
				 struct intel_watermark_params *display,
				 struct intel_watermark_params *cursor)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
	fprintf(stderr, "watermark %d: display plane %d, fbc lines %d,"
		      " cursor %d\n", level, display_wm, fbc_wm, cursor_wm);

	if (fbc_wm > SNB_FBC_MAX_SRWM) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "fbc watermark(%d) is too large(%d), disabling wm%d+\n",
			      fbc_wm, SNB_FBC_MAX_SRWM, level);

		/* fbc has it's own way to disable FBC WM */
		I915_WRITE(DISP_ARB_CTL,
			   I915_READ(DISP_ARB_CTL) | DISP_FBC_WM_DIS);
		return false;
	}

	if (display_wm > display->max_wm) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "display watermark(%d) is too large(%d), disabling wm%d+\n",
			      display_wm, SNB_DISPLAY_MAX_SRWM, level);
		return false;
	}

	if (cursor_wm > cursor->max_wm) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "cursor watermark(%d) is too large(%d), disabling wm%d+\n",
			      cursor_wm, SNB_CURSOR_MAX_SRWM, level);
		return false;
	}

	if (!(fbc_wm || display_wm || cursor_wm)) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "latency %d is 0, disabling wm%d+\n", level, level);
		return false;
	}

	return true;
}

/*
 * Compute watermark values of WM[1-3],
 */
static bool ironlake_compute_srwm(struct drm_device *dev, int level, int plane,
				  int latency_ns,
				   struct intel_watermark_params *display,
				   struct intel_watermark_params *cursor,
				  int *fbc_wm, int *display_wm, int *cursor_wm)
{
	struct drm_crtc *crtc;
	unsigned long line_time_us;
	int hdisplay, htotal, pixel_size, clock;
	int line_count, line_size;
	int small, large;
	int entries;

	if (!latency_ns) {
		*fbc_wm = *display_wm = *cursor_wm = 0;
		return false;
	}

	crtc = intel_get_crtc_for_plane(dev, plane);
	hdisplay = crtc->mode.hdisplay;
	htotal = crtc->mode.htotal;
	clock = crtc->mode.clock;
	pixel_size = crtc->fb->bits_per_pixel / 8;

	line_time_us = (htotal * 1000) / clock;
	line_count = (latency_ns / line_time_us + 1000) / 1000;
	line_size = hdisplay * pixel_size;

	/* Use the minimum of the small and large buffer method for primary */
	small = ((clock * pixel_size / 1000) * latency_ns) / 1000;
	large = line_count * line_size;

	entries = DIV_ROUND_UP(min(small, large), display->cacheline_size);
	*display_wm = entries + display->guard_size;

	/*
	 * Spec says:
	 * FBC WM = ((Final Primary WM * 64) / number of bytes per line) + 2
	 */
	*fbc_wm = DIV_ROUND_UP(*display_wm * 64, line_size) + 2;

	/* calculate the self-refresh watermark for display cursor */
	entries = line_count * pixel_size * 64;
	entries = DIV_ROUND_UP(entries, cursor->cacheline_size);
	*cursor_wm = entries + cursor->guard_size;

	return ironlake_check_srwm(dev, level,
				   *fbc_wm, *display_wm, *cursor_wm,
				   display, cursor);
}

static void ironlake_update_wm(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int fbc_wm, plane_wm, cursor_wm;
	unsigned int enabled;

	enabled = 0;
	if (g4x_compute_wm0(dev, 0,
			    &ironlake_display_wm_info,
			    ILK_LP0_PLANE_LATENCY,
			    &ironlake_cursor_wm_info,
			    ILK_LP0_CURSOR_LATENCY,
			    &plane_wm, &cursor_wm)) {
		I915_WRITE(WM0_PIPEA_ILK,
			   (plane_wm << WM0_PIPE_PLANE_SHIFT) | cursor_wm);
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "FIFO watermarks For pipe A -"
			      " plane %d, " "cursor: %d\n",
			      plane_wm, cursor_wm);
		enabled |= 1;
	}

	if (g4x_compute_wm0(dev, 1,
			    &ironlake_display_wm_info,
			    ILK_LP0_PLANE_LATENCY,
			    &ironlake_cursor_wm_info,
			    ILK_LP0_CURSOR_LATENCY,
			    &plane_wm, &cursor_wm)) {
		I915_WRITE(WM0_PIPEB_ILK,
			   (plane_wm << WM0_PIPE_PLANE_SHIFT) | cursor_wm);
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "FIFO watermarks For pipe B -"
			      " plane %d, cursor: %d\n",
			      plane_wm, cursor_wm);
		enabled |= 2;
	}

	/*
	 * Calculate and update the self-refresh watermark only when one
	 * display plane is used.
	 */
	I915_WRITE(WM3_LP_ILK, 0);
	I915_WRITE(WM2_LP_ILK, 0);
	I915_WRITE(WM1_LP_ILK, 0);

	if (!single_plane_enabled(enabled))
		return;
	enabled = ffs(enabled) - 1;

	/* WM1 */
	if (!ironlake_compute_srwm(dev, 1, enabled,
				   ILK_READ_WM1_LATENCY() * 500,
				   &ironlake_display_srwm_info,
				   &ironlake_cursor_srwm_info,
				   &fbc_wm, &plane_wm, &cursor_wm))
		return;

	I915_WRITE(WM1_LP_ILK,
		   WM1_LP_SR_EN |
		   (ILK_READ_WM1_LATENCY() << WM1_LP_LATENCY_SHIFT) |
		   (fbc_wm << WM1_LP_FBC_SHIFT) |
		   (plane_wm << WM1_LP_SR_SHIFT) |
		   cursor_wm);

	/* WM2 */
	if (!ironlake_compute_srwm(dev, 2, enabled,
				   ILK_READ_WM2_LATENCY() * 500,
				   &ironlake_display_srwm_info,
				   &ironlake_cursor_srwm_info,
				   &fbc_wm, &plane_wm, &cursor_wm))
		return;

	I915_WRITE(WM2_LP_ILK,
		   WM2_LP_EN |
		   (ILK_READ_WM2_LATENCY() << WM1_LP_LATENCY_SHIFT) |
		   (fbc_wm << WM1_LP_FBC_SHIFT) |
		   (plane_wm << WM1_LP_SR_SHIFT) |
		   cursor_wm);

	/*
	 * WM3 is unsupported on ILK, probably because we don't have latency
	 * data for that power state
	 */
}

static void sandybridge_update_wm(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int latency = SNB_READ_WM0_LATENCY() * 100;	/* In unit 0.1us */
	u32 val;
	int fbc_wm, plane_wm, cursor_wm;
	unsigned int enabled;

	enabled = 0;
	if (g4x_compute_wm0(dev, 0,
			    &sandybridge_display_wm_info, latency,
			    &sandybridge_cursor_wm_info, latency,
			    &plane_wm, &cursor_wm)) {
		val = I915_READ(WM0_PIPEA_ILK);
		val &= ~(WM0_PIPE_PLANE_MASK | WM0_PIPE_CURSOR_MASK);
		I915_WRITE(WM0_PIPEA_ILK, val |
			   ((plane_wm << WM0_PIPE_PLANE_SHIFT) | cursor_wm));
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "FIFO watermarks For pipe A -"
			      " plane %d, " "cursor: %d\n",
			      plane_wm, cursor_wm);
		enabled |= 1;
	}

	if (g4x_compute_wm0(dev, 1,
			    &sandybridge_display_wm_info, latency,
			    &sandybridge_cursor_wm_info, latency,
			    &plane_wm, &cursor_wm)) {
		val = I915_READ(WM0_PIPEB_ILK);
		val &= ~(WM0_PIPE_PLANE_MASK | WM0_PIPE_CURSOR_MASK);
		I915_WRITE(WM0_PIPEB_ILK, val |
			   ((plane_wm << WM0_PIPE_PLANE_SHIFT) | cursor_wm));
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "FIFO watermarks For pipe B -"
			      " plane %d, cursor: %d\n",
			      plane_wm, cursor_wm);
		enabled |= 2;
	}

	if ((dev_priv->num_pipe == 3) &&
	    g4x_compute_wm0(dev, 2,
			    &sandybridge_display_wm_info, latency,
			    &sandybridge_cursor_wm_info, latency,
			    &plane_wm, &cursor_wm)) {
		val = I915_READ(WM0_PIPEC_IVB);
		val &= ~(WM0_PIPE_PLANE_MASK | WM0_PIPE_CURSOR_MASK);
		I915_WRITE(WM0_PIPEC_IVB, val |
			   ((plane_wm << WM0_PIPE_PLANE_SHIFT) | cursor_wm));
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "FIFO watermarks For pipe C -"
			      " plane %d, cursor: %d\n",
			      plane_wm, cursor_wm);
		enabled |= 3;
	}

	/*
	 * Calculate and update the self-refresh watermark only when one
	 * display plane is used.
	 *
	 * SNB support 3 levels of watermark.
	 *
	 * WM1/WM2/WM2 watermarks have to be enabled in the ascending order,
	 * and disabled in the descending order
	 *
	 */
	I915_WRITE(WM3_LP_ILK, 0);
	I915_WRITE(WM2_LP_ILK, 0);
	I915_WRITE(WM1_LP_ILK, 0);

	if (!single_plane_enabled(enabled) ||
	    dev_priv->sprite_scaling_enabled)
		return;
	enabled = ffs(enabled) - 1;

	/* WM1 */
	if (!ironlake_compute_srwm(dev, 1, enabled,
				   SNB_READ_WM1_LATENCY() * 500,
				   &sandybridge_display_srwm_info,
				   &sandybridge_cursor_srwm_info,
				   &fbc_wm, &plane_wm, &cursor_wm))
		return;

	I915_WRITE(WM1_LP_ILK,
		   WM1_LP_SR_EN |
		   (SNB_READ_WM1_LATENCY() << WM1_LP_LATENCY_SHIFT) |
		   (fbc_wm << WM1_LP_FBC_SHIFT) |
		   (plane_wm << WM1_LP_SR_SHIFT) |
		   cursor_wm);

	/* WM2 */
	if (!ironlake_compute_srwm(dev, 2, enabled,
				   SNB_READ_WM2_LATENCY() * 500,
				   &sandybridge_display_srwm_info,
				   &sandybridge_cursor_srwm_info,
				   &fbc_wm, &plane_wm, &cursor_wm))
		return;

	I915_WRITE(WM2_LP_ILK,
		   WM2_LP_EN |
		   (SNB_READ_WM2_LATENCY() << WM1_LP_LATENCY_SHIFT) |
		   (fbc_wm << WM1_LP_FBC_SHIFT) |
		   (plane_wm << WM1_LP_SR_SHIFT) |
		   cursor_wm);

	/* WM3 */
	if (!ironlake_compute_srwm(dev, 3, enabled,
				   SNB_READ_WM3_LATENCY() * 500,
				   &sandybridge_display_srwm_info,
				   &sandybridge_cursor_srwm_info,
				   &fbc_wm, &plane_wm, &cursor_wm))
		return;

	I915_WRITE(WM3_LP_ILK,
		   WM3_LP_EN |
		   (SNB_READ_WM3_LATENCY() << WM1_LP_LATENCY_SHIFT) |
		   (fbc_wm << WM1_LP_FBC_SHIFT) |
		   (plane_wm << WM1_LP_SR_SHIFT) |
		   cursor_wm);
}

static bool
sandybridge_compute_sprite_wm(struct drm_device *dev, int plane,
			      uint32_t sprite_width, int pixel_size,
			       struct intel_watermark_params *display,
			      int display_latency_ns, int *sprite_wm)
{
	struct drm_crtc *crtc;
	int clock;
	int entries, tlb_miss;

	crtc = intel_get_crtc_for_plane(dev, plane);
	if (crtc->fb == NULL || !crtc->enabled) {
		*sprite_wm = display->guard_size;
		return false;
	}

	clock = crtc->mode.clock;

	/* Use the small buffer method to calculate the sprite watermark */
	entries = ((clock * pixel_size / 1000) * display_latency_ns) / 1000;
	tlb_miss = display->fifo_size*display->cacheline_size -
		sprite_width * 8;
	if (tlb_miss > 0)
		entries += tlb_miss;
	entries = DIV_ROUND_UP(entries, display->cacheline_size);
	*sprite_wm = entries + display->guard_size;
	if (*sprite_wm > (int)display->max_wm)
		*sprite_wm = display->max_wm;

	return true;
}

static bool
sandybridge_compute_sprite_srwm(struct drm_device *dev, int plane,
				uint32_t sprite_width, int pixel_size,
				 struct intel_watermark_params *display,
				int latency_ns, int *sprite_wm)
{
	struct drm_crtc *crtc;
	unsigned long line_time_us;
	int clock;
	int line_count, line_size;
	int small, large;
	int entries;

	if (!latency_ns) {
		*sprite_wm = 0;
		return false;
	}

	crtc = intel_get_crtc_for_plane(dev, plane);
	clock = crtc->mode.clock;
	if (!clock) {
		*sprite_wm = 0;
		return false;
	}

	line_time_us = (sprite_width * 1000) / clock;
	if (!line_time_us) {
		*sprite_wm = 0;
		return false;
	}

	line_count = (latency_ns / line_time_us + 1000) / 1000;
	line_size = sprite_width * pixel_size;

	/* Use the minimum of the small and large buffer method for primary */
	small = ((clock * pixel_size / 1000) * latency_ns) / 1000;
	large = line_count * line_size;

	entries = DIV_ROUND_UP(min(small, large), display->cacheline_size);
	*sprite_wm = entries + display->guard_size;

	return *sprite_wm > 0x3ff ? false : true;
}

static void sandybridge_update_sprite_wm(struct drm_device *dev, int pipe,
					 uint32_t sprite_width, int pixel_size)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int latency = SNB_READ_WM0_LATENCY() * 100;	/* In unit 0.1us */
	u32 val;
	int sprite_wm, reg;
	int ret;

	switch (pipe) {
	case 0:
		reg = WM0_PIPEA_ILK;
		break;
	case 1:
		reg = WM0_PIPEB_ILK;
		break;
	case 2:
		reg = WM0_PIPEC_IVB;
		break;
	default:
		return; /* bad pipe */
	}

	ret = sandybridge_compute_sprite_wm(dev, pipe, sprite_width, pixel_size,
					    &sandybridge_display_wm_info,
					    latency, &sprite_wm);
	if (!ret) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "failed to compute sprite wm for pipe %d\n",
			      pipe);
		return;
	}

	val = I915_READ(reg);
	val &= ~WM0_PIPE_SPRITE_MASK;
	I915_WRITE(reg, val | (sprite_wm << WM0_PIPE_SPRITE_SHIFT));
	fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
	fprintf(stderr, "sprite watermarks For pipe %d - %d\n", pipe, sprite_wm);


	ret = sandybridge_compute_sprite_srwm(dev, pipe, sprite_width,
					      pixel_size,
					      &sandybridge_display_srwm_info,
					      SNB_READ_WM1_LATENCY() * 500,
					      &sprite_wm);
	if (!ret) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "failed to compute sprite lp1 wm on pipe %d\n",
			      pipe);
		return;
	}
	I915_WRITE(WM1S_LP_ILK, sprite_wm);

	/* Only IVB has two more LP watermarks for sprite */
	if (!IS_IVYBRIDGE(dev))
		return;

	ret = sandybridge_compute_sprite_srwm(dev, pipe, sprite_width,
					      pixel_size,
					      &sandybridge_display_srwm_info,
					      SNB_READ_WM2_LATENCY() * 500,
					      &sprite_wm);
	if (!ret) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "failed to compute sprite lp2 wm on pipe %d\n",
			      pipe);
		return;
	}
	I915_WRITE(WM2S_LP_IVB, sprite_wm);

	ret = sandybridge_compute_sprite_srwm(dev, pipe, sprite_width,
					      pixel_size,
					      &sandybridge_display_srwm_info,
					      SNB_READ_WM3_LATENCY() * 500,
					      &sprite_wm);
	if (!ret) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "failed to compute sprite lp3 wm on pipe %d\n",
			      pipe);
		return;
	}
	I915_WRITE(WM3S_LP_IVB, sprite_wm);
}

/**
 * intel_update_watermarks - update FIFO watermark values based on current modes
 *
 * Calculate watermark values for the various WM regs based on current mode
 * and plane configuration.
 *
 * There are several cases to deal with here:
 *   - normal (i.e. non-self-refresh)
 *   - self-refresh (SR) mode
 *   - lines are large relative to FIFO size (buffer can hold up to 2)
 *   - lines are small relative to FIFO size (buffer can hold more than 2
 *     lines), so need to account for TLB latency
 *
 *   The normal calculation is:
 *     watermark = dotclock * bytes per pixel * latency
 *   where latency is platform & configuration dependent (we assume pessimal
 *   values here).
 *
 *   The SR calculation is:
 *     watermark = (trunc(latency/line time)+1) * surface width *
 *       bytes per pixel
 *   where
 *     line time = htotal / dotclock
 *     surface width = hdisplay for normal plane and 64 for cursor
 *   and latency is assumed to be high, as above.
 *
 * The final value programmed to the register should always be rounded up,
 * and include an extra 2 entries to account for clock crossings.
 *
 * We don't use the sprite, so we can ignore that.  And on Crestline we have
 * to set the non-SR watermarks to 8.
 */
void intel_update_watermarks(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (dev_priv->display.update_wm)
		dev_priv->display.update_wm(dev);
}

/**
 * Lock protecting IPS related data structures
 *   - i915_mch_dev
 *   - dev_priv->max_delay
 *   - dev_priv->min_delay
 *   - dev_priv->fmax
 *   - dev_priv->gpu_busy
 *   - dev_priv->gfx_power
 */

/* Global for IPS driver to get at the current i915 device. Protected by
 * mchdev_lock. */
static struct drm_i915_private *i915_mch_dev;

/* There's a funny hw issue where the hw returns all 0 when reading from
 * GEN6_RP_INTERRUPT_LIMITS. Hence we always need to compute the desired value
 * ourselves, instead of doing a rmw cycle (which might result in us clearing
 * all limits and the gpu stuck at whatever frequency it is at atm).
 */
static u32 gen6_rps_limits(struct drm_i915_private *dev_priv, u8 *val)
{
	u32 limits;

	limits = 0;

	if (*val >= dev_priv->rps.max_delay)
		*val = dev_priv->rps.max_delay;
	limits |= dev_priv->rps.max_delay << 24;

	/* Only set the down limit when we've reached the lowest level to avoid
	 * getting more interrupts, otherwise leave this clear. This prevents a
	 * race in the hw when coming out of rc6: There's a tiny window where
	 * the hw runs at the minimal clock before selecting the desired
	 * frequency, if the down threshold expires in that window we will not
	 * receive a down interrupt. */
	if (*val <= dev_priv->rps.min_delay) {
		*val = dev_priv->rps.min_delay;
		limits |= dev_priv->rps.min_delay << 16;
	}

	return limits;
}

static  struct cparams {
	u16 i;
	u16 t;
	u16 m;
	u16 c;
} cparams[] = {
	{ 1, 1333, 301, 28664 },
	{ 1, 1066, 294, 24460 },
	{ 1, 800, 294, 25192 },
	{ 0, 1333, 276, 27605 },
	{ 0, 1066, 276, 27605 },
	{ 0, 800, 231, 23784 },
};

static void gen6_init_clock_gating(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int pipe;
	uint32_t dspclk_gate = VRHUNIT_CLOCK_GATE_DISABLE;

	I915_WRITE(PCH_DSPCLK_GATE_D, dspclk_gate);

	I915_WRITE(ILK_DISPLAY_CHICKEN2,
		   I915_READ(ILK_DISPLAY_CHICKEN2) |
		   ILK_ELPIN_409_SELECT);

	I915_WRITE(WM3_LP_ILK, 0);
	I915_WRITE(WM2_LP_ILK, 0);
	I915_WRITE(WM1_LP_ILK, 0);

	I915_WRITE(CACHE_MODE_0,
		   _MASKED_BIT_DISABLE(CM0_STC_EVICT_DISABLE_LRA_SNB));

	I915_WRITE(GEN6_UCGCTL1,
		   I915_READ(GEN6_UCGCTL1) |
		   GEN6_BLBUNIT_CLOCK_GATE_DISABLE |
		   GEN6_CSUNIT_CLOCK_GATE_DISABLE);

	/* According to the BSpec vol1g, bit 12 (RCPBUNIT) clock
	 * gating disable must be set.  Failure to set it results in
	 * flickering pixels due to Z write ordering failures after
	 * some amount of runtime in the Mesa "fire" demo, and Unigine
	 * Sanctuary and Tropics, and apparently anything else with
	 * alpha test or pixel discard.
	 *
	 * According to the spec, bit 11 (RCCUNIT) must also be set,
	 * but we didn't debug actual testcases to find it out.
	 *
	 * Also apply WaDisableVDSUnitClockGating and
	 * WaDisableRCPBUnitClockGating.
	 */
	I915_WRITE(GEN6_UCGCTL2,
		   GEN7_VDSUNIT_CLOCK_GATE_DISABLE |
		   GEN6_RCPBUNIT_CLOCK_GATE_DISABLE |
		   GEN6_RCCUNIT_CLOCK_GATE_DISABLE);

	/* Bspec says we need to always set all mask bits. */
	I915_WRITE(_3D_CHICKEN, (0xFFFF << 16) |
		   _3D_CHICKEN_SF_DISABLE_FASTCLIP_CULL);

	/*
	 * According to the spec the following bits should be
	 * set in order to enable memory self-refresh and fbc:
	 * The bit21 and bit22 of 0x42000
	 * The bit21 and bit22 of 0x42004
	 * The bit5 and bit7 of 0x42020
	 * The bit14 of 0x70180
	 * The bit14 of 0x71180
	 */
	I915_WRITE(ILK_DISPLAY_CHICKEN1,
		   I915_READ(ILK_DISPLAY_CHICKEN1) |
		   ILK_FBCQ_DIS | ILK_PABSTRETCH_DIS);
	I915_WRITE(ILK_DISPLAY_CHICKEN2,
		   I915_READ(ILK_DISPLAY_CHICKEN2) |
		   ILK_DPARB_GATE | ILK_VSDPFD_FULL);
	I915_WRITE(ILK_DSPCLK_GATE,
		   I915_READ(ILK_DSPCLK_GATE) |
		   ILK_DPARB_CLK_GATE  |
		   ILK_DPFD_CLK_GATE);

	I915_WRITE(GEN6_MBCTL, I915_READ(GEN6_MBCTL) |
		   GEN6_MBCTL_ENABLE_BOOT_FETCH);

	for_each_pipe(pipe) {
		I915_WRITE(DSPCNTR(pipe),
			   I915_READ(DSPCNTR(pipe)) |
			   DISPPLANE_TRICKLE_FEED_DISABLE);
		intel_flush_display_plane(dev_priv, pipe);
	}
}

static void gen7_setup_fixed_func_scheduler(struct drm_i915_private *dev_priv)
{
	uint32_t reg = I915_READ(GEN7_FF_THREAD_MODE);

	reg &= ~GEN7_FF_SCHED_MASK;
	reg |= GEN7_FF_TS_SCHED_HW;
	reg |= GEN7_FF_VS_SCHED_HW;
	reg |= GEN7_FF_DS_SCHED_HW;

	I915_WRITE(GEN7_FF_THREAD_MODE, reg);
}

static void ivybridge_init_clock_gating(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int pipe;
	uint32_t dspclk_gate = VRHUNIT_CLOCK_GATE_DISABLE;
	uint32_t snpcr;

	I915_WRITE(PCH_DSPCLK_GATE_D, dspclk_gate);

	I915_WRITE(WM3_LP_ILK, 0);
	I915_WRITE(WM2_LP_ILK, 0);
	I915_WRITE(WM1_LP_ILK, 0);

	I915_WRITE(ILK_DSPCLK_GATE, IVB_VRHUNIT_CLK_GATE);

	I915_WRITE(IVB_CHICKEN3,
		   CHICKEN3_DGMG_REQ_OUT_FIX_DISABLE |
		   CHICKEN3_DGMG_DONE_FIX_DISABLE);

	/* Apply the WaDisableRHWOOptimizationForRenderHang workaround. */
	I915_WRITE(GEN7_COMMON_SLICE_CHICKEN1,
		   GEN7_CSC1_RHWO_OPT_DISABLE_IN_RCC);

	/* WaApplyL3ControlAndL3ChickenMode requires those two on Ivy Bridge */
	I915_WRITE(GEN7_L3CNTLREG1,
			GEN7_WA_FOR_GEN7_L3_CONTROL);
	I915_WRITE(GEN7_L3_CHICKEN_MODE_REGISTER,
			GEN7_WA_L3_CHICKEN_MODE);

	/* According to the BSpec vol1g, bit 12 (RCPBUNIT) clock
	 * gating disable must be set.  Failure to set it results in
	 * flickering pixels due to Z write ordering failures after
	 * some amount of runtime in the Mesa "fire" demo, and Unigine
	 * Sanctuary and Tropics, and apparently anything else with
	 * alpha test or pixel discard.
	 *
	 * According to the spec, bit 11 (RCCUNIT) must also be set,
	 * but we didn't debug actual testcases to find it out.
	 *
	 * According to the spec, bit 13 (RCZUNIT) must be set on IVB.
	 * This implements the WaDisableRCZUnitClockGating workaround.
	 */
	I915_WRITE(GEN6_UCGCTL2,
		   GEN6_RCZUNIT_CLOCK_GATE_DISABLE |
		   GEN6_RCCUNIT_CLOCK_GATE_DISABLE);

	/* This is required by WaCatErrorRejectionIssue */
	I915_WRITE(GEN7_SQ_CHICKEN_MBCUNIT_CONFIG,
			I915_READ(GEN7_SQ_CHICKEN_MBCUNIT_CONFIG) |
			GEN7_SQ_CHICKEN_MBCUNIT_SQINTMOB);

	for_each_pipe(pipe) {
		I915_WRITE(DSPCNTR(pipe),
			   I915_READ(DSPCNTR(pipe)) |
			   DISPPLANE_TRICKLE_FEED_DISABLE);
		intel_flush_display_plane(dev_priv, pipe);
	}

	I915_WRITE(GEN6_MBCTL, I915_READ(GEN6_MBCTL) |
		   GEN6_MBCTL_ENABLE_BOOT_FETCH);

	gen7_setup_fixed_func_scheduler(dev_priv);

	/* WaDisable4x2SubspanOptimization */
	I915_WRITE(CACHE_MODE_1,
		   _MASKED_BIT_ENABLE(PIXEL_SUBSPAN_COLLECT_OPT_DISABLE));

	snpcr = I915_READ(GEN6_MBCUNIT_SNPCR);
	snpcr &= ~GEN6_MBC_SNPCR_MASK;
	snpcr |= GEN6_MBC_SNPCR_MED;
	I915_WRITE(GEN6_MBCUNIT_SNPCR, snpcr);
}

static void cpt_init_clock_gating(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int pipe;

	/*
	 * On Ibex Peak and Cougar Point, we need to disable clock
	 * gating for the panel power sequencer or it will fail to
	 * start up when no ports are active.
	 */
	I915_WRITE(SOUTH_DSPCLK_GATE_D, PCH_DPLSUNIT_CLOCK_GATE_DISABLE);
	I915_WRITE(SOUTH_CHICKEN2, I915_READ(SOUTH_CHICKEN2) |
		   DPLS_EDP_PPS_FIX_DIS);
	/* Without this, mode sets may fail silently on FDI */
	for_each_pipe(pipe)
		I915_WRITE(TRANS_CHICKEN2(pipe), TRANS_AUTOTRAIN_GEN_STALL_DIS);
}

void intel_init_clock_gating(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	dev_priv->display.init_clock_gating(dev);

	if (dev_priv->display.init_pch_clock_gating)
		dev_priv->display.init_pch_clock_gating(dev);
}

/* Set up chip specific power management-related functions */
void intel_init_pm(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	/* For cxsr */
	{}

	/* For FIFO watermark updates */
	{
		if (HAS_PCH_CPT(dev))
			dev_priv->display.init_pch_clock_gating = cpt_init_clock_gating;

		if (IS_GEN6(dev)) {
			if (SNB_READ_WM0_LATENCY()) {
				dev_priv->display.update_wm = sandybridge_update_wm;
				dev_priv->display.update_sprite_wm = sandybridge_update_sprite_wm;
			} else {
				fprintf(stderr, "[000000.0] [drm:%s], ",
					__func__);
				fprintf(stderr, "Failed to read display plane latency. "
					      "Disable CxSR\n");
				dev_priv->display.update_wm = NULL;
			}
			dev_priv->display.init_clock_gating = gen6_init_clock_gating;
		} else if (IS_IVYBRIDGE(dev)) {
			/* FIXME: detect B0+ stepping and use auto training */
			if (SNB_READ_WM0_LATENCY()) {
				dev_priv->display.update_wm = sandybridge_update_wm;
				dev_priv->display.update_sprite_wm = sandybridge_update_sprite_wm;
			} else {
				fprintf(stderr, "[000000.0] [drm:%s], ",
					__func__);
				fprintf(stderr, "Failed to read display plane latency. "
					      "Disable CxSR\n");
				dev_priv->display.update_wm = NULL;
			}
			dev_priv->display.init_clock_gating = ivybridge_init_clock_gating;
		} else {
			dev_priv->display.update_wm = NULL;
}
	}
}

static void __gen6_gt_wait_for_thread_c0(struct drm_i915_private *dev_priv)
{
	u32 gt_thread_status_mask;

		gt_thread_status_mask = GEN6_GT_THREAD_STATUS_CORE_MASK;

	/* w/a for a sporadic read returning 0 by waiting for the GT
	 * thread to wake up.
	 */
	if (wait_for_atomic_us((I915_READ_NOTRACE(GEN6_GT_THREAD_STATUS_REG) & gt_thread_status_mask) == 0, 500)) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "GT thread status wait timed out\n");
	}
}

static void __gen6_gt_force_wake_get(struct drm_i915_private *dev_priv)
{
	u32 forcewake_ack;

		forcewake_ack = FORCEWAKE_ACK;

	if (wait_for_atomic_us((I915_READ_NOTRACE(forcewake_ack) & 1) == 0, 500)) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "Force wake wait timed out\n");
	}

	I915_WRITE_NOTRACE(FORCEWAKE, 1);

	if (wait_for_atomic_us((I915_READ_NOTRACE(forcewake_ack) & 1), 500)) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "Force wake wait timed out\n");
	}

	__gen6_gt_wait_for_thread_c0(dev_priv);
}

static void __gen6_gt_force_wake_mt_get(struct drm_i915_private *dev_priv)
{
	u32 forcewake_ack;

		forcewake_ack = FORCEWAKE_MT_ACK;

	if (wait_for_atomic_us((I915_READ_NOTRACE(forcewake_ack) & 1) == 0, 500)) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "Force wake wait timed out\n");
	}

	I915_WRITE_NOTRACE(FORCEWAKE_MT, _MASKED_BIT_ENABLE(1));

	if (wait_for_atomic_us((I915_READ_NOTRACE(forcewake_ack) & 1), 500)) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "Force wake wait timed out\n");
	}

	__gen6_gt_wait_for_thread_c0(dev_priv);
}

/*
 * Generally this is called implicitly by the register read function. However,
 * if some sequence requires the GT to not power down then this function should
 * be called at the beginning of the sequence followed by a call to
 * gen6_gt_force_wake_put() at the end of the sequence.
 */
void gen6_gt_force_wake_get(struct drm_i915_private *dev_priv)
{
	unsigned long irqflags;

	if (dev_priv->forcewake_count++ == 0)
		dev_priv->gt.force_wake_get(dev_priv);
}

void gen6_gt_check_fifodbg(struct drm_i915_private *dev_priv)
{
	u32 gtfifodbg;
	gtfifodbg = I915_READ_NOTRACE(GTFIFODBG);
	if (WARN(gtfifodbg & GT_FIFO_CPU_ERROR_MASK,
	     "MMIO read or write has been dropped %x\n", gtfifodbg))
		I915_WRITE_NOTRACE(GTFIFODBG, GT_FIFO_CPU_ERROR_MASK);
}

static void __gen6_gt_force_wake_put(struct drm_i915_private *dev_priv)
{
	I915_WRITE_NOTRACE(FORCEWAKE, 0);
	/* The below doubles as a POSTING_READ */
	gen6_gt_check_fifodbg(dev_priv);
}

static void __gen6_gt_force_wake_mt_put(struct drm_i915_private *dev_priv)
{
	I915_WRITE_NOTRACE(FORCEWAKE_MT, _MASKED_BIT_DISABLE(1));
	/* The below doubles as a POSTING_READ */
	gen6_gt_check_fifodbg(dev_priv);
}

/*
 * see gen6_gt_force_wake_get()
 */
void gen6_gt_force_wake_put(struct drm_i915_private *dev_priv)
{
	unsigned long irqflags;

	if (--dev_priv->forcewake_count == 0)
		dev_priv->gt.force_wake_put(dev_priv);
}

static void vlv_force_wake_get(struct drm_i915_private *dev_priv)
{
	/* Already awake? */
	if ((I915_READ(0x130094) & 0xa1) == 0xa1)
		return;

	I915_WRITE_NOTRACE(FORCEWAKE_VLV, 0xffffffff);
	POSTING_READ(FORCEWAKE_VLV);

	if (wait_for_atomic_us((I915_READ_NOTRACE(FORCEWAKE_ACK_VLV) & 1), 500)) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "Force wake wait timed out\n");
	}

	__gen6_gt_wait_for_thread_c0(dev_priv);
}

static void vlv_force_wake_put(struct drm_i915_private *dev_priv)
{
	I915_WRITE_NOTRACE(FORCEWAKE_VLV, 0xffff0000);
	/* FIXME: confirm VLV behavior with Punit folks */
	POSTING_READ(FORCEWAKE_VLV);
}

void intel_gt_init(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (IS_VALLEYVIEW(dev)) {
		dev_priv->gt.force_wake_get = vlv_force_wake_get;
		dev_priv->gt.force_wake_put = vlv_force_wake_put;
	} else if (INTEL_INFO(dev)->gen >= 6) {
		dev_priv->gt.force_wake_get = __gen6_gt_force_wake_get;
		dev_priv->gt.force_wake_put = __gen6_gt_force_wake_put;

		/* IVB configs may use multi-threaded forcewake */
		if (IS_IVYBRIDGE(dev) || IS_HASWELL(dev)) {
			u32 ecobus;

			/* A small trick here - if the bios hasn't configured
			 * MT forcewake, and if the device is in RC6, then
			 * force_wake_mt_get will not wake the device and the
			 * ECOBUS read will return zero. Which will be
			 * (correctly) interpreted by the test below as MT
			 * forcewake being disabled.
			 */
			__gen6_gt_force_wake_mt_get(dev_priv);
			ecobus = I915_READ_NOTRACE(ECOBUS);
			__gen6_gt_force_wake_mt_put(dev_priv);

			if (ecobus & FORCEWAKE_MT_ENABLE) {
				fprintf(stderr, "[000000.0] [drm:%s], ",
					__func__);
				fprintf(stderr, "Using MT version of forcewake\n");
				dev_priv->gt.force_wake_get =
					__gen6_gt_force_wake_mt_get;
				dev_priv->gt.force_wake_put =
					__gen6_gt_force_wake_mt_put;
			}
		}
	}
}

