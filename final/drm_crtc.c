

/* Avoid boilerplate.  I'm tired of typing. */
#define DRM_ENUM_NAME_FN(fnname, list)				\
	char *fnname(int val)					\
	{							\
		int i;						\
		for (i = 0; i < ARRAY_SIZE(list); i++) {	\
			if (list[i].type == val)		\
				return list[i].name;		\
		}						\
		return "(unknown)";				\
	}

/*
 * Global properties
 */
static struct drm_prop_enum_list drm_dpms_enum_list[] =
{	{ DRM_MODE_DPMS_ON, "On" },
	{ DRM_MODE_DPMS_STANDBY, "Standby" },
	{ DRM_MODE_DPMS_SUSPEND, "Suspend" },
	{ DRM_MODE_DPMS_OFF, "Off" }
};

DRM_ENUM_NAME_FN(drm_get_dpms_name, drm_dpms_enum_list)

/*
 * Optional properties
 */
static struct drm_prop_enum_list drm_scaling_mode_enum_list[] =
{
	{ DRM_MODE_SCALE_NONE, "None" },
	{ DRM_MODE_SCALE_FULLSCREEN, "Full" },
	{ DRM_MODE_SCALE_CENTER, "Center" },
	{ DRM_MODE_SCALE_ASPECT, "Full aspect" },
};

static struct drm_prop_enum_list drm_dithering_mode_enum_list[] =
{
	{ DRM_MODE_DITHERING_OFF, "Off" },
	{ DRM_MODE_DITHERING_ON, "On" },
	{ DRM_MODE_DITHERING_AUTO, "Automatic" },
};

/*
 * Non-global properties, but "required" for certain connectors.
 */
static struct drm_prop_enum_list drm_dvi_i_select_enum_list[] =
{
	{ DRM_MODE_SUBCONNECTOR_Automatic, "Automatic" }, /* DVI-I and TV-out */
	{ DRM_MODE_SUBCONNECTOR_DVID,      "DVI-D"     }, /* DVI-I  */
	{ DRM_MODE_SUBCONNECTOR_DVIA,      "DVI-A"     }, /* DVI-I  */
};

DRM_ENUM_NAME_FN(drm_get_dvi_i_select_name, drm_dvi_i_select_enum_list)

static struct drm_prop_enum_list drm_dvi_i_subconnector_enum_list[] =
{
	{ DRM_MODE_SUBCONNECTOR_Unknown,   "Unknown"   }, /* DVI-I and TV-out */
	{ DRM_MODE_SUBCONNECTOR_DVID,      "DVI-D"     }, /* DVI-I  */
	{ DRM_MODE_SUBCONNECTOR_DVIA,      "DVI-A"     }, /* DVI-I  */
};

DRM_ENUM_NAME_FN(drm_get_dvi_i_subconnector_name,
		 drm_dvi_i_subconnector_enum_list)

static struct drm_prop_enum_list drm_tv_select_enum_list[] =
{
	{ DRM_MODE_SUBCONNECTOR_Automatic, "Automatic" }, /* DVI-I and TV-out */
	{ DRM_MODE_SUBCONNECTOR_Composite, "Composite" }, /* TV-out */
	{ DRM_MODE_SUBCONNECTOR_SVIDEO,    "SVIDEO"    }, /* TV-out */
	{ DRM_MODE_SUBCONNECTOR_Component, "Component" }, /* TV-out */
	{ DRM_MODE_SUBCONNECTOR_SCART,     "SCART"     }, /* TV-out */
};

DRM_ENUM_NAME_FN(drm_get_tv_select_name, drm_tv_select_enum_list)

static struct drm_prop_enum_list drm_tv_subconnector_enum_list[] =
{
	{ DRM_MODE_SUBCONNECTOR_Unknown,   "Unknown"   }, /* DVI-I and TV-out */
	{ DRM_MODE_SUBCONNECTOR_Composite, "Composite" }, /* TV-out */
	{ DRM_MODE_SUBCONNECTOR_SVIDEO,    "SVIDEO"    }, /* TV-out */
	{ DRM_MODE_SUBCONNECTOR_Component, "Component" }, /* TV-out */
	{ DRM_MODE_SUBCONNECTOR_SCART,     "SCART"     }, /* TV-out */
};

DRM_ENUM_NAME_FN(drm_get_tv_subconnector_name,
		 drm_tv_subconnector_enum_list)

