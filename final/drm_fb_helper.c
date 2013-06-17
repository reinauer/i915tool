

MODULE_AUTHOR("David Airlie, Jesse Barnes");
MODULE_DESCRIPTION("DRM KMS helper");
MODULE_LICENSE("GPL and additional rights");

static LIST_HEAD(kernel_fb_helper_list);

/* simple single crtc case helper function */
int drm_fb_helper_single_add_all_connectors(struct drm_fb_helper *fb_helper)
{
	extern struct drm_device *i915;
	struct drm_device *dev = i915;
	struct drm_connector *connector;
	int i;

	list_for_each_entry(connector, &dev->mode_config.connector_list, head) {
		struct drm_fb_helper_connector *fb_helper_connector;

		fb_helper_connector = allocz(sizeof(struct drm_fb_helper_connector));
		if (!fb_helper_connector)
			goto fail;

		fb_helper_connector->connector = connector;
		fb_helper->connector_info[fb_helper->connector_count++] = fb_helper_connector;
	}
	return 0;
fail:
	for (i = 0; i < fb_helper->connector_count; i++) {
		freez(fb_helper->connector_info[i]);
		fb_helper->connector_info[i] = NULL;
	}
	fb_helper->connector_count = 0;
	return -ENOMEM;
}
EXPORT_SYMBOL(drm_fb_helper_single_add_all_connectors);
EXPORT_SYMBOL(drm_fb_helper_debug_enter);
EXPORT_SYMBOL(drm_fb_helper_debug_leave);
EXPORT_SYMBOL(drm_fb_helper_restore_fbdev_mode);
EXPORT_SYMBOL(drm_fb_helper_panic);
EXPORT_SYMBOL(drm_fb_helper_restore);

#ifdef CONFIG_MAGIC_SYSRQ
static DECLARE_WORK(drm_fb_helper_restore_work, drm_fb_helper_restore_work_fn);
#else

#endif

static void drm_fb_helper_dpms(struct fb_info *info, int dpms_mode)
{
	struct drm_fb_helper *fb_helper = info->par;
	extern struct drm_device *i915;
	struct drm_device *dev = i915;
	struct drm_crtc *crtc;
	struct drm_connector *connector;
	int i, j;

	/*
	 * For each CRTC in this fb, turn the connectors on/off.
	 */
	for (i = 0; i < fb_helper->crtc_count; i++) {
		crtc = fb_helper->crtc_info[i].mode_set.crtc;

		if (!crtc->enabled)
			continue;

		/* Walk the connectors & encoders on this fb turning them on/off */
		for (j = 0; j < fb_helper->connector_count; j++) {
			connector = fb_helper->connector_info[j]->connector;
			drm_helper_connector_dpms(connector, dpms_mode);
			drm_connector_property_set_value(connector,
				dev->mode_config.dpms_property, dpms_mode);
		}
	}
}
EXPORT_SYMBOL(drm_fb_helper_blank);

int drm_fb_helper_init(struct drm_device *dev,
		       struct drm_fb_helper *fb_helper,
		       int crtc_count, int max_conn_count)
{
	struct drm_crtc *crtc;
	int ret = 0;
	int i;

	fb_helper->dev = dev;

	INIT_LIST_HEAD(&fb_helper->kernel_fb_list);

	fb_helper->crtc_info = allocz(crtc_count * sizeof(struct drm_fb_helper_crtc));
	if (!fb_helper->crtc_info)
		return -ENOMEM;

	fb_helper->crtc_count = crtc_count;
	fb_helper->connector_info = allocz(dev->mode_config.num_connector * sizeof(struct drm_fb_helper_connector *));
	if (!fb_helper->connector_info) {
		freez(fb_helper->crtc_info);
		return -ENOMEM;
	}
	fb_helper->connector_count = 0;

	for (i = 0; i < crtc_count; i++) {
		fb_helper->crtc_info[i].mode_set.connectors =
			allocz(max_conn_count * sizeof(struct drm_connector *));

		if (!fb_helper->crtc_info[i].mode_set.connectors) {
			ret = -ENOMEM;
			goto out_free;
		}
		fb_helper->crtc_info[i].mode_set.num_connectors = 0;
	}

	i = 0;
	list_for_each_entry(crtc, &dev->mode_config.crtc_list, head) {
		fb_helper->crtc_info[i].mode_set.crtc = crtc;
		i++;
	}

	return 0;
out_free:
	return -ENOMEM;
}
EXPORT_SYMBOL(drm_fb_helper_init);
EXPORT_SYMBOL(drm_fb_helper_fini);

