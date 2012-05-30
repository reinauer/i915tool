@@
identifier e;
@@
-struct drm_encoder_helper_funcs e = {...};
@@
identifier e;
@@
-struct drm_connector_funcs e = {...};
@@
identifier e;
@@
-struct drm_connector_helper_funcs e = {...};
@@
identifier e;
@@
-struct drm_encoder_funcs e = {...};
@@
identifier e;
@@
-struct dmi_system_id e[] = {...};
@@
identifier s;
expression E;
@@
struct drm_connector_funcs s = {
-.destroy = E,
};
@@
identifier s;
expression E;
@@
struct drm_encoder_funcs s = {
-.destroy = E,
};
@@
identifier s;
@@
-struct dmi_system_id s[] = {...};
@@
type T;
@@
-T intel_no_crt_dmi_callback(...){...}
@@
identifier s;
@@
-struct dmi_system_id s[] = {...};
@@
@@
-static 
intel_crt_load_detect(...){...}

@@
@@
-intel_attached_crt(...){...}
@@
@@
-intel_crt_destroy(...){...}
@@
@@
-intel_crt_detect(...){...}
@@
@@
-intel_crt_detect_ddc(...){...}
@@
@@
-intel_crt_detect_hotplug(...){...}
@@
@@
-intel_crt_dpms(...){...}
@@
@@
-intel_crt_get_modes(...){...}
@@
@@
-intel_crt_init(...){...}
@@
@@
-intel_crt_mode_fixup(...){...}
@@
@@
-intel_crt_mode_set(...){...}
@@
@@
-intel_crt_mode_valid(...){...}
@@
@@
-intel_crt_reset(...){...}
@@
@@
-intel_crt_set_property(...){...}
@@
@@
-intel_ironlake_crt_detect_hotplug(...){...}
