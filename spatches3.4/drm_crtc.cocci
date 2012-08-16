@@
@@
-#include <...>
@@
@@
(
-struct drm_mode_config_funcs{...};
|
struct drm_framebuffer_funcs{
-...
+int nothing;
};
)
@@
identifier d, e;
@@
struct d {...
-	struct mutex e; 
...};
@@
identifier d, e;
@@
struct d {...
-struct device e;
...};
@@
identifier d, e;
@@
struct d {...
-struct device_attribute *e;
...};
@@
type T;
identifier d, e;
@@
-T d(...,struct drm_file *e, ...);
@@
type T;
@@
-T drm_framebuffer_init(...);

