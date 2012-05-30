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
@g4@
identifier g4 =~ ".*g4.*";
@@
- g4 (...) {...}
@@
expression E1;
@@
-g4x_dp_detect(E1)
+connector_status_disconnected
@@
@@
- g4x_dp_detect(...){...}
@@
@@
- intel_dp_add_properties(...){...}
@@
@@
- intel_dp_destroy(...){...}
@@
@@
- intel_dp_detect_audio(...){...}
@@
@@
- intel_dp_encoder_destroy(...){...}
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
type T;
expression E1, E2;
@@
T intel_dp_set_property(...){<...
-if (E1 == E2) {...}
...>}
@@
@@
- ironlake_panel_vdd_work(...){...}
@@
type T;
identifier f;
@@
T f(...)
{<...
-intel_dp_add_properties(...);
...>}
@@
@@
-static
intel_dp_dpms(...){...}
@@
@@
-intel_dp_check_link_status(...){...}