static struct drm_prop_enum_list drm_dirty_info_enum_list[] = {
	{ DRM_MODE_DIRTY_OFF,      "Off"      },
	{ DRM_MODE_DIRTY_ON,       "On"       },
	{ DRM_MODE_DIRTY_ANNOTATE, "Annotate" },
};

DRM_ENUM_NAME_FN(drm_get_dirty_info_name,
		 drm_dirty_info_enum_list)

struct drm_conn_prop_enum_list {
	int type;
	char *name;
	int count;
};

/*
 * Connector and encoder types.
 */
static struct drm_conn_prop_enum_list drm_connector_enum_list[] =
{	{ DRM_MODE_CONNECTOR_Unknown, "Unknown", 0 },
	{ DRM_MODE_CONNECTOR_VGA, "VGA", 0 },
	{ DRM_MODE_CONNECTOR_DVII, "DVI-I", 0 },
	{ DRM_MODE_CONNECTOR_DVID, "DVI-D", 0 },
	{ DRM_MODE_CONNECTOR_DVIA, "DVI-A", 0 },
	{ DRM_MODE_CONNECTOR_Composite, "Composite", 0 },
	{ DRM_MODE_CONNECTOR_SVIDEO, "SVIDEO", 0 },
	{ DRM_MODE_CONNECTOR_LVDS, "LVDS", 0 },
	{ DRM_MODE_CONNECTOR_Component, "Component", 0 },
	{ DRM_MODE_CONNECTOR_9PinDIN, "DIN", 0 },
	{ DRM_MODE_CONNECTOR_DisplayPort, "DP", 0 },
	{ DRM_MODE_CONNECTOR_HDMIA, "HDMI-A", 0 },
	{ DRM_MODE_CONNECTOR_HDMIB, "HDMI-B", 0 },
	{ DRM_MODE_CONNECTOR_TV, "TV", 0 },
	{ DRM_MODE_CONNECTOR_eDP, "eDP", 0 },
	{ DRM_MODE_CONNECTOR_VIRTUAL, "Virtual", 0},
};

static struct drm_prop_enum_list drm_encoder_enum_list[] =
{	{ DRM_MODE_ENCODER_NONE, "None" },
	{ DRM_MODE_ENCODER_DAC, "DAC" },
	{ DRM_MODE_ENCODER_TMDS, "TMDS" },
	{ DRM_MODE_ENCODER_LVDS, "LVDS" },
	{ DRM_MODE_ENCODER_TVDAC, "TV" },
	{ DRM_MODE_ENCODER_VIRTUAL, "Virtual" },
};

char *drm_get_encoder_name(struct drm_encoder *encoder)
{
	static char buf[32];

	snprintf(buf, 32, "%s-%d",
		 drm_encoder_enum_list[encoder->encoder_type].name,
		 encoder->base.id);
	return buf;
}
EXPORT_SYMBOL(drm_get_encoder_name);

char *drm_get_connector_name(struct drm_connector *connector)
{
	static char buf[32];

	snprintf(buf, 32, "%s-%d",
		 drm_connector_enum_list[connector->connector_type].name,
		 connector->connector_type_id);
	return buf;
}
EXPORT_SYMBOL(drm_get_connector_name);

char *drm_get_connector_status_name(enum drm_connector_status status)
{
	if (status == connector_status_connected)
		return "connected";
	else if (status == connector_status_disconnected)
		return "disconnected";
	else
		return "unknown";
}

/**
 * drm_mode_object_get - allocate a new identifier
 * @dev: DRM device
 * @ptr: object pointer, used to generate unique ID
 * @type: object type
 *
 * LOCKING:
 *
 * Create a unique identifier based on @ptr in @dev's identifier space.  Used
 * for tracking modes, CRTCs and connectors.
 *
 * RETURNS:
 * New unique (relative to other objects in @dev) integer identifier for the
 * object.
 */
static int drm_mode_object_get(struct drm_device *dev,
			       struct drm_mode_object *obj, uint32_t obj_type)
{
	int new_id = 0;
	int ret;

again:
	if (idr_pre_get(&dev->mode_config.crtc_idr) == 0) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "Ran out memory getting a mode number\n");
		return -EINVAL;
	}

	ret = idr_get_new_above(&dev->mode_config.crtc_idr, obj, 1, &new_id);
	if (ret == -EAGAIN)
		goto again;

	obj->id = new_id;
	obj->type = obj_type;
	return 0;
}
EXPORT_SYMBOL(drm_mode_object_find);

