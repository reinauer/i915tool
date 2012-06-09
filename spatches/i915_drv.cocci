@@
identifier d;
@@
(
-struct drm_i915_fence_reg{...};
|
-struct drm_i915_error_state{...};
|
-struct i915_hw_ppgtt{...};
|
-struct drm_i915_gem_object{...};
|
-struct drm_i915_gem_phys_object{...};
|
-struct mem_block{...};
|
-struct drm_i915_gem_request{...};
|
-struct drm_i915_file_private{...};
|
-struct drm_i915_master_private{...};
|
-struct work_struct d;
|
-struct delayed_work d;
|
-struct mem_*d;
|
-struct timer_list d;
|
-struct intel_fbc_work *d;
|
-struct drm_i915_error_state *d;
|
-struct intel_hw_status_page{...};
|
-struct intel_hw_status_page d;
)
@@
@@
-#include<...>
@@
identifier d;
@@
struct s {...
-struct intel_encoder d;
...
};
@@
identifier d;
@@
struct s {...
-struct notifier_block d;
...
};
@@
identifier d;
@@
-struct notifier_block d = {...};
@@
identifier s;
identifier d;
@@
struct s {...
-spinlock_t d;
...
};
@@
identifier s;
identifier d;
@@
struct s {...
-atomic_t d;
...
};
@@
identifier s;
identifier d;
@@
struct s {...
-drm_dma_handle_t *d;
...
};
@@
identifier s;
identifier d;
@@
struct s {...
-drm_local_map_t d;
...
};
@@
identifier s;
identifier d;
@@
struct s {...
-spinlock_t *d;
...
};
@@
identifier s;
identifier d;
@@
struct s {...
-struct work_struct d;
...
};
@@
identifier s;
identifier d;
@@
struct s {...
-struct resource d;
...
};
@@
identifier s;
identifier d;
@@
struct s {...
-struct timer_list d;
...
};
@@
identifier s;
identifier d;
@@
struct s {...
-struct intel_overlay *d;
...
};
@@
identifier s;
identifier d;
@@
struct s {...
-struct intel_unpin_work *d;
...
};
@@
identifier s;
identifier d;
@@
struct s {...
-wait_queue_head_t d;
...
};
@@
identifier s;
identifier d;
constant c;
@@
struct s {...
-struct intel_ring_buffer d[c];
...
};
@@
identifier s;
identifier d;
constant c;
@@
struct s {...
-struct drm_i915_fence_reg d[c];
...
};

@@
identifier s;
identifier d;
constant c;
@@
struct s {...
-struct intel_overlay d[c];
...
};
@@
@@
struct drm_i915_display_funcs {
...
-	int (*queue_flip)(...);
...};
@@
identifier s;
@@
struct s {...
-struct {...} mm;
...
};
@@
identifier d, m;
type T;
@@
-T d(..., struct drm_master *m);
@@
identifier d, m;
type T;
@@
-T d(..., struct drm_clip_rect *m, ...);
@@
identifier d, m;
type T;
@@
-T d(..., struct drm_gem_object *m, ...);
@@
identifier d, m;
type T;
@@
-T d(..., struct drm_i915_gem_request *m, ...);
@@
identifier d, m;
type T;
@@
-T d(..., struct fb_var_screeninfo *m, ...);
@@
identifier d, m;
type T;
@@
-T d(..., struct vm_area_struct *m, ...);
@@
identifier d, m;
type T;
@@
-T d(..., struct vm_fault *m, ...);
@@
identifier d, m;
type T;
@@
-T d(..., struct drm_minor *m, ...);
@@
identifier d, m;
type T;
@@
-T d(..., struct file *m, ...);
@@
identifier d, m;
type T;
@@
-T d(..., struct intel_ring_buffer *m, ...);
@@
identifier d, m;
type T;
@@
-T d(..., struct i915_hw_ppgtt *ppgtt, ...);
@@
identifier d;
@@
-struct drm_ioctl_desc d[];
@@
identifier d, m;
type T;
@@
-T d(struct intel_ring_buffer *m) {...}
@@
@@
-intel_gmbus_is_forced_bit(...){...}
@@
@@
-i915_gem_object_pin_fence(...){...}
@@
@@
-i915_gem_object_unpin_fence(...){...}
