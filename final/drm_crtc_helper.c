

static bool drm_kms_helper_poll = true;
module_param_named(poll, drm_kms_helper_poll, bool, 0600);

static void drm_mode_validate_flag(struct drm_connector *connector,
				   int flags)
{
	struct drm_display_mode *mode;

	if (flags == (DRM_MODE_FLAG_DBLSCAN | DRM_MODE_FLAG_INTERLACE))
		return;

	list_for_each_entry(mode, &connector->modes, head) {
		if ((mode->flags & DRM_MODE_FLAG_INTERLACE) &&
				!(flags & DRM_MODE_FLAG_INTERLACE))
			mode->status = MODE_NO_INTERLACE;
		if ((mode->flags & DRM_MODE_FLAG_DBLSCAN) &&
				!(flags & DRM_MODE_FLAG_DBLSCAN))
			mode->status = MODE_NO_DBLESCAN;
	}

	return;
}

/**
 * drm_helper_probe_single_connector_modes - get complete set of display modes
 * @dev: DRM device
 * @maxX: max width for modes
 * @maxY: max height for modes
 *
 * LOCKING:
 * Caller must hold mode config lock.
 *
 * Based on @dev's mode_config layout, scan all the connectors and try to detect
 * modes on them.  Modes will first be added to the connector's probed_modes
 * list, then culled (based on validity and the @maxX, @maxY parameters) and
 * put into the normal modes list.
 *
 * Intended to be used either at bootup time or when major configuration
 * changes have occurred.
 *
 * FIXME: take into account monitor limits
 *
 * RETURNS:
 * Number of modes found on @connector.
 */
int drm_helper_probe_single_connector_modes(struct drm_connector *connector,
					    uint32_t maxX, uint32_t maxY)
{
	extern struct drm_device *i915;
	struct drm_device *dev = i915;
	struct drm_display_mode *mode;
	struct drm_connector_helper_funcs *connector_funcs =
		connector->helper_private;
	int count = 0;
	int mode_flags = 0;

	fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
	fprintf(stderr, "[CONNECTOR:%d:%s]\n", connector->base.id,
			drm_get_connector_name(connector));
	/* set all modes to the unverified state */
	list_for_each_entry(mode, &connector->modes, head)
		mode->status = MODE_UNVERIFIED;

	if (connector->force) {
		if (connector->force == DRM_FORCE_ON)
			connector->status = connector_status_connected;
		else
			connector->status = connector_status_disconnected;
		if (connector->funcs->force)
			connector->funcs->force(connector);
	} else {
		connector->status = connector->funcs->detect(connector, true);
	}

	if (connector->status == connector_status_disconnected) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "[CONNECTOR:%d:%s] disconnected\n",
			connector->base.id, drm_get_connector_name(connector));
		drm_mode_connector_update_edid_property(connector, NULL);
		goto prune;
	}

#ifdef CONFIG_DRM_LOAD_EDID_FIRMWARE
	count = drm_load_edid_firmware(connector);
	if (count == 0)
#endif
		count = (*connector_funcs->get_modes)(connector);

	if (count == 0 && connector->status == connector_status_connected)
		count = drm_add_modes_noedid(connector, 1024, 768);
	if (count == 0)
		goto prune;

	drm_mode_connector_list_update(connector);

	if (maxX && maxY)
		drm_mode_validate_size(dev, &connector->modes, maxX,
				       maxY, 0);

	if (connector->interlace_allowed)
		mode_flags |= DRM_MODE_FLAG_INTERLACE;
	if (connector->doublescan_allowed)
		mode_flags |= DRM_MODE_FLAG_DBLSCAN;
	drm_mode_validate_flag(connector, mode_flags);

	list_for_each_entry(mode, &connector->modes, head) {
		if (mode->status == MODE_OK)
			mode->status = connector_funcs->mode_valid(connector,
								   mode);
	}

prune:
	drm_mode_prune_invalid(dev, &connector->modes, true);

	if (list_empty(&connector->modes))
		return 0;

	fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
	fprintf(stderr, "[CONNECTOR:%d:%s] probed modes :\n", connector->base.id,
			drm_get_connector_name(connector));
	list_for_each_entry(mode, &connector->modes, head) {
		mode->vrefresh = drm_mode_vrefresh(mode);

		drm_mode_set_crtcinfo(mode, CRTC_INTERLACE_HALVE_V);
		drm_mode_debug_printmodeline(mode);
	}

	return count;
}
EXPORT_SYMBOL(drm_helper_probe_single_connector_modes);

