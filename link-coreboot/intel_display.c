

#define HAS_eDP (intel_pipe_has_type(crtc, INTEL_OUTPUT_EDP))

bool intel_pipe_has_type(struct drm_crtc *crtc, int type);
void intel_update_watermarks(struct drm_device *dev);
void intel_increase_pllclock(struct drm_crtc *crtc);

typedef struct {
	/* given values */
	int n;
	int m1, m2;
	int p1, p2;
	/* derived values */
	int	dot;
	int	vco;
	int	m;
	int	p;
} intel_clock_t;

typedef struct {
	int	min, max;
} intel_range_t;

typedef struct {
	int	dot_limit;
	int	p2_slow, p2_fast;
} intel_p2_t;

#define INTEL_P2_NUM		      2
typedef struct intel_limit intel_limit_t;
struct intel_limit {
	intel_range_t   dot, vco, n, m, m1, m2, p, p1;
	intel_p2_t	    p2;
	bool (* find_pll)( intel_limit_t *, struct drm_crtc *,
			int, int, intel_clock_t *, intel_clock_t *);
};

/* FDI */
#define IRONLAKE_FDI_FREQ		2700000 /* in kHz for mode->clock */
bool
intel_g4x_find_best_PLL( intel_limit_t *limit, struct drm_crtc *crtc,
			int target, int refclk, intel_clock_t *match_clock,
			intel_clock_t *best_clock);
bool
intel_find_pll_ironlake_dp( intel_limit_t *, struct drm_crtc *crtc,
			   int target, int refclk, intel_clock_t *match_clock,
			   intel_clock_t *best_clock);

inline u32 /* units of 100MHz */
intel_fdi_link_freq(struct drm_device *dev)
{
	
		return 27;
}

/* LVDS 100mhz refclk limits. */
static  intel_limit_t intel_limits_ironlake_single_lvds_100m = {
	.dot = { .min = 25000, .max = 350000 },
	.vco = { .min = 1760000, .max = 3510000 },
	.n = { .min = 1, .max = 2 },
	.m = { .min = 79, .max = 126 },
	.m1 = { .min = 12, .max = 22 },
	.m2 = { .min = 5, .max = 9 },
	.p = { .min = 28, .max = 112 },
	.p1 = { .min = 2, .max = 8 },
	.p2 = { .dot_limit = 225000,
		.p2_slow = 14, .p2_fast = 14 },
	.find_pll = intel_g4x_find_best_PLL,
};

static  intel_limit_t intel_limits_ironlake_display_port = {
	.dot = { .min = 25000, .max = 350000 },
	.vco = { .min = 1760000, .max = 3510000},
	.n = { .min = 1, .max = 2 },
	.m = { .min = 81, .max = 90 },
	.m1 = { .min = 12, .max = 22 },
	.m2 = { .min = 5, .max = 9 },
	.p = { .min = 10, .max = 20 },
	.p1 = { .min = 1, .max = 2},
	.p2 = { .dot_limit = 0,
		.p2_slow = 10, .p2_fast = 10 },
	.find_pll = intel_find_pll_ironlake_dp,
};

void intel_clock(struct drm_device *dev, int refclk, intel_clock_t *clock)
{
	
	clock->m = 5 * (clock->m1 + 2) + (clock->m2 + 2);
	clock->p = clock->p1 * clock->p2;
	clock->vco = refclk * clock->m / (clock->n + 2);
	clock->dot = clock->vco / clock->p;
}

/**
 * Returns whether any output on the specified pipe is of the specified type
 */
bool intel_pipe_has_type(struct drm_crtc *crtc, int type)
{
	struct drm_device *dev = crtc->dev;
	struct drm_mode_config *mode_config = &dev->mode_config;
	struct intel_encoder *encoder;

	list_for_each_entry(encoder, &mode_config->encoder_list, base.head)
		if (encoder->base.crtc == crtc && encoder->type == type)
			return true;

	return false;
}

#define INTELPllInvalid(s)   do { /* DRM_DEBUG(s); */ return false; } while (0)
/**
 * Returns whether the given set of divisors are valid for a given refclk with
 * the given connectors.
 */

bool intel_PLL_is_valid(struct drm_device *dev,
			        intel_limit_t *limit,
			        intel_clock_t *clock)
{
	if (clock->p1  < limit->p1.min  || limit->p1.max  < clock->p1)
		INTELPllInvalid("p1 out of range\n");
	if (clock->p   < limit->p.min   || limit->p.max   < clock->p)
		INTELPllInvalid("p out of range\n");
	if (clock->m2  < limit->m2.min  || limit->m2.max  < clock->m2)
		INTELPllInvalid("m2 out of range\n");
	if (clock->m1  < limit->m1.min  || limit->m1.max  < clock->m1)
		INTELPllInvalid("m1 out of range\n");
	if (clock->m1 <= clock->m2 && !IS_PINEVIEW(dev))
		INTELPllInvalid("m1 <= m2\n");
	if (clock->m   < limit->m.min   || limit->m.max   < clock->m)
		INTELPllInvalid("m out of range\n");
	if (clock->n   < limit->n.min   || limit->n.max   < clock->n)
		INTELPllInvalid("n out of range\n");
	if (clock->vco < limit->vco.min || limit->vco.max < clock->vco)
		INTELPllInvalid("vco out of range\n");
	/* XXX: We may need to be checking "Dot clock" depending on the multiplier,
	 * connector, etc., rather than just a single range.
	 */
	if (clock->dot < limit->dot.min || limit->dot.max < clock->dot)
		INTELPllInvalid("dot out of range\n");

	return true;
}

bool
intel_g4x_find_best_PLL( intel_limit_t *limit, struct drm_crtc *crtc,
			int target, int refclk, intel_clock_t *match_clock,
			intel_clock_t *best_clock)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	intel_clock_t clock;
	int max_n;
	bool found;
	/* approximately equals target * 0.00585 */
	int err_most = (target >> 8) + (target >> 9);
	found = false;

	if (intel_pipe_has_type(crtc, INTEL_OUTPUT_LVDS)) {
		int lvds_reg;

		if (HAS_PCH_SPLIT(dev))
			lvds_reg = PCH_LVDS;
		
		if ((I915_READ(lvds_reg) & LVDS_CLKB_POWER_MASK) ==
		    LVDS_CLKB_POWER_UP)
			clock.p2 = limit->p2.p2_fast;
		else
			clock.p2 = limit->p2.p2_slow;
	} else {
		if (target < limit->p2.dot_limit)
			clock.p2 = limit->p2.p2_slow;
		else
			clock.p2 = limit->p2.p2_fast;
	}

	memset(best_clock, 0, sizeof(*best_clock));
	max_n = limit->n.max;
	/* based on hardware requirement, prefer smaller n to precision */
	for (clock.n = limit->n.min; clock.n <= max_n; clock.n++) {
		/* based on hardware requirement, prefere larger m1,m2 */
		for (clock.m1 = limit->m1.max;
		     clock.m1 >= limit->m1.min; clock.m1--) {
			for (clock.m2 = limit->m2.max;
			     clock.m2 >= limit->m2.min; clock.m2--) {
				for (clock.p1 = limit->p1.max;
				     clock.p1 >= limit->p1.min; clock.p1--) {
					int this_err;

					intel_clock(dev, refclk, &clock);
					if (!intel_PLL_is_valid(dev, limit,
								&clock))
						continue;
					if (match_clock &&
					    clock.p != match_clock->p)
						continue;

					this_err = abs(clock.dot - target);
					if (this_err < err_most) {
						*best_clock = clock;
						err_most = this_err;
						max_n = clock.n;
						found = true;
					}
				}
			}
		}
	}
	return found;
}

bool
intel_find_pll_ironlake_dp( intel_limit_t *limit, struct drm_crtc *crtc,
			   int target, int refclk, intel_clock_t *match_clock,
			   intel_clock_t *best_clock)
{
	struct drm_device *dev = crtc->dev;
	intel_clock_t clock;

	if (target < 200000) {
		clock.n = 1;
		clock.p1 = 2;
		clock.p2 = 10;
		clock.m1 = 12;
		clock.m2 = 9;
	} else {
		clock.n = 2;
		clock.p1 = 1;
		clock.p2 = 10;
		clock.m1 = 14;
		clock.m2 = 8;
	}
	intel_clock(dev, refclk, &clock);
	memcpy(best_clock, &clock, sizeof(intel_clock_t));
	return true;
}

/**
 * intel_wait_for_vblank - wait for vblank on a given pipe
 * @dev: drm device
 * @pipe: pipe to wait for
 *
 * Wait for vblank to occur on a given pipe.  Needed for various bits of
 * mode setting code.
 */
void intel_wait_for_vblank(struct drm_device *dev, int pipe)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int pipestat_reg = PIPESTAT(pipe);

	/* Clear existing vblank status. Note this will clear any other
	 * sticky status fields as well.
	 *
	 * This races with i915_driver_irq_handler() with the result
	 * that either function could miss a vblank event.  Here it is not
	 * fatal, as we will either wait upon the next vblank interrupt or
	 * timeout.  Generally speaking intel_wait_for_vblank() is only
	 * called during modeset at which time the GPU should be idle and
	 * should *not* be performing page flips and thus not waiting on
	 * vblanks...
	 * Currently, the result of us stealing a vblank from the irq
	 * handler is that a single frame will be skipped during swapbuffers.
	 */
	I915_WRITE(pipestat_reg,
		   I915_READ(pipestat_reg) | PIPE_VBLANK_INTERRUPT_STATUS);

	/* Wait for vblank interrupt bit to set */
	if (wait_for(I915_READ(pipestat_reg) &
		     PIPE_VBLANK_INTERRUPT_STATUS,
		     50)) {
		     	fprintf(stderr, "[000000.0] [drm:%s], ",
				     __func__);
			     fprintf(stderr, "vblank wait timed out\n");
		     }
}

char *state_string(bool enabled)
{
	return enabled ? "on" : "off";
}

/* Only for pre-ILK configs */
void assert_pll(struct drm_i915_private *dev_priv,
		       enum pipe pipe, bool state)
{
	int reg;
	u32 val;
	bool cur_state;

	reg = DPLL(pipe);
	val = I915_READ(reg);
	cur_state = !!(val & DPLL_VCO_ENABLE);
	if (cur_state != state) { 
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr,
	     "PLL state assertion failure (expected %s, current %s)\n",
	     state_string(state), state_string(cur_state));
}
}
#define assert_pll_enabled(d, p) assert_pll(d, p, true)
#define assert_pll_disabled(d, p) assert_pll(d, p, false)

/* For ILK+ */
void assert_pch_pll(struct drm_i915_private *dev_priv,
			   enum pipe pipe, bool state)
{
	int reg;
	u32 val;
	bool cur_state;