static int setcolreg(struct drm_crtc *crtc, u16 red, u16 green,
		     u16 blue, u16 regno, struct fb_info *info)
{
	struct drm_fb_helper *fb_helper = info->par;
	struct drm_framebuffer *fb = fb_helper->fb;
	int pindex;

	if (info->fix.visual == FB_VISUAL_TRUECOLOR) {
		u32 *palette;
		u32 value;
		/* place color in psuedopalette */
		if (regno > 16)
			return -EINVAL;
		palette = (u32 *)info->pseudo_palette;
		red >>= (16 - info->var.red.length);
		green >>= (16 - info->var.green.length);
		blue >>= (16 - info->var.blue.length);
		value = (red << info->var.red.offset) |
			(green << info->var.green.offset) |
			(blue << info->var.blue.offset);
		if (info->var.transp.length > 0) {
			u32 mask = (1 << info->var.transp.length) - 1;
			mask <<= info->var.transp.offset;
			value |= mask;
		}
		palette[regno] = value;
		return 0;
	}

	pindex = regno;

	if (fb->bits_per_pixel == 16) {
		pindex = regno << 3;

		if (fb->depth == 16 && regno > 63)
			return -EINVAL;
		if (fb->depth == 15 && regno > 31)
			return -EINVAL;

		if (fb->depth == 16) {
			u16 r, g, b;
			int i;
			if (regno < 32) {
				for (i = 0; i < 8; i++)
					fb_helper->funcs->gamma_set(crtc, red,
						green, blue, pindex + i);
			}

			fb_helper->funcs->gamma_get(crtc, &r,
						    &g, &b,
						    pindex >> 1);

			for (i = 0; i < 4; i++)
				fb_helper->funcs->gamma_set(crtc, r,
							    green, b,
							    (pindex >> 1) + i);
		}
	}

	if (fb->depth != 16)
		fb_helper->funcs->gamma_set(crtc, red, green, blue, pindex);
	return 0;
}

int drm_fb_helper_setcmap(struct fb_cmap *cmap, struct fb_info *info)
{
	struct drm_fb_helper *fb_helper = info->par;
	struct drm_crtc_helper_funcs *crtc_funcs;
	u16 *red, *green, *blue, *transp;
	struct drm_crtc *crtc;
	int i, j, rc = 0;
	int start;

	for (i = 0; i < fb_helper->crtc_count; i++) {
		crtc = fb_helper->crtc_info[i].mode_set.crtc;
		crtc_funcs = crtc->helper_private;

		red = cmap->red;
		green = cmap->green;
		blue = cmap->blue;
		transp = cmap->transp;
		start = cmap->start;

		for (j = 0; j < cmap->len; j++) {
			u16 hred, hgreen, hblue, htransp = 0xffff;

			hred = *red++;
			hgreen = *green++;
			hblue = *blue++;

			if (transp)
				htransp = *transp++;

			rc = setcolreg(crtc, hred, hgreen, hblue, start++, info);
			if (rc)
				return rc;
		}
		crtc_funcs->load_lut(crtc);
	}
	return rc;
}
EXPORT_SYMBOL(drm_fb_helper_setcmap);
EXPORT_SYMBOL(drm_fb_helper_check_var);

/* this will let fbcon do the mode init */
int drm_fb_helper_set_par(struct fb_info *info)
{
	struct drm_fb_helper *fb_helper = info->par;
	extern struct drm_device *i915;
	struct drm_device *dev = i915;
	struct fb_var_screeninfo *var = &info->var;
	struct drm_crtc *crtc;
	int ret;
	int i;

	if (var->pixclock != 0) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "PIXEL CLOCK SET\n");
		return -EINVAL;
	}

	for (i = 0; i < fb_helper->crtc_count; i++) {
		crtc = fb_helper->crtc_info[i].mode_set.crtc;
		ret = crtc->funcs->set_config(&fb_helper->crtc_info[i].mode_set);
		if (ret) {
			return ret;
		}
	}

	if (fb_helper->delayed_hotplug) {
		fb_helper->delayed_hotplug = false;
		drm_fb_helper_hotplug_event(fb_helper);
	}
	return 0;
}
EXPORT_SYMBOL(drm_fb_helper_set_par);
EXPORT_SYMBOL(drm_fb_helper_pan_display);

