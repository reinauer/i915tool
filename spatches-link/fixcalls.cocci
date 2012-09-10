@@
expression E;
statement S1, S2;
@@
-if (HAS_PCH_SPLIT(E))
S1
-else
-S2
@@
expression E;
statement S1, S2;
identifier out_reg;
@@
-if (out_reg == PCH_DP_D && ...)
-S1
-else
S2
@@
@@
-i915_warn_stolen(...){...}
@@
@@
-intel_enable_ppgtt(...){...}
@@
statement S;
@@
-if (IS_GEN3(...) && ...) S;

@@
@@
-i915_pineview_get_mem_freq(...){...}
@@
@@
-i915_mch_val(...){...}
@@
@@
-pvid_to_extvid(...){...}
@@
identifier d;
expression E;
expression S1, S2, S3;
@@
-if (IS_IVYBRIDGE(d))
S1;
- else if (E) S2; else S3;
@@
@@
-intel_opregion_init(...);
@@
@@
-intel_teardown_gmbus(...);
@@
@@
-intel_teardown_mchbar(...);
@@
@@
-freez(...);
@@
@@
-intel_dp_i2c_init(...);
@@
identifier f;
identifier s;
type T;
@@
-T f(...,struct drm_connector *s,...){...}
@@
@@
-drm_mode_debug_printmodeline(...);
