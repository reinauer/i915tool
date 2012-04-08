@@
identifier dev;
expression i;
@@
-struct drm_i915_private *dev = i;
+extern struct drm_device *i915;  struct drm_i915_private *dev = i915->dev_private;
@@
identifier dev;
expression i;
@@
-struct drm_device *dev = i;
+extern struct drm_device *i915;  struct drm_device *dev = i915;
@@
identifier dev;
expression i;
@@
-struct pci_dev *dev = i;
+extern struct drm_device *i915; struct pci_dev *dev = i915->pdev;
@@
@@
-#include "i915_drm.h"
@@
@@
-#include "drm.h"
@@
@@
-#include "drmP.h"
@@
@@
-#include "i915_trace.h"
@@
identifier d;
@@
-(d)->pci_device
+(d)->pdev->device_id
@@
identifier s, d;
@@
struct s {...
-struct spinlock d;
...
};
@@
identifier s, d;
@@
struct s {...
-struct mutex d;
...
};
@@
identifier d, f;
@@
struct drm_connector_funcs d = {
-.fill_modes = f,
};
@@
identifier d, f;
@@
struct drm_connector_funcs d = {
-.destroy = f,
};
@@
identifier d, f;
@@
struct drm_encoder_funcs d = {
-.destroy = f,
};
