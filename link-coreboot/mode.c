
struct drm_display_mode {
	/* Header */
	struct list_head head;
	struct drm_mode_object base;

	char name[DRM_DISPLAY_MODE_LEN];

	enum drm_mode_status status;
	unsigned int type;

	/* Proposed mode values */
	int clock;		/* in kHz */
	int hdisplay;
	int hsync_start;
	int hsync_end;
	int htotal;
	int hskew;
	int vdisplay;
	int vsync_start;
	int vsync_end;
	int vtotal;
	int vscan;
	unsigned int flags;

	/* Addressable image size (may be 0 for projectors, etc.) */
	int width_mm;
	int height_mm;

	/* Actual mode we give to hw */
	int clock_index;
	int synth_clock;
	int crtc_hdisplay;
	int crtc_hblank_start;
	int crtc_hblank_end;
	int crtc_hsync_start;
	int crtc_hsync_end;
	int crtc_htotal;
	int crtc_hskew;
	int crtc_vdisplay;
	int crtc_vblank_start;
	int crtc_vblank_end;
	int crtc_vsync_start;
	int crtc_vsync_end;
	int crtc_vtotal;
	int crtc_hadjusted;
	int crtc_vadjusted;

	/* Driver private mode info */
	int private_size;
	int *private;
	int private_flags;

	int vrefresh;		/* in Hz */
	int hsync;		/* in kHz */
};

struct  drm_display_mode linkmode = {
	"2560x1700",
	60,
	285250,
	2560,
	2608,
	2640,
	2720,
	1700,
	1703,
	1713,
	1749,
	0x48,
	0xa,
};