	if (HAS_PCH_CPT(dev_priv->dev)) {
		u32 pch_dpll;

		pch_dpll = I915_READ(PCH_DPLL_SEL);

		/* Make sure the selected PLL is enabled to the transcoder */
		if (!((pch_dpll >> (4 * pipe)) & 8)) { 
			fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
			fprintf(stderr,
		     "transcoder %d PLL not enabled\n", pipe);
		}

		/* Convert the transcoder pipe number to a pll pipe number */
		pipe = (pch_dpll >> (4 * pipe)) & 1;
	}

	reg = PCH_DPLL(pipe);
	val = I915_READ(reg);
	cur_state = !!(val & DPLL_VCO_ENABLE);
	if (cur_state != state) { 
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr,
	     "PCH PLL state assertion failure (expected %s, current %s)\n",
	     state_string(state), state_string(cur_state));
}
}
#define assert_pch_pll_enabled(d, p) assert_pch_pll(d, p, true)
#define assert_pch_pll_disabled(d, p) assert_pch_pll(d, p, false)

void assert_fdi_tx(struct drm_i915_private *dev_priv,
			  enum pipe pipe, bool state)
{
	int reg;
	u32 val;
	bool cur_state;

	reg = FDI_TX_CTL(pipe);
	val = I915_READ(reg);
	cur_state = !!(val & FDI_TX_ENABLE);
	if (cur_state != state) { 
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr,
	     "FDI TX state assertion failure (expected %s, current %s)\n",
	     state_string(state), state_string(cur_state));
}
}
#define assert_fdi_tx_enabled(d, p) assert_fdi_tx(d, p, true)
#define assert_fdi_tx_disabled(d, p) assert_fdi_tx(d, p, false)

void assert_fdi_rx(struct drm_i915_private *dev_priv,
			  enum pipe pipe, bool state)
{
	int reg;
	u32 val;
	bool cur_state;

	reg = FDI_RX_CTL(pipe);
	val = I915_READ(reg);
	cur_state = !!(val & FDI_RX_ENABLE);
	if (cur_state != state) { 
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr,
	     "FDI RX state assertion failure (expected %s, current %s)\n",
	     state_string(state), state_string(cur_state));
}
}
#define assert_fdi_rx_enabled(d, p) assert_fdi_rx(d, p, true)
#define assert_fdi_rx_disabled(d, p) assert_fdi_rx(d, p, false)

void assert_fdi_tx_pll_enabled(struct drm_i915_private *dev_priv,
				      enum pipe pipe)
{
	int reg;
	u32 val;

	/* ILK FDI PLL is always enabled */
	if (dev_priv->info->gen == 5)
		return;

	reg = FDI_TX_CTL(pipe);
	val = I915_READ(reg);
	if (!(val & FDI_TX_PLL_ENABLE)) { 
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "FDI TX PLL assertion failure, should be active but is disabled\n");
	}
}

void assert_fdi_rx_pll_enabled(struct drm_i915_private *dev_priv,
				      enum pipe pipe)
{
	int reg;
	u32 val;

	reg = FDI_RX_CTL(pipe);
	val = I915_READ(reg);
	if (!(val & FDI_RX_PLL_ENABLE)) { 
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "FDI RX PLL assertion failure, should be active but is disabled\n");
	}
}

void assert_panel_unlocked(struct drm_i915_private *dev_priv,
				  enum pipe pipe)
{
	int pp_reg, lvds_reg;
	u32 val;
	enum pipe panel_pipe = PIPE_A;
	bool locked = true;

	{
		pp_reg = PCH_PP_CONTROL;
		lvds_reg = PCH_LVDS;
	}

	val = I915_READ(pp_reg);
	if (!(val & PANEL_POWER_ON) ||
	    ((val & PANEL_UNLOCK_REGS) == PANEL_UNLOCK_REGS))
		locked = false;

	if (I915_READ(lvds_reg) & LVDS_PIPEB_SELECT)
		panel_pipe = PIPE_B;

	if (panel_pipe == pipe && locked) { 
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr,
	     "panel assertion failure, pipe %c regs locked\n",
	     pipe_name(pipe));
}
}

void assert_pipe(struct drm_i915_private *dev_priv,
		 enum pipe pipe, bool state)
{
	int reg;
	u32 val;
	bool cur_state;

	/* if we need the pipe A quirk it must be always on */
	if (pipe == PIPE_A && dev_priv->quirks & QUIRK_PIPEA_FORCE)
		state = true;

	reg = PIPECONF(pipe);
	val = I915_READ(reg);
	cur_state = !!(val & PIPECONF_ENABLE);
	if (cur_state != state) { 
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr,
	     "pipe %c assertion failure (expected %s, current %s)\n",
	     pipe_name(pipe), state_string(state), state_string(cur_state));
}
}

void assert_plane(struct drm_i915_private *dev_priv,
			 enum plane plane, bool state)
{
	int reg;
	u32 val;
	bool cur_state;

	reg = DSPCNTR(plane);
	val = I915_READ(reg);
	cur_state = !!(val & DISPLAY_PLANE_ENABLE);
	if (cur_state != state) { 
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr,
	     "plane %c assertion failure (expected %s, current %s)\n",
	     plane_name(plane), state_string(state), state_string(cur_state));
}
}

#define assert_plane_enabled(d, p) assert_plane(d, p, true)
#define assert_plane_disabled(d, p) assert_plane(d, p, false)

void assert_planes_disabled(struct drm_i915_private *dev_priv,
				   enum pipe pipe)
{
	int reg, i;
	u32 val;
	int cur_pipe;

	/* Planes are fixed to pipes on ILK+ */
	{
		reg = DSPCNTR(pipe);
		val = I915_READ(reg);
		if ((val & DISPLAY_PLANE_ENABLE)) { 
			fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
			fprintf(stderr,
		     "plane %c assertion failure, should be disabled but not\n",
		     plane_name(pipe));
}
		return;
	}

	/* Need to check both planes against the pipe */
	for (i = 0; i < 2; i++) {
		reg = DSPCNTR(i);
		val = I915_READ(reg);
		cur_pipe = (val & DISPPLANE_SEL_PIPE_MASK) >>
			DISPPLANE_SEL_PIPE_SHIFT;
		if ((val & DISPLAY_PLANE_ENABLE) && pipe == cur_pipe) { 
			fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
			fprintf(stderr,
		     "plane %c assertion failure, should be off on pipe %c but is still active\n",
		     plane_name(i), pipe_name(pipe));
}
	}
}

void assert_pch_refclk_enabled(struct drm_i915_private *dev_priv)
{
	u32 val;
	bool enabled;

	val = I915_READ(PCH_DREF_CONTROL);
	enabled = !!(val & (DREF_SSC_SOURCE_MASK | DREF_NONSPREAD_SOURCE_MASK |
			    DREF_SUPERSPREAD_SOURCE_MASK));
	if (!enabled) { 
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "PCH refclk assertion failure, should be active but is disabled\n");
	}
}

bool dp_pipe_enabled(struct drm_i915_private *dev_priv,
			    enum pipe pipe, u32 port_sel, u32 val)
{
	if ((val & DP_PORT_EN) == 0)
		return false;

	if (HAS_PCH_CPT(dev_priv->dev)) {
		u32	trans_dp_ctl_reg = TRANS_DP_CTL(pipe);
		u32	trans_dp_ctl = I915_READ(trans_dp_ctl_reg);
		if ((trans_dp_ctl & TRANS_DP_PORT_SEL_MASK) != port_sel)
			return false;
	} else {
		if ((val & DP_PIPE_MASK) != (pipe << 30))
			return false;
	}
	return true;
}

/**
 * intel_enable_pch_pll - enable PCH PLL
 * @dev_priv: i915 private structure
 * @pipe: pipe PLL to enable
 *
 * The PCH PLL needs to be enabled before the PCH transcoder, since it
 * drives the transcoder clock.
 */
void intel_enable_pch_pll(struct drm_i915_private *dev_priv,
				 enum pipe pipe)
{
	int reg;
	u32 val;

	if (pipe > 1)
		return;

	/* PCH only available on ILK+ */
	BUG_ON(dev_priv->info->gen < 5);

	/* PCH refclock must be enabled first */
	assert_pch_refclk_enabled(dev_priv);

	reg = PCH_DPLL(pipe);
	val = I915_READ(reg);
	val |= DPLL_VCO_ENABLE;
	I915_WRITE(reg, val);
	POSTING_READ(reg);
	udelay(200);
}

void intel_enable_transcoder(struct drm_i915_private *dev_priv,
				    enum pipe pipe)
{
	int reg;
	u32 val, pipeconf_val;
	struct drm_crtc *crtc = dev_priv->pipe_to_crtc_mapping[pipe];

	/* PCH only available on ILK+ */
	BUG_ON(dev_priv->info->gen < 5);

	/* Make sure PCH DPLL is enabled */
	assert_pch_pll_enabled(dev_priv, pipe);

	/* FDI must be feeding us bits for PCH ports */
	assert_fdi_tx_enabled(dev_priv, pipe);
	assert_fdi_rx_enabled(dev_priv, pipe);

	reg = TRANSCONF(pipe);
	val = I915_READ(reg);
	pipeconf_val = I915_READ(PIPECONF(pipe));

	val &= ~TRANS_INTERLACE_MASK;
	if ((pipeconf_val & PIPECONF_INTERLACE_MASK) == PIPECONF_INTERLACED_ILK)
		if (HAS_PCH_IBX(dev_priv->dev) &&
		    intel_pipe_has_type(crtc, INTEL_OUTPUT_SDVO))
			val |= TRANS_LEGACY_INTERLACED_ILK;
		else
			val |= TRANS_INTERLACED;
	else
		val |= TRANS_PROGRESSIVE;

	I915_WRITE(reg, val | TRANS_ENABLE);
	if (wait_for(I915_READ(reg) & TRANS_STATE_ENABLE, 100)) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "failed to enable transcoder %d\n", pipe);
	}
}

/**
 * intel_enable_pipe - enable a pipe, asserting requirements
 * @dev_priv: i915 private structure
 * @pipe: pipe to enable
 * @pch_port: on ILK+, is this pipe driving a PCH port or not
 *
 * Enable @pipe, making sure that various hardware specific requirements
 * are met, if applicable, e.g. PLL enabled, LVDS pairs enabled, etc.
 *
 * @pipe should be %PIPE_A or %PIPE_B.
 *
 * Will wait until the pipe is actually running (i.e. first vblank) before
 * returning.
 */
