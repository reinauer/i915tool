

struct fb_ops intelfb_ops = {
	.fb_setcmap = drm_fb_helper_setcmap,
};

static int intel_fb_find_or_create_single(struct drm_fb_helper *helper,
					  struct drm_fb_helper_surface_size *sizes)
{
	struct intel_fbdev *ifbdev = (struct intel_fbdev *)helper;
	int new_fb = 0;
	int ret;

	if (!helper->fb) {
		ret = intelfb_create(ifbdev, sizes);
		if (ret)
			return ret;
		new_fb = 1;
	}
	return new_fb;
}

static struct drm_fb_helper_funcs intel_fb_helper_funcs = {
	.gamma_set = intel_crtc_fb_gamma_set,
	.gamma_get = intel_crtc_fb_gamma_get,
	.fb_probe = intel_fb_find_or_create_single,
};

int intel_fbdev_init(struct drm_device *dev)
{
	struct intel_fbdev *ifbdev;
	drm_i915_private_t *dev_priv = dev->dev_private;
	int ret;

	ifbdev = allocz(sizeof(struct intel_fbdev));
	if (!ifbdev)
		return -ENOMEM;

	dev_priv->fbdev = ifbdev;
	ifbdev->helper.funcs = &intel_fb_helper_funcs;

	ret = drm_fb_helper_init(dev, &ifbdev->helper,
				 dev_priv->num_pipe,
				 INTELFB_CONN_LIMIT);
	if (ret) {
		freez(ifbdev);
		return ret;
	}

	drm_fb_helper_single_add_all_connectors(&ifbdev->helper);
	drm_fb_helper_initial_config(&ifbdev->helper, 32);
	return 0;
}

MODULE_LICENSE("GPL and additional rights");

void intel_fb_output_poll_changed(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	drm_fb_helper_hotplug_event(&dev_priv->fbdev->helper);
}
