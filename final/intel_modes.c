

/**
 * intel_ddc_probe
 *
 */
bool intel_ddc_probe(struct intel_encoder *intel_encoder, int ddc_bus)
{
	struct drm_i915_private *dev_priv = intel_encoder->base.dev->dev_private;
	u8 out_buf[] = { 0x0, 0x0};
	u8 buf[2];
	struct i2c_msg msgs[] = {
		{
			.addr = DDC_ADDR,
			.flags = 0,
			.len = 1,
			.buf = out_buf,
		},
		{
			.addr = DDC_ADDR,
			.flags = I2C_M_RD,
			.len = 1,
			.buf = buf,
		}
	};

	return i2c_transfer(intel_gmbus_get_adapter(dev_priv, ddc_bus),
			    msgs, 2) == 2;
}

/**
 * intel_ddc_get_modes - get modelist from monitor
 * @connector: DRM connector device to use
 * @adapter: i2c adapter
 *
 * Fetch the EDID information from @connector using the DDC bus.
 */
int intel_ddc_get_modes(struct drm_connector *connector,
			struct i2c_adapter *adapter)
{
	struct edid *edid;
	int ret = 0;

	edid = drm_get_edid(connector, adapter);
	if (edid) {
		drm_mode_connector_update_edid_property(connector, edid);
		ret = drm_add_edid_modes(connector, edid);
		drm_edid_to_eld(connector, edid);
		connector->display_info.raw_edid = NULL;
		freez(edid);
	}

	return ret;
}

static const struct drm_prop_enum_list force_audio_names[] = {
	{ HDMI_AUDIO_OFF_DVI, "force-dvi" },
	{ HDMI_AUDIO_OFF, "off" },
	{ HDMI_AUDIO_AUTO, "auto" },
	{ HDMI_AUDIO_ON, "on" },
};

static const struct drm_prop_enum_list broadcast_rgb_names[] = {
	{ 0, "Full" },
	{ 1, "Limited 16:235" },
};
