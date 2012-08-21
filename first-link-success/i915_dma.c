

/* Implement basically the same security restrictions as hardware does
 * for MI_BATCH_NON_SECURE.  These can be made stricter at any time.
 *
 * Most of the calculations below involve calculating the size of a
 * particular instruction.  It's important to get the size right as
 * that tells us where the next instruction to check is.  Any illegal
 * instruction detected will be given a size of zero, which is a
 * signal to abort the rest of the buffer.
 */
static int validate_cmd(int cmd)
{
	switch (((cmd >> 29) & 0x7)) {
	case 0x0:
		switch ((cmd >> 23) & 0x3f) {
		case 0x0:
			return 1;	/* MI_NOOP */
		case 0x4:
			return 1;	/* MI_FLUSH */
		default:
			return 0;	/* disallow everything else */
		}
		break;
	case 0x1:
		return 0;	/* reserved */
	case 0x2:
		return (cmd & 0xff) + 2;	/* 2d commands */
	case 0x3:
		if (((cmd >> 24) & 0x1f) <= 0x18)
			return 1;

		switch ((cmd >> 24) & 0x1f) {
		case 0x1c:
			return 1;
		case 0x1d:
			switch ((cmd >> 16) & 0xff) {
			case 0x3:
				return (cmd & 0x1f) + 2;
			case 0x4:
				return (cmd & 0xf) + 2;
			default:
				return (cmd & 0xffff) + 2;
			}
		case 0x1e:
			if (cmd & (1 << 23))
				return (cmd & 0xffff) + 1;
			else
				return 1;
		case 0x1f:
			if ((cmd & (1 << 23)) == 0)	/* inline vertices */
				return (cmd & 0x1ffff) + 2;
			else if (cmd & (1 << 17))	/* indirect random */
				if ((cmd & 0xffff) == 0)
					return 0;	/* unknown length, too hard */
				else
					return (((cmd & 0xffff) + 1) / 2) + 1;
			else
				return 2;	/* indirect sequential */
		default:
			return 0;
		}
	default:
		return 0;
	}

	return 0;
}

static int i915_get_bridge_dev(struct drm_device *dev)
{
	extern struct drm_device *i915;
	struct drm_i915_private *dev_priv = i915->dev_private;

	dev_priv->bridge_dev = pci_get_bus_and_slot(0, PCI_DEVFN(0, 0));
	if (!dev_priv->bridge_dev) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "bridge device not found\n");
		return -1;
	}
	return 0;
}

#define MCHBAR_I915 0x44
#define MCHBAR_I965 0x48
#define MCHBAR_SIZE (4*4096)

#define DEVEN_REG 0x54
#define   DEVEN_MCHBAR_EN (1 << 28)

#define PTE_ADDRESS_MASK		0xfffff000
#define PTE_ADDRESS_MASK_HIGH		0x000000f0 /* i915+ */
#define PTE_MAPPING_TYPE_UNCACHED	(0 << 1)
#define PTE_MAPPING_TYPE_DCACHE		(1 << 1) /* i830 only */
#define PTE_MAPPING_TYPE_CACHED		(3 << 1)
#define PTE_MAPPING_TYPE_MASK		(3 << 1)
#define PTE_VALID			(1 << 0)

static void i915_warn_stolen(struct drm_device *dev)
{
	fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
	fprintf(stderr, "not enough stolen space for compressed buffer, disabling\n");
	fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
	fprintf(stderr, "hint: you may be able to increase stolen memory size in the BIOS to avoid this\n");
}

static bool
intel_enable_ppgtt(struct drm_device *dev)
{
	if (i915_enable_ppgtt >= 0)
		return i915_enable_ppgtt;

#ifdef CONFIG_INTEL_IOMMU
	/* Disable ppgtt on SNB if VT-d is on. */
	if (INTEL_INFO(dev)->gen == 6 && intel_iommu_gfx_mapped)
		return false;
#endif

	return true;
}