/**
 * drm_framebuffer_init - initialize a framebuffer
 * @dev: DRM device
 *
 * LOCKING:
 * Caller must hold mode config lock.
 *
 * Allocates an ID for the framebuffer's parent mode object, sets its mode
 * functions & device file and adds it to the master fd list.
 *
 * RETURNS:
 * Zero on success, error code on failure.
 */
int drm_framebuffer_init(struct drm_device *dev, struct drm_framebuffer *fb,
			 const struct drm_framebuffer_funcs *funcs)
{
	int ret;

	ret = drm_mode_object_get(dev, &fb->base, DRM_MODE_OBJECT_FB);
	if (ret)
		return ret;

	fb->dev = dev;
	fb->funcs = funcs;
	dev->mode_config.num_fb++;
	list_add(&fb->head, &dev->mode_config.fb_list);

	return 0;
}
EXPORT_SYMBOL(drm_framebuffer_init);
EXPORT_SYMBOL(drm_framebuffer_cleanup);

/**
 * drm_crtc_init - Initialise a new CRTC object
 * @dev: DRM device
 * @crtc: CRTC object to init
 * @funcs: callbacks for the new CRTC
 *
 * LOCKING:
 * Caller must hold mode config lock.
 *
 * Inits a new object created as base part of an driver crtc object.
 *
 * RETURNS:
 * Zero on success, error code on failure.
 */
int drm_crtc_init(struct drm_device *dev, struct drm_crtc *crtc,
		   const struct drm_crtc_funcs *funcs)
{
	int ret;

	crtc->dev = dev;
	crtc->funcs = funcs;

	ret = drm_mode_object_get(dev, &crtc->base, DRM_MODE_OBJECT_CRTC);
	if (ret)
		goto out;

	list_add_tail(&crtc->head, &dev->mode_config.crtc_list);
	dev->mode_config.num_crtc++;

 out:

	return ret;
}
EXPORT_SYMBOL(drm_crtc_init);
EXPORT_SYMBOL(drm_crtc_cleanup);

/**
 * drm_mode_probed_add - add a mode to a connector's probed mode list
 * @connector: connector the new mode
 * @mode: mode data
 *
 * LOCKING:
 * Caller must hold mode config lock.
 *
 * Add @mode to @connector's mode list for later use.
 */
void drm_mode_probed_add(struct drm_connector *connector,
			 struct drm_display_mode *mode)
{
	list_add(&mode->head, &connector->probed_modes);
}
EXPORT_SYMBOL(drm_mode_probed_add);
EXPORT_SYMBOL(drm_mode_remove);

/**
 * drm_connector_init - Init a preallocated connector
 * @dev: DRM device
 * @connector: the connector to init
 * @funcs: callbacks for this connector
 * @name: user visible name of the connector
 *
 * LOCKING:
 * Takes mode config lock.
 *
 * Initialises a preallocated connector. Connectors should be
 * subclassed as part of driver connector objects.
 *
 * RETURNS:
 * Zero on success, error code on failure.
 */
int drm_connector_init(struct drm_device *dev,
		       struct drm_connector *connector,
		       const struct drm_connector_funcs *funcs,
		       int connector_type)
{
	int ret;

	ret = drm_mode_object_get(dev, &connector->base, DRM_MODE_OBJECT_CONNECTOR);
	if (ret)
		goto out;

	connector->dev = dev;
	connector->funcs = funcs;
	connector->connector_type = connector_type;
	connector->connector_type_id =
		++drm_connector_enum_list[connector_type].count; /* TODO */
	INIT_LIST_HEAD(&connector->user_modes);
	INIT_LIST_HEAD(&connector->probed_modes);
	INIT_LIST_HEAD(&connector->modes);
	connector->edid_blob_ptr = NULL;

	list_add_tail(&connector->head, &dev->mode_config.connector_list);
	dev->mode_config.num_connector++;

	if (connector_type != DRM_MODE_CONNECTOR_VIRTUAL)
		drm_connector_attach_property(connector,
					      dev->mode_config.edid_property,
					      0);

	drm_connector_attach_property(connector,
				      dev->mode_config.dpms_property, 0);

 out:

	return ret;
}
EXPORT_SYMBOL(drm_connector_init);
EXPORT_SYMBOL(drm_connector_cleanup);
EXPORT_SYMBOL(drm_connector_unplug_all);

