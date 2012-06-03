@@
@@
- centre_horizontally(...){...}
@@
@@
- centre_vertically(...){...}
@@
@@
- intel_lid_notify(...){...}
@@
@@
-intel_lvds_destroy(...){...}
@@
identifier d;
@@
intel_lvds_detect(...){...
- d = intel_panel_detect(...);
+d = connector_status_connected;
...}
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
-static
lvds_is_present_in_vbt(...){...}
@@
identifier d;
@@
-struct dmi_system_id d [] = {...};
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
-drm_mode_create_scaling_mode_property(...);
@@
@@
-drm_connector_attach_property(...);
@@
@@
-intel_lvds_disable(...);
@@
@@
-static
intel_lvds_dpms(...){...}