void intel_enable_pipe(struct drm_i915_private *dev_priv, enum pipe pipe,
			      bool pch_port)
{
	int reg;
	u32 val;

	/*
	 * A pipe without a PLL won't actually be able to drive bits from
	 * a plane.  On ILK+ the pipe PLLs are integrated, so we don't
	 * need the check.
	 */
	if (!HAS_PCH_SPLIT(dev_priv->dev))
		assert_pll_enabled(dev_priv, pipe);
	else {
		if (pch_port) {
			/* if driving the PCH, we need FDI enabled */
			assert_fdi_rx_pll_enabled(dev_priv, pipe);
			assert_fdi_tx_pll_enabled(dev_priv, pipe);
		}
		/* FIXME: assert CPU port conditions for SNB+ */
	}

	reg = PIPECONF(pipe);
	val = I915_READ(reg);
	if (val & PIPECONF_ENABLE)
		return;

	I915_WRITE(reg, val | PIPECONF_ENABLE);
	intel_wait_for_vblank(dev_priv->dev, pipe);
}

/*
 * Plane regs are double buffered, going from enabled->disabled needs a
 * trigger in order to latch.  The display address reg provides this.
 */
void intel_flush_display_plane(struct drm_i915_private *dev_priv,
				      enum plane plane)
{
	I915_WRITE(DSPADDR(plane), I915_READ(DSPADDR(plane)));
	I915_WRITE(DSPSURF(plane), I915_READ(DSPSURF(plane)));
}

/**
 * intel_enable_plane - enable a display plane on a given pipe
 * @dev_priv: i915 private structure
 * @plane: plane to enable
 * @pipe: pipe being fed
 *
 * Enable @plane on @pipe, making sure that @pipe is running first.
 */
void intel_enable_plane(struct drm_i915_private *dev_priv,
			       enum plane plane, enum pipe pipe)
{
	int reg;
	u32 val;

	/* If the pipe isn't enabled, we can't pump pixels and may hang */
	assert_pipe_enabled(dev_priv, pipe);

	reg = DSPCNTR(plane);
	val = I915_READ(reg);
	if (val & DISPLAY_PLANE_ENABLE)
		return;

	I915_WRITE(reg, val | DISPLAY_PLANE_ENABLE);
	intel_flush_display_plane(dev_priv, plane);
	intel_wait_for_vblank(dev_priv->dev, pipe);
}

int ironlake_update_plane(struct drm_crtc *crtc,
				 struct drm_framebuffer *fb, int x, int y)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	struct intel_framebuffer *intel_fb;
	struct drm_i915_gem_object *obj;
	int plane = intel_crtc->plane;
	unsigned long Start, Offset;
	u32 dspcntr;
	u32 reg;

	switch (plane) {
	case 0:
	case 1:
	case 2:
		break;
	default:
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "Can't update plane %d in SAREA\n", plane);
		return -EINVAL;
	}

	intel_fb = to_intel_framebuffer(fb);
	obj = intel_fb->obj;

	reg = DSPCNTR(plane);
	dspcntr = I915_READ(reg);
	/* Mask out pixel format bits in case we change it */
	dspcntr &= ~DISPPLANE_PIXFORMAT_MASK;
	switch (fb->bits_per_pixel) {
	case 8:
		dspcntr |= DISPPLANE_8BPP;
		break;
	case 16:
		if (fb->depth != 16)
			return -EINVAL;

		dspcntr |= DISPPLANE_16BPP;
		break;
	case 24:
	case 32:
		if (fb->depth == 24)
			dspcntr |= DISPPLANE_32BPP_NO_ALPHA;
		else if (fb->depth == 30)
			dspcntr |= DISPPLANE_32BPP_30BIT_NO_ALPHA;
		else
			return -EINVAL;
		break;
	default:
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "Unknown color depth %d\n", fb->bits_per_pixel);
		return -EINVAL;
	}

	/* must disable */
	dspcntr |= DISPPLANE_TRICKLE_FEED_DISABLE;

	I915_WRITE(reg, dspcntr);

	Start = obj->gtt_offset;
	Offset = y * fb->pitches[0] + x * (fb->bits_per_pixel / 8);

	fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
	fprintf(stderr, "Writing base %08lX %08lX %d %d %d\n",
		      Start, Offset, x, y, fb->pitches[0]);
	I915_WRITE(DSPSTRIDE(plane), fb->pitches[0]);
	I915_WRITE(DSPSURF(plane), Start);
	I915_WRITE(DSPTILEOFF(plane), (y << 16) | x);
	I915_WRITE(DSPADDR(plane), Offset);
	POSTING_READ(reg);

	return 0;
}

/* Assume fb object is pinned & idle & fenced and just update base pointers */
int
intel_pipe_set_base_atomic(struct drm_crtc *crtc, struct drm_framebuffer *fb,
			   int x, int y, enum mode_set_atomic state)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	int ret;

	ret = dev_priv->display.update_plane(crtc, fb, x, y);
	if (ret)
		return ret;

	intel_increase_pllclock(crtc);

	return 0;
}

int
intel_pipe_set_base(struct drm_crtc *crtc, int x, int y,
		    struct drm_framebuffer *old_fb)
{
	struct drm_device *dev = crtc->dev;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	int ret;

	/* no fb bound */
	if (!crtc->fb) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "No FB bound\n");
		return 0;
	}

	switch (intel_crtc->plane) {
	case 0:
	case 1:
		break;
	case 2:
		if (IS_IVYBRIDGE(dev))
			break;
		/* fall through otherwise */
	default:
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "no plane for crtc\n");
		return -EINVAL;
	}

	ret = 0;
	if (ret != 0) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "pin & fence failed\n");
		return ret;
	}

	if (old_fb) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr,
			"Warning: somebody tried to call i9xx_crtc_disable\n");
	}

	ret = intel_pipe_set_base_atomic(crtc, crtc->fb, x, y,
					 LEAVE_ATOMIC_MODE_SET);
	if (ret) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "failed to update base address\n");
		return ret;
	}

	if (intel_crtc->pipe) {
	} else {
	}

	return 0;
}

void ironlake_set_pll_edp(struct drm_crtc *crtc, int clock)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 dpa_ctl;

	fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
	fprintf(stderr, "eDP PLL enable for clock %d\n", clock);
	dpa_ctl = I915_READ(DP_A);
	dpa_ctl &= ~DP_PLL_FREQ_MASK;

	if (clock < 200000) {
		u32 temp;
		dpa_ctl |= DP_PLL_FREQ_160MHZ;
		/* workaround for 160Mhz:
		   1) program 0x4600c bits 15:0 = 0x8124
		   2) program 0x46010 bit 0 = 1
		   3) program 0x46034 bit 24 = 1
		   4) program 0x64000 bit 14 = 1
		   */
		temp = I915_READ(0x4600c);
		temp &= 0xffff0000;
		I915_WRITE(0x4600c, temp | 0x8124);

		temp = I915_READ(0x46010);
		I915_WRITE(0x46010, temp | 1);

		temp = I915_READ(0x46034);
		I915_WRITE(0x46034, temp | (1 << 24));
	} else {
		dpa_ctl |= DP_PLL_FREQ_270MHZ;
	}
	I915_WRITE(DP_A, dpa_ctl);

	POSTING_READ(DP_A);
	udelay(500);
}

void intel_fdi_normal_train(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	int pipe = intel_crtc->pipe;
	u32 reg, temp;

	/* enable normal train */
	reg = FDI_TX_CTL(pipe);
	temp = I915_READ(reg);
	if (IS_IVYBRIDGE(dev)) {
		temp &= ~FDI_LINK_TRAIN_NONE_IVB;
		temp |= FDI_LINK_TRAIN_NONE_IVB | FDI_TX_ENHANCE_FRAME_ENABLE;
	} else {
		temp &= ~FDI_LINK_TRAIN_NONE;
		temp |= FDI_LINK_TRAIN_NONE | FDI_TX_ENHANCE_FRAME_ENABLE;
	}
	I915_WRITE(reg, temp);

	reg = FDI_RX_CTL(pipe);
	temp = I915_READ(reg);
	if (HAS_PCH_CPT(dev)) {
		temp &= ~FDI_LINK_TRAIN_PATTERN_MASK_CPT;
		temp |= FDI_LINK_TRAIN_NORMAL_CPT;
	} else {
		temp &= ~FDI_LINK_TRAIN_NONE;
		temp |= FDI_LINK_TRAIN_NONE;
	}
	I915_WRITE(reg, temp | FDI_RX_ENHANCE_FRAME_ENABLE);

	/* wait one idle pattern time */
	POSTING_READ(reg);
	udelay(1000);

	/* IVB wants error correction enabled */
	if (IS_IVYBRIDGE(dev))
		I915_WRITE(reg, I915_READ(reg) | FDI_FS_ERRC_ENABLE |
			   FDI_FE_ERRC_ENABLE);
}

void cpt_phase_pointer_enable(struct drm_device *dev, int pipe)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 flags = I915_READ(SOUTH_CHICKEN1);

	flags |= FDI_PHASE_SYNC_OVR(pipe);
	I915_WRITE(SOUTH_CHICKEN1, flags); /* once to unlock... */
	flags |= FDI_PHASE_SYNC_EN(pipe);
	I915_WRITE(SOUTH_CHICKEN1, flags); /* then again to enable */
	POSTING_READ(SOUTH_CHICKEN1);
}

/* The FDI link training functions for ILK/Ibexpeak. */
void ironlake_fdi_link_train(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	int pipe = intel_crtc->pipe;
	int plane = intel_crtc->plane;
	u32 reg, temp, tries;

	/* FDI needs bits from pipe & plane first */
	assert_pipe_enabled(dev_priv, pipe);
	assert_plane_enabled(dev_priv, plane);

	/* Train 1: umask FDI RX Interrupt symbol_lock and bit_lock bit
	   for train result */
	reg = FDI_RX_IMR(pipe);
	temp = I915_READ(reg);
	temp &= ~FDI_RX_SYMBOL_LOCK;
	temp &= ~FDI_RX_BIT_LOCK;
	I915_WRITE(reg, temp);
	I915_READ(reg);
	udelay(150);

	/* enable CPU FDI TX and PCH FDI RX */
	reg = FDI_TX_CTL(pipe);
	temp = I915_READ(reg);
	temp &= ~(7 << 19);
	temp |= (intel_crtc->fdi_lanes - 1) << 19;
	temp &= ~FDI_LINK_TRAIN_NONE;
	temp |= FDI_LINK_TRAIN_PATTERN_1;
	I915_WRITE(reg, temp | FDI_TX_ENABLE);

	reg = FDI_RX_CTL(pipe);
	temp = I915_READ(reg);
	temp &= ~FDI_LINK_TRAIN_NONE;
	temp |= FDI_LINK_TRAIN_PATTERN_1;
	I915_WRITE(reg, temp | FDI_RX_ENABLE);

	POSTING_READ(reg);
	udelay(150);

	reg = FDI_RX_IIR(pipe);
	for (tries = 0; tries < 5; tries++) {
		temp = I915_READ(reg);
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "FDI_RX_IIR 0x%x\n", temp);

		if ((temp & FDI_RX_BIT_LOCK)) {
			fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
			fprintf(stderr, "FDI train 1 done.\n");
			I915_WRITE(reg, temp | FDI_RX_BIT_LOCK);
			break;
		}
	}
	if (tries == 5) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "FDI train 1 fail!\n");
	}

	/* Train 2 */
	reg = FDI_TX_CTL(pipe);
	temp = I915_READ(reg);
	temp &= ~FDI_LINK_TRAIN_NONE;
	temp |= FDI_LINK_TRAIN_PATTERN_2;
	I915_WRITE(reg, temp);

	reg = FDI_RX_CTL(pipe);
	temp = I915_READ(reg);
	temp &= ~FDI_LINK_TRAIN_NONE;
	temp |= FDI_LINK_TRAIN_PATTERN_2;
	I915_WRITE(reg, temp);

	POSTING_READ(reg);
	udelay(150);

	reg = FDI_RX_IIR(pipe);
	for (tries = 0; tries < 5; tries++) {
		temp = I915_READ(reg);
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "FDI_RX_IIR 0x%x\n", temp);

		if (temp & FDI_RX_SYMBOL_LOCK) {
			I915_WRITE(reg, temp | FDI_RX_SYMBOL_LOCK);
			fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
			fprintf(stderr, "FDI train 2 done.\n");
			break;
		}
	}
	if (tries == 5) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "FDI train 2 fail!\n");
	}

	fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
	fprintf(stderr, "FDI train done\n");

}

