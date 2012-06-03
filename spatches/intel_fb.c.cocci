@@
identifier d;
@@
-struct fb_ops d  = {...};
@@
@@
-intel_fb_find_or_create_single(...){...}
@@
@@
-intel_fbdev_destroy(...){...}
@@
@@
-intel_fb_restore_mode(...){...}
@@
@@
-intelfb_create(...){...}
@@
identifier d;
@@
struct drm_fb_helper_funcs d = {
-	.fb_probe = intel_fb_find_or_create_single,
};