int drm_encoder_init(struct drm_device *dev,
		      struct drm_encoder *encoder,
		      const struct drm_encoder_funcs *funcs,
		      int encoder_type)
{
	int ret;

	ret = drm_mode_object_get(dev, &encoder->base, DRM_MODE_OBJECT_ENCODER);
	if (ret)
		goto out;

	encoder->dev = dev;
	encoder->encoder_type = encoder_type;
	encoder->funcs = funcs;

	list_add_tail(&encoder->head, &dev->mode_config.encoder_list);
	dev->mode_config.num_encoder++;

 out:

	return ret;
}
EXPORT_SYMBOL(drm_encoder_init);
EXPORT_SYMBOL(drm_encoder_cleanup);
EXPORT_SYMBOL(drm_plane_init);
EXPORT_SYMBOL(drm_plane_cleanup);

/**
 * drm_mode_create - create a new display mode
 * @dev: DRM device
 *
 * LOCKING:
 * Caller must hold DRM mode_config lock.
 *
 * Create a new drm_display_mode, give it an ID, and return it.
 *
 * RETURNS:
 * Pointer to new mode on success, NULL on error.
 */
struct drm_display_mode *drm_mode_create(struct drm_device *dev)
{
	struct drm_display_mode *nmode;

	nmode = allocz(sizeof(struct drm_display_mode));
	if (!nmode)
		return NULL;

	if (drm_mode_object_get(dev, &nmode->base, DRM_MODE_OBJECT_MODE)) {
		freez(nmode);
		return NULL;
	}

	return nmode;
}
EXPORT_SYMBOL(drm_mode_create);
EXPORT_SYMBOL(drm_mode_destroy);

static int drm_mode_create_standard_connector_properties(struct drm_device *dev)
{
	struct drm_property *edid;
	struct drm_property *dpms;

	/*
	 * Standard properties (apply to all connectors)
	 */
	edid = drm_property_create(dev, DRM_MODE_PROP_BLOB |
				   DRM_MODE_PROP_IMMUTABLE,
				   "EDID", 0);
	dev->mode_config.edid_property = edid;

	dpms = drm_property_create_enum(dev, 0,
				   "DPMS", drm_dpms_enum_list,
				   ARRAY_SIZE(drm_dpms_enum_list));
	dev->mode_config.dpms_property = dpms;

	return 0;
}
EXPORT_SYMBOL(drm_mode_create_dvi_i_properties);
EXPORT_SYMBOL(drm_mode_create_tv_properties);
EXPORT_SYMBOL(drm_mode_create_scaling_mode_property);
EXPORT_SYMBOL(drm_mode_create_dithering_property);
EXPORT_SYMBOL(drm_mode_create_dirty_info_property);

/**
 * drm_mode_config_init - initialize DRM mode_configuration structure
 * @dev: DRM device
 *
 * LOCKING:
 * None, should happen single threaded at init time.
 *
 * Initialize @dev's mode_config structure, used for tracking the graphics
 * configuration of @dev.
 */
void drm_mode_config_init(struct drm_device *dev)
{
	INIT_LIST_HEAD(&dev->mode_config.fb_list);
	INIT_LIST_HEAD(&dev->mode_config.crtc_list);
	INIT_LIST_HEAD(&dev->mode_config.connector_list);
	INIT_LIST_HEAD(&dev->mode_config.encoder_list);
	INIT_LIST_HEAD(&dev->mode_config.property_list);
	INIT_LIST_HEAD(&dev->mode_config.property_blob_list);
	INIT_LIST_HEAD(&dev->mode_config.plane_list);
	idr_init(&dev->mode_config.crtc_idr);

	drm_mode_create_standard_connector_properties(dev);

	/* Just to be sure */
	dev->mode_config.num_fb = 0;
	dev->mode_config.num_connector = 0;
	dev->mode_config.num_crtc = 0;
	dev->mode_config.num_encoder = 0;
}
EXPORT_SYMBOL(drm_mode_config_init);
EXPORT_SYMBOL(drm_mode_group_init_legacy_group);
EXPORT_SYMBOL(drm_mode_config_cleanup);

