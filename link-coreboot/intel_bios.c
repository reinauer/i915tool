#define	SLAVE_ADDR1	0x70
#define	SLAVE_ADDR2	0x72

static int panel_type;

int intel_bios_ssc_frequency(struct drm_device *dev,
				    bool alternate)
{
	switch (INTEL_INFO(dev)->gen) {
	case 2:
		return alternate ? 66 : 48;
	case 3:
	case 4:
		return alternate ? 100 : 96;
	default:
		return alternate ? 100 : 120;
	}
}

void
init_vbt_defaults(struct drm_i915_private *dev_priv)
{
	extern struct drm_device *i915;
	struct drm_device *dev = i915;

	dev_priv->crt_ddc_pin = GMBUS_PORT_VGADDC;

	/* LFP panel data */
	dev_priv->lvds_dither = 1;
	dev_priv->lvds_vbt = 0;

	/* SDVO panel data */
	dev_priv->sdvo_lvds_vbt_mode = NULL;

	/* general features */
	dev_priv->int_tv_support = 1;
	dev_priv->int_crt_support = 1;

	/* Default to using SSC */
	dev_priv->lvds_use_ssc = 1;

	/* Core/SandyBridge/IvyBridge use 120MHz reference clock for LVDS */
		dev_priv->lvds_ssc_freq = intel_bios_ssc_frequency(dev, 0);
	
	fprintf(stderr, "Set default to SSC at %dMHz\n", dev_priv->lvds_ssc_freq);

	/* eDP data */
	dev_priv->edp.bpp = 18;
}