static  int snb_b_fdi_train_param[] = {
	FDI_LINK_TRAIN_400MV_0DB_SNB_B,
	FDI_LINK_TRAIN_400MV_6DB_SNB_B,
	FDI_LINK_TRAIN_600MV_3_5DB_SNB_B,
	FDI_LINK_TRAIN_800MV_0DB_SNB_B,
};

/* The FDI link training functions for SNB/Cougarpoint. */
void gen6_fdi_link_train(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	int pipe = intel_crtc->pipe;
	u32 reg, temp, i, retry;

	/* Train 1: umask FDI RX Interrupt symbol_lock and bit_lock bit
	   for train result */
	reg = FDI_RX_IMR(pipe);
	temp = I915_READ(reg);
	temp &= ~FDI_RX_SYMBOL_LOCK;
	temp &= ~FDI_RX_BIT_LOCK;
	I915_WRITE(reg, temp);

	POSTING_READ(reg);
	udelay(150);

	/* enable CPU FDI TX and PCH FDI RX */
	reg = FDI_TX_CTL(pipe);
	temp = I915_READ(reg);
	temp &= ~(7 << 19);
	temp |= (intel_crtc->fdi_lanes - 1) << 19;
	temp &= ~FDI_LINK_TRAIN_NONE;
	temp |= FDI_LINK_TRAIN_PATTERN_1;
	temp &= ~FDI_LINK_TRAIN_VOL_EMP_MASK;
	/* SNB-B */
	temp |= FDI_LINK_TRAIN_400MV_0DB_SNB_B;
	I915_WRITE(reg, temp | FDI_TX_ENABLE);

	reg = FDI_RX_CTL(pipe);
	temp = I915_READ(reg);
	if (HAS_PCH_CPT(dev)) {
		temp &= ~FDI_LINK_TRAIN_PATTERN_MASK_CPT;
		temp |= FDI_LINK_TRAIN_PATTERN_1_CPT;
	} else {
		temp &= ~FDI_LINK_TRAIN_NONE;
		temp |= FDI_LINK_TRAIN_PATTERN_1;
	}
	I915_WRITE(reg, temp | FDI_RX_ENABLE);

	POSTING_READ(reg);
	udelay(150);

	if (HAS_PCH_CPT(dev))
		cpt_phase_pointer_enable(dev, pipe);

	for (i = 0; i < 4; i++) {
		reg = FDI_TX_CTL(pipe);
		temp = I915_READ(reg);
		temp &= ~FDI_LINK_TRAIN_VOL_EMP_MASK;
		temp |= snb_b_fdi_train_param[i];
		I915_WRITE(reg, temp);

		POSTING_READ(reg);
		udelay(500);

		for (retry = 0; retry < 5; retry++) {
			reg = FDI_RX_IIR(pipe);
			temp = I915_READ(reg);
			fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
			fprintf(stderr, "FDI_RX_IIR 0x%x\n", temp);
			if (temp & FDI_RX_BIT_LOCK) {
				I915_WRITE(reg, temp | FDI_RX_BIT_LOCK);
				fprintf(stderr, "[000000.0] [drm:%s], ",
					__func__);
				fprintf(stderr, "FDI train 1 done.\n");
				break;
			}
			udelay(50);
		}
		if (retry < 5)
			break;
	}
	if (i == 4) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "FDI train 1 fail!\n");
	}

	/* Train 2 */
	reg = FDI_TX_CTL(pipe);
	temp = I915_READ(reg);
	temp &= ~FDI_LINK_TRAIN_NONE;
	temp |= FDI_LINK_TRAIN_PATTERN_2;
	if (IS_GEN6(dev)) {
		temp &= ~FDI_LINK_TRAIN_VOL_EMP_MASK;
		/* SNB-B */
		temp |= FDI_LINK_TRAIN_400MV_0DB_SNB_B;
	}
	I915_WRITE(reg, temp);

	reg = FDI_RX_CTL(pipe);
	temp = I915_READ(reg);
	if (HAS_PCH_CPT(dev)) {
		temp &= ~FDI_LINK_TRAIN_PATTERN_MASK_CPT;
		temp |= FDI_LINK_TRAIN_PATTERN_2_CPT;
	} else {
		temp &= ~FDI_LINK_TRAIN_NONE;
		temp |= FDI_LINK_TRAIN_PATTERN_2;
	}
	I915_WRITE(reg, temp);

	POSTING_READ(reg);
	udelay(150);

	for (i = 0; i < 4; i++) {
		reg = FDI_TX_CTL(pipe);
		temp = I915_READ(reg);
		temp &= ~FDI_LINK_TRAIN_VOL_EMP_MASK;
		temp |= snb_b_fdi_train_param[i];
		I915_WRITE(reg, temp);

		POSTING_READ(reg);
		udelay(500);

		for (retry = 0; retry < 5; retry++) {
			reg = FDI_RX_IIR(pipe);
			temp = I915_READ(reg);
			fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
			fprintf(stderr, "FDI_RX_IIR 0x%x\n", temp);
			if (temp & FDI_RX_SYMBOL_LOCK) {
				I915_WRITE(reg, temp | FDI_RX_SYMBOL_LOCK);
				fprintf(stderr, "[000000.0] [drm:%s], ",
					__func__);
				fprintf(stderr, "FDI train 2 done.\n");
				break;
			}
			udelay(50);
		}
		if (retry < 5)
			break;
	}
	if (i == 4) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "FDI train 2 fail!\n");
	}

	fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
	fprintf(stderr, "FDI train done.\n");
}

/* Manual link training for Ivy Bridge A0 parts */
void ivb_manual_fdi_link_train(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	int pipe = intel_crtc->pipe;
	u32 reg, temp, i;

	/* Train 1: umask FDI RX Interrupt symbol_lock and bit_lock bit
	   for train result */
	reg = FDI_RX_IMR(pipe);
	temp = I915_READ(reg);
	temp &= ~FDI_RX_SYMBOL_LOCK;
	temp &= ~FDI_RX_BIT_LOCK;
	I915_WRITE(reg, temp);

	POSTING_READ(reg);
	udelay(150);

	/* enable CPU FDI TX and PCH FDI RX */
	reg = FDI_TX_CTL(pipe);
	temp = I915_READ(reg);
	temp &= ~(7 << 19);
	temp |= (intel_crtc->fdi_lanes - 1) << 19;
	temp &= ~(FDI_LINK_TRAIN_AUTO | FDI_LINK_TRAIN_NONE_IVB);
	temp |= FDI_LINK_TRAIN_PATTERN_1_IVB;
	temp &= ~FDI_LINK_TRAIN_VOL_EMP_MASK;
	temp |= FDI_LINK_TRAIN_400MV_0DB_SNB_B;
	temp |= FDI_COMPOSITE_SYNC;
	I915_WRITE(reg, temp | FDI_TX_ENABLE);

	reg = FDI_RX_CTL(pipe);
	temp = I915_READ(reg);
	temp &= ~FDI_LINK_TRAIN_AUTO;
	temp &= ~FDI_LINK_TRAIN_PATTERN_MASK_CPT;
	temp |= FDI_LINK_TRAIN_PATTERN_1_CPT;
	temp |= FDI_COMPOSITE_SYNC;
	I915_WRITE(reg, temp | FDI_RX_ENABLE);

	POSTING_READ(reg);
	udelay(150);

	if (HAS_PCH_CPT(dev))
		cpt_phase_pointer_enable(dev, pipe);

	for (i = 0; i < 4; i++) {
		reg = FDI_TX_CTL(pipe);
		temp = I915_READ(reg);
		temp &= ~FDI_LINK_TRAIN_VOL_EMP_MASK;
		temp |= snb_b_fdi_train_param[i];
		I915_WRITE(reg, temp);

		POSTING_READ(reg);
		udelay(500);

		reg = FDI_RX_IIR(pipe);
		temp = I915_READ(reg);
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "FDI_RX_IIR 0x%x\n", temp);

		if (temp & FDI_RX_BIT_LOCK ||
		    (I915_READ(reg) & FDI_RX_BIT_LOCK)) {
			I915_WRITE(reg, temp | FDI_RX_BIT_LOCK);
			fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
			fprintf(stderr, "FDI train 1 done.\n");
			break;
		}
	}
	if (i == 4) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "FDI train 1 fail!\n");
	}

	/* Train 2 */
	reg = FDI_TX_CTL(pipe);
	temp = I915_READ(reg);
	temp &= ~FDI_LINK_TRAIN_NONE_IVB;
	temp |= FDI_LINK_TRAIN_PATTERN_2_IVB;
	temp &= ~FDI_LINK_TRAIN_VOL_EMP_MASK;
	temp |= FDI_LINK_TRAIN_400MV_0DB_SNB_B;
	I915_WRITE(reg, temp);

	reg = FDI_RX_CTL(pipe);
	temp = I915_READ(reg);
	temp &= ~FDI_LINK_TRAIN_PATTERN_MASK_CPT;
	temp |= FDI_LINK_TRAIN_PATTERN_2_CPT;
	I915_WRITE(reg, temp);

	POSTING_READ(reg);
	udelay(150);

	for (i = 0; i < 4; i++) {
		reg = FDI_TX_CTL(pipe);
		temp = I915_READ(reg);
		temp &= ~FDI_LINK_TRAIN_VOL_EMP_MASK;
		temp |= snb_b_fdi_train_param[i];
		I915_WRITE(reg, temp);

		POSTING_READ(reg);
		udelay(500);

		reg = FDI_RX_IIR(pipe);
		temp = I915_READ(reg);
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "FDI_RX_IIR 0x%x\n", temp);

		if (temp & FDI_RX_SYMBOL_LOCK) {
			I915_WRITE(reg, temp | FDI_RX_SYMBOL_LOCK);
			fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
			fprintf(stderr, "FDI train 2 done.\n");
			break;
		}
	}
	if (i == 4) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "FDI train 2 fail!\n");
	}

	fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
	fprintf(stderr, "FDI train done.\n");
}