/* Original addfb only supported RGB formats, so figure out which one */
uint32_t drm_mode_legacy_fb_format(uint32_t bpp, uint32_t depth)
{
	uint32_t fmt;

	switch (bpp) {
	case 8:
		fmt = DRM_FORMAT_RGB332;
		break;
	case 16:
		if (depth == 15)
			fmt = DRM_FORMAT_XRGB1555;
		else
			fmt = DRM_FORMAT_RGB565;
		break;
	case 24:
		fmt = DRM_FORMAT_RGB888;
		break;
	case 32:
		if (depth == 24)
			fmt = DRM_FORMAT_XRGB8888;
		else if (depth == 30)
			fmt = DRM_FORMAT_XRGB2101010;
		else
			fmt = DRM_FORMAT_ARGB8888;
		break;
	default:
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "bad bpp, assuming x8r8g8b8 pixel format\n");
		fmt = DRM_FORMAT_XRGB8888;
		break;
	}

	return fmt;
}
EXPORT_SYMBOL(drm_mode_legacy_fb_format);

static int format_check(struct drm_mode_fb_cmd2 *r)
{
	uint32_t format = r->pixel_format & ~DRM_FORMAT_BIG_ENDIAN;

	switch (format) {
	case DRM_FORMAT_C8:
	case DRM_FORMAT_RGB332:
	case DRM_FORMAT_BGR233:
	case DRM_FORMAT_XRGB4444:
	case DRM_FORMAT_XBGR4444:
	case DRM_FORMAT_RGBX4444:
	case DRM_FORMAT_BGRX4444:
	case DRM_FORMAT_ARGB4444:
	case DRM_FORMAT_ABGR4444:
	case DRM_FORMAT_RGBA4444:
	case DRM_FORMAT_BGRA4444:
	case DRM_FORMAT_XRGB1555:
	case DRM_FORMAT_XBGR1555:
	case DRM_FORMAT_RGBX5551:
	case DRM_FORMAT_BGRX5551:
	case DRM_FORMAT_ARGB1555:
	case DRM_FORMAT_ABGR1555:
	case DRM_FORMAT_RGBA5551:
	case DRM_FORMAT_BGRA5551:
	case DRM_FORMAT_RGB565:
	case DRM_FORMAT_BGR565:
	case DRM_FORMAT_RGB888:
	case DRM_FORMAT_BGR888:
	case DRM_FORMAT_XRGB8888:
	case DRM_FORMAT_XBGR8888:
	case DRM_FORMAT_RGBX8888:
	case DRM_FORMAT_BGRX8888:
	case DRM_FORMAT_ARGB8888:
	case DRM_FORMAT_ABGR8888:
	case DRM_FORMAT_RGBA8888:
	case DRM_FORMAT_BGRA8888:
	case DRM_FORMAT_XRGB2101010:
	case DRM_FORMAT_XBGR2101010:
	case DRM_FORMAT_RGBX1010102:
	case DRM_FORMAT_BGRX1010102:
	case DRM_FORMAT_ARGB2101010:
	case DRM_FORMAT_ABGR2101010:
	case DRM_FORMAT_RGBA1010102:
	case DRM_FORMAT_BGRA1010102:
	case DRM_FORMAT_YUYV:
	case DRM_FORMAT_YVYU:
	case DRM_FORMAT_UYVY:
	case DRM_FORMAT_VYUY:
	case DRM_FORMAT_AYUV:
	case DRM_FORMAT_NV12:
	case DRM_FORMAT_NV21:
	case DRM_FORMAT_NV16:
	case DRM_FORMAT_NV61:
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
		return 0;
	default:
		return -EINVAL;
	}
}
EXPORT_SYMBOL(drm_mode_attachmode_crtc);
EXPORT_SYMBOL(drm_mode_detachmode_crtc);

struct drm_property *drm_property_create(struct drm_device *dev, int flags,
					 const char *name, int num_values)
{
	struct drm_property *property = NULL;
	int ret;

	property = allocz(sizeof(struct drm_property));
	if (!property)
		return NULL;

	if (num_values) {
		property->values = allocz(sizeof(uint64_t) * num_values);
		if (!property->values)
			goto fail;
	}

	ret = drm_mode_object_get(dev, &property->base, DRM_MODE_OBJECT_PROPERTY);
	if (ret)
		goto fail;

	property->flags = flags;
	property->num_values = num_values;
	INIT_LIST_HEAD(&property->enum_blob_list);

	if (name) {
		strncpy(property->name, name, DRM_PROP_NAME_LEN);
		property->name[DRM_PROP_NAME_LEN-1] = '\0';
	}

	list_add_tail(&property->head, &dev->mode_config.property_list);
	return property;
fail:
	freez(property->values);
	freez(property);
	return NULL;
}
EXPORT_SYMBOL(drm_property_create);