static int i915_load_modeset_init(struct drm_device *dev)
{
	extern struct drm_device *i915;
	struct drm_i915_private *dev_priv = i915->dev_private;
	int ret;

	ret = intel_parse_bios(dev);
	if (ret) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "failed to find VBIOS tables\n");
	}

	/* If we have > 1 VGA cards, then we need to arbitrate access
	 * to the common VGA resources.
	 *
	 * If we are a secondary display controller (!PCI_DISPLAY_CLASS_VGA),
	 * then we do not take part in VGA arbitration and the
	 * vga_client_register() fails with -ENODEV.
	 */
	ret = 0;
	if (ret && ret != -ENODEV)
		return -1;

	ret = 0;
	if (ret)
		return -1;

	/* IIR "flip pending" bit means done if this bit is set */
	if (IS_GEN3(dev) && (I915_READ(ECOSKPD) & ECO_FLIP_DONE))
		dev_priv->flip_pending_is_done = true;

	intel_modeset_init(dev);

	ret = 0;
	if (ret)
		return -1;

	ret = 0;
	if (ret)
		return -1;

	/* Always safe in the mode setting case. */
	/* FIXME: do pre/post-mode set stuff in core KMS code */
	dev->vblank_disable_allowed = 1;

	ret = intel_fbdev_init(dev);
	if (ret)
		return -1;

	return 0;

	return ret;
}

static void i915_pineview_get_mem_freq(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	u32 tmp;

	tmp = I915_READ(CLKCFG);

	switch (tmp & CLKCFG_FSB_MASK) {
	case CLKCFG_FSB_533:
		dev_priv->fsb_freq = 533; /* 133*4 */
		break;
	case CLKCFG_FSB_800:
		dev_priv->fsb_freq = 800; /* 200*4 */
		break;
	case CLKCFG_FSB_667:
		dev_priv->fsb_freq =  667; /* 167*4 */
		break;
	case CLKCFG_FSB_400:
		dev_priv->fsb_freq = 400; /* 100*4 */
		break;
	}

	switch (tmp & CLKCFG_MEM_MASK) {
	case CLKCFG_MEM_533:
		dev_priv->mem_freq = 533;
		break;
	case CLKCFG_MEM_667:
		dev_priv->mem_freq = 667;
		break;
	case CLKCFG_MEM_800:
		dev_priv->mem_freq = 800;
		break;
	}

	/* detect pineview DDR3 setting */
	tmp = I915_READ(CSHRDDR3CTL);
	dev_priv->is_ddr3 = (tmp & CSHRDDR3CTL_DDR3) ? 1 : 0;
}

static void i915_ironlake_get_mem_freq(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	u16 ddrpll, csipll;

	ddrpll = I915_READ16(DDRMPLL1);
	csipll = I915_READ16(CSIPLL0);

	switch (ddrpll & 0xff) {
	case 0xc:
		dev_priv->mem_freq = 800;
		break;
	case 0x10:
		dev_priv->mem_freq = 1066;
		break;
	case 0x14:
		dev_priv->mem_freq = 1333;
		break;
	case 0x18:
		dev_priv->mem_freq = 1600;
		break;
	default:
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "unknown memory frequency 0x%02x\n",
				 ddrpll & 0xff);
		dev_priv->mem_freq = 0;
		break;
	}

	dev_priv->r_t = dev_priv->mem_freq;

	switch (csipll & 0x3ff) {
	case 0x00c:
		dev_priv->fsb_freq = 3200;
		break;
	case 0x00e:
		dev_priv->fsb_freq = 3733;
		break;
	case 0x010:
		dev_priv->fsb_freq = 4266;
		break;
	case 0x012:
		dev_priv->fsb_freq = 4800;
		break;
	case 0x014:
		dev_priv->fsb_freq = 5333;
		break;
	case 0x016:
		dev_priv->fsb_freq = 5866;
		break;
	case 0x018:
		dev_priv->fsb_freq = 6400;
		break;
	default:
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "unknown fsb frequency 0x%04x\n",
				 csipll & 0x3ff);
		dev_priv->fsb_freq = 0;
		break;
	}

	if (dev_priv->fsb_freq == 3200) {
		dev_priv->c_m = 0;
	} else if (dev_priv->fsb_freq > 3200 && dev_priv->fsb_freq <= 4800) {
		dev_priv->c_m = 1;
	} else {
		dev_priv->c_m = 2;
	}
}

