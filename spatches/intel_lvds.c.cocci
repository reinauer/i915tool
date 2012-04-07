@@
@@
- centre_horizontally(...){...}
@@
@@
- centre_vertically(...){...}
@@
@@
- intel_attached_lvds(...){...}
@@
@@
- intel_find_lvds_downclock(...){...}
@@
@@
- intel_lid_notify(...){...}
@@
@@
- intel_lvds_commit(...){...}
@@
@@
- intel_lvds_destroy(...){...}
@@
@@
- intel_lvds_detect(...){...}
@@
@@
- intel_lvds_disable(...){...}
@@
@@
- intel_lvds_dpms(...){...}
@@
@@
- intel_lvds_enable(...){...}
@@
@@
- intel_lvds_get_modes(...){...}
@@
@@
- intel_lvds_mode_fixup(...){...}
@@
@@
- intel_lvds_mode_set(...){...}
@@
@@
- intel_lvds_mode_valid(...){...}
@@
@@
- intel_lvds_prepare(...){...}
@@
@@
- intel_lvds_set_property(...){...}
@@
@@
- intel_no_lvds_dmi_callback(...){...}
@@
@@
- intel_no_modeset_on_lid_dmi_callback(...){...}
@@
@@
- panel_fitter_scaling(...){...}
@@
@@
- to_intel_lvds(...){...}
@@
@@
-static
lvds_is_present_in_vbt(...){...}
@@
identifier d;
@@
-struct dmi_system_id d[] = {...};
@@
identifier d;
@@
- struct drm_encoder_helper_funcs d = {...};
@@
identifier d;
@@
-struct drm_connector_funcs d = {...};
@@
identifier d;
@@
- struct drm_encoder_funcs d = {...};
@@
identifier d;
@@
- struct drm_connector_helper_funcs d = {...};
@@
type T;
identifier f;
@@
T f(...){<...
(
-dmi_check_system(...)
+ 0
|
-acpi_lid_notifier_register(...)
+ 0
)
...>}
@@
@@
-drm_connector_init(...);
@@
@@
-drm_encoder_init(...);
@@
@@
-drm_encoder_helper_add(...);
@@
@@
-drm_connector_helper_add(...);
@@
@@
-drm_mode_create_scaling_mode_property(...);
@@
@@
-drm_connector_attach_property(...);
@@
@@
-drm_mode_connector_update_edid_property(...);
@@
@@
-intel_find_lvds_downclock(...);