int drm_fb_helper_single_fb_probe(struct drm_fb_helper *fb_helper,
				  int preferred_bpp)
{
	int new_fb = 0;
	int crtc_count = 0;
	int i;
	struct fb_info *info;
	struct drm_fb_helper_surface_size sizes;
	int gamma_size = 0;

	memset(&sizes, 0, sizeof(struct drm_fb_helper_surface_size));
	sizes.surface_depth = 24;
	sizes.surface_bpp = 32;
	sizes.fb_width = (unsigned)-1;
	sizes.fb_height = (unsigned)-1;

	/* if driver picks 8 or 16 by default use that
	   for both depth/bpp */
	if (preferred_bpp != sizes.surface_bpp) {
		sizes.surface_depth = sizes.surface_bpp = preferred_bpp;
	}
	/* first up get a count of crtcs now in use and new min/maxes width/heights */
	for (i = 0; i < fb_helper->connector_count; i++) {
		struct drm_fb_helper_connector *fb_helper_conn = fb_helper->connector_info[i];
		struct drm_cmdline_mode *cmdline_mode;

		cmdline_mode = &fb_helper_conn->cmdline_mode;

		if (cmdline_mode->bpp_specified) {
			switch (cmdline_mode->bpp) {
			case 8:
				sizes.surface_depth = sizes.surface_bpp = 8;
				break;
			case 15:
				sizes.surface_depth = 15;
				sizes.surface_bpp = 16;
				break;
			case 16:
				sizes.surface_depth = sizes.surface_bpp = 16;
				break;
			case 24:
				sizes.surface_depth = sizes.surface_bpp = 24;
				break;
			case 32:
				sizes.surface_depth = 24;
				sizes.surface_bpp = 32;
				break;
			}
			break;
		}
	}

	crtc_count = 0;
	for (i = 0; i < fb_helper->crtc_count; i++) {
		struct drm_display_mode *desired_mode;
		desired_mode = fb_helper->crtc_info[i].desired_mode;

		if (desired_mode) {
			if (gamma_size == 0)
				gamma_size = fb_helper->crtc_info[i].mode_set.crtc->gamma_size;
			if (desired_mode->hdisplay < sizes.fb_width)
				sizes.fb_width = desired_mode->hdisplay;
			if (desired_mode->vdisplay < sizes.fb_height)
				sizes.fb_height = desired_mode->vdisplay;
			if (desired_mode->hdisplay > sizes.surface_width)
				sizes.surface_width = desired_mode->hdisplay;
			if (desired_mode->vdisplay > sizes.surface_height)
				sizes.surface_height = desired_mode->vdisplay;
			crtc_count++;
		}
	}

	if (crtc_count == 0 || sizes.fb_width == -1 || sizes.fb_height == -1) {
		/* hmm everyone went away - assume VGA cable just fell out
		   and will come back later. */
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "Cannot find any crtc or sizes - going 1024x768\n");
		sizes.fb_width = sizes.surface_width = 1024;
		sizes.fb_height = sizes.surface_height = 768;
	}

	/* push down into drivers */
	new_fb = (*fb_helper->funcs->fb_probe)(fb_helper, &sizes);
	if (new_fb < 0)
		return new_fb;

	info = fb_helper->fbdev;

	/* set the fb pointer */
	for (i = 0; i < fb_helper->crtc_count; i++) {
		fb_helper->crtc_info[i].mode_set.fb = fb_helper->fb;
	}

	if (new_fb) {
		info->var.pixclock = 0;
		if (0 < 0) {
			return -EINVAL;
		}

		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "fb%d: %s frame buffer device\n", info->node,
		       info->fix.id);

	} else {
		drm_fb_helper_set_par(info);
	}

	/* Switch back to kernel console on panic */
	/* multi card linked list maybe */
	
	if (new_fb)
		list_add(&fb_helper->kernel_fb_list, &kernel_fb_helper_list);

	return 0;
}
EXPORT_SYMBOL(drm_fb_helper_single_fb_probe);