/**
 * drm_helper_encoder_in_use - check if a given encoder is in use
 * @encoder: encoder to check
 *
 * LOCKING:
 * Caller must hold mode config lock.
 *
 * Walk @encoders's DRM device's mode_config and see if it's in use.
 *
 * RETURNS:
 * True if @encoder is part of the mode_config, false otherwise.
 */
bool drm_helper_encoder_in_use(struct drm_encoder *encoder)
{
	struct drm_connector *connector;
	extern struct drm_device *i915;
	struct drm_device *dev = i915;
	list_for_each_entry(connector, &dev->mode_config.connector_list, head)
		if (connector->encoder == encoder)
			return true;
	return false;
}
EXPORT_SYMBOL(drm_helper_encoder_in_use);

/**
 * drm_helper_crtc_in_use - check if a given CRTC is in a mode_config
 * @crtc: CRTC to check
 *
 * LOCKING:
 * Caller must hold mode config lock.
 *
 * Walk @crtc's DRM device's mode_config and see if it's in use.
 *
 * RETURNS:
 * True if @crtc is part of the mode_config, false otherwise.
 */
bool drm_helper_crtc_in_use(struct drm_crtc *crtc)
{
	struct drm_encoder *encoder;
	extern struct drm_device *i915;
	struct drm_device *dev = i915;
	/* FIXME: Locking around list access? */
	list_for_each_entry(encoder, &dev->mode_config.encoder_list, head)
		if (encoder->crtc == crtc && drm_helper_encoder_in_use(encoder))
			return true;
	return false;
}
EXPORT_SYMBOL(drm_helper_crtc_in_use);

static void
drm_encoder_disable(struct drm_encoder *encoder)
{
	struct drm_encoder_helper_funcs *encoder_funcs = encoder->helper_private;

	if (encoder_funcs->disable)
		(*encoder_funcs->disable)(encoder);
	else
		(*encoder_funcs->dpms)(encoder, DRM_MODE_DPMS_OFF);
}
EXPORT_SYMBOL(drm_helper_disable_unused_functions);

/*
 * Check the CRTC we're going to map each output to vs. its current
 * CRTC.  If they don't match, we have to disable the output and the CRTC
 * since the driver will have to re-route things.
 */
static void
drm_crtc_prepare_encoders(struct drm_device *dev)
{
	struct drm_encoder_helper_funcs *encoder_funcs;
	struct drm_encoder *encoder;

	list_for_each_entry(encoder, &dev->mode_config.encoder_list, head) {
		encoder_funcs = encoder->helper_private;
		/* Disable unused encoders */
		if (encoder->crtc == NULL)
			drm_encoder_disable(encoder);
		/* Disable encoders whose CRTC is about to change */
		if (encoder_funcs->get_crtc &&
		    encoder->crtc != (*encoder_funcs->get_crtc)(encoder))
			drm_encoder_disable(encoder);
	}
}

/**
 * drm_crtc_set_mode - set a mode
 * @crtc: CRTC to program
 * @mode: mode to use
 * @x: width of mode
 * @y: height of mode
 *
 * LOCKING:
 * Caller must hold mode config lock.
 *
 * Try to set @mode on @crtc.  Give @crtc and its associated connectors a chance
 * to fixup or reject the mode prior to trying to set it.
 *
 * RETURNS:
 * True if the mode was set successfully, or false otherwise.
 */
bool drm_crtc_helper_set_mode(struct drm_crtc *crtc,
			      struct drm_display_mode *mode,
			      int x, int y,
			      struct drm_framebuffer *old_fb)
{
	extern struct drm_device *i915;
	struct drm_device *dev = i915;
	struct drm_display_mode *adjusted_mode, saved_mode, saved_hwmode;
	struct drm_crtc_helper_funcs *crtc_funcs = crtc->helper_private;
	struct drm_encoder_helper_funcs *encoder_funcs;
	int saved_x, saved_y;
	struct drm_encoder *encoder;
	bool ret = true;

	crtc->enabled = drm_helper_crtc_in_use(crtc);
	if (!crtc->enabled)
		return true;

	adjusted_mode = drm_mode_duplicate(dev, mode);
	if (!adjusted_mode)
		return false;

	saved_hwmode = crtc->hwmode;
	saved_mode = crtc->mode;
	saved_x = crtc->x;
	saved_y = crtc->y;

	/* Update crtc values up front so the driver can rely on them for mode
	 * setting.
	 */
	crtc->mode = *mode;
	crtc->x = x;
	crtc->y = y;

