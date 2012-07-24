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
@@
-intel_fbdev_fini(...){...}
@@
@@
-intel_fbdev_set_suspend(...){...}
@@
identifier d, e;
@@
struct drm_fb_helper_funcs d = {
-	.fb_probe = e,
};
@@
identifier d;
expression e;
@@
struct fb_ops d = {
-.owner = e,
};
@@
identifier d,e;
@@
struct fb_ops d = {
- .fb_check_var = e,
};
@@
identifier d,e;
@@
struct fb_ops d = {
-.fb_set_par = e,
};
@@
identifier d,e;
@@
struct fb_ops d = {
-.fb_fillrect = e,
};
@@
identifier d,e;
@@
struct fb_ops d = {
-.fb_copyarea = e,
};
@@
identifier d,e;
@@
struct fb_ops d = {
-.fb_imageblit = e,
};
@@
identifier d,e;
@@
struct fb_ops d = {
-.fb_pan_display = e,
};
@@
identifier d,e;
@@
struct fb_ops d = {
-.fb_blank = e,
};
@@
identifier d,e;
@@
struct fb_ops d = {
-.fb_debug_enter = e,
};
@@
identifier d,e;
@@
struct fb_ops d = {
-.fb_debug_leave = e,
};
