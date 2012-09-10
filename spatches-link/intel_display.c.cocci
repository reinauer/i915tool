@@
type T;
@@
-T intel_limits_i8xx_dvo  = {...};
@@
type T;@@
-T intel_limits_i8xx_lvds  = {...};
@@
type T;
@@
-T intel_limits_i9xx_sdvo  = {...};
@@
type T;
@@
-T intel_limits_i9xx_lvds  = {...};
@@
type T;
@@
-T intel_limits_pineview_sdvo  = {...};
@@
type T;
@@
-T intel_limits_pineview_lvds  = {...};
@@
type T;
@@
-T intel_limits_ironlake_dac = {...};
@@
type T;
@@
-T intel_limits_ironlake_single_lvds = {...};
@@
type T;
@@
-T intel_limits_ironlake_dual_lvds = {...};
@@
type T;
@@
-T intel_limits_ironlake_dual_lvds_100m = {...};
@@
@@
-adpa_pipe_enabled(...){...}
@@
@@
-assert_pch_dp_disabled(...){...}
@@
@@
-assert_pch_hdmi_disabled(...){...}
@@
@@
-assert_pch_ports_disabled(...){...}
@@
@@
-assert_transcoder_disabled(...){...}
@@
@@
-g4x_check_srwm(...){...}
@@
@@
-g4x_compute_srwm(...){...}
@@
@@
-g4x_update_wm(...){...}
@@
@@
-g4x_write_eld(...){...}
@@
@@
-gen6_init_clock_gating(...){...}
@@
@@
-gen6_set_rps(...){...}
@@
@@
-has_edp_a(...){...}
@@
@@
-hdmi_pipe_enabled(...){...}
@@
@@
-i915_disable_vga(...){...}
@@
@@
-i9xx_adjust_sdvo_tv_clock(...){...}
@@
@@
-i9xx_crtc_dpms(...){...}
@@
@@
-i9xx_get_refclk(...){...}
@@
@@
-i9xx_update_pll_dividers(...){...}
@@
@@
-intel_best_encoder(...){...}
@@
@@
-intel_calculate_wm(...){...}
@@
@@
-intel_connector_attach_encoder(...){...}
@@
@@
-intel_crtc_clock_get(...){...}
@@
@@
-intel_crtc_dpms(...){...}
@@
@@
-intel_crtc_driving_pch(...){...}
@@
@@
-intel_crtc_fb_gamma_get(...){...}
@@
@@
-intel_crtc_fb_gamma_set(...){...}
@@
@@
-intel_crtc_gamma_set(...){...}
@@
@@
-intel_crtc_load_lut(...){...}
@@
@@
-intel_crtc_mode_get(...){...}
@@
@@
-intel_crtc_reset(...){...}
@@
@@
-intel_disable_fbc(...){...}
@@
@@
-intel_disable_pch_pll(...){...}
@@
@@
-intel_disable_pch_ports(...){...}
@@
@@
-intel_disable_pipe(...){...}
@@
@@
-intel_disable_plane(...){...}
@@
@@
-intel_disable_pll(...){...}
@@
@@
-intel_disable_transcoder(...){...}
@@
@@
-intel_eld_uptodate(...){...}
@@
@@
-intel_enable_rc6(...){...}
@@
@@
-intel_encoder_clones(...){...}
@@
@@
-intel_encoder_commit(...){...}
@@
@@
-intel_encoder_prepare(...){...}
@@
@@
-intel_fbc_enabled(...){...}
@@
@@
-intel_find_best_PLL(...){...}
@@
@@
-intel_find_pll_g4x_dp(...){...}
@@
@@
-intel_framebuffer_create(...){...}
@@
@@
-intel_framebuffer_create_for_mode(...){...}
@@
@@
-intel_framebuffer_init(...){...}
@@
@@
-intel_framebuffer_pitch_for_width(...){...}
@@
@@
-intel_framebuffer_size_for_mode(...){...}
@@
@@
-intel_init_clock_gating(...){...}
@@
@@
-intel_init_emon(...){...}
@@
@@
-intel_ironlake_limit(...){...}
@@
@@
-intel_limit(...){...}
@@
@@
-intel_modeset_init(...){...}
@@
@@
-intel_pxfreq(...){...}
@@
@@
-intel_release_load_detect_pipe(...){...}
@@
@@
-intel_sanitize_modesetting(...){...}
@@
@@
-intel_setup_outputs(...){...}
@@
@@
-intel_unpin_fb_obj(...){...}
@@
@@
-intel_wait_for_pipe_off(...){...}
@@
@@
-intel_write_eld(...){...}
@@
@@
-intel_dp_mode_set(...){...}
@@
@@
-intel_dp_mode_fixup(...){...}
@@
@@
-ironlake_crtc_commit(...){...}
@@
@@
-ironlake_crtc_disable(...){...}
@@
@@
-ironlake_crtc_dpms(...){...}
@@
@@
-ironlake_crtc_enable(...){...}
@@
@@
-ironlake_crtc_prepare(...){...}
@@
@@
-ironlake_enable_drps(...){...}
@@
@@
-ironlake_enable_fbc(...){...}
@@
@@
-ironlake_fbc_enabled(...){...}
@@
@@
-ironlake_set_drps(...){...}
@@
@@
-ironlake_write_eld(...){...}
@@
@@
-lvds_pipe_enabled(...){...}
@@
identifier d;
identifier E1, E2;
@@
d =
-intel_limit(E1, E2);
+ &intel_limits_ironlake_display_port;
@@
identifier d;
@@
-struct drm_crtc_helper_funcs d = {...};
@@
identifier d;
@@
-struct drm_crtc_funcs d = {...};
@@
@@
-intel_crtc_init(...){...}
@@
@@
-intel_init_display(...){...}

@@
@@
-ironlake_dp_detect(...){...}
@@
@@
-intel_unpin_fb_obj(...);