	/* Pass our mode to the connectors and the CRTC to give them a chance to
	 * adjust it according to limitations or connector properties, and also
	 * a chance to reject the mode entirely.
	 */
	list_for_each_entry(encoder, &dev->mode_config.encoder_list, head) {

		if (encoder->crtc != crtc)
			continue;
		encoder_funcs = encoder->helper_private;
		if (!(ret = encoder_funcs->mode_fixup(encoder, mode,
						      adjusted_mode))) {
			fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
			fprintf(stderr, "Encoder fixup failed\n");
			goto done;
		}
	}

	if (!(ret = crtc_funcs->mode_fixup(crtc, mode, adjusted_mode))) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "CRTC fixup failed\n");
		goto done;
	}
	fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
	fprintf(stderr, "[CRTC:%d]\n", crtc->base.id);

	/* Prepare the encoders and CRTCs before setting the mode. */
	list_for_each_entry(encoder, &dev->mode_config.encoder_list, head) {

		if (encoder->crtc != crtc)
			continue;
		encoder_funcs = encoder->helper_private;
		/* Disable the encoders as the first thing we do. */
		encoder_funcs->prepare(encoder);
	}

	drm_crtc_prepare_encoders(dev);

	/* Set up the DPLL and any encoders state that needs to adjust or depend
	 * on the DPLL.
	 */
	ret = !crtc_funcs->mode_set(crtc, mode, adjusted_mode, x, y, old_fb);
	if (!ret)
	    goto done;

	list_for_each_entry(encoder, &dev->mode_config.encoder_list, head) {

		if (encoder->crtc != crtc)
			continue;

		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "[ENCODER:%d:%s] set [MODE:%d:%s]\n",
			encoder->base.id, drm_get_encoder_name(encoder),
			mode->base.id, mode->name);
		encoder_funcs = encoder->helper_private;
		encoder_funcs->mode_set(encoder, mode, adjusted_mode);
	}

	/* Now enable the clocks, plane, pipe, and connectors that we set up. */
	crtc_funcs->commit(crtc);

	list_for_each_entry(encoder, &dev->mode_config.encoder_list, head) {

		if (encoder->crtc != crtc)
			continue;

		encoder_funcs = encoder->helper_private;
		encoder_funcs->commit(encoder);

	}

	/* Store real post-adjustment hardware mode. */
	crtc->hwmode = *adjusted_mode;

	/* FIXME: add subpixel order */
done:
	if (!ret) {
		crtc->hwmode = saved_hwmode;
		crtc->mode = saved_mode;
		crtc->x = saved_x;
		crtc->y = saved_y;
	}

	return ret;
}
EXPORT_SYMBOL(drm_crtc_helper_set_mode);
EXPORT_SYMBOL(drm_crtc_helper_set_config);

static int drm_helper_choose_encoder_dpms(struct drm_encoder *encoder)
{
	int dpms = DRM_MODE_DPMS_OFF;
	struct drm_connector *connector;
	extern struct drm_device *i915;
	struct drm_device *dev = i915;

	list_for_each_entry(connector, &dev->mode_config.connector_list, head)
		if (connector->encoder == encoder)
			if (connector->dpms < dpms)
				dpms = connector->dpms;
	return dpms;
}

static int drm_helper_choose_crtc_dpms(struct drm_crtc *crtc)
{
	int dpms = DRM_MODE_DPMS_OFF;
	struct drm_connector *connector;
	extern struct drm_device *i915;
	struct drm_device *dev = i915;

	list_for_each_entry(connector, &dev->mode_config.connector_list, head)
		if (connector->encoder && connector->encoder->crtc == crtc)
			if (connector->dpms < dpms)
				dpms = connector->dpms;
	return dpms;
}

/**
 * drm_helper_connector_dpms
 * @connector affected connector
 * @mode DPMS mode
 *
 * Calls the low-level connector DPMS function, then
 * calls appropriate encoder and crtc DPMS functions as well
 */