void ironlake_fdi_pll_enable(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	int pipe = intel_crtc->pipe;
	u32 reg, temp;

	/* Write the TU size bits so error detection works */
	I915_WRITE(FDI_RX_TUSIZE1(pipe),
		   I915_READ(PIPE_DATA_M1(pipe)) & TU_SIZE_MASK);

	/* enable PCH FDI RX PLL, wait warmup plus DMI latency */
	reg = FDI_RX_CTL(pipe);
	temp = I915_READ(reg);
	temp &= ~((0x7 << 19) | (0x7 << 16));
	temp |= (intel_crtc->fdi_lanes - 1) << 19;
	temp |= (I915_READ(PIPECONF(pipe)) & PIPE_BPC_MASK) << 11;
	I915_WRITE(reg, temp | FDI_RX_PLL_ENABLE);

	POSTING_READ(reg);
	udelay(200);

	/* Switch from Rawclk to PCDclk */
	temp = I915_READ(reg);
	I915_WRITE(reg, temp | FDI_PCDCLK);

	POSTING_READ(reg);
	udelay(200);

	/* Enable CPU FDI TX PLL, always on for Ironlake */
	reg = FDI_TX_CTL(pipe);
	temp = I915_READ(reg);
	if ((temp & FDI_TX_PLL_ENABLE) == 0) {
		I915_WRITE(reg, temp | FDI_TX_PLL_ENABLE);

		POSTING_READ(reg);
		udelay(100);
	}
}

void cpt_phase_pointer_disable(struct drm_device *dev, int pipe)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 flags = I915_READ(SOUTH_CHICKEN1);

	flags &= ~(FDI_PHASE_SYNC_EN(pipe));
	I915_WRITE(SOUTH_CHICKEN1, flags); /* once to disable... */
	flags &= ~(FDI_PHASE_SYNC_OVR(pipe));
	I915_WRITE(SOUTH_CHICKEN1, flags); /* then again to lock */
	POSTING_READ(SOUTH_CHICKEN1);
}
void ironlake_fdi_disable(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	int pipe = intel_crtc->pipe;
	u32 reg, temp;

	/* disable CPU FDI tx and PCH FDI rx */
	reg = FDI_TX_CTL(pipe);
	temp = I915_READ(reg);
	I915_WRITE(reg, temp & ~FDI_TX_ENABLE);
	POSTING_READ(reg);

	reg = FDI_RX_CTL(pipe);
	temp = I915_READ(reg);
	temp &= ~(0x7 << 16);
	temp |= (I915_READ(PIPECONF(pipe)) & PIPE_BPC_MASK) << 11;
	I915_WRITE(reg, temp & ~FDI_RX_ENABLE);

	POSTING_READ(reg);
	udelay(100);

	/* Ironlake workaround, disable clock pointer after downing FDI */
	if (HAS_PCH_CPT(dev)) {
		cpt_phase_pointer_disable(dev, pipe);
	}

	/* still set train pattern 1 */
	reg = FDI_TX_CTL(pipe);
	temp = I915_READ(reg);
	temp &= ~FDI_LINK_TRAIN_NONE;
	temp |= FDI_LINK_TRAIN_PATTERN_1;
	I915_WRITE(reg, temp);

	reg = FDI_RX_CTL(pipe);
	temp = I915_READ(reg);
	if (HAS_PCH_CPT(dev)) {
		temp &= ~FDI_LINK_TRAIN_PATTERN_MASK_CPT;
		temp |= FDI_LINK_TRAIN_PATTERN_1_CPT;
	} else {
		temp &= ~FDI_LINK_TRAIN_NONE;
		temp |= FDI_LINK_TRAIN_PATTERN_1;
	}
	/* BPC in FDI rx is consistent with that in PIPECONF */
	temp &= ~(0x07 << 16);
	temp |= (I915_READ(PIPECONF(pipe)) & PIPE_BPC_MASK) << 11;
	I915_WRITE(reg, temp);

	POSTING_READ(reg);
	udelay(100);
}

/*
 * Enable PCH resources required for PCH ports:
 *   - PCH PLLs
 *   - FDI training & RX/TX
 *   - update transcoder timings
 *   - DP transcoding bits
 *   - transcoder
 */
void ironlake_pch_enable(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	int pipe = intel_crtc->pipe;
	u32 reg, temp, transc_sel;

	/* For PCH output, training FDI link */
	dev_priv->display.fdi_link_train(crtc);

	intel_enable_pch_pll(dev_priv, pipe);

	if (HAS_PCH_CPT(dev)) {
		transc_sel = intel_crtc->use_pll_a ? TRANSC_DPLLA_SEL :
			TRANSC_DPLLB_SEL;

		/* Be sure PCH DPLL SEL is set */
		temp = I915_READ(PCH_DPLL_SEL);
		if (pipe == 0) {
			temp &= ~(TRANSA_DPLLB_SEL);
			temp |= (TRANSA_DPLL_ENABLE | TRANSA_DPLLA_SEL);
		} else if (pipe == 1) {
			temp &= ~(TRANSB_DPLLB_SEL);
			temp |= (TRANSB_DPLL_ENABLE | TRANSB_DPLLB_SEL);
		} else if (pipe == 2) {
			temp &= ~(TRANSC_DPLLB_SEL);
			temp |= (TRANSC_DPLL_ENABLE | transc_sel);
		}
		I915_WRITE(PCH_DPLL_SEL, temp);
	}

	/* set transcoder timing, panel must allow it */
	assert_panel_unlocked(dev_priv, pipe);
	I915_WRITE(TRANS_HTOTAL(pipe), I915_READ(HTOTAL(pipe)));
	I915_WRITE(TRANS_HBLANK(pipe), I915_READ(HBLANK(pipe)));
	I915_WRITE(TRANS_HSYNC(pipe),  I915_READ(HSYNC(pipe)));

	I915_WRITE(TRANS_VTOTAL(pipe), I915_READ(VTOTAL(pipe)));
	I915_WRITE(TRANS_VBLANK(pipe), I915_READ(VBLANK(pipe)));
	I915_WRITE(TRANS_VSYNC(pipe),  I915_READ(VSYNC(pipe)));
	I915_WRITE(TRANS_VSYNCSHIFT(pipe),  I915_READ(VSYNCSHIFT(pipe)));

	intel_fdi_normal_train(crtc);

	/* For PCH DP, enable TRANS_DP_CTL */
	if (HAS_PCH_CPT(dev) &&
	    (intel_pipe_has_type(crtc, INTEL_OUTPUT_DISPLAYPORT) ||
	     intel_pipe_has_type(crtc, INTEL_OUTPUT_EDP))) {
		u32 bpc = (I915_READ(PIPECONF(pipe)) & PIPE_BPC_MASK) >> 5;
		reg = TRANS_DP_CTL(pipe);
		temp = I915_READ(reg);
		temp &= ~(TRANS_DP_PORT_SEL_MASK |
			  TRANS_DP_SYNC_MASK |
			  TRANS_DP_BPC_MASK);
		temp |= (TRANS_DP_OUTPUT_ENABLE |
			 TRANS_DP_ENH_FRAMING);
		temp |= bpc << 9; /* same format but at 11:9 */

		if (crtc->mode.flags & DRM_MODE_FLAG_PHSYNC)
			temp |= TRANS_DP_HSYNC_ACTIVE_HIGH;
		if (crtc->mode.flags & DRM_MODE_FLAG_PVSYNC)
			temp |= TRANS_DP_VSYNC_ACTIVE_HIGH;

		switch (intel_trans_dp_port_sel(crtc)) {
		case PCH_DP_B:
			temp |= TRANS_DP_PORT_SEL_B;
			break;
		case PCH_DP_C:
			temp |= TRANS_DP_PORT_SEL_C;
			break;
		case PCH_DP_D:
			temp |= TRANS_DP_PORT_SEL_D;
			break;
		default:
			fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
			fprintf(stderr, "Wrong PCH DP port return. Guess port B\n");
			temp |= TRANS_DP_PORT_SEL_B;
			break;
		}

		I915_WRITE(reg, temp);
	}

	intel_enable_transcoder(dev_priv, pipe);
}

void intel_cpt_verify_modeset(struct drm_device *dev, int pipe)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int dslreg = PIPEDSL(pipe), tc2reg = TRANS_CHICKEN2(pipe);
	u32 temp;

	temp = I915_READ(dslreg);
	udelay(500);
	if (wait_for(I915_READ(dslreg) != temp, 5)) {
		/* Without this, mode sets may fail silently on FDI */
		I915_WRITE(tc2reg, TRANS_AUTOTRAIN_GEN_STALL_DIS);
		udelay(250);
		I915_WRITE(tc2reg, 0);
		if (wait_for(I915_READ(dslreg) != temp, 5)) {
			fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
			fprintf(stderr, "mode set failed: pipe %d stuck\n", pipe);
		}
	}
}

bool intel_crtc_mode_fixup(struct drm_crtc *crtc,
				  struct drm_display_mode *mode,
				  struct drm_display_mode *adjusted_mode)
{
	struct drm_device *dev = crtc->dev;

	{
		/* FDI link clock is fixed at 2.7G */
		if (mode->clock * 3 > IRONLAKE_FDI_FREQ * 4)
			return false;
	}

	/* All interlaced capable intel hw wants timings in frames. Note though
	 * that intel_lvds_mode_fixup does some funny tricks with the crtc
	 * timings, so we need to be careful not to clobber these.*/
	if (!(adjusted_mode->private_flags & INTEL_MODE_CRTC_TIMINGS_SET))
		drm_mode_set_crtcinfo(adjusted_mode, 0);

	return true;
}

struct fdi_m_n {
	u32        tu;
	u32        gmch_m;
	u32        gmch_n;
	u32        link_m;
	u32        link_n;
};

void
fdi_reduce_ratio(u32 *num, u32 *den)
{
	while (*num > 0xffffff || *den > 0xffffff) {
		*num >>= 1;
		*den >>= 1;
	}
}

void
ironlake_compute_m_n(int bits_per_pixel, int nlanes, int pixel_clock,
		     int link_clock, struct fdi_m_n *m_n)
{
	m_n->tu = 64; /* default size */

	/* BUG_ON(pixel_clock > INT_MAX / 36); */
	m_n->gmch_m = bits_per_pixel * pixel_clock;
	m_n->gmch_n = link_clock * nlanes * 8;
	fdi_reduce_ratio(&m_n->gmch_m, &m_n->gmch_n);

	m_n->link_m = pixel_clock;
	m_n->link_n = link_clock;
	fdi_reduce_ratio(&m_n->link_m, &m_n->link_n);
}