static const struct cparams {
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

unsigned long i915_mch_val(struct drm_i915_private *dev_priv)
{
	unsigned long m, x, b;
	u32 tsfs;

	tsfs = I915_READ(TSFS);

	m = ((tsfs & TSFS_SLOPE_MASK) >> TSFS_SLOPE_SHIFT);
	x = I915_READ8(TR1);

	b = tsfs & TSFS_INTR_MASK;

	return ((m * x) / 127) - b;
}

static u16 pvid_to_extvid(struct drm_i915_private *dev_priv, u8 pxvid)
{
	static const struct v_table {
		u16 vd; /* in .1 mil */
		u16 vm; /* in .1 mil */
	} v_table[] = {
		{ 0, 0, },
		{ 375, 0, },
		{ 500, 0, },
		{ 625, 0, },
		{ 750, 0, },
		{ 875, 0, },
		{ 1000, 0, },
		{ 1125, 0, },
		{ 4125, 3000, },
		{ 4125, 3000, },
		{ 4125, 3000, },
		{ 4125, 3000, },
		{ 4125, 3000, },
		{ 4125, 3000, },
		{ 4125, 3000, },
		{ 4125, 3000, },
		{ 4125, 3000, },
		{ 4125, 3000, },
		{ 4125, 3000, },
		{ 4125, 3000, },
		{ 4125, 3000, },
		{ 4125, 3000, },
		{ 4125, 3000, },
		{ 4125, 3000, },
		{ 4125, 3000, },
		{ 4125, 3000, },
		{ 4125, 3000, },
		{ 4125, 3000, },
		{ 4125, 3000, },
		{ 4125, 3000, },
		{ 4125, 3000, },
		{ 4125, 3000, },
		{ 4250, 3125, },
		{ 4375, 3250, },
		{ 4500, 3375, },
		{ 4625, 3500, },
		{ 4750, 3625, },
		{ 4875, 3750, },
		{ 5000, 3875, },
		{ 5125, 4000, },
		{ 5250, 4125, },
		{ 5375, 4250, },
		{ 5500, 4375, },
		{ 5625, 4500, },
		{ 5750, 4625, },
		{ 5875, 4750, },
		{ 6000, 4875, },
		{ 6125, 5000, },
		{ 6250, 5125, },
		{ 6375, 5250, },
		{ 6500, 5375, },
		{ 6625, 5500, },
		{ 6750, 5625, },
		{ 6875, 5750, },
		{ 7000, 5875, },
		{ 7125, 6000, },
		{ 7250, 6125, },
		{ 7375, 6250, },
		{ 7500, 6375, },
		{ 7625, 6500, },
		{ 7750, 6625, },
		{ 7875, 6750, },
		{ 8000, 6875, },
		{ 8125, 7000, },
		{ 8250, 7125, },
		{ 8375, 7250, },
		{ 8500, 7375, },
		{ 8625, 7500, },
		{ 8750, 7625, },
		{ 8875, 7750, },
		{ 9000, 7875, },
		{ 9125, 8000, },
		{ 9250, 8125, },
		{ 9375, 8250, },
		{ 9500, 8375, },
		{ 9625, 8500, },
		{ 9750, 8625, },
		{ 9875, 8750, },
		{ 10000, 8875, },
		{ 10125, 9000, },
		{ 10250, 9125, },
		{ 10375, 9250, },
		{ 10500, 9375, },
		{ 10625, 9500, },
		{ 10750, 9625, },
		{ 10875, 9750, },
		{ 11000, 9875, },
		{ 11125, 10000, },
		{ 11250, 10125, },
		{ 11375, 10250, },
		{ 11500, 10375, },
		{ 11625, 10500, },
		{ 11750, 10625, },
		{ 11875, 10750, },
		{ 12000, 10875, },
		{ 12125, 11000, },
		{ 12250, 11125, },
		{ 12375, 11250, },
		{ 12500, 11375, },
		{ 12625, 11500, },
		{ 12750, 11625, },
		{ 12875, 11750, },
		{ 13000, 11875, },
		{ 13125, 12000, },
		{ 13250, 12125, },
		{ 13375, 12250, },
		{ 13500, 12375, },
		{ 13625, 12500, },
		{ 13750, 12625, },
		{ 13875, 12750, },
		{ 14000, 12875, },
		{ 14125, 13000, },
		{ 14250, 13125, },
		{ 14375, 13250, },
		{ 14500, 13375, },
		{ 14625, 13500, },
		{ 14750, 13625, },
		{ 14875, 13750, },
		{ 15000, 13875, },
		{ 15125, 14000, },
		{ 15250, 14125, },
		{ 15375, 14250, },
		{ 15500, 14375, },
		{ 15625, 14500, },
		{ 15750, 14625, },
		{ 15875, 14750, },
		{ 16000, 14875, },
		{ 16125, 15000, },
	};
	if (dev_priv->info->is_mobile)
		return v_table[pxvid].vm;
	else
		return v_table[pxvid].vd;
}

/* Global for IPS driver to get at the current i915 device */
static struct drm_i915_private *i915_mch_dev;
EXPORT_SYMBOL_GPL(i915_read_mch_val);
EXPORT_SYMBOL_GPL(i915_gpu_raise);
EXPORT_SYMBOL_GPL(i915_gpu_lower);
EXPORT_SYMBOL_GPL(i915_gpu_busy);
EXPORT_SYMBOL_GPL(i915_gpu_turbo_disable);

/**
 * i915_driver_load - setup chip and create an initial config
 * @dev: DRM device
 * @flags: startup flags
 *
 * The driver load routine has to do several things:
 *   - drive output discovery via intel_modeset_init()
 *   - initialize the memory manager
 *   - allocate initial config memory
 *   - setup the DRM framebuffer with the allocated memory
 */
int i915_driver_load(struct drm_device *dev, unsigned long flags)
{
	struct drm_i915_private *dev_priv;
	int ret = 0, mmio_bar;
	uint32_t agp_size;

	/* i915 has 4 more counters */
	dev->counters += 4;

	dev_priv = allocz(sizeof(drm_i915_private_t));
	if (dev_priv == NULL)
		return -ENOMEM;

	dev->dev_private = (void *)dev_priv;
	dev_priv->dev = dev;
	dev_priv->info = (struct intel_device_info *) flags;

	if (i915_get_bridge_dev(dev)) {
		ret = -EIO;
		return -1;
	}

	fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
	fprintf(stderr, "Warning: somebody tried to call pci_set_master\n");

	/* 965GM sometimes incorrectly writes to hardware status page (HWS)
	 * using 32bit addressing, overwriting memory if HWS is located
	 * above 4GB.
	 *
	 * The documentation also mentions an issue with undefined
	 * behaviour if any general state is accessed within a page above 4GB,
	 * which also needs to be handled carefully.
	 */
	if (IS_BROADWATER(dev) || IS_CRESTLINE(dev))
		{}

	mmio_bar = IS_GEN2(dev) ? 1 : 0;
	dev_priv->regs = pci_iomap(dev->pdev, mmio_bar, 0);
	if (!dev_priv->regs) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "failed to map registers\n");
		ret = -EIO;
		return -1;
	}

	/* enable GEM by default */
	dev_priv->has_gem = 1;


	/* Try to make sure MCHBAR is enabled before poking at it */
	intel_setup_gmbus(dev);

	/* Make sure the bios did its job and set up vital registers */
	intel_setup_bios(dev);


	{}

	/* On the 945G/GM, the chipset reports the MSI capability on the
	 * integrated graphics even though the support isn't actually there
	 * according to the published specs.  It doesn't appear to function
	 * correctly in testing on 945G.
	 * This may be a side effect of MSI having been made available for PEG
	 * and the registers being closely associated.
	 *
	 * According to chipset errata, on the 965GM, MSI interrupts may
	 * be lost or delayed, but we use them anyways to avoid
	 * stuck interrupts on some machines.
	 */
	if (!IS_I945G(dev) && !IS_I945GM(dev))
		{}

	if (IS_IVYBRIDGE(dev))
		dev_priv->num_pipe = 3;
	else if (IS_MOBILE(dev) || !IS_GEN2(dev))
		dev_priv->num_pipe = 2;
	else
		dev_priv->num_pipe = 1;

	ret = 0;
	if (ret)
		return -1;

	intel_detect_pch(dev);

	if (1) {
		ret = i915_load_modeset_init(dev);
		if (ret < 0) {
			fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
			fprintf(stderr, "failed to init modeset\n");
			return -1;
		}
	}

	/* Must be done after probing outputs */
	intel_opregion_init(dev);

	return 0;


	intel_teardown_gmbus(dev);
	intel_teardown_mchbar(dev);
	freez(dev_priv);
	return ret;
}