struct drm_property *drm_property_create_enum(struct drm_device *dev, int flags,
					 const char *name,
					 const struct drm_prop_enum_list *props,
					 int num_values)
{
	struct drm_property *property;
	int i, ret;

	flags |= DRM_MODE_PROP_ENUM;

	property = drm_property_create(dev, flags, name, num_values);
	if (!property)
		return NULL;

	for (i = 0; i < num_values; i++) {
		ret = drm_property_add_enum(property, i,
				      props[i].type,
				      props[i].name);
		if (ret) {
			return NULL;
		}
	}

	return property;
}
EXPORT_SYMBOL(drm_property_create_enum);

struct drm_property *drm_property_create_range(struct drm_device *dev, int flags,
					 const char *name,
					 uint64_t min, uint64_t max)
{
	struct drm_property *property;

	flags |= DRM_MODE_PROP_RANGE;

	property = drm_property_create(dev, flags, name, 2);
	if (!property)
		return NULL;

	property->values[0] = min;
	property->values[1] = max;

	return property;
}
EXPORT_SYMBOL(drm_property_create_range);

int drm_property_add_enum(struct drm_property *property, int index,
			  uint64_t value, const char *name)
{
	struct drm_property_enum *prop_enum;

	if (!(property->flags & DRM_MODE_PROP_ENUM))
		return -EINVAL;

	if (!list_empty(&property->enum_blob_list)) {
		list_for_each_entry(prop_enum, &property->enum_blob_list, head) {
			if (prop_enum->value == value) {
				strncpy(prop_enum->name, name, DRM_PROP_NAME_LEN);
				prop_enum->name[DRM_PROP_NAME_LEN-1] = '\0';
				return 0;
			}
		}
	}

	prop_enum = allocz(sizeof(struct drm_property_enum));
	if (!prop_enum)
		return -ENOMEM;

	strncpy(prop_enum->name, name, DRM_PROP_NAME_LEN);
	prop_enum->name[DRM_PROP_NAME_LEN-1] = '\0';
	prop_enum->value = value;

	property->values[index] = value;
	list_add_tail(&prop_enum->head, &property->enum_blob_list);
	return 0;
}
EXPORT_SYMBOL(drm_property_add_enum);
EXPORT_SYMBOL(drm_property_destroy);

int drm_connector_attach_property(struct drm_connector *connector,
			       struct drm_property *property, uint64_t init_val)
{
	int i;

	for (i = 0; i < DRM_CONNECTOR_MAX_PROPERTY; i++) {
		if (connector->property_ids[i] == 0) {
			connector->property_ids[i] = property->base.id;
			connector->property_values[i] = init_val;
			break;
		}
	}

	if (i == DRM_CONNECTOR_MAX_PROPERTY)
		return -EINVAL;
	return 0;
}
EXPORT_SYMBOL(drm_connector_attach_property);

int drm_connector_property_set_value(struct drm_connector *connector,
				  struct drm_property *property, uint64_t value)
{
	int i;

	for (i = 0; i < DRM_CONNECTOR_MAX_PROPERTY; i++) {
		if (connector->property_ids[i] == property->base.id) {
			connector->property_values[i] = value;
			break;
		}
	}

	if (i == DRM_CONNECTOR_MAX_PROPERTY)
		return -EINVAL;
	return 0;
}
EXPORT_SYMBOL(drm_connector_property_set_value);

int drm_connector_property_get_value(struct drm_connector *connector,
				  struct drm_property *property, uint64_t *val)
{
	int i;

	for (i = 0; i < DRM_CONNECTOR_MAX_PROPERTY; i++) {
		if (connector->property_ids[i] == property->base.id) {
			*val = connector->property_values[i];
			break;
		}
	}

	if (i == DRM_CONNECTOR_MAX_PROPERTY)
		return -EINVAL;
	return 0;
}
EXPORT_SYMBOL(drm_connector_property_get_value);