void drm_fb_helper_fill_fix(struct fb_info *info, uint32_t pitch,
			    uint32_t depth)
{
	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.visual = depth == 8 ? FB_VISUAL_PSEUDOCOLOR :
		FB_VISUAL_TRUECOLOR;
	info->fix.mmio_start = 0;
	info->fix.mmio_len = 0;
	info->fix.type_aux = 0;
	info->fix.xpanstep = 1; /* doing it in hw */
	info->fix.ypanstep = 1; /* doing it in hw */
	info->fix.ywrapstep = 0;
	info->fix.accel = FB_ACCEL_NONE;
	info->fix.type_aux = 0;

	info->fix.line_length = pitch;
	return;
}
EXPORT_SYMBOL(drm_fb_helper_fill_fix);

void drm_fb_helper_fill_var(struct fb_info *info, struct drm_fb_helper *fb_helper,
			    uint32_t fb_width, uint32_t fb_height)
{
	struct drm_framebuffer *fb = fb_helper->fb;
	info->pseudo_palette = fb_helper->pseudo_palette;
	info->var.xres_virtual = fb->width;
	info->var.yres_virtual = fb->height;
	info->var.bits_per_pixel = fb->bits_per_pixel;
	info->var.accel_flags = FB_ACCELF_TEXT;
	info->var.xoffset = 0;
	info->var.yoffset = 0;
	info->var.activate = FB_ACTIVATE_NOW;
	info->var.height = -1;
	info->var.width = -1;

	switch (fb->depth) {
	case 8:
		info->var.red.offset = 0;
		info->var.green.offset = 0;
		info->var.blue.offset = 0;
		info->var.red.length = 8; /* 8bit DAC */
		info->var.green.length = 8;
		info->var.blue.length = 8;
		info->var.transp.offset = 0;
		info->var.transp.length = 0;
		break;
	case 15:
		info->var.red.offset = 10;
		info->var.green.offset = 5;
		info->var.blue.offset = 0;
		info->var.red.length = 5;
		info->var.green.length = 5;
		info->var.blue.length = 5;
		info->var.transp.offset = 15;
		info->var.transp.length = 1;
		break;
	case 16:
		info->var.red.offset = 11;
		info->var.green.offset = 5;
		info->var.blue.offset = 0;
		info->var.red.length = 5;
		info->var.green.length = 6;
		info->var.blue.length = 5;
		info->var.transp.offset = 0;
		break;
	case 24:
		info->var.red.offset = 16;
		info->var.green.offset = 8;
		info->var.blue.offset = 0;
		info->var.red.length = 8;
		info->var.green.length = 8;
		info->var.blue.length = 8;
		info->var.transp.offset = 0;
		info->var.transp.length = 0;
		break;
	case 32:
		info->var.red.offset = 16;
		info->var.green.offset = 8;
		info->var.blue.offset = 0;
		info->var.red.length = 8;
		info->var.green.length = 8;
		info->var.blue.length = 8;
		info->var.transp.offset = 24;
		info->var.transp.length = 8;
		break;
	default:
		break;
	}

	info->var.xres = fb_width;
	info->var.yres = fb_height;
}
EXPORT_SYMBOL(drm_fb_helper_fill_var);

static int drm_fb_helper_probe_connector_modes(struct drm_fb_helper *fb_helper,
					       uint32_t maxX,
					       uint32_t maxY)
{
	struct drm_connector *connector;
	int count = 0;
	int i;

	for (i = 0; i < fb_helper->connector_count; i++) {
		connector = fb_helper->connector_info[i]->connector;
		count += connector->funcs->fill_modes(connector, maxX, maxY);
	}

	return count;
}

static struct drm_display_mode *drm_has_preferred_mode(struct drm_fb_helper_connector *fb_connector, int width, int height)
{
	struct drm_display_mode *mode;

	list_for_each_entry(mode, &fb_connector->connector->modes, head) {
		if (drm_mode_width(mode) > width ||
		    drm_mode_height(mode) > height)
			continue;
		if (mode->type & DRM_MODE_TYPE_PREFERRED)
			return mode;
	}
	return NULL;
}