struct intel_watermark_params {
	unsigned long fifo_size;
	unsigned long max_wm;
	unsigned long default_wm;
	unsigned long guard_size;
	unsigned long cacheline_size;
};

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

struct cxsr_latency {
	int is_desktop;
	int is_ddr3;
	unsigned long fsb_freq;
	unsigned long mem_freq;
	unsigned long display_sr;
	unsigned long display_hpll_disable;
	unsigned long cursor_sr;
	unsigned long cursor_hpll_disable;
};

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

bool g4x_compute_wm0(struct drm_device *dev,
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
bool ironlake_check_srwm(struct drm_device *dev, int level,
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
bool ironlake_compute_srwm(struct drm_device *dev, int level, int plane,
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

void ironlake_update_wm(struct drm_device *dev)
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

void sandybridge_update_wm(struct drm_device *dev)
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

	/* IVB has 3 pipes */
	if (IS_IVYBRIDGE(dev) &&
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

bool
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

bool
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

void sandybridge_update_sprite_wm(struct drm_device *dev, int pipe,
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

void intel_update_sprite_watermarks(struct drm_device *dev, int pipe,
				    uint32_t sprite_width, int pixel_size)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (dev_priv->display.update_sprite_wm)
		dev_priv->display.update_sprite_wm(dev, pipe, sprite_width,
						   pixel_size);
}

inline bool intel_panel_use_ssc(struct drm_i915_private *dev_priv)
{
	if (i915_panel_use_ssc >= 0)
		return i915_panel_use_ssc != 0;
	return dev_priv->lvds_use_ssc
		&& !(dev_priv->quirks & QUIRK_LVDS_SSC_DISABLE);
}

/*
 * Initialize reference clocks when the driver loads
 */
void ironlake_init_pch_refclk(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_mode_config *mode_config = &dev->mode_config;
	struct intel_encoder *encoder;
	u32 temp;
	bool has_lvds = false;
	bool has_cpu_edp = false;
	bool has_pch_edp = false;
	bool has_panel = false;
	bool has_ck505 = false;
	bool can_ssc = false;

	/* We need to take the global config into account */
	list_for_each_entry(encoder, &mode_config->encoder_list,
			    base.head) {
		switch (encoder->type) {
		case INTEL_OUTPUT_LVDS:
			has_panel = true;
			has_lvds = true;
			break;
		case INTEL_OUTPUT_EDP:
			has_panel = true;
			if (intel_encoder_is_pch_edp(&encoder->base))
				has_pch_edp = true;
			else
				has_cpu_edp = true;
			break;
		}
	}

	{
		has_ck505 = false;
		can_ssc = true;
	}

	fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
	fprintf(stderr, "has_panel %d has_lvds %d has_pch_edp %d has_cpu_edp %d has_ck505 %d\n",
		      has_panel, has_lvds, has_pch_edp, has_cpu_edp,
		      has_ck505);

	/* Ironlake: try to setup display ref clock before DPLL
	 * enabling. This is only under driver's control after
	 * PCH B stepping, previous chipset stepping should be
	 * ignoring this setting.
	 */
	temp = I915_READ(PCH_DREF_CONTROL);
	/* Always enable nonspread source */
	temp &= ~DREF_NONSPREAD_SOURCE_MASK;

	if (has_ck505)
		temp |= DREF_NONSPREAD_CK505_ENABLE;
	else
		temp |= DREF_NONSPREAD_SOURCE_ENABLE;

	if (has_panel) {
		temp &= ~DREF_SSC_SOURCE_MASK;
		temp |= DREF_SSC_SOURCE_ENABLE;

		/* SSC must be turned on before enabling the CPU output  */
		if (intel_panel_use_ssc(dev_priv) && can_ssc) {
			fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
			fprintf(stderr, "Using SSC on panel\n");
			temp |= DREF_SSC1_ENABLE;
		} else
			temp &= ~DREF_SSC1_ENABLE;

		/* Get SSC going before enabling the outputs */
		I915_WRITE(PCH_DREF_CONTROL, temp);
		POSTING_READ(PCH_DREF_CONTROL);
		udelay(200);

		temp &= ~DREF_CPU_SOURCE_OUTPUT_MASK;

		/* Enable CPU source on CPU attached eDP */
		if (has_cpu_edp) {
			if (intel_panel_use_ssc(dev_priv) && can_ssc) {
				fprintf(stderr, "[000000.0] [drm:%s], ",
					__func__);
				fprintf(stderr, "Using SSC on eDP\n");
				temp |= DREF_CPU_SOURCE_OUTPUT_DOWNSPREAD;
			}
			else
				temp |= DREF_CPU_SOURCE_OUTPUT_NONSPREAD;
		} else
			temp |= DREF_CPU_SOURCE_OUTPUT_DISABLE;

		I915_WRITE(PCH_DREF_CONTROL, temp);
		POSTING_READ(PCH_DREF_CONTROL);
		udelay(200);
	} else {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "Disabling SSC entirely\n");

		temp &= ~DREF_CPU_SOURCE_OUTPUT_MASK;

		/* Turn off CPU output */
		temp |= DREF_CPU_SOURCE_OUTPUT_DISABLE;

		I915_WRITE(PCH_DREF_CONTROL, temp);
		POSTING_READ(PCH_DREF_CONTROL);
		udelay(200);

		/* Turn off the SSC source */
		temp &= ~DREF_SSC_SOURCE_MASK;
		temp |= DREF_SSC_SOURCE_DISABLE;

		/* Turn off SSC1 */
		temp &= ~ DREF_SSC1_ENABLE;

		I915_WRITE(PCH_DREF_CONTROL, temp);
		POSTING_READ(PCH_DREF_CONTROL);
		udelay(200);
	}
}

int ironlake_get_refclk(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_encoder *encoder;
	struct drm_mode_config *mode_config = &dev->mode_config;
	struct intel_encoder *edp_encoder = NULL;
	int num_connectors = 0;
	bool is_lvds = false;

	list_for_each_entry(encoder, &mode_config->encoder_list, base.head) {
		if (encoder->base.crtc != crtc)
			continue;

		switch (encoder->type) {
		case INTEL_OUTPUT_LVDS:
			is_lvds = true;
			break;
		case INTEL_OUTPUT_EDP:
			edp_encoder = encoder;
			break;
		}
		num_connectors++;
	}

	if (is_lvds && intel_panel_use_ssc(dev_priv) && num_connectors < 2) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "using SSC reference clock of %d MHz\n",
			      dev_priv->lvds_ssc_freq);
		return dev_priv->lvds_ssc_freq * 1000;
	}

	return 120000;
}

int ironlake_crtc_mode_set(struct drm_crtc *crtc,
				  struct drm_display_mode *mode,
				  struct drm_display_mode *adjusted_mode,
				  int x, int y,
				  struct drm_framebuffer *old_fb)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	int pipe = intel_crtc->pipe;
	int plane = intel_crtc->plane;
	int refclk, num_connectors = 0;
	intel_clock_t clock, reduced_clock;
	u32 dpll, fp = 0, fp2 = 0, dspcntr, pipeconf;
	bool ok, has_reduced_clock = false, is_sdvo = false;
	bool is_crt = false, is_lvds = false, is_tv = false, is_dp = false;
	struct intel_encoder *has_edp_encoder = NULL;
	struct drm_mode_config *mode_config = &dev->mode_config;
	struct intel_encoder *encoder;
	 intel_limit_t *limit;
	int ret;
	struct fdi_m_n m_n = {0};
	u32 temp;
	u32 lvds_sync = 0;
	int target_clock, pixel_multiplier, lane, link_bw, factor;
	unsigned int pipe_bpp;
	bool dither;

	list_for_each_entry(encoder, &mode_config->encoder_list, base.head) {
		if (encoder->base.crtc != crtc)
			continue;

		switch (encoder->type) {
		case INTEL_OUTPUT_LVDS:
			is_lvds = true;
			break;
		case INTEL_OUTPUT_SDVO:
		case INTEL_OUTPUT_HDMI:
			is_sdvo = true;
			if (encoder->needs_tv_clock)
				is_tv = true;
			break;
		case INTEL_OUTPUT_TVOUT:
			is_tv = true;
			break;
		case INTEL_OUTPUT_ANALOG:
			is_crt = true;
			break;
		case INTEL_OUTPUT_DISPLAYPORT:
			is_dp = true;
			break;
		case INTEL_OUTPUT_EDP:
			has_edp_encoder = encoder;
			break;
		}

		num_connectors++;
	}

	refclk = ironlake_get_refclk(crtc);

	/*
	 * Returns a set of divisors for the desired target clock with the given
	 * refclk, or FALSE.  The returned values represent the clock equation:
	 * reflck * (5 * (m1 + 2) + (m2 + 2)) / (n + 2) / p1 / p2.
	 */
	limit = &intel_limits_ironlake_display_port;
	ok = limit->find_pll(limit, crtc, adjusted_mode->clock, refclk, NULL,
			     &clock);
	if (!ok) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "Couldn't find PLL settings for mode!\n");
		return -EINVAL;
	}

	if (is_lvds && dev_priv->lvds_downclock_avail) {
		/*
		 * Ensure we match the reduced clock's P to the target clock.
		 * If the clocks don't match, we can't switch the display clock
		 * by using the FP0/FP1. In such case we will disable the LVDS
		 * downclock feature.
		*/
		has_reduced_clock = limit->find_pll(limit, crtc,
						    dev_priv->lvds_downclock,
						    refclk,
						    &clock,
						    &reduced_clock);
	}
	/* SDVO TV has fixed PLL values depend on its clock range,
	   this mirrors vbios setting. */
	if (is_sdvo && is_tv) {
		if (adjusted_mode->clock >= 100000
		    && adjusted_mode->clock < 140500) {
			clock.p1 = 2;
			clock.p2 = 10;
			clock.n = 3;
			clock.m1 = 16;
			clock.m2 = 8;
		} else if (adjusted_mode->clock >= 140500
			   && adjusted_mode->clock <= 200000) {
			clock.p1 = 1;
			clock.p2 = 10;
			clock.n = 6;
			clock.m1 = 12;
			clock.m2 = 8;
		}
	}

	/* FDI link */
	pixel_multiplier = intel_mode_get_pixel_multiplier(adjusted_mode);
	lane = 0;
	/* CPU eDP doesn't require FDI link, so just set DP M/N
	   according to current link config */
	if (has_edp_encoder &&
	    !intel_encoder_is_pch_edp(&has_edp_encoder->base)) {
		target_clock = mode->clock;
		intel_edp_link_config(has_edp_encoder,
				      &lane, &link_bw);
	} else {
		/* [e]DP over FDI requires target mode clock
		   instead of link clock */
		if (is_dp || intel_encoder_is_pch_edp(&has_edp_encoder->base))
			target_clock = mode->clock;
		else
			target_clock = adjusted_mode->clock;

		/* FDI is a binary signal running at ~2.7GHz, encoding
		 * each output octet as 10 bits. The actual frequency
		 * is stored as a divider into a 100MHz clock, and the
		 * mode pixel clock is stored in units of 1KHz.
		 * Hence the bw of each lane in terms of the mode signal
		 * is:
		 */
		link_bw = intel_fdi_link_freq(dev) * MHz(100)/KHz(1)/10;
	}

	/* determine panel color depth */
	temp = I915_READ(PIPECONF(pipe));
	temp &= ~PIPE_BPC_MASK;
	dither = intel_choose_pipe_bpp_dither(crtc, &pipe_bpp, mode);
	switch (pipe_bpp) {
	case 18:
		temp |= PIPE_6BPC;
		break;
	case 24:
		temp |= PIPE_8BPC;
		break;
	case 30:
		temp |= PIPE_10BPC;
		break;
	case 36:
		temp |= PIPE_12BPC;
		break;
	default:
		if (1) { 
			fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
			fprintf(stderr, "intel_choose_pipe_bpp returned invalid value %d\n",
			pipe_bpp);
		}
		temp |= PIPE_8BPC;
		pipe_bpp = 24;
		break;
	}

	intel_crtc->bpp = pipe_bpp;
	I915_WRITE(PIPECONF(pipe), temp);

	if (!lane) {
		/*
		 * Account for spread spectrum to avoid
		 * oversubscribing the link. Max center spread
		 * is 2.5%; use 5% for safety's sake.
		 */
		u32 bps = target_clock * intel_crtc->bpp * 21 / 20;
		lane = bps / (link_bw * 8) + 1;
	}

	intel_crtc->fdi_lanes = lane;

	if (pixel_multiplier > 1)
		link_bw *= pixel_multiplier;
	ironlake_compute_m_n(intel_crtc->bpp, lane, target_clock, link_bw,
			     &m_n);

	fp = clock.n << 16 | clock.m1 << 8 | clock.m2;
	if (has_reduced_clock)
		fp2 = reduced_clock.n << 16 | reduced_clock.m1 << 8 |
			reduced_clock.m2;

	/* Enable autotuning of the PLL clock (if permissible) */
	factor = 21;
	if (is_lvds) {
		if ((intel_panel_use_ssc(dev_priv) &&
		     dev_priv->lvds_ssc_freq == 100) ||
		    (I915_READ(PCH_LVDS) & LVDS_CLKB_POWER_MASK) == LVDS_CLKB_POWER_UP)
			factor = 25;
	} else if (is_sdvo && is_tv)
		factor = 20;

	if (clock.m < factor * clock.n)
		fp |= FP_CB_TUNE;

	dpll = 0;

	if (is_lvds)
		dpll |= DPLLB_MODE_LVDS;
	else
		dpll |= DPLLB_MODE_DAC_SERIAL;
	if (is_sdvo) {
		int pixel_multiplier = intel_mode_get_pixel_multiplier(adjusted_mode);
		if (pixel_multiplier > 1) {
			dpll |= (pixel_multiplier - 1) << PLL_REF_SDVO_HDMI_MULTIPLIER_SHIFT;
		}
		dpll |= DPLL_DVO_HIGH_SPEED;
	}
	if (is_dp || intel_encoder_is_pch_edp(&has_edp_encoder->base))
		dpll |= DPLL_DVO_HIGH_SPEED;

	/* compute bitmask from p1 value */
	dpll |= (1 << (clock.p1 - 1)) << DPLL_FPA01_P1_POST_DIV_SHIFT;
	/* also FPA1 */
	dpll |= (1 << (clock.p1 - 1)) << DPLL_FPA1_P1_POST_DIV_SHIFT;

	switch (clock.p2) {
	case 5:
		dpll |= DPLL_DAC_SERIAL_P2_CLOCK_DIV_5;
		break;
	case 7:
		dpll |= DPLLB_LVDS_P2_CLOCK_DIV_7;
		break;
	case 10:
		dpll |= DPLL_DAC_SERIAL_P2_CLOCK_DIV_10;
		break;
	case 14:
		dpll |= DPLLB_LVDS_P2_CLOCK_DIV_14;
		break;
	}

	if (is_sdvo && is_tv)
		dpll |= PLL_REF_INPUT_TVCLKINBC;
	else if (is_tv)
		/* XXX: just matching BIOS for now */
		/*	dpll |= PLL_REF_INPUT_TVCLKINBC; */
		dpll |= 3;
	else if (is_lvds && intel_panel_use_ssc(dev_priv) && num_connectors < 2)
		dpll |= PLLB_REF_INPUT_SPREADSPECTRUMIN;
	else
		dpll |= PLL_REF_INPUT_DREFCLK;

	/* setup pipeconf */
	pipeconf = I915_READ(PIPECONF(pipe));

	/* Set up the display plane register */
	dspcntr = DISPPLANE_GAMMA_ENABLE;

	fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
	fprintf(stderr, "Mode for pipe %d:\n", pipe);

	/* PCH eDP needs FDI, but CPU eDP does not */
	if (!intel_crtc->no_pll) {
		if (!has_edp_encoder ||
		    intel_encoder_is_pch_edp(&has_edp_encoder->base)) {
			I915_WRITE(PCH_FP0(pipe), fp);
			I915_WRITE(PCH_DPLL(pipe), dpll & ~DPLL_VCO_ENABLE);

			POSTING_READ(PCH_DPLL(pipe));
			udelay(150);
		}
	} else {
		if (dpll == (I915_READ(PCH_DPLL(0)) & 0x7fffffff) &&
		    fp == I915_READ(PCH_FP0(0))) {
			intel_crtc->use_pll_a = true;
			fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
			fprintf(stderr, "using pipe a dpll\n");
		} else if (dpll == (I915_READ(PCH_DPLL(1)) & 0x7fffffff) &&
			   fp == I915_READ(PCH_FP0(1))) {
			intel_crtc->use_pll_a = false;
			fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
			fprintf(stderr, "using pipe b dpll\n");
		} else {
			fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
			fprintf(stderr, "no matching PLL configuration for pipe 2\n");
			return -EINVAL;
		}
	}

	/* The LVDS pin pair needs to be on before the DPLLs are enabled.
	 * This is an exception to the general rule that mode_set doesn't turn
	 * things on.
	 */
	if (is_lvds) {
		temp = I915_READ(PCH_LVDS);
		temp |= LVDS_PORT_EN | LVDS_A0A2_CLKA_POWER_UP;
		if (HAS_PCH_CPT(dev)) {
			temp &= ~PORT_TRANS_SEL_MASK;
			temp |= PORT_TRANS_SEL_CPT(pipe);
		} else {
			if (pipe == 1)
				temp |= LVDS_PIPEB_SELECT;
			else
				temp &= ~LVDS_PIPEB_SELECT;
		}

		/* set the corresponsding LVDS_BORDER bit */
		temp |= dev_priv->lvds_border_bits;
		/* Set the B0-B3 data pairs corresponding to whether we're going to
		 * set the DPLLs for dual-channel mode or not.
		 */
		if (clock.p2 == 7)
			temp |= LVDS_B0B3_POWER_UP | LVDS_CLKB_POWER_UP;
		else
			temp &= ~(LVDS_B0B3_POWER_UP | LVDS_CLKB_POWER_UP);

		/* It would be nice to set 24 vs 18-bit mode (LVDS_A3_POWER_UP)
		 * appropriately here, but we need to look more thoroughly into how
		 * panels behave in the two modes.
		 */
		if (adjusted_mode->flags & DRM_MODE_FLAG_NHSYNC)
			lvds_sync |= LVDS_HSYNC_POLARITY;
		if (adjusted_mode->flags & DRM_MODE_FLAG_NVSYNC)
			lvds_sync |= LVDS_VSYNC_POLARITY;
		if ((temp & (LVDS_HSYNC_POLARITY | LVDS_VSYNC_POLARITY))
		    != lvds_sync) {
			char flags[2] = "-+";
			fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
			fprintf(stderr, "Changing LVDS panel from "
				 "(%chsync, %cvsync) to (%chsync, %cvsync)\n",
				 flags[!(temp & LVDS_HSYNC_POLARITY)],
				 flags[!(temp & LVDS_VSYNC_POLARITY)],
				 flags[!(lvds_sync & LVDS_HSYNC_POLARITY)],
				 flags[!(lvds_sync & LVDS_VSYNC_POLARITY)]);
			temp &= ~(LVDS_HSYNC_POLARITY | LVDS_VSYNC_POLARITY);
			temp |= lvds_sync;
		}
		I915_WRITE(PCH_LVDS, temp);
	}

	pipeconf &= ~PIPECONF_DITHER_EN;
	pipeconf &= ~PIPECONF_DITHER_TYPE_MASK;
	if ((is_lvds && dev_priv->lvds_dither) || dither) {
		pipeconf |= PIPECONF_DITHER_EN;
		pipeconf |= PIPECONF_DITHER_TYPE_SP;
	}
	if (is_dp || intel_encoder_is_pch_edp(&has_edp_encoder->base)) {
		intel_dp_set_m_n(crtc, mode, adjusted_mode);
	} else {
		/* For non-DP output, clear any trans DP clock recovery setting.*/
		I915_WRITE(TRANSDATA_M1(pipe), 0);
		I915_WRITE(TRANSDATA_N1(pipe), 0);
		I915_WRITE(TRANSDPLINK_M1(pipe), 0);
		I915_WRITE(TRANSDPLINK_N1(pipe), 0);
	}

	if (!intel_crtc->no_pll &&
	    (!has_edp_encoder ||
	     intel_encoder_is_pch_edp(&has_edp_encoder->base))) {
		I915_WRITE(PCH_DPLL(pipe), dpll);

		/* Wait for the clocks to stabilize. */
		POSTING_READ(PCH_DPLL(pipe));
		udelay(150);

		/* The pixel multiplier can only be updated once the
		 * DPLL is enabled and the clocks are stable.
		 *
		 * So write it again.
		 */
		I915_WRITE(PCH_DPLL(pipe), dpll);
	}

	intel_crtc->lowfreq_avail = false;
	if (!intel_crtc->no_pll) {
		if (is_lvds && has_reduced_clock && i915_powersave) {
			I915_WRITE(PCH_FP1(pipe), fp2);
			intel_crtc->lowfreq_avail = true;
			if (HAS_PIPE_CXSR(dev)) {
				fprintf(stderr, "[000000.0] [drm:%s], ",
					__func__);
				fprintf(stderr, "enabling CxSR downclocking\n");
				pipeconf |= PIPECONF_CXSR_DOWNCLOCK;
			}
		} else {
			I915_WRITE(PCH_FP1(pipe), fp);
			if (HAS_PIPE_CXSR(dev)) {
				fprintf(stderr, "[000000.0] [drm:%s], ",
					__func__);
				fprintf(stderr, "disabling CxSR downclocking\n");
				pipeconf &= ~PIPECONF_CXSR_DOWNCLOCK;
			}
		}
	}

	pipeconf &= ~PIPECONF_INTERLACE_MASK;
	if (adjusted_mode->flags & DRM_MODE_FLAG_INTERLACE) {
		pipeconf |= PIPECONF_INTERLACED_ILK;
		/* the chip adds 2 halflines automatically */
		adjusted_mode->crtc_vtotal -= 1;
		adjusted_mode->crtc_vblank_end -= 1;
		I915_WRITE(VSYNCSHIFT(pipe),
			   adjusted_mode->crtc_hsync_start
			   - adjusted_mode->crtc_htotal/2);
	} else {
		pipeconf |= PIPECONF_PROGRESSIVE;
		I915_WRITE(VSYNCSHIFT(pipe), 0);
	}

	I915_WRITE(HTOTAL(pipe),
		   (adjusted_mode->crtc_hdisplay - 1) |
		   ((adjusted_mode->crtc_htotal - 1) << 16));
	I915_WRITE(HBLANK(pipe),
		   (adjusted_mode->crtc_hblank_start - 1) |
		   ((adjusted_mode->crtc_hblank_end - 1) << 16));
	I915_WRITE(HSYNC(pipe),
		   (adjusted_mode->crtc_hsync_start - 1) |
		   ((adjusted_mode->crtc_hsync_end - 1) << 16));

	I915_WRITE(VTOTAL(pipe),
		   (adjusted_mode->crtc_vdisplay - 1) |
		   ((adjusted_mode->crtc_vtotal - 1) << 16));
	I915_WRITE(VBLANK(pipe),
		   (adjusted_mode->crtc_vblank_start - 1) |
		   ((adjusted_mode->crtc_vblank_end - 1) << 16));
	I915_WRITE(VSYNC(pipe),
		   (adjusted_mode->crtc_vsync_start - 1) |
		   ((adjusted_mode->crtc_vsync_end - 1) << 16));

	/* pipesrc controls the size that is scaled from, which should
	 * always be the user's requested size.
	 */
	I915_WRITE(PIPESRC(pipe),
		   ((mode->hdisplay - 1) << 16) | (mode->vdisplay - 1));

	I915_WRITE(PIPE_DATA_M1(pipe), TU_SIZE(m_n.tu) | m_n.gmch_m);
	I915_WRITE(PIPE_DATA_N1(pipe), m_n.gmch_n);
	I915_WRITE(PIPE_LINK_M1(pipe), m_n.link_m);
	I915_WRITE(PIPE_LINK_N1(pipe), m_n.link_n);

	if (has_edp_encoder &&
	    !intel_encoder_is_pch_edp(&has_edp_encoder->base)) {
		ironlake_set_pll_edp(crtc, adjusted_mode->clock);
	}

	I915_WRITE(PIPECONF(pipe), pipeconf);
	POSTING_READ(PIPECONF(pipe));

	intel_wait_for_vblank(dev, pipe);

	I915_WRITE(DSPCNTR(plane), dspcntr);
	POSTING_READ(DSPCNTR(plane));

	ret = intel_pipe_set_base(crtc, x, y, old_fb);

	intel_update_watermarks(dev);

	return ret;
}

