extern struct fb_ops intelfb_ops;

int intelfb_create(struct intel_fbdev *ifbdev,
			  struct drm_fb_helper_surface_size *sizes)
{
	extern struct drm_device *i915;
	struct drm_device *dev = i915;
	extern struct drm_device *i915;
	struct drm_i915_private *dev_priv = i915->dev_private;
	struct fb_info *info;
	struct drm_framebuffer *fb;
	struct drm_mode_fb_cmd2 mode_cmd;
	struct drm_i915_gem_object *obj;
	int size, ret;

	/* we don't do packed 24bpp */
	if (sizes->surface_bpp == 24)
		sizes->surface_bpp = 32;

	mode_cmd.width = sizes->surface_width;
	mode_cmd.height = sizes->surface_height;

	mode_cmd.pitches[0] = ALIGN(mode_cmd.width * ((sizes->surface_bpp + 7) /
						      8), 64);
	mode_cmd.pixel_format = drm_mode_legacy_fb_format(sizes->surface_bpp,
							  sizes->surface_depth);

	size = mode_cmd.pitches[0] * mode_cmd.height;
	size = ALIGN(size, PAGE_SIZE);
	info = allocz(sizeof(*info));
	if (!info) {
		ret = -ENOMEM;
	}

	info->par = ifbdev;

	ret = intel_framebuffer_init(dev, &ifbdev->ifb, &mode_cmd, (struct drm_i915_gem_object *)gfx);
	if (ret)
		return -1;

	fb = &ifbdev->ifb.base;

	ifbdev->helper.fb = fb;
	ifbdev->helper.fbdev = info;

	strcpy(info->fix.id, "inteldrmfb");

	info->flags = FBINFO_DEFAULT | FBINFO_CAN_FORCE_OUTPUT;
	info->fbops = &intelfb_ops;

	ret = fb_alloc_cmap(&info->cmap, 256, 0);
	if (ret) {
		ret = -ENOMEM;
		goto fail;
	}
	/* setup aperture base/size for vesafb takeover */
	info->apertures = alloc_apertures(1);
	if (!info->apertures) {
		ret = -ENOMEM;
		goto fail;
	}
	info->apertures->ranges[0].base = dev->mode_config.fb_base;
	info->apertures->ranges[0].size = aperturesize;

	info->fix.smem_start = dev->mode_config.fb_base;
	info->fix.smem_len = size;

	info->screen_base = gfx;
	if (!info->screen_base) {
		ret = -ENOSPC;
		goto fail;
	}
	info->screen_size = size;

//	memset(info->screen_base, 0, size);

	drm_fb_helper_fill_fix(info, fb->pitches[0], fb->depth);
	drm_fb_helper_fill_var(info, &ifbdev->helper, sizes->fb_width, sizes->fb_height);

	/* Use default scratch pixmap (info->pixmap.flags = FB_PIXMAP_SYSTEM) */

	fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
	fprintf(stderr, "allocated %dx%d fb: 0x%08x, bo %p\n",
		      fb->width, fb->height,
		      obj->gtt_offset, obj);


	return 0;
fail:
	return ret;

}