static bool drm_connector_enabled(struct drm_connector *connector, bool strict)
{
	bool enable;

	if (strict) {
		enable = connector->status == connector_status_connected;
	} else {
		enable = connector->status != connector_status_disconnected;
	}
	return enable;
}

static void drm_enable_connectors(struct drm_fb_helper *fb_helper,
				  bool *enabled)
{
	bool any_enabled = false;
	struct drm_connector *connector;
	int i = 0;

	for (i = 0; i < fb_helper->connector_count; i++) {
		connector = fb_helper->connector_info[i]->connector;
		enabled[i] = drm_connector_enabled(connector, true);
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "connector %d enabled? %s\n", connector->base.id,
			  enabled[i] ? "yes" : "no");
		any_enabled |= enabled[i];
	}

	if (any_enabled)
		return;

	for (i = 0; i < fb_helper->connector_count; i++) {
		connector = fb_helper->connector_info[i]->connector;
		enabled[i] = drm_connector_enabled(connector, false);
	}
}

static bool drm_target_cloned(struct drm_fb_helper *fb_helper,
			      struct drm_display_mode **modes,
			      bool *enabled, int width, int height)
{
	int count, i, j;
	bool can_clone = false;
	struct drm_fb_helper_connector *fb_helper_conn;
	struct drm_display_mode *dmt_mode, *mode;

	/* only contemplate cloning in the single crtc case */
	if (fb_helper->crtc_count > 1)
		return false;

	count = 0;
	for (i = 0; i < fb_helper->connector_count; i++) {
		if (enabled[i])
			count++;
	}

	/* only contemplate cloning if more than one connector is enabled */
	if (count <= 1)
		return false;

	/* check the command line or if nothing common pick 1024x768 */
	can_clone = true;
	for (i = 0; i < fb_helper->connector_count; i++) {
		if (!enabled[i])
			continue;
		fb_helper_conn = fb_helper->connector_info[i];
		modes[i] = NULL;
		if (!modes[i]) {
			can_clone = false;
			break;
		}
		for (j = 0; j < i; j++) {
			if (!enabled[j])
				continue;
			if (!drm_mode_equal(modes[j], modes[i]))
				can_clone = false;
		}
	}

	if (can_clone) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "can clone using command line\n");
		return true;
	}

	/* try and find a 1024x768 mode on each connector */
	can_clone = true;
	dmt_mode = drm_mode_find_dmt(fb_helper->dev, 1024, 768, 60);

	for (i = 0; i < fb_helper->connector_count; i++) {

		if (!enabled[i])
			continue;

		fb_helper_conn = fb_helper->connector_info[i];
		list_for_each_entry(mode, &fb_helper_conn->connector->modes, head) {
			if (drm_mode_equal(mode, dmt_mode))
				modes[i] = mode;
		}
		if (!modes[i])
			can_clone = false;
	}

	if (can_clone) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "can clone using 1024x768\n");
		return true;
	}
	fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
	fprintf(stderr, "kms: can't enable cloning when we probably wanted to.\n");
	return false;
}

static bool drm_target_preferred(struct drm_fb_helper *fb_helper,
				 struct drm_display_mode **modes,
				 bool *enabled, int width, int height)
{
	struct drm_fb_helper_connector *fb_helper_conn;
	int i;

	for (i = 0; i < fb_helper->connector_count; i++) {
		fb_helper_conn = fb_helper->connector_info[i];

		if (enabled[i] == false)
			continue;

		DRM_DEBUG_KMS("looking for cmdline mode on connector %d\n",
			      fb_helper_conn->connector->base.id);

		/* got for command line mode first */
		modes[i] = NULL;
		if (!modes[i]) {
			DRM_DEBUG_KMS("looking for preferred mode on connector %d\n",
				      fb_helper_conn->connector->base.id);
			modes[i] = drm_has_preferred_mode(fb_helper_conn, width, height);
		}
		/* No preferred modes, pick one off the list */
		if (!modes[i] && !list_empty(&fb_helper_conn->connector->modes)) {
			list_for_each_entry(modes[i], &fb_helper_conn->connector->modes, head)
				break;
		}
		DRM_DEBUG_KMS("found mode %s\n", modes[i] ? modes[i]->name :
			  "none");
	}
	return true;
}