int intel_crtc_mode_set(struct drm_crtc *crtc,
			       struct drm_display_mode *mode,
			       struct drm_display_mode *adjusted_mode,
			       int x, int y,
			       struct drm_framebuffer *old_fb)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	int pipe = intel_crtc->pipe;
	int ret;

	ret = dev_priv->display.crtc_mode_set(crtc, mode, adjusted_mode,
					      x, y, old_fb);

	if (ret)
		intel_crtc->dpms_mode = DRM_MODE_DPMS_OFF;
	else
		intel_crtc->dpms_mode = DRM_MODE_DPMS_ON;

	return ret;
}

/**
 * Get a pipe with a simple mode set on it for doing load-based monitor
 * detection.
 *
 * It will be up to the load-detect code to adjust the pipe as appropriate for
 * its requirements.  The pipe will be connected to no other encoders.
 *
 * Currently this code will only succeed if there is a pipe with no encoders
 * configured for it.  In the future, it could choose to temporarily disable
 * some outputs to free up a pipe for its use.
 *
 * \return crtc, or NULL if no pipes are available.
 */

/* VESA 640x480x72Hz mode to set on the pipe */
static struct drm_display_mode load_detect_mode = {
	DRM_MODE("640x480", DRM_MODE_TYPE_DEFAULT, 31500, 640, 664,
		 704, 832, 0, 480, 489, 491, 520, 0, DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
};

#define GPU_IDLE_TIMEOUT 400 /* ms */

#define CRTC_IDLE_TIMEOUT 700 /* ms */

void intel_increase_pllclock(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	int pipe = intel_crtc->pipe;
	int dpll_reg = DPLL(pipe);
	int dpll;

	if (HAS_PCH_SPLIT(dev))
		return;

	if (!dev_priv->lvds_downclock_avail)
		return;

	dpll = I915_READ(dpll_reg);
	if (!HAS_PIPE_CXSR(dev) && (dpll & DISPLAY_RATE_SELECT_FPA1)) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "upclocking LVDS\n");

