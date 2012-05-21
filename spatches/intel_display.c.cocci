@@
identifier d;
@@
- struct drm_framebuffer_funcs d = {...};
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
- adpa_pipe_enabled(...){...}
@@
@@
- assert_pch_dp_disabled(...){...}
@@
@@
- assert_pch_hdmi_disabled(...){...}
@@
@@
- assert_pch_ports_disabled(...){...}
@@
@@
- assert_transcoder_disabled(...){...}
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
- disable_pch_hdmi(...){...}
@@
@@
- do_intel_finish_page_flip(...){...}
@@
@@
- dp_pipe_enabled(...){...}
@@
@@
- g4x_check_srwm(...){...}
@@
@@
- g4x_compute_srwm(...){...}
@@
@@
- g4x_compute_wm0(...){...}
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
- g4x_update_wm(...){...}
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
- hdmi_pipe_enabled(...){...}
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
- intel_calculate_wm(...){...}
@@
@@
- intel_cancel_fbc_work(...){...}
@@
@@
- intel_clear_scanline_wait(...){...}
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
- intel_crtc_fb_gamma_get(...){...}
@@
@@
- intel_crtc_fb_gamma_set(...){...}
@@
@@
- intel_crtc_gamma_set(...){...}
@@
@@
- intel_crtc_idle_timer(...){...}
@@
@@
- intel_crtc_mode_fixup(...){...}
@@
@@
- intel_crtc_mode_set(...){...}
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
- intel_decrease_pllclock(...){...}
@@
@@
- intel_default_queue_flip(...){...}
@@
@@
- intel_disable_fbc(...){...}
@@
@@
- intel_disable_pch_pll(...){...}
@@
@@
- intel_disable_pch_ports(...){...}
@@
@@
- intel_disable_pll(...){...}
@@
@@
- intel_disable_transcoder(...){...}
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
- intel_encoder_commit(...){...}
@@
@@
- intel_encoder_destroy(...){...}
@@
@@
- intel_encoder_prepare(...){...}
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
- intel_framebuffer_create(...){...}
@@
@@
- intel_framebuffer_create_for_mode(...){...}
@@
@@
- intel_framebuffer_init(...){...}
@@
@@
- intel_framebuffer_pitch_for_width(...){...}
@@
@@
- intel_framebuffer_size_for_mode(...){...}
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
- intel_get_load_detect_pipe(...){...}
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
- intel_increase_pllclock(...){...}
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
- intel_release_load_detect_pipe(...){...}
@@
@@
- intel_unpin_work_fn(...){...}
@@
@@
- intel_update_fbc(...){...}
@@
@@
- intel_update_watermarks(...){...}
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
- ironlake_check_srwm(...){...}
@@
@@
- ironlake_compute_srwm(...){...}
@@
@@
- ironlake_crtc_commit(...){...}
@@
@@
- ironlake_crtc_disable(...){...}
@@
@@
- ironlake_crtc_prepare(...){...}
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
- intel_pipe_set_base(...){...}
@@
@@
- ironlake_setup_rc6(...){...}
@@
@@
- ironlake_teardown_rc6(...){...}
@@
@@
- ironlake_update_wm(...){...}
@@
@@
- ivb_update_cursor(...){...}
@@
@@
- lvds_pipe_enabled(...){...}
@@
@@
- mode_fits_in_fbdev(...){...}
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
- sandybridge_update_wm(...){...}
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
type T;
identifier f;
@@
T f(...)
{<...
- intel_update_watermarks(...);
...>}
@@
type T;
identifier f, d;
@@
T f(...)
{<...
- d = intel_pipe_set_base(...);
...>}
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
type T;
identifier f;
@@
T f(...)
{<...
- drm_mode_connector_attach_encoder(...);
...>}
@@
type T;
identifier f;
@@
T f(...)
{<...
- ironlake_crtc_disable(...);
...>}
@@
type T;
identifier f;
@@
T f(...)
{<...
- drm_crtc_helper_add(...);
...>}
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
identifier s;
expression E;
@@
struct drm_crtc_helper_funcs s = {
-	.mode_fixup = E,
};
@@
identifier s;
expression E;
@@
struct drm_crtc_helper_funcs s = {
-	.mode_set = E,
};
@@
identifier s;
expression E;
@@
struct drm_crtc_helper_funcs s = {
-	.mode_set_base = E,
};
@@
identifier s;
expression E;
@@
struct drm_crtc_helper_funcs s = {
-	.mode_set_base_atomic = E,
};
@@
identifier s;
expression E;
@@
struct drm_crtc_helper_funcs s = {
-	.load_lut = E,
};
@@
identifier s;
expression E;
@@
struct drm_crtc_helper_funcs s = {
-	.disable = E,
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
-if (SNB_READ_WM0_LATENCY()) S1 else S2
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
-if (HAS_PCH_IBX(...)) S1  else
S2
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
identifier d;
expression E;
@@
-d.prepare = E;
@@
identifier d;
expression E;
@@
-d.commit = E;
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
identifier dev, d, f;
@@
-dev->d.force_wake_get = f;
@@
identifier dev, d, f;
@@
-dev->d.force_wake_put = f;
@@
@@
-drm_vblank_post_modeset(...);
@@
@@
-drm_vblank_pre_modeset(...);
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