static int drm_pick_crtcs(struct drm_fb_helper *fb_helper,
			  struct drm_fb_helper_crtc **best_crtcs,
			  struct drm_display_mode **modes,
			  int n, int width, int height)
{
	int c, o;
	extern struct drm_device *i915;
	struct drm_device *dev = i915;
	struct drm_connector *connector;
	struct drm_connector_helper_funcs *connector_funcs;
	struct drm_encoder *encoder;
	struct drm_fb_helper_crtc *best_crtc;
	int my_score, best_score, score;
	struct drm_fb_helper_crtc **crtcs, *crtc;
	struct drm_fb_helper_connector *fb_helper_conn;

	if (n == fb_helper->connector_count)
		return 0;

	fb_helper_conn = fb_helper->connector_info[n];
	connector = fb_helper_conn->connector;

	best_crtcs[n] = NULL;
	best_crtc = NULL;
	best_score = drm_pick_crtcs(fb_helper, best_crtcs, modes, n+1, width, height);
	if (modes[n] == NULL)
		return best_score;

	crtcs = allocz(dev->mode_config.num_connector * sizeof(struct drm_fb_helper_crtc *));
	if (!crtcs)
		return best_score;

	my_score = 1;
	if (connector->status == connector_status_connected)
		my_score++;
	if (0)
		my_score++;
	if (drm_has_preferred_mode(fb_helper_conn, width, height))
		my_score++;

	connector_funcs = connector->helper_private;
	encoder = connector_funcs->best_encoder(connector);
	if (!encoder)
		goto out;

	/* select a crtc for this connector and then attempt to configure
	   remaining connectors */
	for (c = 0; c < fb_helper->crtc_count; c++) {
		crtc = &fb_helper->crtc_info[c];

		if ((encoder->possible_crtcs & (1 << c)) == 0) {
			continue;
		}

		for (o = 0; o < n; o++)
			if (best_crtcs[o] == crtc)
				break;

		if (o < n) {
			/* ignore cloning unless only a single crtc */
			if (fb_helper->crtc_count > 1)
				continue;

			if (!drm_mode_equal(modes[o], modes[n]))
				continue;
		}

		crtcs[n] = crtc;
		memcpy(crtcs, best_crtcs, n * sizeof(struct drm_fb_helper_crtc *));
		score = my_score + drm_pick_crtcs(fb_helper, crtcs, modes, n + 1,
						  width, height);
		if (score > best_score) {
			best_crtc = crtc;
			best_score = score;
			memcpy(best_crtcs, crtcs,
			       dev->mode_config.num_connector *
			       sizeof(struct drm_fb_helper_crtc *));
		}
	}
out:
	freez(crtcs);
	return best_score;
}

static void drm_setup_crtcs(struct drm_fb_helper *fb_helper)
{
	extern struct drm_device *i915;
	struct drm_device *dev = i915;
	struct drm_fb_helper_crtc **crtcs;
	struct drm_display_mode **modes;
	struct drm_encoder *encoder;
	struct drm_mode_set *modeset;
	bool *enabled;
	int width, height;
	int i, ret;

	fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
	fprintf(stderr, "\n");

	width = dev->mode_config.max_width;
	height = dev->mode_config.max_height;

	/* clean out all the encoder/crtc combos */
	list_for_each_entry(encoder, &dev->mode_config.encoder_list, head) {
		encoder->crtc = NULL;
	}

	crtcs =allocz(dev->mode_config.num_connector * sizeof(struct drm_fb_helper_crtc *));
	modes =allocz(dev->mode_config.num_connector * sizeof(struct drm_display_mode *));
	enabled =allocz(dev->mode_config.num_connector * sizeof(bool));

	drm_enable_connectors(fb_helper, enabled);

	ret = 0;
	if (!ret) {
		ret = drm_target_preferred(fb_helper, modes, enabled, width, height);
		if (!ret) {
			fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
			fprintf(stderr, "Unable to find initial modes\n");
		}
	}

	fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
	fprintf(stderr, "picking CRTCs for %dx%d config\n", width, height);

	drm_pick_crtcs(fb_helper, crtcs, modes, 0, width, height);

	/* need to set the modesets up here for use later */
	/* fill out the connector<->crtc mappings into the modesets */
	for (i = 0; i < fb_helper->crtc_count; i++) {
		modeset = &fb_helper->crtc_info[i].mode_set;
		modeset->num_connectors = 0;
	}

	for (i = 0; i < fb_helper->connector_count; i++) {
		struct drm_display_mode *mode = modes[i];
		struct drm_fb_helper_crtc *fb_crtc = crtcs[i];
		modeset = &fb_crtc->mode_set;

		if (mode && fb_crtc) {
			fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
			fprintf(stderr, "desired mode %s set on crtc %d\n",
				      mode->name, fb_crtc->mode_set.crtc->base.id);
			fb_crtc->desired_mode = mode;
			if (modeset->mode)
				{}
			modeset->mode = drm_mode_duplicate(dev,
							   fb_crtc->desired_mode);
			modeset->connectors[modeset->num_connectors++] = fb_helper->connector_info[i]->connector;
		}
	}

	freez(crtcs);
	freez(modes);
	freez(enabled);
}