		assert_panel_unlocked(dev_priv, pipe);

		dpll &= ~DISPLAY_RATE_SELECT_FPA1;
		I915_WRITE(dpll_reg, dpll);
		intel_wait_for_vblank(dev, pipe);

		dpll = I915_READ(dpll_reg);
		if (dpll & DISPLAY_RATE_SELECT_FPA1) {
			fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
			fprintf(stderr, "failed to upclock LVDS!\n");
		}
	}

	/* Schedule downclock */
	fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
	fprintf(stderr, "Warning: not scheduling mod_timer\n");
}

static  struct drm_framebuffer_funcs intel_fb_funcs = {
	
	0
};

void ironlake_init_clock_gating(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	uint32_t dspclk_gate = VRHUNIT_CLOCK_GATE_DISABLE;

	/* Required for FBC */
	dspclk_gate |= DPFCUNIT_CLOCK_GATE_DISABLE |
		DPFCRUNIT_CLOCK_GATE_DISABLE |
		DPFDUNIT_CLOCK_GATE_DISABLE;
	/* Required for CxSR */
	dspclk_gate |= DPARBUNIT_CLOCK_GATE_DISABLE;

	I915_WRITE(PCH_3DCGDIS0,
		   MARIUNIT_CLOCK_GATE_DISABLE |
		   SVSMUNIT_CLOCK_GATE_DISABLE);
	I915_WRITE(PCH_3DCGDIS1,
		   VFMUNIT_CLOCK_GATE_DISABLE);

	I915_WRITE(PCH_DSPCLK_GATE_D, dspclk_gate);

	/*
	 * According to the spec the following bits should be set in
	 * order to enable memory self-refresh
	 * The bit 22/21 of 0x42004
	 * The bit 5 of 0x42020
	 * The bit 15 of 0x45000
	 */
	I915_WRITE(ILK_DISPLAY_CHICKEN2,
		   (I915_READ(ILK_DISPLAY_CHICKEN2) |
		    ILK_DPARB_GATE | ILK_VSDPFD_FULL));
	I915_WRITE(ILK_DSPCLK_GATE,
		   (I915_READ(ILK_DSPCLK_GATE) |
		    ILK_DPARB_CLK_GATE));
	I915_WRITE(DISP_ARB_CTL,
		   (I915_READ(DISP_ARB_CTL) |
		    DISP_FBC_WM_DIS));
	I915_WRITE(WM3_LP_ILK, 0);
	I915_WRITE(WM2_LP_ILK, 0);
	I915_WRITE(WM1_LP_ILK, 0);

	/*
	 * Based on the document from hardware guys the following bits
	 * should be set unconditionally in order to enable FBC.
	 * The bit 22 of 0x42000
	 * The bit 22 of 0x42004
	 * The bit 7,8,9 of 0x42020.
	 */
	if (IS_IRONLAKE_M(dev)) {
		I915_WRITE(ILK_DISPLAY_CHICKEN1,
			   I915_READ(ILK_DISPLAY_CHICKEN1) |
			   ILK_FBCQ_DIS);
		I915_WRITE(ILK_DISPLAY_CHICKEN2,
			   I915_READ(ILK_DISPLAY_CHICKEN2) |
			   ILK_DPARB_GATE);
		I915_WRITE(ILK_DSPCLK_GATE,
			   I915_READ(ILK_DSPCLK_GATE) |
			   ILK_DPFC_DIS1 |
			   ILK_DPFC_DIS2 |
			   ILK_CLK_FBC);
	}

	I915_WRITE(ILK_DISPLAY_CHICKEN2,
		   I915_READ(ILK_DISPLAY_CHICKEN2) |
		   ILK_ELPIN_409_SELECT);
	I915_WRITE(_3D_CHICKEN2,
		   _3D_CHICKEN2_WM_READ_PIPELINED << 16 |
		   _3D_CHICKEN2_WM_READ_PIPELINED);
}

void ivybridge_init_clock_gating(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int pipe;
	uint32_t dspclk_gate = VRHUNIT_CLOCK_GATE_DISABLE;

	I915_WRITE(PCH_DSPCLK_GATE_D, dspclk_gate);

	I915_WRITE(WM3_LP_ILK, 0);
	I915_WRITE(WM2_LP_ILK, 0);
	I915_WRITE(WM1_LP_ILK, 0);

	/* According to the spec, bit 13 (RCZUNIT) must be set on IVB.
	 * This implements the WaDisableRCZUnitClockGating workaround.
	 */
	I915_WRITE(GEN6_UCGCTL2, GEN6_RCZUNIT_CLOCK_GATE_DISABLE);

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
}

void cpt_init_clock_gating(struct drm_device *dev)
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

struct intel_quirk {
	int device;
	int subsystem_vendor;
	int subsystem_device;
	void (*hook)(struct drm_device *dev);
};

#ifdef CONFIG_DEBUG_FS

struct intel_display_error_state {
	struct intel_cursor_error_state {
		u32 control;
		u32 position;
		u32 base;
		u32 size;
	} cursor[2];

	struct intel_pipe_error_state {
		u32 conf;
		u32 source;

		u32 htotal;
		u32 hblank;
		u32 hsync;
		u32 vtotal;
		u32 vblank;
		u32 vsync;
	} pipe[2];

	struct intel_plane_error_state {
		u32 control;
		u32 stride;
		u32 size;
		u32 pos;
		u32 addr;
		u32 surface;
		u32 tile_offset;
	} plane[2];
};
#endif
