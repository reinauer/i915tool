@@
type T;
identifier f;
struct drm_device *d;
expression E;
@@
T f(...)
{<...
d = 
-E;
+i915;
...>}
@@
type T;
identifier d;
@@
T d(...)
{<...
-kfree(
+free(
...);
...>}
@@
type T;
identifier d;
identifier dev;
expression E;
@@
T d(...)
{<...
(
-intel_dp_encoder_destroy(...);
|
-intel_dp_destroy(...);
|
-drm_connector_init(...);
|
-drm_encoder_helper_add(...);
|
-drm_encoder_init(...);
|
-drm_connector_helper_add(...);
|
-drm_sysfs_connector_add(...);
|
-INIT_DELAYED_WORK(...);
|
-schedule_delayed_work(...);
)
...>}
@@
struct drm_connector *d;
struct intel_encoder *ie;
identifier f;
type T;
expression E;
@@
T f(...)
{<...
(
- d->polled = E;
|
- ie->hot_plug = E;
)
...>}
@@
identifier s, d;
@@
struct s {...
-struct delayed_work d;
...
};
@@
@@ 
- intel_connector_attach_encoder(...){...}
@g4@
identifier g4 =~ ".*g4.*";
@@
- g4 (...) {...}
@@
@@
- g4x_dp_detect(...){...}
@@
@@
- intel_channel_eq_ok(...){...}
@@
@@
- intel_clock_recovery_ok(...){...}
@@
@@
- intel_dp_add_properties(...){...}
@@
@@
- intel_dp_aux_native_write(...){...}
@@
@@
- intel_dp_aux_native_write_1(...){...}
@@
@@
- intel_dp_check_link_status(...){...}
@@
@@
- intel_dp_commit(...){...}
@@
@@
- intel_dp_complete_link_train(...){...}
@@
@@
- intel_dp_destroy(...){...}
@@
@@
- intel_dp_detect(...){...}
@@
@@
- intel_dp_detect_audio(...){...}
@@
@@
- intel_dp_encoder_destroy(...){...}
@@
@@
- intel_dp_get_edid(...){...}
@@
@@
- intel_dp_get_edid_modes(...){...}
@@
@@
- intel_dp_get_link_status(...){...}
@@
@@
- intel_dp_get_modes(...){...}
@@
@@
- intel_dp_get_sink_irq(...){...}
@@
@@
- intel_dp_handle_test_request(...){...}
@@
@@
- intel_dp_hot_plug(...){...}
@@
@@
- intel_dp_link_down(...){...}
@@
@@
- intel_dp_link_status(...){...}
@@
@@
- intel_dp_mode_fixup(...){...}
@@
@@
- intel_dp_mode_set(...){...}
@@
@@
- intel_dp_pre_emphasis_max(...){...}
@@
@@
- intel_dp_prepare(...){...}
@@
@@
- intel_dp_set_link_train(...){...}
@@
@@
- intel_dp_set_property(...){...}
@@
@@
- intel_dp_sink_dpms(...){...}
@@
@@
- intel_dp_start_link_train(...){...}
@@
@@
- intel_dp_voltage_max(...){...}
@@
@@
- intel_get_adjust_request_pre_emphasis(...){...}
@@
@@
- intel_get_adjust_request_voltage(...){...}
@@
@@
- intel_get_adjust_train(...){...}
@@
@@
- intel_get_lane_status(...){...}
@@
@@
- ironlake_panel_vdd_work(...){...}
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
- struct drm_connector_helper_funcs d = {...};
@@
identifier d;
@@
- struct drm_encoder_funcs d = {...};
@@
type T;
identifier f;
@@
T f(...)
{<...
-intel_dp_add_properties(...);
...>}