void drm_helper_connector_dpms(struct drm_connector *connector, int mode)
{
	struct drm_encoder *encoder = connector->encoder;
	struct drm_crtc *crtc = encoder ? encoder->crtc : NULL;
	int old_dpms;

	if (mode == connector->dpms)
		return;

	old_dpms = connector->dpms;
	connector->dpms = mode;

	/* from off to on, do crtc then encoder */
	if (mode < old_dpms) {
		if (crtc) {
			struct drm_crtc_helper_funcs *crtc_funcs = crtc->helper_private;
			if (crtc_funcs->dpms)
				(*crtc_funcs->dpms) (crtc,
						     drm_helper_choose_crtc_dpms(crtc));
		}
		if (encoder) {
			struct drm_encoder_helper_funcs *encoder_funcs = encoder->helper_private;
			if (encoder_funcs->dpms)
				(*encoder_funcs->dpms) (encoder,
							drm_helper_choose_encoder_dpms(encoder));
		}
	}

	/* from on to off, do encoder then crtc */
	if (mode > old_dpms) {
		if (encoder) {
			struct drm_encoder_helper_funcs *encoder_funcs = encoder->helper_private;
			if (encoder_funcs->dpms)
				(*encoder_funcs->dpms) (encoder,
							drm_helper_choose_encoder_dpms(encoder));
		}
		if (crtc) {
			struct drm_crtc_helper_funcs *crtc_funcs = crtc->helper_private;
			if (crtc_funcs->dpms)
				(*crtc_funcs->dpms) (crtc,
						     drm_helper_choose_crtc_dpms(crtc));
		}
	}

	return;
}
EXPORT_SYMBOL(drm_helper_connector_dpms);

int drm_helper_mode_fill_fb_struct(struct drm_framebuffer *fb,
				   struct drm_mode_fb_cmd2 *mode_cmd)
{
	int i;

	fb->width = mode_cmd->width;
	fb->height = mode_cmd->height;
	for (i = 0; i < 4; i++) {
		fb->pitches[i] = mode_cmd->pitches[i];
		fb->offsets[i] = mode_cmd->offsets[i];
	}
	drm_fb_get_bpp_depth(mode_cmd->pixel_format, &fb->depth,
				    &fb->bits_per_pixel);
	fb->pixel_format = mode_cmd->pixel_format;

	return 0;
}
EXPORT_SYMBOL(drm_helper_mode_fill_fb_struct);

int drm_helper_resume_force_mode(struct drm_device *dev)
{
	struct drm_crtc *crtc;
	struct drm_encoder *encoder;
	struct drm_encoder_helper_funcs *encoder_funcs;
	struct drm_crtc_helper_funcs *crtc_funcs;
	int ret;

	list_for_each_entry(crtc, &dev->mode_config.crtc_list, head) {

		if (!crtc->enabled)
			continue;

		ret = drm_crtc_helper_set_mode(crtc, &crtc->mode,
					       crtc->x, crtc->y, crtc->fb);

		if (ret == false) {
			fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
			fprintf(stderr, "failed to set mode on crtc %p\n", crtc);
		}

		/* Turn off outputs that were already powered off */
		if (drm_helper_choose_crtc_dpms(crtc)) {
			list_for_each_entry(encoder, &dev->mode_config.encoder_list, head) {

				if(encoder->crtc != crtc)
					continue;

				encoder_funcs = encoder->helper_private;
				if (encoder_funcs->dpms)
					(*encoder_funcs->dpms) (encoder,
								drm_helper_choose_encoder_dpms(encoder));
			}

			crtc_funcs = crtc->helper_private;
			if (crtc_funcs->dpms)
				(*crtc_funcs->dpms) (crtc,
						     drm_helper_choose_crtc_dpms(crtc));
		}
	}
	/* disable the unused connectors while restoring the modesetting */
	return 0;
}
EXPORT_SYMBOL(drm_helper_resume_force_mode);

#define DRM_OUTPUT_POLL_PERIOD (10*HZ)
EXPORT_SYMBOL(drm_kms_helper_poll_disable);
EXPORT_SYMBOL(drm_kms_helper_poll_enable);
EXPORT_SYMBOL(drm_kms_helper_poll_init);
EXPORT_SYMBOL(drm_kms_helper_poll_fini);
EXPORT_SYMBOL(drm_helper_hpd_irq_event);


/**
 * drm_format_num_planes - get the number of planes for format
 * @format: pixel format (DRM_FORMAT_*)
 *
 * RETURNS:
 * The number of planes used by the specified pixel format.
 */
int drm_format_num_planes(uint32_t format)
{
	switch (format) {
	case DRM_FORMAT_YUV410:
	case DRM_FORMAT_YVU410:
	case DRM_FORMAT_YUV411:
	case DRM_FORMAT_YVU411:
	case DRM_FORMAT_YUV420:
	case DRM_FORMAT_YVU420:
	case DRM_FORMAT_YUV422:
	case DRM_FORMAT_YVU422:
	case DRM_FORMAT_YUV444:
	case DRM_FORMAT_YVU444:
		return 3;
	case DRM_FORMAT_NV12:
	case DRM_FORMAT_NV21:
	case DRM_FORMAT_NV16:
	case DRM_FORMAT_NV61:
		return 2;
	default:
		return 1;
	}
}
EXPORT_SYMBOL(drm_format_num_planes);
