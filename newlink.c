{V, 0, "(null)", 0x0, 0x0, 0},
{W, 1, "", PCH_GMBUS0, 0x00000000, 0},
{R, 1, "", PP_ON_DELAYS, 0x00000000, 0},
{R, 1, "", PP_OFF_DELAYS, 0x00000000, 0},
{W, 1, "", PP_ON_DELAYS, 0x019007d0, 0},
{W, 1, "", PP_OFF_DELAYS, 0x015e07d0, 0},
{M, 1, "[drm:intel_detect_pch], Found PatherPoint PCH", 0x0, 0x0, 0},
{M, 1, "[drm:i915_load_modeset_init], failed to find VBIOS tables", 0x0, 0x0, 0},
{R, 50, "", 0x130040, 0x00000001, 10},
{W, 1, "", 0xa188, 0x00010001, 0},
{R, 1, "", 0xa188, 0x00010001, 0},
{R, 1, "", 0x130040, 0x00000001, 0},
{R, 1, "", 0x13805c, 0x40000000, 0},
{R, 1, "", 0xa180, 0x84100020, 0},
{W, 1, "", 0xa188, 0x00010000, 0},
{R, 1, "", 0x120000, 0x00000000, 0},
{M, 1, "[drm:intel_init_display], Using MT version of forcewake", 0x0, 0x0, 0},
{R, 1, "", 0x145d10, 0x2010040c, 0},
{M, 1, "[drm:intel_modeset_init], 3 display pipes available.", 0x0, 0x0, 0},
{R, 1, "", _PIPEACONF, 0x00000000, 0},
{W, 1, "", _PIPEACONF, 0x00000000, 0},
{R, 1, "", _PIPEBCONF, 0x00000000, 0},
{W, 1, "", _PIPEBCONF, 0x00000000, 0},
{R, 1, "", 0x72008, 0x00000000, 0},
{W, 1, "", 0x72008, 0x00000000, 0},
{R, 1, "", _PIPEACONF, 0x00000000, 0},
{W, 1, "", _PIPEACONF, 0x00000000, 0},
{R, 1, "", _PIPEBCONF, 0x00000000, 0},
{W, 1, "", _PIPEBCONF, 0x00000000, 0},
{R, 1, "", 0x72008, 0x00000000, 0},
{W, 1, "", 0x72008, 0x00000000, 0},
{R, 1, "", _PIPEACONF, 0x00000000, 0},
{W, 1, "", _PIPEACONF, 0x00000000, 0},
{R, 1, "", _PIPEBCONF, 0x00000000, 0},
{W, 1, "", _PIPEBCONF, 0x00000000, 0},
{R, 1, "", 0x72008, 0x00000000, 0},
{W, 1, "", 0x72008, 0x00000000, 300},
{W, 1, "", CPU_VGACNTRL, 0x80000000, 0},
{R, 1, "", CPU_VGACNTRL, 0x80000000, 0},
{R, 1, "", 0x64000, 0x0000001c, 0},
{R, 1, "", PCH_PP_ON_DELAYS, ( PANEL_PORT_SELECT_MASK &0x40000000)| PANEL_POWER_UP_DELAY_SHIFT |0x47d007d0, 0},
{R, 1, "", PCH_PP_OFF_DELAYS,  PANEL_POWER_DOWN_DELAY_SHIFT |0x01f407d0, 0},
{R, 1, "", PCH_PP_DIVISOR, 0x00186906, 0},
{M, 1, "[drm:intel_dp_init], cur t1_t3 2000 t8 2000 t9 2000 t10 500t11_t12 6000", 0x0, 0x0, 0},
{M, 1, "[drm:intel_dp_init], vbt t1_t3 0 t8 0 t9 0 t10 0 t11_t12 0", 0x0, 0x0, 0},
{M, 1, "[drm:intel_dp_init], panel power up delay 200,power down delay 50, power cycle delay 600", 0x0, 0x0, 0},
{M, 1, "[drm:intel_dp_init], backlight on delay 200, off delay 200", 0x0, 0x0, 0},
{M, 1, "[drm:ironlake_edp_panel_vdd_on], Turn eDP VDD on", 0x0, 0x0, 0},
{R, 1, "", PCH_PP_CONTROL, 0x00000000, 0},
{R, 1, "", PCH_PP_STATUS, 0x00000000, 0},
{M, 1, "[drm:ironlake_wait_panel_power_cycle], Wait for panel power cycle", 0x0, 0x0, 0},
{M, 1, "[drm:ironlake_wait_panel_status], R PCH_PP_CONTROL:00000000", 0x0, 0x0, 0},
{R, 2, "", PCH_PP_STATUS, 0x00000000, 0},
{R, 1, "", PCH_PP_CONTROL, 0x00000000, 0},
{W, 1, "", PCH_PP_CONTROL, (PCH_PP_UNLOCK&0xabcd0000)| EDP_FORCE_VDD |0xabcd0008, 0},
{R, 1, "", PCH_PP_CONTROL, (PCH_PP_UNLOCK&0xabcd0000)| EDP_FORCE_VDD |0xabcd0008, 0},
{M, 1, "[drm:ironlake_edp_panel_vdd_on], R PCH_PP_CONTROL:abcd0008", 0x0, 0x0, 0},
{R, 2, "", PCH_PP_STATUS, 0x00000000, 0},
{M, 1, "[drm:ironlake_edp_panel_vdd_on], eDP was not running", 0x0, 0x0, 0},
{R, 1, "", PCH_PP_STATUS, 0x00000000, 0},
{R, 1, "", PCH_PP_CONTROL, (PCH_PP_UNLOCK&0xabcd0000)| EDP_FORCE_VDD |0xabcd0008, 0},
{R, 1, "", PCH_PP_STATUS, 0x00000000, 0},
{R, 1, "", PCH_PP_CONTROL, (PCH_PP_UNLOCK&0xabcd0000)| EDP_FORCE_VDD |0xabcd0008, 0},
{R, 1, "", DPA_AUX_CH_CTL, 0x014300c8, 0},
{W, 1, "", DPA_AUX_CH_DATA1, 0x9000000e, 0},
{W, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY | DP_AUX_CH_CTL_DONE | DP_AUX_CH_CTL_TIME_OUT_ERROR | DP_AUX_CH_CTL_RECEIVE_ERROR |0xd24500c8, 0},
{R, 2, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY |0x814500c8, 100},
{R, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY |0x807500c8, 100},
{R, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY |0x810500c8, 100},
{R, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_DONE |0x410500c8, 0},
{W, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_DONE | DP_AUX_CH_CTL_TIME_OUT_ERROR | DP_AUX_CH_CTL_RECEIVE_ERROR |0x530500c8, 0},
{R, 1, "", DPA_AUX_CH_DATA1, 0x00110a84, 0},
{R, 1, "", DPA_AUX_CH_DATA2, 0x41000001, 0},
{R, 1, "", DPA_AUX_CH_DATA3, 0xc0020000, 0},
{R, 1, "", DPA_AUX_CH_DATA4, 0x001f0000, 0},
{M, 1, "[drm:intel_dp_i2c_init], i2c_init DPDDC-A", 0x0, 0x0, 0},
{R, 1, "", PCH_PP_STATUS, 0x00000000, 0},
{R, 1, "", PCH_PP_CONTROL, (PCH_PP_UNLOCK&0xabcd0000)| EDP_FORCE_VDD |0xabcd0008, 0},
{R, 1, "", PCH_PP_STATUS, 0x00000000, 0},
{R, 1, "", PCH_PP_CONTROL, (PCH_PP_UNLOCK&0xabcd0000)| EDP_FORCE_VDD |0xabcd0008, 0},
{R, 1, "", DPA_AUX_CH_CTL, 0x010500c8, 0},
{W, 1, "", DPA_AUX_CH_DATA1, 0x40000000, 0},
{W, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY | DP_AUX_CH_CTL_DONE | DP_AUX_CH_CTL_TIME_OUT_ERROR | DP_AUX_CH_CTL_RECEIVE_ERROR |0xd23500c8, 0},
{R, 2, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY |0x810500c8, 100},
{R, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_DONE |0x401500c8, 0},
{W, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_DONE | DP_AUX_CH_CTL_TIME_OUT_ERROR | DP_AUX_CH_CTL_RECEIVE_ERROR |0x521500c8, 0},
{R, 1, "", DPA_AUX_CH_DATA1, 0x00000000, 0},
{R, 1, "", PCH_PP_STATUS, 0x00000000, 0},
{R, 1, "", PCH_PP_CONTROL, (PCH_PP_UNLOCK&0xabcd0000)| EDP_FORCE_VDD |0xabcd0008, 0},
{R, 1, "", PCH_PP_STATUS, 0x00000000, 0},
{R, 1, "", PCH_PP_CONTROL, (PCH_PP_UNLOCK&0xabcd0000)| EDP_FORCE_VDD |0xabcd0008, 0},
{R, 1, "", DPA_AUX_CH_CTL, 0x001500c8, 0},
{W, 1, "", DPA_AUX_CH_DATA1, 0x00000000, 0},
{W, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY | DP_AUX_CH_CTL_DONE | DP_AUX_CH_CTL_TIME_OUT_ERROR | DP_AUX_CH_CTL_RECEIVE_ERROR |0xd23500c8, 0},
{R, 2, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY |0x801500c8, 100},
{R, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_DONE |0x401500c8, 0},
{W, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_DONE | DP_AUX_CH_CTL_TIME_OUT_ERROR | DP_AUX_CH_CTL_RECEIVE_ERROR |0x521500c8, 0},
{R, 1, "", DPA_AUX_CH_DATA1, 0x00000000, 0},
{M, 1, "[drm:ironlake_edp_panel_vdd_off], Turn eDP VDD off 1", 0x0, 0x0, 0},
{R, 1, "", BLC_PWM_CPU_CTL, 0x000010ce, 0},
{M, 1, "[drm:intel_panel_get_backlight], get backlight PWM = 4302", 0x0, 0x0, 0},
{M, 1, "[drm:intel_dp_aux_ch], dp_aux_ch timeout status 0x5145003f", 0x0, 0x0, 0},
{M, 1, "[drm:intel_dp_i2c_aux_ch], aux_ch failed -110", 0x0, 0x0, 0},
{M, 1, "[drm:ironlake_init_pch_refclk], has_panel 1 has_lvds 0 has_pch_edp 0has_cpu_edp 1 has_ck505 0", 0x0, 0x0, 0},
{R, 1, "", PCH_DREF_CONTROL, 0x00000000, 0},
{M, 1, "[drm:ironlake_init_pch_refclk], Using SSC on panel", 0x0, 0x0, 0},
{W, 1, "", PCH_DREF_CONTROL,  DREF_SSC_SOURCE_ENABLE | DREF_NONSPREAD_SOURCE_ENABLE | DREF_SSC1_ENABLE |0x00001402, 0},
{R, 1, "", PCH_DREF_CONTROL,  DREF_SSC_SOURCE_ENABLE | DREF_NONSPREAD_SOURCE_ENABLE | DREF_SSC1_ENABLE |0x00001402, 200},
{M, 1, "[drm:ironlake_init_pch_refclk], Using SSC on eDP", 0x0, 0x0, 0},
{W, 1, "", PCH_DREF_CONTROL,  DREF_CPU_SOURCE_OUTPUT_DOWNSPREAD | DREF_SSC_SOURCE_ENABLE | DREF_NONSPREAD_SOURCE_ENABLE | DREF_SSC1_ENABLE |0x00005402, 0},
{R, 1, "", PCH_DREF_CONTROL,  DREF_CPU_SOURCE_OUTPUT_DOWNSPREAD | DREF_SSC_SOURCE_ENABLE | DREF_NONSPREAD_SOURCE_ENABLE | DREF_SSC1_ENABLE |0x00005402, 200},
{W, 1, "", ILK_DSPCLK_GATE,  IVB_VRHUNIT_CLK_GATE |0x10000000, 0},
{W, 1, "", WM3_LP_ILK, 0x00000000, 0},
{W, 1, "", WM2_LP_ILK, 0x00000000, 0},
{W, 1, "", WM1_LP_ILK, 0x00000000, 0},
{W, 1, "", 0x9404, 0x00002000, 0},
{W, 1, "", ILK_DSPCLK_GATE,  IVB_VRHUNIT_CLK_GATE |0x10000000, 0},
{W, 1, "", IVB_CHICKEN3, 0x00000024, 0},
{W, 1, "", 0x7010, 0x04000400, 0},
{W, 1, "", 0xb01c, 0x3c4fff8c, 0},
{W, 1, "", 0xb030, 0x20000000, 0},
{R, 1, "", 0x9030, 0x00000000, 0},
{W, 1, "", 0x9030, 0x00000800, 0},
{R, 1, "", _DSPACNTR, 0x00000000, 0},
{W, 1, "", _DSPACNTR, 0x00004000, 0},
{R, 1, "", _DSPAADDR, 0x00000000, 0},
{W, 1, "", _DSPAADDR, 0x00000000, 0},
{R, 1, "", _DSPASIZE+c, 0x00000000, 0},
{W, 1, "", _DSPASIZE+c, 0x00000000, 0},
{R, 1, "", _DSPBCNTR, 0x00000000, 0},
{W, 1, "", _DSPBCNTR, 0x00004000, 0},
{R, 1, "", _DSPBADDR, 0x00000000, 0},
{W, 1, "", _DSPBADDR, 0x00000000, 0},
{R, 1, "", _DSPBSURF, 0x00000000, 0},
{W, 1, "", _DSPBSURF, 0x00000000, 0},
{R, 1, "", _DVSACNTR, 0x00000000, 0},
{W, 1, "", _DVSACNTR,  DVS_TRICKLE_FEED_DISABLE |0x00004000, 0},
{R, 1, "", _DVSALINOFF, 0x00000000, 0},
{W, 1, "", _DVSALINOFF, 0x00000000, 0},
{R, 1, "", _DVSASURF, 0x00000000, 0},
{W, 1, "", _DVSASURF, 0x00000000, 0},
{W, 1, "", SOUTH_DSPCLK_GATE_D,  PCH_DPLSUNIT_CLOCK_GATE_DISABLE |0x20000000, 0},
{R, 1, "", SOUTH_CHICKEN2, 0x00000000, 0},
{W, 1, "", SOUTH_CHICKEN2,  DPLS_EDP_PPS_FIX_DIS |0x00000001, 0},
{W, 1, "", _TRANSA_CHICKEN2, 0x80000000, 0},
{W, 1, "", _TRANSB_CHICKEN2,  TRANS_AUTOTRAIN_GEN_STALL_DIS |0x80000000, 0},
{M, 1, "[drm:drm_edid_to_eld], ELD:no CEA Extension found", 0x0, 0x0, 0},
{M, 1, "[drm:drm_helper_probe_single_connector_modes], [CONNECTOR:6:eDP-1]probed modes :", 0x0, 0x0, 0},
{M, 1, "[drm:drm_mode_debug_printmodeline],Modeline 0:"2560x1700" 60 285250 2560 2608 2640 2720 1700 1703 1713 17490x48 0xa", 0x0, 0x0, 0},
{M, 1, "[drm:drm_setup_crtcs], ", 0x0, 0x0, 0},
{M, 1, "[drm:drm_enable_connectors], connector 6 enabled? yes", 0x0, 0x0, 0},
{M, 1, "[drm:drm_setup_crtcs], picking CRTCs for 8192x8192 config", 0x0, 0x0, 0},
{M, 1, "[drm:drm_setup_crtcs], desired mode 2560x1700 set on crtc 3", 0x0, 0x0, 0},
{M, 1, "[drm:drm_helper_probe_single_connector_modes], [CONNECTOR:6:eDP-1]", 0x0, 0x0, 0},
{M, 1, "[drm:intel_dp_detect], DPCD:110a8441000001c0", 0x0, 0x0, 0},
{M, 1, "[drm:ironlake_edp_panel_vdd_on], Turn eDP VDD on", 0x0, 0x0, 0},
{M, 1, "[drm:intel_dp_detect], DPCD:110a8441000001c0", 0x0, 0x0, 0},
{M, 1, "[drm:drm_enable_connectors], connector 6 enabled? yes", 0x0, 0x0, 0},
{M, 1, "[drm:intel_get_load_detect_pipe], [CONNECTOR:6:eDP-1],[ENCODER:7:TMDS-7]", 0x0, 0x0, 0},
{M, 1, "[drm:intel_dp_mode_fixup], Display port link bw 0a lane count 4clock 270000", 0x0, 0x0, 0},
{M, 1, "[drm:drm_crtc_helper_set_mode], [CRTC:3]", 0x0, 0x0, 0},
{R, 1, "", PCH_PP_STATUS, 0x00000000, 0},
{R, 1, "", PCH_PP_CONTROL, (PCH_PP_UNLOCK&0xabcd0000)| EDP_FORCE_VDD |0xabcd0008, 0},
{R, 1, "", PCH_PP_STATUS, 0x00000000, 0},
{R, 1, "", PCH_PP_CONTROL, (PCH_PP_UNLOCK&0xabcd0000)| EDP_FORCE_VDD |0xabcd0008, 0},
{R, 1, "", DPA_AUX_CH_CTL, 0x001500c8, 0},
{W, 1, "", DPA_AUX_CH_DATA1, 0x80060000, 0},
{W, 1, "", DPA_AUX_CH_DATA2, 0x01000000, 0},
{W, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY | DP_AUX_CH_CTL_DONE | DP_AUX_CH_CTL_TIME_OUT_ERROR | DP_AUX_CH_CTL_RECEIVE_ERROR |0xd25500c8, 0},
{R, 2, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY |0x801500c8, 100},
{R, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_DONE |0x401500c8, 0},
{W, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_DONE | DP_AUX_CH_CTL_TIME_OUT_ERROR | DP_AUX_CH_CTL_RECEIVE_ERROR |0x521500c8, 0},
{R, 1, "", DPA_AUX_CH_DATA1, 0x00000000, 0},
{R, 1, "", 0x64000, 0x0000001c, 0},
{M, 1, "[drm:ironlake_edp_panel_vdd_off], Turn eDP VDD off 1", 0x0, 0x0, 0},
{R, 2, "", PCH_DP_D, 0x00000004, 0},
{R, 1, "", _PIPEACONF, 0x00000000, 0},
{W, 1, "", _PIPEACONF,  PIPECONF_BPP_6 |0x00000040, 0},
{R, 1, "", _PIPEACONF,  PIPECONF_BPP_6 |0x00000040, 0},
{M, 1, "[drm:ironlake_crtc_mode_set], Mode for pipe 0:", 0x0, 0x0, 0},
{M, 1, "[drm:drm_mode_debug_printmodeline],Modeline 0:"2560x1700" 60 285250 2560 2608 2640 2720 1700 1703 1713 1749 0x48 0xa", 0x0, 0x0, 0},
{W, 1, "", _TRANSA_DATA_M1, 0x00000000, 0},
{W, 1, "", _TRANSA_DATA_N1, 0x00000000, 0},
{W, 1, "", _TRANSA_DP_LINK_M1, 0x00000000, 0},
{W, 1, "", _TRANSA_DP_LINK_N1, 0x00000000, 0},
{W, 1, "", _PCH_FPA1, 0x00020e08, 0},
{W, 1, "", _VSYNCSHIFT_A, 0x00000000, 0},
{W, 1, "", _HTOTAL_A, 0x0a9f09ff, 0},
{W, 1, "", _HBLANK_A, 0x0a9f09ff, 0},
{W, 1, "", _HSYNC_A, 0x0a4f0a2f, 0},
{W, 1, "", _VTOTAL_A, 0x06d406a3, 0},
{W, 1, "", _VBLANK_A, 0x06d406a3, 0},
{W, 1, "", _VSYNC_A, 0x06b006a6, 0},
{W, 1, "", _PIPEASRC, 0x09ff06a3, 0},
{W, 1, "", _PIPEA_DATA_M1, 0x7e4e58a4, 0},
{W, 1, "", _PIPEA_DATA_N1, 0x0083d600, 0},
{W, 1, "", _PIPEA_LINK_M1, 0x00045a42, 0},
{W, 1, "", _PIPEA_LINK_N1, 0x00041eb0, 0},
{M, 1, "[drm:ironlake_set_pll_edp], eDP PLL enable for clock 270000", 0x0, 0x0, 0},
{R, 1, "", 0x64000, 0x0000001c, 0},
{W, 1, "", 0x64000, 0x0000001c, 0},
{R, 1, "", 0x64000, 0x0000001c, 500},
{W, 1, "", _PIPEACONF,  PIPECONF_BPP_6 | PIPECONF_DITHER_EN |0x00000050, 0},
{R, 1, "", _PIPEACONF,  PIPECONF_BPP_6 | PIPECONF_DITHER_EN |0x00000050, 0},
{R, 1, "", _PIPEASTAT, 0x00000000, 0},
{W, 1, "", _PIPEASTAT,  PIPE_VBLANK_INTERRUPT_STATUS |0x00000002, 0},
{R, 4562, "", _PIPEASTAT, 0x00000000, 0},
{M, 1, "[drm:intel_wait_for_vblank], vblank wait timed out", 0x0, 0x0, 0},
{W, 1, "", _DSPACNTR,  DISPPLANE_GAMMA_ENABLE |0x40000000, 0},
{R, 2, "", _DSPACNTR,  DISPPLANE_GAMMA_ENABLE |0x40000000, 0},
{W, 1, "", _DSPACNTR,  DISPPLANE_GAMMA_ENABLE |0x58004000, 0},
{M, 1, "[drm:ironlake_update_plane], Writing base 00000000 00000000 0 0 10240", 0x0, 0x0, 0},
{W, 1, "", _DSPASTRIDE, 0x00002800, 0},
{W, 1, "", _DSPASIZE+c, 0x00000000, 0},
{W, 1, "", _DSPACNTR+24, 0x00000000, 0},
{W, 1, "", _DSPAADDR, 0x00000000, 0},
{R, 1, "", _DSPACNTR,  DISPPLANE_GAMMA_ENABLE |0x58004000, 0},
{R, 1, "", 0x145d10, 0x2010040c, 0},
{R, 1, "", WM0_PIPEA_ILK,  WM0_PIPE_PLANE_SHIFT | WM0_PIPE_SPRITE_SHIFT |0x00783818, 0},
{W, 1, "", WM0_PIPEA_ILK, 0x00183806, 0},
{M, 1, "[drm:sandybridge_update_wm], FIFO watermarks For pipe A - plane 24,cursor:6", 0x0, 0x0, 0},
{W, 1, "", WM3_LP_ILK, 0x00000000, 0},
{W, 1, "", WM2_LP_ILK, 0x00000000, 0},
{W, 1, "", WM1_LP_ILK, 0x00000000, 0},
{R, 1, "", 0x145d10, 0x2010040c, 0},
{M, 1, "[drm:ironlake_check_srwm], watermark 1:display plane 38, fbc lines 3,cursor 6", 0x0, 0x0, 0},
{R, 1, "", 0x145d10, 0x2010040c, 0},
{W, 1, "", WM1_LP_ILK,  WM1_LP_SR_EN |( WM1_LP_FBC_SHIFT &0x4)|0x84302606, 0},
{R, 1, "", 0x145d10, 0x2010040c, 0},
{M, 1, "[drm:ironlake_check_srwm], watermark 2:display plane 145, fbc lines 3,cursor 6", 0x0, 0x0, 0},
{R, 1, "", 0x145d10, 0x2010040c, 0},
{W, 1, "", WM2_LP_ILK,  WM2_LP_EN |0x90309106, 0},
{R, 1, "", 0x145d10, 0x2010040c, 0},
{M, 1, "[drm:ironlake_check_srwm], watermark 3:display plane 288, fbc lines 4,cursor 10", 0x0, 0x0, 0},
{R, 1, "", 0x145d10, 0x2010040c, 0},
{W, 1, "", WM3_LP_ILK,  WM3_LP_EN |0xa041200a, 0},
{M, 1, "[drm:drm_crtc_helper_set_mode], [ENCODER:7:TMDS-7]set [MODE:0:2560x1700]", 0x0, 0x0, 0},
{M, 1, "[drm:ironlake_edp_pll_on], ", 0x0, 0x0, 0},
{R, 1, "", 0x64000, 0x0000001c, 0},
{W, 1, "", 0x64000, 0x0000401c, 0},
{R, 1, "", 0x64000, 0x0000401c, 200},
{R, 1, "", 0x64000, 0x0000401c, 0},
{R, 1, "", 0x145d10, 0x2010040c, 0},
{R, 1, "", WM0_PIPEA_ILK, 0x00183806, 0},
{W, 1, "", WM0_PIPEA_ILK, 0x00183806, 0},
{M, 1, "[drm:sandybridge_update_wm], FIFO watermarks For pipe A - plane 24,cursor:6", 0x0, 0x0, 0},
{W, 1, "", WM3_LP_ILK, 0x00000000, 0},
{W, 1, "", WM2_LP_ILK, 0x00000000, 0},
{W, 1, "", WM1_LP_ILK, 0x00000000, 0},
{R, 1, "", 0x145d10, 0x2010040c, 0},
{M, 1, "[drm:ironlake_check_srwm], watermark 1:display plane 38, fbc lines 3,cursor 6", 0x0, 0x0, 0},
{R, 1, "", 0x145d10, 0x2010040c, 0},
{W, 1, "", WM1_LP_ILK,  WM1_LP_SR_EN |( WM1_LP_FBC_SHIFT &0x4)|0x84302606, 0},
{R, 1, "", 0x145d10, 0x2010040c, 0},
{M, 1, "[drm:ironlake_check_srwm], watermark 2:display plane 145, fbc lines 3,cursor 6", 0x0, 0x0, 0},
{R, 1, "", 0x145d10, 0x2010040c, 0},
{W, 1, "", WM2_LP_ILK,  WM2_LP_EN |0x90309106, 0},
{R, 1, "", 0x145d10, 0x2010040c, 0},
{M, 1, "[drm:ironlake_check_srwm], watermark 3:display plane 288, fbc lines 4,cursor 10", 0x0, 0x0, 0},
{R, 1, "", 0x145d10, 0x2010040c, 0},
{W, 1, "", WM3_LP_ILK,  WM3_LP_EN |0xa041200a, 0},
{R, 1, "", _FDI_TXA_CTL, 0x00040000, 0},
{W, 1, "", _FDI_TXA_CTL, 0x00040000, 0},
{R, 1, "", _FDI_TXA_CTL, 0x00040000, 0},
{R, 1, "", _FDI_RXA_CTL, 0x00000040, 0},
{R, 1, "", _PIPEACONF,  PIPECONF_BPP_6 | PIPECONF_DITHER_EN |0x00000050, 0},
{W, 1, "", _FDI_RXA_CTL, 0x00020040, 0},
{R, 1, "", _FDI_RXA_CTL, 0x00020040, 100},
{R, 1, "", SOUTH_CHICKEN1, 0x00000000, 0},
{W, 2, "", SOUTH_CHICKEN1, 0x00000000, 0},
{R, 1, "", SOUTH_CHICKEN1, 0x00000000, 0},
{R, 1, "", _FDI_TXA_CTL, 0x00040000, 0},
{W, 1, "", _FDI_TXA_CTL, 0x00040000, 0},
{R, 1, "", _FDI_RXA_CTL, 0x00020040, 0},
{R, 1, "", _PIPEACONF,  PIPECONF_BPP_6 | PIPECONF_DITHER_EN |0x00000050, 0},
{W, 1, "", _FDI_RXA_CTL, 0x00020040, 0},
{R, 1, "", _FDI_RXA_CTL, 0x00020040, 100},
{W, 1, "", _LGC_PALETTE_A, 0x00000000, 0},
{W, 1, "", _LGC_PALETTE_A+4, 0x00010101, 0},
{W, 1, "", _LGC_PALETTE_A+8, 0x00020202, 0},
{W, 1, "", _LGC_PALETTE_A+c, 0x00030303, 0},
{W, 1, "", _LGC_PALETTE_A+10, 0x00040404, 0},
{W, 1, "", _LGC_PALETTE_A+14, 0x00050505, 0},
{W, 1, "", _LGC_PALETTE_A+18, 0x00060606, 0},
{W, 1, "", _LGC_PALETTE_A+1c, 0x00070707, 0},
{W, 1, "", _LGC_PALETTE_A+20, 0x00080808, 0},
{W, 1, "", _LGC_PALETTE_A+24, 0x00090909, 0},
{W, 1, "", _LGC_PALETTE_A+28, 0x000a0a0a, 0},
{W, 1, "", _LGC_PALETTE_A+2c, 0x000b0b0b, 0},
{W, 1, "", _LGC_PALETTE_A+30, 0x000c0c0c, 0},
{W, 1, "", _LGC_PALETTE_A+34, 0x000d0d0d, 0},
{W, 1, "", _LGC_PALETTE_A+38, 0x000e0e0e, 0},
{W, 1, "", _LGC_PALETTE_A+3c, 0x000f0f0f, 0},
{W, 1, "", _LGC_PALETTE_A+40, 0x00101010, 0},
{W, 1, "", _LGC_PALETTE_A+44, 0x00111111, 0},
{W, 1, "", _LGC_PALETTE_A+48, 0x00121212, 0},
{W, 1, "", _LGC_PALETTE_A+4c, 0x00131313, 0},
{W, 1, "", _LGC_PALETTE_A+50, 0x00141414, 0},
{W, 1, "", _LGC_PALETTE_A+54, 0x00151515, 0},
{W, 1, "", _LGC_PALETTE_A+58, 0x00161616, 0},
{W, 1, "", _LGC_PALETTE_A+5c, 0x00171717, 0},
{W, 1, "", _LGC_PALETTE_A+60, 0x00181818, 0},
{W, 1, "", _LGC_PALETTE_A+64, 0x00191919, 0},
{W, 1, "", _LGC_PALETTE_A+68, 0x001a1a1a, 0},
{W, 1, "", _LGC_PALETTE_A+6c, 0x001b1b1b, 0},
{W, 1, "", _LGC_PALETTE_A+70, 0x001c1c1c, 0},
{W, 1, "", _LGC_PALETTE_A+74, 0x001d1d1d, 0},
{W, 1, "", _LGC_PALETTE_A+78, 0x001e1e1e, 0},
{W, 1, "", _LGC_PALETTE_A+7c, 0x001f1f1f, 0},
{W, 1, "", 0x4a080, 0x00202020, 0},
{W, 1, "", 0x4a084, 0x00212121, 0},
{W, 1, "", 0x4a088, 0x00222222, 0},
{W, 1, "", 0x4a08c, 0x00232323, 0},
{W, 1, "", 0x4a090, 0x00242424, 0},
{W, 1, "", 0x4a094, 0x00252525, 0},
{W, 1, "", 0x4a098, 0x00262626, 0},
{W, 1, "", 0x4a09c, 0x00272727, 0},
{W, 1, "", 0x4a0a0, 0x00282828, 0},
{W, 1, "", 0x4a0a4, 0x00292929, 0},
{W, 1, "", 0x4a0a8, 0x002a2a2a, 0},
{W, 1, "", 0x4a0ac, 0x002b2b2b, 0},
{W, 1, "", 0x4a0b0, 0x002c2c2c, 0},
{W, 1, "", 0x4a0b4, 0x002d2d2d, 0},
{W, 1, "", 0x4a0b8, 0x002e2e2e, 0},
{W, 1, "", 0x4a0bc, 0x002f2f2f, 0},
{W, 1, "", 0x4a0c0, 0x00303030, 0},
{W, 1, "", 0x4a0c4, 0x00313131, 0},
{W, 1, "", 0x4a0c8, 0x00323232, 0},
{W, 1, "", 0x4a0cc, 0x00333333, 0},
{W, 1, "", 0x4a0d0, 0x00343434, 0},
{W, 1, "", 0x4a0d4, 0x00353535, 0},
{W, 1, "", 0x4a0d8, 0x00363636, 0},
{W, 1, "", 0x4a0dc, 0x00373737, 0},
{W, 1, "", 0x4a0e0, 0x00383838, 0},
{W, 1, "", 0x4a0e4, 0x00393939, 0},
{W, 1, "", 0x4a0e8, 0x003a3a3a, 0},
{W, 1, "", 0x4a0ec, 0x003b3b3b, 0},
{W, 1, "", 0x4a0f0, 0x003c3c3c, 0},
{W, 1, "", 0x4a0f4, 0x003d3d3d, 0},
{W, 1, "", 0x4a0f8, 0x003e3e3e, 0},
{W, 1, "", 0x4a0fc, 0x003f3f3f, 0},
{W, 1, "", 0x4a100, 0x00404040, 0},
{W, 1, "", 0x4a104, 0x00414141, 0},
{W, 1, "", 0x4a108, 0x00424242, 0},
{W, 1, "", 0x4a10c, 0x00434343, 0},
{W, 1, "", 0x4a110, 0x00444444, 0},
{W, 1, "", 0x4a114, 0x00454545, 0},
{W, 1, "", 0x4a118, 0x00464646, 0},
{W, 1, "", 0x4a11c, 0x00474747, 0},
{W, 1, "", 0x4a120, 0x00484848, 0},
{W, 1, "", 0x4a124, 0x00494949, 0},
{W, 1, "", 0x4a128, 0x004a4a4a, 0},
{W, 1, "", 0x4a12c, 0x004b4b4b, 0},
{W, 1, "", 0x4a130, 0x004c4c4c, 0},
{W, 1, "", 0x4a134, 0x004d4d4d, 0},
{W, 1, "", 0x4a138, 0x004e4e4e, 0},
{W, 1, "", 0x4a13c, 0x004f4f4f, 0},
{W, 1, "", 0x4a140, 0x00505050, 0},
{W, 1, "", 0x4a144, 0x00515151, 0},
{W, 1, "", 0x4a148, 0x00525252, 0},
{W, 1, "", 0x4a14c, 0x00535353, 0},
{W, 1, "", 0x4a150, 0x00545454, 0},
{W, 1, "", 0x4a154, 0x00555555, 0},
{W, 1, "", 0x4a158, 0x00565656, 0},
{W, 1, "", 0x4a15c, 0x00575757, 0},
{W, 1, "", 0x4a160, 0x00585858, 0},
{W, 1, "", 0x4a164, 0x00595959, 0},
{W, 1, "", 0x4a168, 0x005a5a5a, 0},
{W, 1, "", 0x4a16c, 0x005b5b5b, 0},
{W, 1, "", 0x4a170, 0x005c5c5c, 0},
{W, 1, "", 0x4a174, 0x005d5d5d, 0},
{W, 1, "", 0x4a178, 0x005e5e5e, 0},
{W, 1, "", 0x4a17c, 0x005f5f5f, 0},
{W, 1, "", 0x4a180, 0x00606060, 0},
{W, 1, "", 0x4a184, 0x00616161, 0},
{W, 1, "", 0x4a188, 0x00626262, 0},
{W, 1, "", 0x4a18c, 0x00636363, 0},
{W, 1, "", 0x4a190, 0x00646464, 0},
{W, 1, "", 0x4a194, 0x00656565, 0},
{W, 1, "", 0x4a198, 0x00666666, 0},
{W, 1, "", 0x4a19c, 0x00676767, 0},
{W, 1, "", 0x4a1a0, 0x00686868, 0},
{W, 1, "", 0x4a1a4, 0x00696969, 0},
{W, 1, "", 0x4a1a8, 0x006a6a6a, 0},
{W, 1, "", 0x4a1ac, 0x006b6b6b, 0},
{W, 1, "", 0x4a1b0, 0x006c6c6c, 0},
{W, 1, "", 0x4a1b4, 0x006d6d6d, 0},
{W, 1, "", 0x4a1b8, 0x006e6e6e, 0},
{W, 1, "", 0x4a1bc, 0x006f6f6f, 0},
{W, 1, "", 0x4a1c0, 0x00707070, 0},
{W, 1, "", 0x4a1c4, 0x00717171, 0},
{W, 1, "", 0x4a1c8, 0x00727272, 0},
{W, 1, "", 0x4a1cc, 0x00737373, 0},
{W, 1, "", 0x4a1d0, 0x00747474, 0},
{W, 1, "", 0x4a1d4, 0x00757575, 0},
{W, 1, "", 0x4a1d8, 0x00767676, 0},
{W, 1, "", 0x4a1dc, 0x00777777, 0},
{W, 1, "", 0x4a1e0, 0x00787878, 0},
{W, 1, "", 0x4a1e4, 0x00797979, 0},
{W, 1, "", 0x4a1e8, 0x007a7a7a, 0},
{W, 1, "", 0x4a1ec, 0x007b7b7b, 0},
{W, 1, "", 0x4a1f0, 0x007c7c7c, 0},
{W, 1, "", 0x4a1f4, 0x007d7d7d, 0},
{W, 1, "", 0x4a1f8, 0x007e7e7e, 0},
{W, 1, "", 0x4a1fc, 0x007f7f7f, 0},
{W, 1, "", 0x4a200, 0x00808080, 0},
{W, 1, "", 0x4a204, 0x00818181, 0},
{W, 1, "", 0x4a208, 0x00828282, 0},
{W, 1, "", 0x4a20c, 0x00838383, 0},
{W, 1, "", 0x4a210, 0x00848484, 0},
{W, 1, "", 0x4a214, 0x00858585, 0},
{W, 1, "", 0x4a218, 0x00868686, 0},
{W, 1, "", 0x4a21c, 0x00878787, 0},
{W, 1, "", 0x4a220, 0x00888888, 0},
{W, 1, "", 0x4a224, 0x00898989, 0},
{W, 1, "", 0x4a228, 0x008a8a8a, 0},
{W, 1, "", 0x4a22c, 0x008b8b8b, 0},
{W, 1, "", 0x4a230, 0x008c8c8c, 0},
{W, 1, "", 0x4a234, 0x008d8d8d, 0},
{W, 1, "", 0x4a238, 0x008e8e8e, 0},
{W, 1, "", 0x4a23c, 0x008f8f8f, 0},
{W, 1, "", 0x4a240, 0x00909090, 0},
{W, 1, "", 0x4a244, 0x00919191, 0},
{W, 1, "", 0x4a248, 0x00929292, 0},
{W, 1, "", 0x4a24c, 0x00939393, 0},
{W, 1, "", 0x4a250, 0x00949494, 0},
{W, 1, "", 0x4a254, 0x00959595, 0},
{W, 1, "", 0x4a258, 0x00969696, 0},
{W, 1, "", 0x4a25c, 0x00979797, 0},
{W, 1, "", 0x4a260, 0x00989898, 0},
{W, 1, "", 0x4a264, 0x00999999, 0},
{W, 1, "", 0x4a268, 0x009a9a9a, 0},
{W, 1, "", 0x4a26c, 0x009b9b9b, 0},
{W, 1, "", 0x4a270, 0x009c9c9c, 0},
{W, 1, "", 0x4a274, 0x009d9d9d, 0},
{W, 1, "", 0x4a278, 0x009e9e9e, 0},
{W, 1, "", 0x4a27c, 0x009f9f9f, 0},
{W, 1, "", 0x4a280, 0x00a0a0a0, 0},
{W, 1, "", 0x4a284, 0x00a1a1a1, 0},
{W, 1, "", 0x4a288, 0x00a2a2a2, 0},
{W, 1, "", 0x4a28c, 0x00a3a3a3, 0},
{W, 1, "", 0x4a290, 0x00a4a4a4, 0},
{W, 1, "", 0x4a294, 0x00a5a5a5, 0},
{W, 1, "", 0x4a298, 0x00a6a6a6, 0},
{W, 1, "", 0x4a29c, 0x00a7a7a7, 0},
{W, 1, "", 0x4a2a0, 0x00a8a8a8, 0},
{W, 1, "", 0x4a2a4, 0x00a9a9a9, 0},
{W, 1, "", 0x4a2a8, 0x00aaaaaa, 0},
{W, 1, "", 0x4a2ac, 0x00ababab, 0},
{W, 1, "", 0x4a2b0, 0x00acacac, 0},
{W, 1, "", 0x4a2b4, 0x00adadad, 0},
{W, 1, "", 0x4a2b8, 0x00aeaeae, 0},
{W, 1, "", 0x4a2bc, 0x00afafaf, 0},
{W, 1, "", 0x4a2c0, 0x00b0b0b0, 0},
{W, 1, "", 0x4a2c4, 0x00b1b1b1, 0},
{W, 1, "", 0x4a2c8, 0x00b2b2b2, 0},
{W, 1, "", 0x4a2cc, 0x00b3b3b3, 0},
{W, 1, "", 0x4a2d0, 0x00b4b4b4, 0},
{W, 1, "", 0x4a2d4, 0x00b5b5b5, 0},
{W, 1, "", 0x4a2d8, 0x00b6b6b6, 0},
{W, 1, "", 0x4a2dc, 0x00b7b7b7, 0},
{W, 1, "", 0x4a2e0, 0x00b8b8b8, 0},
{W, 1, "", 0x4a2e4, 0x00b9b9b9, 0},
{W, 1, "", 0x4a2e8, 0x00bababa, 0},
{W, 1, "", 0x4a2ec, 0x00bbbbbb, 0},
{W, 1, "", 0x4a2f0, 0x00bcbcbc, 0},
{W, 1, "", 0x4a2f4, 0x00bdbdbd, 0},
{W, 1, "", 0x4a2f8, 0x00bebebe, 0},
{W, 1, "", 0x4a2fc, 0x00bfbfbf, 0},
{W, 1, "", 0x4a300, 0x00c0c0c0, 0},
{W, 1, "", 0x4a304, 0x00c1c1c1, 0},
{W, 1, "", 0x4a308, 0x00c2c2c2, 0},
{W, 1, "", 0x4a30c, 0x00c3c3c3, 0},
{W, 1, "", 0x4a310, 0x00c4c4c4, 0},
{W, 1, "", 0x4a314, 0x00c5c5c5, 0},
{W, 1, "", 0x4a318, 0x00c6c6c6, 0},
{W, 1, "", 0x4a31c, 0x00c7c7c7, 0},
{W, 1, "", 0x4a320, 0x00c8c8c8, 0},
{W, 1, "", 0x4a324, 0x00c9c9c9, 0},
{W, 1, "", 0x4a328, 0x00cacaca, 0},
{W, 1, "", 0x4a32c, 0x00cbcbcb, 0},
{W, 1, "", 0x4a330, 0x00cccccc, 0},
{W, 1, "", 0x4a334, 0x00cdcdcd, 0},
{W, 1, "", 0x4a338, 0x00cecece, 0},
{W, 1, "", 0x4a33c, 0x00cfcfcf, 0},
{W, 1, "", 0x4a340, 0x00d0d0d0, 0},
{W, 1, "", 0x4a344, 0x00d1d1d1, 0},
{W, 1, "", 0x4a348, 0x00d2d2d2, 0},
{W, 1, "", 0x4a34c, 0x00d3d3d3, 0},
{W, 1, "", 0x4a350, 0x00d4d4d4, 0},
{W, 1, "", 0x4a354, 0x00d5d5d5, 0},
{W, 1, "", 0x4a358, 0x00d6d6d6, 0},
{W, 1, "", 0x4a35c, 0x00d7d7d7, 0},
{W, 1, "", 0x4a360, 0x00d8d8d8, 0},
{W, 1, "", 0x4a364, 0x00d9d9d9, 0},
{W, 1, "", 0x4a368, 0x00dadada, 0},
{W, 1, "", 0x4a36c, 0x00dbdbdb, 0},
{W, 1, "", 0x4a370, 0x00dcdcdc, 0},
{W, 1, "", 0x4a374, 0x00dddddd, 0},
{W, 1, "", 0x4a378, 0x00dedede, 0},
{W, 1, "", 0x4a37c, 0x00dfdfdf, 0},
{W, 1, "", 0x4a380, 0x00e0e0e0, 0},
{W, 1, "", 0x4a384, 0x00e1e1e1, 0},
{W, 1, "", 0x4a388, 0x00e2e2e2, 0},
{W, 1, "", 0x4a38c, 0x00e3e3e3, 0},
{W, 1, "", 0x4a390, 0x00e4e4e4, 0},
{W, 1, "", 0x4a394, 0x00e5e5e5, 0},
{W, 1, "", 0x4a398, 0x00e6e6e6, 0},
{W, 1, "", 0x4a39c, 0x00e7e7e7, 0},
{W, 1, "", 0x4a3a0, 0x00e8e8e8, 0},
{W, 1, "", 0x4a3a4, 0x00e9e9e9, 0},
{W, 1, "", 0x4a3a8, 0x00eaeaea, 0},
{W, 1, "", 0x4a3ac, 0x00ebebeb, 0},
{W, 1, "", 0x4a3b0, 0x00ececec, 0},
{W, 1, "", 0x4a3b4, 0x00ededed, 0},
{W, 1, "", 0x4a3b8, 0x00eeeeee, 0},
{W, 1, "", 0x4a3bc, 0x00efefef, 0},
{W, 1, "", 0x4a3c0, 0x00f0f0f0, 0},
{W, 1, "", 0x4a3c4, 0x00f1f1f1, 0},
{W, 1, "", 0x4a3c8, 0x00f2f2f2, 0},
{W, 1, "", 0x4a3cc, 0x00f3f3f3, 0},
{W, 1, "", 0x4a3d0, 0x00f4f4f4, 0},
{W, 1, "", 0x4a3d4, 0x00f5f5f5, 0},
{W, 1, "", 0x4a3d8, 0x00f6f6f6, 0},
{W, 1, "", 0x4a3dc, 0x00f7f7f7, 0},
{W, 1, "", 0x4a3e0, 0x00f8f8f8, 0},
{W, 1, "", 0x4a3e4, 0x00f9f9f9, 0},
{W, 1, "", 0x4a3e8, 0x00fafafa, 0},
{W, 1, "", 0x4a3ec, 0x00fbfbfb, 0},
{W, 1, "", 0x4a3f0, 0x00fcfcfc, 0},
{W, 1, "", 0x4a3f4, 0x00fdfdfd, 0},
{W, 1, "", 0x4a3f8, 0x00fefefe, 0},
{W, 1, "", 0x4a3fc, 0x00ffffff, 0},
{R, 1, "", _PIPEACONF,  PIPECONF_BPP_6 | PIPECONF_DITHER_EN |0x00000050, 0},
{W, 1, "", _PIPEACONF,  PIPECONF_ENABLE | PIPECONF_BPP_6 | PIPECONF_DITHER_EN |0x80000050, 0},
{R, 1, "", _PIPEASTAT, 0x00000000, 0},
{W, 1, "", _PIPEASTAT,  PIPE_VBLANK_INTERRUPT_STATUS |0x00000002, 0},
{R, 4533, "", _PIPEASTAT, 0x00000000, 0},
{M, 1, "[drm:intel_wait_for_vblank], vblank wait timed out", 0x0, 0x0, 0},
{R, 1, "", _PIPEACONF,  PIPECONF_ENABLE | PIPECONF_DOUBLE_WIDE | PIPECONF_BPP_6 | PIPECONF_DITHER_EN |0xc0000050, 0},
{R, 1, "", _DSPACNTR,  DISPPLANE_GAMMA_ENABLE |0x58004000, 0},
{W, 1, "", _DSPACNTR,  DISPLAY_PLANE_ENABLE | DISPPLANE_GAMMA_ENABLE |0xd8004000, 0},
{R, 1, "", _DSPAADDR, 0x00000000, 0},
{W, 1, "", _DSPAADDR, 0x00000000, 0},
{R, 1, "", _DSPASIZE+c, 0x00000000, 0},
{W, 1, "", _DSPASIZE+c, 0x00000000, 0},
{R, 1, "", _PIPEASTAT, 0x00000000, 0},
{W, 1, "", _PIPEASTAT,  PIPE_VBLANK_INTERRUPT_STATUS |0x00000002, 0},
{R, 4392, "", _PIPEASTAT, 0x00000000, 0},
{M, 1, "[drm:intel_wait_for_vblank], vblank wait timed out", 0x0, 0x0, 0},
{M, 1, "[drm:ironlake_edp_panel_vdd_on], Turn eDP VDD on", 0x0, 0x0, 0},
{R, 1, "", PCH_PP_CONTROL, (PCH_PP_UNLOCK&0xabcd0000)| EDP_FORCE_VDD |0xabcd0008, 0},
{M, 1, "[drm:ironlake_edp_panel_on], Turn eDP power on", 0x0, 0x0, 0},
{R, 1, "", PCH_PP_STATUS, 0x00000000, 0},
{M, 1, "[drm:ironlake_wait_panel_power_cycle], Wait for panel power cycle", 0x0, 0x0, 0},
{M, 1, "[drm:ironlake_wait_panel_status], R PCH_PP_CONTROL:abcd0008", 0x0, 0x0, 0},
{R, 2, "", PCH_PP_STATUS, 0x00000000, 0},
{R, 1, "", PCH_PP_CONTROL, (PCH_PP_UNLOCK&0xabcd0000)| EDP_FORCE_VDD |0xabcd0008, 0},
{W, 1, "", PCH_PP_CONTROL, (PCH_PP_UNLOCK&0xabcd0000)| EDP_FORCE_VDD | PANEL_POWER_RESET | PANEL_POWER_ON |0xabcd000b, 0},
{R, 1, "", PCH_PP_CONTROL, (PCH_PP_UNLOCK&0xabcd0000)| EDP_FORCE_VDD | PANEL_POWER_RESET | PANEL_POWER_ON |0xabcd000b, 0},
{M, 1, "[drm:ironlake_wait_panel_on], Wait for panel power on", 0x0, 0x0, 0},
{M, 1, "[drm:ironlake_wait_panel_status], R PCH_PP_CONTROL:abcd000b", 0x0, 0x0, 0},
{R, 4, "", PCH_PP_STATUS, 0x0000000a, 0},
{R, 16983, "", PCH_PP_STATUS, 0x9000000a, 0},
{R, 17839, "", PCH_PP_STATUS, 0x90000009, 0},
{R, 1, "", PCH_PP_STATUS, 0x80000008, 0},
{M, 1, "[drm:ironlake_edp_panel_vdd_off], Turn eDP VDD off 1", 0x0, 0x0, 0},
{R, 2, "", PCH_PP_CONTROL, (PCH_PP_UNLOCK&0xabcd0000)| EDP_FORCE_VDD | PANEL_POWER_RESET | PANEL_POWER_ON |0xabcd000b, 0},
{W, 1, "", PCH_PP_CONTROL, (PCH_PP_UNLOCK&0xabcd0000)| PANEL_POWER_RESET | PANEL_POWER_ON |0xabcd0003, 0},
{R, 1, "", PCH_PP_CONTROL, (PCH_PP_UNLOCK&0xabcd0000)| PANEL_POWER_RESET | PANEL_POWER_ON |0xabcd0003, 0},
{M, 1, "[drm:ironlake_panel_vdd_off_sync], R PCH_PP_CONTROL:abcd0003", 0x0, 0x0, 0},
{R, 1, "", PCH_PP_STATUS, 0x80000008, 0},
{W, 1, "", 0x64000, 0x8e1c4104, 0},
{R, 1, "", 0x64000, 0x8e1c4104, 0},
{R, 2, "", PCH_PP_STATUS, 0x80000008, 0},
{R, 1, "", 0x64000, 0x8cdc4104, 0},
{M, 1, "[drm:intel_dp_link_down], ", 0x0, 0x0, 0},
{W, 1, "", 0x64000, 0x8e1c0004, 0},
{R, 1, "", 0x64000, 0x8e1c0004, 100},
{W, 1, "", 0x64000, 0x8e1c0204, 0},
{R, 1, "", 0x64000, 0x8e1c0204, 0},
{W, 1, "", 0x64000, 0x0e1c0304, 0},
{R, 2, "", 0x64000, 0x0e1c0304, 0},
{R, 2, "", PCH_PP_STATUS, 0x80000008, 0},
{R, 1, "", DPA_AUX_CH_CTL, 0x007500c8, 0},
{W, 1, "", DPA_AUX_CH_DATA1, 0x80010008, 0},
{W, 1, "", DPA_AUX_CH_DATA2, 0x0a840000, 0},
{W, 1, "", DPA_AUX_CH_DATA3, 0x00000000, 0},
{W, 1, "", DPA_AUX_CH_DATA4, 0x01000000, 0},
{W, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY | DP_AUX_CH_CTL_DONE | DP_AUX_CH_CTL_TIME_OUT_ERROR | DP_AUX_CH_CTL_RECEIVE_ERROR |0xd2d500c8, 0},
{R, 3, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY |0x807500c8, 100},
{R, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_DONE |0x401500c8, 0},
{W, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_DONE | DP_AUX_CH_CTL_TIME_OUT_ERROR | DP_AUX_CH_CTL_RECEIVE_ERROR |0x521500c8, 0},
{R, 1, "", DPA_AUX_CH_DATA1, 0x00000000, 0},
{W, 1, "", 0x64000, 0x891c4004, 0},
{R, 1, "", 0x64000, 0x891c4004, 0},
{R, 2, "", PCH_PP_STATUS, 0x80000008, 0},
{R, 1, "", DPA_AUX_CH_CTL, 0x001500c8, 0},
{W, 1, "", DPA_AUX_CH_DATA1, 0x80010200, 0},
{W, 1, "", DPA_AUX_CH_DATA2, 0x21000000, 0},
{W, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY | DP_AUX_CH_CTL_DONE | DP_AUX_CH_CTL_TIME_OUT_ERROR | DP_AUX_CH_CTL_RECEIVE_ERROR |0xd25500c8, 0},
{R, 2, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY |0x801500c8, 100},
{R, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_DONE |0x401500c8, 0},
{W, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_DONE | DP_AUX_CH_CTL_TIME_OUT_ERROR | DP_AUX_CH_CTL_RECEIVE_ERROR |0x521500c8, 0},
{R, 1, "", DPA_AUX_CH_DATA1, 0x00000000, 0},
{R, 2, "", PCH_PP_STATUS, 0x80000008, 0},
{R, 1, "", DPA_AUX_CH_CTL, 0x001500c8, 0},
{W, 1, "", DPA_AUX_CH_DATA1, 0x80010303, 0},
{W, 1, "", DPA_AUX_CH_DATA2, 0x00000000, 0},
{W, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY | DP_AUX_CH_CTL_DONE | DP_AUX_CH_CTL_TIME_OUT_ERROR | DP_AUX_CH_CTL_RECEIVE_ERROR |0xd28500c8, 0},
{R, 3, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY |0x801500c8, 100},
{R, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_DONE |0x401500c8, 0},
{W, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_DONE | DP_AUX_CH_CTL_TIME_OUT_ERROR | DP_AUX_CH_CTL_RECEIVE_ERROR |0x521500c8, 0},
{R, 1, "", DPA_AUX_CH_DATA1, 0x00000000, 100},
{R, 2, "", PCH_PP_STATUS, 0x80000008, 0},
{R, 1, "", DPA_AUX_CH_CTL, 0x001500c8, 0},
{W, 1, "", DPA_AUX_CH_DATA1, 0x90020205, 0},
{W, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY | DP_AUX_CH_CTL_DONE | DP_AUX_CH_CTL_TIME_OUT_ERROR | DP_AUX_CH_CTL_RECEIVE_ERROR |0xd24500c8, 0},
{R, 2, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY |0x801500c8, 100},
{R, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY |0x804500c8, 100},
{R, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_DONE |0x407500c8, 0},
{W, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_DONE | DP_AUX_CH_CTL_TIME_OUT_ERROR | DP_AUX_CH_CTL_RECEIVE_ERROR |0x527500c8, 0},
{R, 1, "", DPA_AUX_CH_DATA1, 0x00111180, 0},
{R, 1, "", DPA_AUX_CH_DATA2, 0x02000000, 0},
{M, 1, "[drm:intel_dp_start_link_train], clock recovery OK", 0x0, 0x0, 0},
{W, 1, "", 0x64000, 0x891c4104, 0},
{R, 1, "", 0x64000, 0x891c4104, 0},
{R, 2, "", PCH_PP_STATUS, 0x80000008, 0},
{R, 1, "", DPA_AUX_CH_CTL, 0x007500c8, 0},
{W, 1, "", DPA_AUX_CH_DATA1, 0x80010200, 0},
{W, 1, "", DPA_AUX_CH_DATA2, 0x22000000, 0},
{W, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY | DP_AUX_CH_CTL_DONE | DP_AUX_CH_CTL_TIME_OUT_ERROR | DP_AUX_CH_CTL_RECEIVE_ERROR |0xd25500c8, 0},
{R, 2, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY |0x807500c8, 100},
{R, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_DONE |0x401500c8, 0},
{W, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_DONE | DP_AUX_CH_CTL_TIME_OUT_ERROR | DP_AUX_CH_CTL_RECEIVE_ERROR |0x521500c8, 0},
{R, 1, "", DPA_AUX_CH_DATA1, 0x00000000, 0},
{R, 2, "", PCH_PP_STATUS, 0x80000008, 0},
{R, 1, "", DPA_AUX_CH_CTL, 0x001500c8, 0},
{W, 1, "", DPA_AUX_CH_DATA1, 0x80010303, 0},
{W, 1, "", DPA_AUX_CH_DATA2, 0x00000000, 0},
{W, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY | DP_AUX_CH_CTL_DONE | DP_AUX_CH_CTL_TIME_OUT_ERROR | DP_AUX_CH_CTL_RECEIVE_ERROR |0xd28500c8, 0},
{R, 2, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY |0x801500c8, 100},
{R, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY |0x800500c8, 100},
{R, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_DONE |0x401500c8, 0},
{W, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_DONE | DP_AUX_CH_CTL_TIME_OUT_ERROR | DP_AUX_CH_CTL_RECEIVE_ERROR |0x521500c8, 0},
{R, 1, "", DPA_AUX_CH_DATA1, 0x00000000, 400},
{R, 2, "", PCH_PP_STATUS, 0x80000008, 0},
{R, 1, "", DPA_AUX_CH_CTL, 0x001500c8, 0},
{W, 1, "", DPA_AUX_CH_DATA1, 0x90020205, 0},
{W, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY | DP_AUX_CH_CTL_DONE | DP_AUX_CH_CTL_TIME_OUT_ERROR | DP_AUX_CH_CTL_RECEIVE_ERROR |0xd24500c8, 0},
{R, 2, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY |0x801500c8, 100},
{R, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY |0x804500c8, 100},
{R, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_DONE |0x407500c8, 0},
{W, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_DONE | DP_AUX_CH_CTL_TIME_OUT_ERROR | DP_AUX_CH_CTL_RECEIVE_ERROR |0x527500c8, 0},
{R, 1, "", DPA_AUX_CH_DATA1, 0x00777781, 0},
{R, 1, "", DPA_AUX_CH_DATA2, 0x02000000, 0},
{W, 1, "", 0x64000, 0x891c4304, 0},
{R, 1, "", 0x64000, 0x891c4304, 0},
{R, 2, "", PCH_PP_STATUS, 0x80000008, 0},
{R, 1, "", DPA_AUX_CH_CTL, 0x007500c8, 0},
{W, 1, "", DPA_AUX_CH_DATA1, 0x80010200, 0},
{W, 1, "", DPA_AUX_CH_DATA2, 0x00000000, 0},
{W, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY | DP_AUX_CH_CTL_DONE | DP_AUX_CH_CTL_TIME_OUT_ERROR | DP_AUX_CH_CTL_RECEIVE_ERROR |0xd25500c8, 0},
{R, 2, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_SEND_BUSY |0x807500c8, 100},
{R, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_DONE |0x401500c8, 0},
{W, 1, "", DPA_AUX_CH_CTL,  DP_AUX_CH_CTL_DONE | DP_AUX_CH_CTL_TIME_OUT_ERROR | DP_AUX_CH_CTL_RECEIVE_ERROR |0x521500c8, 0},
{R, 1, "", DPA_AUX_CH_DATA1, 0x00000000, 0},
{M, 1, "[drm:ironlake_edp_backlight_on], ", 0x0, 0x0, 0},
{R, 1, "", PCH_PP_CONTROL, (PCH_PP_UNLOCK&0xabcd0000)| PANEL_POWER_RESET | PANEL_POWER_ON |0xabcd0003, 0},
{W, 1, "", PCH_PP_CONTROL, (PCH_PP_UNLOCK&0xabcd0000)| EDP_BLC_ENABLE | PANEL_POWER_RESET | PANEL_POWER_ON |0xabcd0007, 0},
{R, 1, "", PCH_PP_CONTROL, (PCH_PP_UNLOCK&0xabcd0000)| EDP_BLC_ENABLE | PANEL_POWER_RESET | PANEL_POWER_ON |0xabcd0007, 0},
{R, 1, "", _PIPEADSL, 0x00000633, 500},
{R, 1, "", _PIPEADSL, 0x00000652, 0},
{R, 1, "", _PIPEASTAT, 0x00000000, 0},
{W, 1, "", _PIPEASTAT,  PIPE_VBLANK_INTERRUPT_STATUS |0x00000002, 0},
{R, 5085, "", _PIPEASTAT, 0x00000000, 0},
{M, 1, "[drm:intel_wait_for_vblank], vblank wait timed out", 0x0, 0x0, 0},
{M, 1, "[drm:intel_dp_mode_fixup], Display port link bw 0a lane count 4clock 270000", 0x0, 0x0, 0},
{M, 1, "[drm:drm_crtc_helper_set_mode], [CRTC:3]", 0x0, 0x0, 0},
{(null), 0, "(null)", 0x0, 0x0, 0},
