@@
identifier d;
@@
struct drm_framebuffer_funcs d = {
-...
+0
};
@@
identifier d;
@@
- struct drm_mode_config_funcs d = {...};
@@
identifier d;
@@
- struct intel_quirk d[] = {...};
@@
@@
-mode_fits_in_fbdev(...){...}
@@
@@
- broadwater_init_clock_gating(...){...}
@@
@@
- crestline_init_clock_gating(...){...}
@@
@@
- disable_pch_dp(...){...}
@@
@@
- disable_pch_dp(...);
@@
@@
- disable_pch_hdmi(...){...}
@@
@@
- disable_pch_hdmi(...);
@@
@@
- do_intel_finish_page_flip(...){...}
@@
@@
- g4x_disable_fbc(...){...}
@@
@@
- g4x_enable_fbc(...){...}
@@
@@
- g4x_fbc_enabled(...){...}
@@
@@
- g4x_init_clock_gating(...){...}
@@
@@
- gen3_init_clock_gating(...){...}
@@
@@
- gen6_disable_rps(...){...}
@@
@@
- gen6_enable_rps(...){...}
@@
@@
-static
gen6_fdi_link_train(...){...}
@@
@@
- i830_get_display_clock_speed(...){...}
@@
@@
- i830_get_fifo_size(...){...}
@@
@@
- i830_init_clock_gating(...){...}
@@
@@
- i830_update_wm(...){...}
@@
@@
- i845_get_fifo_size(...){...}
@@
@@
- i845_update_cursor(...){...}
@@
@@
- i855_get_display_clock_speed(...){...}
@@
@@
- i85x_get_fifo_size(...){...}
@@
@@
- i85x_init_clock_gating(...){...}
@@
@@
- i865_get_display_clock_speed(...){...}
@@
@@
- i8xx_disable_fbc(...){...}
@@
@@
- i8xx_enable_fbc(...){...}
@@
@@
- i8xx_fbc_enabled(...){...}
@@
@@
- i915_get_display_clock_speed(...){...}
@@
@@
- i915gm_get_display_clock_speed(...){...}
@@
@@
- i945_get_display_clock_speed(...){...}
@@
@@
- i965_update_wm(...){...}
@@
@@
- i9xx_crtc_commit(...){...}
@@
@@
-i9xx_crtc_disable(...){...}
@@
@@
- i9xx_crtc_enable(...){...}
@@
@@
- i9xx_crtc_mode_set(...){...}
@@
@@
- i9xx_crtc_prepare(...){...}
@@
@@
- i9xx_get_fifo_size(...){...}
@@
@@
- i9xx_misc_get_display_clock_speed(...){...}
@@
@@
- i9xx_update_cursor(...){...}
@@
@@
- i9xx_update_plane(...){...}
@@
@@
- i9xx_update_wm(...){...}
@@
@@
- ibx_init_clock_gating(...){...}
@@
@@
- intel_alloc_context_page(...){...}
@@
@@
- intel_clear_scanline_wait(...){...}
@@
@@
- intel_clear_scanline_wait(...);
@@
@@
- intel_cancel_fbc_work(...){...}
@@
@@
-intel_cancel_fbc_work(...);
@@
@@
- intel_crtc_cursor_move(...){...}
@@
@@
- intel_crtc_cursor_set(...){...}
@@
@@
- intel_crtc_destroy(...){...}
@@
@@
- intel_crtc_disable(...){...}
@@
@@
- intel_crtc_dpms_overlay(...){...}
@@
@@
- intel_crtc_idle_timer(...){...}
@@
@@
- intel_crtc_page_flip(...){...}
@@
@@
- intel_crtc_update_cursor(...){...}
@@
@@
- intel_crtc_wait_for_pending_flips(...){...}
@@
@@
- intel_crtc_wait_for_pending_flips(...);
@@
@@
- intel_decrease_pllclock(...){...}
@@
@@
- intel_default_queue_flip(...){...}
@@
@@
- intel_display_capture_error_state(...){...}
@@
@@
- intel_display_print_error_state(...){...}
@@
@@
- intel_enable_fbc(...){...}
@@
@@
- intel_enable_pll(...){...}
@@
@@
- intel_encoder_destroy(...){...}
@@
@@
- intel_fbc_work_fn(...){...}
@@
@@
- intel_finish_page_flip(...){...}
@@
@@
- intel_finish_page_flip_plane(...){...}
@@
@@
- intel_g4x_limit(...){...}
@@
@@
- intel_gen2_queue_flip(...){...}
@@
@@
- intel_gen3_queue_flip(...){...}
@@
@@
- intel_gen4_queue_flip(...){...}
@@
@@
- intel_gen6_queue_flip(...){...}
@@
@@
- gen6_update_ring_freq(...){...}
@@
@@
- intel_gen7_queue_flip(...){...}
@@
@@
- intel_get_cxsr_latency(...){...}
@@
@@
- intel_get_pipe_from_crtc_id(...){...}
@@
@@
- intel_gpu_idle_timer(...){...}
@@
@@
- intel_idle_update(...){...}
@@
@@
- intel_init_quirks(...){...}
@@
@@
- intel_mark_busy(...){...}
@@
@@
- intel_modeset_gem_init(...){...}
@@
@@
- intel_modeset_cleanup(...){...}
@@
@@
- intel_modeset_vga_set_state(...){...}
@@
@@
- intel_pin_and_fence_fb_obj(...){...}
@@
@@
- intel_prepare_page_flip(...){...}
@@
@@
- intel_unpin_work_fn(...){...}
@@
@@
- intel_update_fbc(...){...}
@@
@@
- intel_user_framebuffer_create(...){...}
@@
@@
- intel_user_framebuffer_create_handle(...){...}
@@
@@
- intel_user_framebuffer_destroy(...){...}
@@
@@
- ironlake_disable_drps(...){...}
@@
@@
- ironlake_disable_fbc(...){...}
@@
@@
- ironlake_disable_rc6(...){...}
@@
@@
- ironlake_enable_rc6(...){...}
@@
@@
- ironlake_setup_rc6(...){...}
@@
@@
- ironlake_teardown_rc6(...){...}
@@
@@
- ivb_update_cursor(...){...}
@@
@@
- pineview_clock(...){...}
@@
@@
- pineview_disable_cxsr(...){...}
@@
@@
- pineview_update_wm(...){...}
@@
@@
- quirk_pipea_force(...){...}
@@
@@
- quirk_ssc_force_disable(...){...}
@@
@@
- sandybridge_blit_fbc_update(...){...}
@@
@@
- single_enabled_crtc(...){...}
@@
@@
- intel_choose_pipe_bpp_dither(...){...}
@@
@@
- static
intel_setup_outputs(...){...}
@@
@@
- static
has_edp_a(...){...}
@@
@@
-drm_gem_object_unreference_unlocked(...);
@@
type T;
identifier f;
@@
T f(...)
{<...
- intel_choose_pipe_bpp_dither(...);
...>}
@@
type T;
identifier f;
@@
T f(...)
{<...
- sandybridge_blit_fbc_update(...);
...>}
@@
type T;
identifier f;
@@
T f(...)
{<...
- intel_update_fbc(...);
...>}
@@
type T;
identifier f;
@@
T f(...)
{<...
- intel_crtc_update_cursor(...);
...>}
@@
type T;
identifier f;
@@
T f(...)
{<...
- drm_mode_crtc_set_gamma_size(...);
...>}
@@
identifier s;
expression E;
@@
struct drm_crtc_funcs s = {
-.destroy = E,
};
@@
identifier s;
expression E;
@@
struct drm_crtc_funcs s = {
-.gamma_set = E,
};
@@
identifier s;
expression E;
@@
struct drm_crtc_funcs s = {
-.restore = E,
};
@@
identifier s;
expression E;
@@
struct drm_crtc_funcs s = {
-.cursor_set = E,
};
@@
identifier s;
expression E;
@@
struct drm_crtc_funcs s = {
-.cursor_move = E,
};
@@
identifier s;
expression E;
@@
struct drm_crtc_funcs s = {
-.page_flip = E,
};
@@
identifier s;
expression E;
@@
struct drm_crtc_funcs s = {
-.destroy = E,
};
@@
identifier s;
expression E;
@@
struct drm_crtc_funcs s = {
-.set_config = E,
};
@@
identifier f;
type T;
@@
T f(...){<...
- gen6_update_ring_freq(...)
...>}
@@
identifier f;
type T;
@@
T f(...){<...
- gen6_enable_rps(...)
...>}
@@
statement S;
@@
-if (I915_HAS_FBC(...)) S 
@@
statement S;
@@
-if (HAS_PCH_IBX(...)) S 
@@
statement S;
@@
-if (IS_I865G(...)) S 
@@
statement S;
@@
-if (IS_GEN2(...)) S 
@@
statement S;
@@
-if (IS_GEN3(...)) S 
@@
statement S;
@@
-if (IS_GEN2(...)) S 
@@
statement S;
@@
-if (IS_GEN5(...)) S 
@@
statement S;
@@
-if (IS_PINEVIEW(...)) S 
@@
statement S;
@@
-if (IS_G4X(...)) S 
@@
statement S;
@@
-if (IS_GEN5(...)) S 
@@
statement S;
@@
-if (IS_GEN4(...)) S 
@@
statement S;
@@
-if (IS_GM45(...)) S 
@@
statement S;
@@
-if (IS_CRESTLINE(...)) S 
@@
statement S1, S2;
@@
-if (IS_HASWELL(...)) S1 else
S2 
@@
statement S1, S2;
@@
-if (IS_I865G(...)) S1 else
S2 
@@
statement S1, S2;
@@
-if (IS_GEN2(...)) S1 else
S2 
@@
statement S1, S2;
@@
-if (IS_GEN3(...)) S1 else
S2 
@@
statement S1, S2;
@@
-if (IS_GEN2(...)) S1 else
S2 
@@
statement S1, S2;
@@
-if (IS_GEN5(...)) S1 else
S2 
@@
statement S1, S2;
@@
-if (IS_PINEVIEW(...)) S1 else
S2 
@@
statement S1, S2;
@@
-if (IS_G4X(...)) S1 else
S2 
@@
statement S1, S2;
@@
-if (IS_GEN4(...)) S1 else
S2 
@@
statement S1, S2;
@@
-if (IS_GM45(...)) S1 else
S2 
@@
statement S1, S2;
@@
-if (IS_CRESTLINE(...)) S1  else
S2
@@
statement S1, S2;
@@
-if (IS_I85X(...)) S1  else
S2
@@
statement S1, S2;
@@
-if (IS_845G(...)) S1  else
S2
@@
statement S1, S2;
@@
-if (HAS_PCH_IBX(...)) S1  else
S2
@@
statement S1, S2;
@@
if (HAS_PCH_SPLIT(...)) S1  
- else S2
@@
identifier a;
identifier d;
expression E;
@@
-d->a.queue_flip = E;
@@
identifier d;
statement S1, S2;
expression E;
@@
-if (d->tiling_mode != E) S1 else S2
@@
identifier d;
expression E;
@@
-d->display.disable_fbc = E;
@@
identifier dev, d;
@@
-dev->d.get_display_clock_speed = i945_get_display_clock_speed;
@@
identifier dev, d;
@@
-dev->d.get_display_clock_speed = i915_get_display_clock_speed;
@@
identifier dev, d;
@@
-dev->d.get_display_clock_speed = i9xx_misc_get_display_clock_speed;
@@
identifier dev, d;
@@
-dev->d.get_display_clock_speed = i915_get_display_clock_speed;
@@
type T;
identifier f;
@@
T f(...){<...
(
-intel_plane_init(...)
+ 0
)
...>}
@@
identifier dev, d;
@@
-dev->d.get_display_clock_speed = i915gm_get_display_clock_speed;
@@
identifier dev, d;
@@
-dev->d.get_display_clock_speed = i855_get_display_clock_speed;
@@
identifier dev, d;
@@
-dev->d.get_display_clock_speed = i830_get_display_clock_speed;
@@
@@
-intel_limit_t  intel_limits_g4x_sdvo = {...};
@@
@@
- intel_limit_t intel_limits_g4x_hdmi = {...};
@@
@@
- intel_limit_t intel_limits_g4x_single_channel_lvds = {...};
@@
@@
- intel_limit_t intel_limits_g4x_dual_channel_lvds = {...};
@@
@@
- intel_limit_t intel_limits_g4x_display_port = {...};
@@
@@
-drm_vblank_post_modeset(...);
@@
identifier e;
@@
e = 
-intel_pin_and_fence_fb_obj(...);
+0;
@@
@@
-i915_gem_object_unpin(...);
@@
@@
-drm_vblank_pre_modeset(...);
@@
@@
-drm_vblank_off(...);
@@
@@
intel_crtc_update_cursor(...);
@@
identifier m, d;
@@
-m = d->primary->master->driver_priv;
@@
identifier d;
@@
-struct drm_i915_master_private *d;
@@
identifier d, m;
expression e;
@@
-d->sarea_priv->m = e;
@@
identifer a,c;
@@
-a = b->primary->master->driver_priv;
@@
identifier m;
statement S;
@@
-if (!m->sarea_priv) S
@@
identifier m;
statement S;
@@
-if (!m->primary->master) S
@@
identifier m;
statement S;
@@
-if (m->release_fb) S
@@
identifier f;
type T;
@@
T f(...){<...
- mode_fits_in_fbdev(...)
+NULL
...>}
@@
@@
intel_pipe_set_base(...)
{<...
-if (old_fb){...}
...>}
@@
@@
-mod_timer(...);
+fprintf(stderr, "Warning: not scheduling mod_timer\n");
@@
@@
-i9xx_crtc_enable(...);
+fprintf(stderr, "Warning: somebody tried to call i9xx_crtc_enable\n");
@@
@@
-i9xx_crtc_disable(...);
+fprintf(stderr, "Warning: somebody tried to call i9xx_crtc_disable\n");
@@
@@
-intel_finish_fb(...);
+fprintf(stderr, "Warning: somebody tried to call i9xx_crtc_disable\n");
@@
@@
-intel_finish_fb(...){...}
@@
@@
-intel_dual_link_lvds_callback(...){...}
@@
identifier d;
@@
-struct dmi_system_id d[] = {...};
@@
@@
-intel_init_power_wells(...);
@@
@@
-intel_prepare_ddi(...);
@@
@@
-intel_enable_gt_powersave(...);
@@
@@
-intel_disable_fbc(...);
@@
@@
-intel_update_linetime_watermarks(...);
@@
@@
-intel_mark_fb_busy(...){...}
@@
@@
-intel_mark_fb_idle(...){...}
@@
@@
-drm_calc_timestamping_ants(...);