/**
 * drm_helper_initial_config - setup a sane initial connector configuration
 * @dev: DRM device
 *
 * LOCKING:
 * Called at init time, must take mode config lock.
 *
 * Scan the CRTCs and connectors and try to put together an initial setup.
 * At the moment, this is a cloned configuration across all heads with
 * a new framebuffer object as the backing store.
 *
 * RETURNS:
 * Zero if everything went ok, nonzero otherwise.
 */
bool drm_fb_helper_initial_config(struct drm_fb_helper *fb_helper, int bpp_sel)
{
	extern struct drm_device *i915;
	struct drm_device *dev = i915;
	int count = 0;

	count = drm_fb_helper_probe_connector_modes(fb_helper,
						    dev->mode_config.max_width,
						    dev->mode_config.max_height);
	/*
	 * we shouldn't end up with no modes here.
	 */
	if (count == 0) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "No connectors reported connected with modes\n");
	}
	drm_setup_crtcs(fb_helper);

	return drm_fb_helper_single_fb_probe(fb_helper, bpp_sel);
}
EXPORT_SYMBOL(drm_fb_helper_initial_config);

/**
 * drm_fb_helper_hotplug_event - respond to a hotplug notification by
 *                               probing all the outputs attached to the fb.
 * @fb_helper: the drm_fb_helper
 *
 * LOCKING:
 * Called at runtime, must take mode config lock.
 *
 * Scan the connectors attached to the fb_helper and try to put together a
 * setup after *notification of a change in output configuration.
 *
 * RETURNS:
 * 0 on success and a non-zero error code otherwise.
 */
int drm_fb_helper_hotplug_event(struct drm_fb_helper *fb_helper)
{
	extern struct drm_device *i915;
	struct drm_device *dev = i915;
	int count = 0;
	u32 max_width, max_height, bpp_sel;
	bool bound = false, crtcs_bound = false;
	struct drm_crtc *crtc;

	if (!fb_helper->fb)
		return 0;

	list_for_each_entry(crtc, &dev->mode_config.crtc_list, head) {
		if (crtc->fb)
			crtcs_bound = true;
		if (crtc->fb == fb_helper->fb)
			bound = true;
	}

	if (!bound && crtcs_bound) {
		fb_helper->delayed_hotplug = true;
		return 0;
	}
	fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
	fprintf(stderr, "\n");

	max_width = fb_helper->fb->width;
	max_height = fb_helper->fb->height;
	bpp_sel = fb_helper->fb->bits_per_pixel;

	count = drm_fb_helper_probe_connector_modes(fb_helper, max_width,
						    max_height);
	drm_setup_crtcs(fb_helper);

	return drm_fb_helper_single_fb_probe(fb_helper, bpp_sel);
}
EXPORT_SYMBOL(drm_fb_helper_hotplug_event);

/* The Kconfig DRM_KMS_HELPER selects FRAMEBUFFER_CONSOLE (if !EXPERT)
 * but the module doesn't depend on any fb console symbols.  At least
 * attempt to load fbcon to avoid leaving the system without a usable console.
 */
#if defined(CONFIG_FRAMEBUFFER_CONSOLE_MODULE) && !defined(CONFIG_EXPERT)


module_init(drm_fb_helper_modinit);
#endif