static struct drm_property_blob *drm_property_create_blob(struct drm_device *dev, int length,
							  void *data)
{
	struct drm_property_blob *blob;
	int ret;

	if (!length || !data)
		return NULL;

	blob = allocz(sizeof(struct drm_property_blob) + length);
	if (!blob)
		return NULL;

	ret = drm_mode_object_get(dev, &blob->base, DRM_MODE_OBJECT_BLOB);
	if (ret) {
		freez(blob);
		return NULL;
	}

	blob->length = length;

	memcpy(blob->data, data, length);

	list_add_tail(&blob->head, &dev->mode_config.property_blob_list);
	return blob;
}

int drm_mode_connector_update_edid_property(struct drm_connector *connector,
					    struct edid *edid)
{
	extern struct drm_device *i915;
	struct drm_device *dev = i915;
	int ret = 0, size;

	if (connector->edid_blob_ptr)
		{}

	/* Delete edid, when there is none. */
	if (!edid) {
		connector->edid_blob_ptr = NULL;
		ret = drm_connector_property_set_value(connector, dev->mode_config.edid_property, 0);
		return ret;
	}

	size = EDID_LENGTH * (1 + edid->extensions);
	connector->edid_blob_ptr = drm_property_create_blob(connector->dev,
							    size, edid);

	ret = drm_connector_property_set_value(connector,
					       dev->mode_config.edid_property,
					       connector->edid_blob_ptr->base.id);

	return ret;
}
EXPORT_SYMBOL(drm_mode_connector_update_edid_property);

int drm_mode_connector_attach_encoder(struct drm_connector *connector,
				      struct drm_encoder *encoder)
{
	int i;

	for (i = 0; i < DRM_CONNECTOR_MAX_ENCODER; i++) {
		if (connector->encoder_ids[i] == 0) {
			connector->encoder_ids[i] = encoder->base.id;
			return 0;
		}
	}
	return -ENOMEM;
}
EXPORT_SYMBOL(drm_mode_connector_attach_encoder);
EXPORT_SYMBOL(drm_mode_connector_detach_encoder);
EXPORT_SYMBOL(drm_mode_crtc_set_gamma_size);
EXPORT_SYMBOL(drm_mode_config_reset);

/*
 * Just need to support RGB formats here for compat with code that doesn't
 * use pixel formats directly yet.
 */
void drm_fb_get_bpp_depth(uint32_t format, unsigned int *depth,
			  int *bpp)
{
	switch (format) {
	case DRM_FORMAT_RGB332:
	case DRM_FORMAT_BGR233:
		*depth = 8;
		*bpp = 8;
		break;
	case DRM_FORMAT_XRGB1555:
	case DRM_FORMAT_XBGR1555:
	case DRM_FORMAT_RGBX5551:
	case DRM_FORMAT_BGRX5551:
	case DRM_FORMAT_ARGB1555:
	case DRM_FORMAT_ABGR1555:
	case DRM_FORMAT_RGBA5551:
	case DRM_FORMAT_BGRA5551:
		*depth = 15;
		*bpp = 16;
		break;
	case DRM_FORMAT_RGB565:
	case DRM_FORMAT_BGR565:
		*depth = 16;
		*bpp = 16;
		break;
	case DRM_FORMAT_RGB888:
	case DRM_FORMAT_BGR888:
		*depth = 24;
		*bpp = 24;
		break;
	case DRM_FORMAT_XRGB8888:
	case DRM_FORMAT_XBGR8888:
	case DRM_FORMAT_RGBX8888:
	case DRM_FORMAT_BGRX8888:
		*depth = 24;
		*bpp = 32;
		break;
	case DRM_FORMAT_XRGB2101010:
	case DRM_FORMAT_XBGR2101010:
	case DRM_FORMAT_RGBX1010102:
	case DRM_FORMAT_BGRX1010102:
	case DRM_FORMAT_ARGB2101010:
	case DRM_FORMAT_ABGR2101010:
	case DRM_FORMAT_RGBA1010102:
	case DRM_FORMAT_BGRA1010102:
		*depth = 30;
		*bpp = 32;
		break;
	case DRM_FORMAT_ARGB8888:
	case DRM_FORMAT_ABGR8888:
	case DRM_FORMAT_RGBA8888:
	case DRM_FORMAT_BGRA8888:
		*depth = 32;
		*bpp = 32;
		break;
	default:
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "unsupported pixel format\n");
		*depth = 0;
		*bpp = 0;
		break;
	}
}
EXPORT_SYMBOL(drm_fb_get_bpp_depth);
