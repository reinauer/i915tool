#include <stdio.h>
#include <stdlib.h>
#include <sys/io.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "final/i915_reg.h"

int verbose = 0;

enum {
	vmsg = 1, vio = 2, vspin = 4,
};

char *names[] = {
#include "names.c"
};

int nnames = sizeof(names)/sizeof(names[0]);

char *regname(unsigned long addr)
{
	static char name[128];
	int i;
	int offset;
	unsigned long truncaddr;

	if (addr > nnames){
		sprintf(name, "0x%lx", addr);
		return name;
	}
	if (names[addr])
		return names[addr];
	/* for now we'll take up to 6 bits of offset */
	for(i = 1, truncaddr = addr; i < 0x80; i = (i << 1) | 1){
		offset = addr & i;
		truncaddr = addr & (~i);
		if (names[truncaddr]){
			sprintf(name,"%s+%x", names[truncaddr], offset);
			return name;
		}
	}
	/* oh well ... */
	sprintf(name, "0x%lx", addr);
	return name;
}

#define M 1
#define R 2
#define W 3
#define V 4
#define I 8
char *opnames[] = {
	[M] "M",
	[R] "R",
	[W] "W",
	[V] "V",
	[I] "I",
};

struct iodef {
	unsigned char op;
	unsigned int count;
	char *msg;
	unsigned long addr;
	unsigned long data;
	unsigned long udelay;
} iodefs[] = {
{V,0,},
//{V, 7, },
{W, 1, "", PCH_GMBUS0, 0x00000000, },
{R, 1, "", PP_ON_DELAYS, 0x00000000, },
{R, 1, "", PP_OFF_DELAYS, 0x00000000, },
{W, 1, "", PP_ON_DELAYS, 0x019007d0, },
{W, 1, "", PP_OFF_DELAYS, 0x015e07d0, },
{M, 1, "[drm:intel_detect_pch], Found PatherPoint PCH"},
{M, 1, "[drm:i915_load_modeset_init], failed to find VBIOS tables"},
{R, 50, "", 0x130040, 0x00000001,  10},
{W, 1, "", 0xa188, 0x00010001, },
{R, 1, "", 0xa188, 0x00010001, },
{R, 1, "", 0x130040, 0x00000001, },
{R, 1, "", 0x13805c, 0x40000000, },
{R, 1, "", 0xa180, 0x84100020, },
{W, 1, "", 0xa188, 0x00010000, },
{R, 1, "", 0x120000, 0x00000000, },
{M, 1, "[drm:intel_init_display], Using MT version of forcewake"},
{R, 1, "", 0x145d10, 0x2010040c, },
{M, 1, "[drm:intel_modeset_init], 3 display pipes available."},
{R, 1, "", _PIPEACONF, 0x00000000, },
{W, 1, "", _PIPEACONF, 0x00000000, },
{R, 1, "", _PIPEBCONF, 0x00000000, },
{W, 1, "", _PIPEBCONF, 0x00000000, },
{R, 1, "", 0x72008, 0x00000000, },
{W, 1, "", 0x72008, 0x00000000, },
{R, 1, "", _PIPEACONF, 0x00000000, },
{W, 1, "", _PIPEACONF, 0x00000000, },
{R, 1, "", _PIPEBCONF, 0x00000000, },
{W, 1, "", _PIPEBCONF, 0x00000000, },
{R, 1, "", 0x72008, 0x00000000, },
{W, 1, "", 0x72008, 0x00000000, },
{R, 1, "", _PIPEACONF, 0x00000000, },
{W, 1, "", _PIPEACONF, 0x00000000, },
{R, 1, "", _PIPEBCONF, 0x00000000, },
{W, 1, "", _PIPEBCONF, 0x00000000, },
{R, 1, "", 0x72008, 0x00000000, },
{W, 1, "", 0x72008, 0x00000000,  300},
{W, 1, "", CPU_VGACNTRL, 0x80000000, },
{R, 1, "", CPU_VGACNTRL, 0x80000000, },
{R, 1, "", 0x64000, 0x0000001c, },
{R, 1, "", PCH_PP_ON_DELAYS, 0x47d007d0, },
{R, 1, "", PCH_PP_OFF_DELAYS, 0x01f407d0, },
{R, 1, "", PCH_PP_DIVISOR, 0x00186906, },
{M, 1, "[drm:intel_dp_init], cur t1_t3 2000 t8 2000 t9 2000 t10 500"
    "t11_t12 6000"},
{M, 1, "[drm:intel_dp_init], vbt t1_t3 0 t8 0 t9 0 t10 0 t11_t12 0"},
{M, 1, "[drm:intel_dp_init], panel power up delay 200,"
    "power down delay 50, power cycle delay 600"},
{M, 1, "[drm:intel_dp_init], backlight on delay 200, off delay 200"},
{M, 1, "[drm:ironlake_edp_panel_vdd_on], Turn eDP VDD on"},
{R, 1, "", PCH_PP_CONTROL, 0x00000000, },
{R, 1, "", PCH_PP_STATUS, 0x00000000, },
{M, 1, "[drm:ironlake_wait_panel_power_cycle], Wait for panel power cycle"},
{M, 1, "[drm:ironlake_wait_panel_status], R PCH_PP_CONTROL:00000000"},
{R, 2, "", PCH_PP_STATUS, 0x00000000, },
{R, 1, "", PCH_PP_CONTROL, 0x00000000, },
{W, 1, "", PCH_PP_CONTROL, 0xabcd0008, },
{R, 1, "", PCH_PP_CONTROL, 0xabcd0008, },
{M, 1, "[drm:ironlake_edp_panel_vdd_on], R PCH_PP_CONTROL:abcd0008"},
{R, 2, "", PCH_PP_STATUS, 0x00000000, },
{M, 1, "[drm:ironlake_edp_panel_vdd_on], eDP was not running"},
{R, 1, "", PCH_PP_STATUS, 0x00000000, },
{R, 1, "", PCH_PP_CONTROL, 0xabcd0008, },
{R, 1, "", PCH_PP_STATUS, 0x00000000, },
{R, 1, "", PCH_PP_CONTROL, 0xabcd0008, },
{R, 1, "", DPA_AUX_CH_CTL, 0x014300c8, },
{W, 1, "", DPA_AUX_CH_DATA1, 0x9000000e, },
{W, 1, "", DPA_AUX_CH_CTL, 0xd24500c8, },
{R, 2, "", DPA_AUX_CH_CTL, 0x814500c8,  100},
{R, 1, "", DPA_AUX_CH_CTL, 0x807500c8,  100},
{R, 1, "", DPA_AUX_CH_CTL, 0x810500c8,  100},
{R, 1, "", DPA_AUX_CH_CTL, 0x410500c8, },
{W, 1, "", DPA_AUX_CH_CTL, 0x530500c8, },
{R, 1, "", DPA_AUX_CH_DATA1, 0x00110a84, },
{R, 1, "", DPA_AUX_CH_DATA2, 0x41000001, },
{R, 1, "", DPA_AUX_CH_DATA3, 0xc0020000, },
{R, 1, "", DPA_AUX_CH_DATA4, 0x001f0000, },
{M, 1, "[drm:intel_dp_i2c_init], i2c_init DPDDC-A"},
{R, 1, "", PCH_PP_STATUS, 0x00000000, },
{R, 1, "", PCH_PP_CONTROL, 0xabcd0008, },
{R, 1, "", PCH_PP_STATUS, 0x00000000, },
{R, 1, "", PCH_PP_CONTROL, 0xabcd0008, },
{R, 1, "", DPA_AUX_CH_CTL, 0x010500c8, },
{W, 1, "", DPA_AUX_CH_DATA1, 0x40000000, },
{W, 1, "", DPA_AUX_CH_CTL, 0xd23500c8, },
{R, 2, "", DPA_AUX_CH_CTL, 0x810500c8,  100},
{R, 1, "", DPA_AUX_CH_CTL, 0x401500c8, },
{W, 1, "", DPA_AUX_CH_CTL, 0x521500c8, },
{R, 1, "", DPA_AUX_CH_DATA1, 0x00000000, },
{R, 1, "", PCH_PP_STATUS, 0x00000000, },
{R, 1, "", PCH_PP_CONTROL, 0xabcd0008, },
{R, 1, "", PCH_PP_STATUS, 0x00000000, },
{R, 1, "", PCH_PP_CONTROL, 0xabcd0008, },
{R, 1, "", DPA_AUX_CH_CTL, 0x001500c8, },
{W, 1, "", DPA_AUX_CH_DATA1, 0x00000000, },
{W, 1, "", DPA_AUX_CH_CTL, 0xd23500c8, },
{R, 2, "", DPA_AUX_CH_CTL, 0x801500c8,  100},
{R, 1, "", DPA_AUX_CH_CTL, 0x401500c8, },
{W, 1, "", DPA_AUX_CH_CTL, 0x521500c8, },
{R, 1, "", DPA_AUX_CH_DATA1, 0x00000000, },
{M, 1, "[drm:ironlake_edp_panel_vdd_off], Turn eDP VDD off 1"},
{R, 1, "", BLC_PWM_CPU_CTL, 0x000010ce, },
{M, 1, "[drm:intel_panel_get_backlight], get backlight PWM = 4302"},
{M, 1, "[drm:intel_dp_aux_ch], dp_aux_ch timeout status 0x5145003f"},
{M, 1, "[drm:intel_dp_i2c_aux_ch], aux_ch failed -110"},
{M, 1,
"[drm:ironlake_init_pch_refclk], has_panel 1 has_lvds 0 has_pch_edp 0"
    "has_cpu_edp 1 has_ck505 0"},
{R, 1, "", PCH_DREF_CONTROL, 0x00000000, },
{M, 1, "[drm:ironlake_init_pch_refclk], Using SSC on panel"},
{W, 1, "", PCH_DREF_CONTROL, 0x00001402, },
{R, 1, "", PCH_DREF_CONTROL, 0x00001402,  200},
{M, 1, "[drm:ironlake_init_pch_refclk], Using SSC on eDP"},
{W, 1, "", PCH_DREF_CONTROL, 0x00005402, },
{R, 1, "", PCH_DREF_CONTROL, 0x00005402,  200},
{W, 1, "", ILK_DSPCLK_GATE, 0x10000000, },
{W, 1, "", WM3_LP_ILK, 0x00000000, },
{W, 1, "", WM2_LP_ILK, 0x00000000, },
{W, 1, "", WM1_LP_ILK, 0x00000000, },
{W, 1, "", 0x9404, 0x00002000, },
{W, 1, "", ILK_DSPCLK_GATE, 0x10000000, },
{W, 1, "", IVB_CHICKEN3, 0x00000024, },
{W, 1, "", 0x7010, 0x04000400, },
{W, 1, "", 0xb01c, 0x3c4fff8c, },
{W, 1, "", 0xb030, 0x20000000, },
{R, 1, "", 0x9030, 0x00000000, },
{W, 1, "", 0x9030, 0x00000800, },
{R, 1, "", _DSPACNTR, 0x00000000, },
{W, 1, "", _DSPACNTR, 0x00004000, },
{R, 1, "", _DSPAADDR, 0x00000000, },
{W, 1, "", _DSPAADDR, 0x00000000, },
{R, 1, "", _DSPASIZE+0xc, 0x00000000, },
{W, 1, "", _DSPASIZE+0xc, 0x00000000, },
{R, 1, "", _DSPBCNTR, 0x00000000, },
{W, 1, "", _DSPBCNTR, 0x00004000, },
{R, 1, "", _DSPBADDR, 0x00000000, },
{W, 1, "", _DSPBADDR, 0x00000000, },
{R, 1, "", _DSPBSURF, 0x00000000, },
{W, 1, "", _DSPBSURF, 0x00000000, },
{R, 1, "", _DVSACNTR, 0x00000000, },
{W, 1, "", _DVSACNTR, 0x00004000, },
{R, 1, "", _DVSALINOFF, 0x00000000, },
{W, 1, "", _DVSALINOFF, 0x00000000, },
{R, 1, "", _DVSASURF, 0x00000000, },
{W, 1, "", _DVSASURF, 0x00000000, },
{W, 1, "", SOUTH_DSPCLK_GATE_D, 0x20000000, },
{R, 1, "", SOUTH_CHICKEN2, 0x00000000, },
{W, 1, "", SOUTH_CHICKEN2, 0x00000001, },
{W, 1, "", _TRANSA_CHICKEN2, 0x80000000, },
{W, 1, "", _TRANSB_CHICKEN2, 0x80000000, },
/* to here, it works ok  with v0 */
//{V, 7,},
{M, 1, "[drm:drm_edid_to_eld], ELD:no CEA Extension found"},
{M, 1, "[drm:drm_helper_probe_single_connector_modes], [CONNECTOR:6:eDP-1]"
    "probed modes :"},
{M, 1, "[drm:drm_mode_debug_printmodeline],"
"Modeline 0:\"2560x1700\" 60 285250 2560 2608 2640 2720 1700 1703 1713 1749"
"0x48 0xa"},
{M, 1, "[drm:drm_setup_crtcs], "},
{M, 1, "[drm:drm_enable_connectors], connector 6 enabled? yes"},
{M, 1, "[drm:drm_setup_crtcs], picking CRTCs for 8192x8192 config"},
{M, 1, "[drm:drm_setup_crtcs], desired mode 2560x1700 set on crtc 3"},
{M, 1, "[drm:drm_helper_probe_single_connector_modes], [CONNECTOR:6:eDP-1]"},
{M, 1, "[drm:intel_dp_detect], DPCD:110a8441000001c0"},
{M, 1, "[drm:ironlake_edp_panel_vdd_on], Turn eDP VDD on"},
//{V, 7,},
{M, 1, "[drm:intel_dp_detect], DPCD:110a8441000001c0"},
{M, 1, "[drm:drm_enable_connectors], connector 6 enabled? yes"},
{M, 1, "[drm:intel_get_load_detect_pipe], [CONNECTOR:6:eDP-1],"
"[ENCODER:7:TMDS-7]"},
{M, 1, "[drm:intel_dp_mode_fixup], Display port link bw 0a lane count 4"
"clock 270000"},
{M, 1, "[drm:drm_crtc_helper_set_mode], [CRTC:3]"},
{R, 1, "", PCH_PP_STATUS, 0x00000000, },
{R, 1, "", PCH_PP_CONTROL, 0xabcd0008, },
{R, 1, "", PCH_PP_STATUS, 0x00000000, },
{R, 1, "", PCH_PP_CONTROL, 0xabcd0008, },
{R, 1, "", DPA_AUX_CH_CTL, 0x001500c8, },
{W, 1, "", DPA_AUX_CH_DATA1, 0x80060000, },
{W, 1, "", DPA_AUX_CH_DATA2, 0x01000000, },
{W, 1, "", DPA_AUX_CH_CTL, 0xd25500c8, },
{R, 2, "", DPA_AUX_CH_CTL, 0x801500c8,  100},
{R, 1, "", DPA_AUX_CH_CTL, 0x401500c8, },
{W, 1, "", DPA_AUX_CH_CTL, 0x521500c8, },
{R, 1, "", DPA_AUX_CH_DATA1, 0x00000000, },
{R, 1, "", 0x64000, 0x0000001c, },
{M, 1, "[drm:ironlake_edp_panel_vdd_off], Turn eDP VDD off 1"},
#if 0
/* I hope we never try to use this. It is left here as a documentation thing. */
/* SCALING HACK */
/* these were determined by reading registers.
 * They should stretch the display.
 * They don't.
 * From u-boot? After vbios?
 */
{V, 7, },
{M, 1, "Turning on panel fitter (must be done before power cycle)"},
{W, 1, "Enabled,PIPEA,Hardcoded edge enhance", _PFA_CTL_1,    0x80800000, },
/* status: can't ever set vscale.
 * Which may be why we get no display at all if we try. */
{W, 1, "stretch", _PFA_VSCALE,   /*0x00004000*/0xffffffff, },
{W, 1, "stretch", _PFA_HSCALE,   /*0x00004000*/0xffffffff, },
{W, 1, "2560x1700", _PFA_WIN_SZ,   0x0a0006a4, },
//{W, 1, "2560x1700", _PFA_WIN_SZ,   0x05000352, },
{W, 1, "@[0,0]", _PFA_WIN_POS,  0x00000000, },
{R, 1, "Vstretch", _PFA_VSCALE,   0x00004000, },
{R, 1, "Hstretch", _PFA_HSCALE,   0x00004000, },
{R, 1, "2560x1700", _PFA_WIN_SZ,   0x0a0006a4, },
{R, 1, "@[0,0]", _PFA_WIN_POS,  0x00000000, },
{R, 1, "Enabled,PIPEA,Hardcoded edge enhance", _PFA_CTL_1,    0x80800000, },
{V,0,},
/* END SCALING HACK */
#endif
{R, 2, "", PCH_DP_D, 0x00000004, },
{R, 1, "", _PIPEACONF, 0x00000000, },
{W, 1, "", _PIPEACONF, 0x00000040, },
{R, 1, "", _PIPEACONF, 0x00000040, },
{M, 1, "[drm:ironlake_crtc_mode_set], Mode for pipe 0:"},
{M, 1, "[drm:drm_mode_debug_printmodeline],"
"Modeline 0:\"2560x1700\" 60 285250 2560 2608 2640 2720 1700 1703 1713 1749"
" 0x48 0xa"},
{W, 1, "", _TRANSA_DATA_M1, 0x00000000, },
{W, 1, "", _TRANSA_DATA_N1, 0x00000000, },
{W, 1, "", _TRANSA_DP_LINK_M1, 0x00000000, },
{W, 1, "", _TRANSA_DP_LINK_N1, 0x00000000, },
{W, 1, "", _PCH_FPA1, 0x00020e08, },
{W, 1, "", _VSYNCSHIFT_A, 0x00000000, },
{W, 1, "", _HTOTAL_A, 0x0a9f09ff, },
{W, 1, "", _HBLANK_A, 0x0a9f09ff, },
{W, 1, "", _HSYNC_A, 0x0a4f0a2f, },
{W, 1, "", _VTOTAL_A, 0x06d406a3, },
{W, 1, "", _VBLANK_A, 0x06d406a3, },
{W, 1, "", _VSYNC_A, 0x06b006a6, },
{W, 1, "", _PIPEASRC, 0x09ff06a3, },
{W, 1, "", _PIPEA_DATA_M1, 0x7e4e58a4, },
{W, 1, "", _PIPEA_DATA_N1, 0x0083d600, },
{W, 1, "", _PIPEA_LINK_M1, 0x00045a42, },
{W, 1, "", _PIPEA_LINK_N1, 0x00041eb0, },
{M, 1, "[drm:ironlake_set_pll_edp], eDP PLL enable for clock 270000"},
{R, 1, "", 0x64000, 0x0000001c, },
{W, 1, "", 0x64000, 0x0000001c, },
{R, 1, "", 0x64000, 0x0000001c,  500},
{W, 1, "", _PIPEACONF, 0x00000050, },
{R, 1, "", _PIPEACONF, 0x00000050, },
{R, 1, "", _PIPEASTAT, 0x00000000, },
{W, 1, "", _PIPEASTAT, 0x00000002, },
{R, 4562, "", _PIPEASTAT, 0x00000000, },
{M, 1, "[drm:intel_wait_for_vblank], vblank wait timed out"},
{W, 1, "", _DSPACNTR, 0x40000000, },
{R, 2, "", _DSPACNTR, 0x40000000, },
{W, 1, "", _DSPACNTR, 0x58004000, },
{M, 1, "[drm:ironlake_update_plane], Writing base 00000000 00000000 0 0 10240"},
{W, 1, "", _DSPASTRIDE, 0x00002800, },
{W, 1, "", _DSPASIZE+0xc, 0x00000000, },
{W, 1, "", _DSPACNTR+0x24, 0x00000000, },
{W, 1, "", _DSPAADDR, 0x00000000, },
{R, 1, "", _DSPACNTR, 0x58004000, },
{R, 1, "", 0x145d10, 0x2010040c, },
{R, 1, "", WM0_PIPEA_ILK, 0x00783818, },
{W, 1, "", WM0_PIPEA_ILK, 0x00183806, },
{M, 1, "[drm:sandybridge_update_wm], FIFO watermarks For pipe A - plane 24,"
"cursor:6"},
{W, 1, "", WM3_LP_ILK, 0x00000000, },
{W, 1, "", WM2_LP_ILK, 0x00000000, },
{W, 1, "", WM1_LP_ILK, 0x00000000, },
{R, 1, "", 0x145d10, 0x2010040c, },
{M, 1, "[drm:ironlake_check_srwm], watermark 1:display plane 38, fbc lines 3,"
"cursor 6"},
{R, 1, "", 0x145d10, 0x2010040c, },
{W, 1, "", WM1_LP_ILK, 0x84302606, },
{R, 1, "", 0x145d10, 0x2010040c, },
{M, 1,"[drm:ironlake_check_srwm], watermark 2:display plane 145, fbc lines 3,"
    "cursor 6"},
{R, 1, "", 0x145d10, 0x2010040c, },
{W, 1, "", WM2_LP_ILK, 0x90309106, },
{R, 1, "", 0x145d10, 0x2010040c, },
{M, 1, "[drm:ironlake_check_srwm], watermark 3:display plane 288, fbc lines 4,"
    "cursor 10"},
{R, 1, "", 0x145d10, 0x2010040c, },
{W, 1, "", WM3_LP_ILK, 0xa041200a, },
{M, 1, "[drm:drm_crtc_helper_set_mode], [ENCODER:7:TMDS-7]"
    "set [MODE:0:2560x1700]"},
{M, 1, "[drm:ironlake_edp_pll_on], "},
{R, 1, "", 0x64000, 0x0000001c, },
{W, 1, "", 0x64000, 0x0000401c, },
{R, 1, "", 0x64000, 0x0000401c,  200},
{R, 1, "", 0x64000, 0x0000401c, },
{R, 1, "", 0x145d10, 0x2010040c, },
{R, 1, "", WM0_PIPEA_ILK, 0x00183806, },
{W, 1, "", WM0_PIPEA_ILK, 0x00183806, },
{M, 1, "[drm:sandybridge_update_wm], FIFO watermarks For pipe A - plane 24,"
"cursor:6"},
{W, 1, "", WM3_LP_ILK, 0x00000000, },
{W, 1, "", WM2_LP_ILK, 0x00000000, },
{W, 1, "", WM1_LP_ILK, 0x00000000, },
{R, 1, "", 0x145d10, 0x2010040c, },
{M, 1, "[drm:ironlake_check_srwm], watermark 1:display plane 38, fbc lines 3,"
    "cursor 6"},
{R, 1, "", 0x145d10, 0x2010040c, },
{W, 1, "", WM1_LP_ILK, 0x84302606, },
{R, 1, "", 0x145d10, 0x2010040c, },
{M, 1, "[drm:ironlake_check_srwm], watermark 2:display plane 145, fbc lines 3,"
    "cursor 6"},
{R, 1, "", 0x145d10, 0x2010040c, },
{W, 1, "", WM2_LP_ILK, 0x90309106, },
{R, 1, "", 0x145d10, 0x2010040c, },
{M, 1, "[drm:ironlake_check_srwm], watermark 3:display plane 288, fbc lines 4,"
    "cursor 10"},
{R, 1, "", 0x145d10, 0x2010040c, },
{W, 1, "", WM3_LP_ILK, 0xa041200a, },
{R, 1, "", _FDI_TXA_CTL, 0x00040000, },
{W, 1, "", _FDI_TXA_CTL, 0x00040000, },
{R, 1, "", _FDI_TXA_CTL, 0x00040000, },
{R, 1, "", _FDI_RXA_CTL, 0x00000040, },
{R, 1, "", _PIPEACONF, 0x00000050, },
{W, 1, "", _FDI_RXA_CTL, 0x00020040, },
{R, 1, "", _FDI_RXA_CTL, 0x00020040,  100},
{R, 1, "", SOUTH_CHICKEN1, 0x00000000, },
{W, 2, "", SOUTH_CHICKEN1, 0x00000000, },
{R, 1, "", SOUTH_CHICKEN1, 0x00000000, },
{R, 1, "", _FDI_TXA_CTL, 0x00040000, },
{W, 1, "", _FDI_TXA_CTL, 0x00040000, },
{R, 1, "", _FDI_RXA_CTL, 0x00020040, },
{R, 1, "", _PIPEACONF, 0x00000050, },
{W, 1, "", _FDI_RXA_CTL, 0x00020040, },
{R, 1, "", _FDI_RXA_CTL, 0x00020040,  100},
{W, 1, "", _LGC_PALETTE_A, 0x00000000, },
{W, 1, "", _LGC_PALETTE_A+0x4, 0x00010101, },
{W, 1, "", _LGC_PALETTE_A+0x8, 0x00020202, },
{W, 1, "", _LGC_PALETTE_A+0xc, 0x00030303, },
{W, 1, "", _LGC_PALETTE_A+0x10, 0x00040404, },
{W, 1, "", _LGC_PALETTE_A+0x14, 0x00050505, },
{W, 1, "", _LGC_PALETTE_A+0x18, 0x00060606, },
{W, 1, "", _LGC_PALETTE_A+0x1c, 0x00070707, },
{W, 1, "", _LGC_PALETTE_A+0x20, 0x00080808, },
{W, 1, "", _LGC_PALETTE_A+0x24, 0x00090909, },
{W, 1, "", _LGC_PALETTE_A+0x28, 0x000a0a0a, },
{W, 1, "", _LGC_PALETTE_A+0x2c, 0x000b0b0b, },
{W, 1, "", _LGC_PALETTE_A+0x30, 0x000c0c0c, },
{W, 1, "", _LGC_PALETTE_A+0x34, 0x000d0d0d, },
{W, 1, "", _LGC_PALETTE_A+0x38, 0x000e0e0e, },
{W, 1, "", _LGC_PALETTE_A+0x3c, 0x000f0f0f, },
{W, 1, "", _LGC_PALETTE_A+0x40, 0x00101010, },
{W, 1, "", _LGC_PALETTE_A+0x44, 0x00111111, },
{W, 1, "", _LGC_PALETTE_A+0x48, 0x00121212, },
{W, 1, "", _LGC_PALETTE_A+0x4c, 0x00131313, },
{W, 1, "", _LGC_PALETTE_A+0x50, 0x00141414, },
{W, 1, "", _LGC_PALETTE_A+0x54, 0x00151515, },
{W, 1, "", _LGC_PALETTE_A+0x58, 0x00161616, },
{W, 1, "", _LGC_PALETTE_A+0x5c, 0x00171717, },
{W, 1, "", _LGC_PALETTE_A+0x60, 0x00181818, },
{W, 1, "", _LGC_PALETTE_A+0x64, 0x00191919, },
{W, 1, "", _LGC_PALETTE_A+0x68, 0x001a1a1a, },
{W, 1, "", _LGC_PALETTE_A+0x6c, 0x001b1b1b, },
{W, 1, "", _LGC_PALETTE_A+0x70, 0x001c1c1c, },
{W, 1, "", _LGC_PALETTE_A+0x74, 0x001d1d1d, },
{W, 1, "", _LGC_PALETTE_A+0x78, 0x001e1e1e, },
{W, 1, "", _LGC_PALETTE_A+0x7c, 0x001f1f1f, },
{W, 1, "", 0x4a080, 0x00202020, },
{W, 1, "", 0x4a084, 0x00212121, },
{W, 1, "", 0x4a088, 0x00222222, },
{W, 1, "", 0x4a08c, 0x00232323, },
{W, 1, "", 0x4a090, 0x00242424, },
{W, 1, "", 0x4a094, 0x00252525, },
{W, 1, "", 0x4a098, 0x00262626, },
{W, 1, "", 0x4a09c, 0x00272727, },
{W, 1, "", 0x4a0a0, 0x00282828, },
{W, 1, "", 0x4a0a4, 0x00292929, },
{W, 1, "", 0x4a0a8, 0x002a2a2a, },
{W, 1, "", 0x4a0ac, 0x002b2b2b, },
{W, 1, "", 0x4a0b0, 0x002c2c2c, },
{W, 1, "", 0x4a0b4, 0x002d2d2d, },
{W, 1, "", 0x4a0b8, 0x002e2e2e, },
{W, 1, "", 0x4a0bc, 0x002f2f2f, },
{W, 1, "", 0x4a0c0, 0x00303030, },
{W, 1, "", 0x4a0c4, 0x00313131, },
{W, 1, "", 0x4a0c8, 0x00323232, },
{W, 1, "", 0x4a0cc, 0x00333333, },
{W, 1, "", 0x4a0d0, 0x00343434, },
{W, 1, "", 0x4a0d4, 0x00353535, },
{W, 1, "", 0x4a0d8, 0x00363636, },
{W, 1, "", 0x4a0dc, 0x00373737, },
{W, 1, "", 0x4a0e0, 0x00383838, },
{W, 1, "", 0x4a0e4, 0x00393939, },
{W, 1, "", 0x4a0e8, 0x003a3a3a, },
{W, 1, "", 0x4a0ec, 0x003b3b3b, },
{W, 1, "", 0x4a0f0, 0x003c3c3c, },
{W, 1, "", 0x4a0f4, 0x003d3d3d, },
{W, 1, "", 0x4a0f8, 0x003e3e3e, },
{W, 1, "", 0x4a0fc, 0x003f3f3f, },
{W, 1, "", 0x4a100, 0x00404040, },
{W, 1, "", 0x4a104, 0x00414141, },
{W, 1, "", 0x4a108, 0x00424242, },
{W, 1, "", 0x4a10c, 0x00434343, },
{W, 1, "", 0x4a110, 0x00444444, },
{W, 1, "", 0x4a114, 0x00454545, },
{W, 1, "", 0x4a118, 0x00464646, },
{W, 1, "", 0x4a11c, 0x00474747, },
{W, 1, "", 0x4a120, 0x00484848, },
{W, 1, "", 0x4a124, 0x00494949, },
{W, 1, "", 0x4a128, 0x004a4a4a, },
{W, 1, "", 0x4a12c, 0x004b4b4b, },
{W, 1, "", 0x4a130, 0x004c4c4c, },
{W, 1, "", 0x4a134, 0x004d4d4d, },
{W, 1, "", 0x4a138, 0x004e4e4e, },
{W, 1, "", 0x4a13c, 0x004f4f4f, },
{W, 1, "", 0x4a140, 0x00505050, },
{W, 1, "", 0x4a144, 0x00515151, },
{W, 1, "", 0x4a148, 0x00525252, },
{W, 1, "", 0x4a14c, 0x00535353, },
{W, 1, "", 0x4a150, 0x00545454, },
{W, 1, "", 0x4a154, 0x00555555, },
{W, 1, "", 0x4a158, 0x00565656, },
{W, 1, "", 0x4a15c, 0x00575757, },
{W, 1, "", 0x4a160, 0x00585858, },
{W, 1, "", 0x4a164, 0x00595959, },
{W, 1, "", 0x4a168, 0x005a5a5a, },
{W, 1, "", 0x4a16c, 0x005b5b5b, },
{W, 1, "", 0x4a170, 0x005c5c5c, },
{W, 1, "", 0x4a174, 0x005d5d5d, },
{W, 1, "", 0x4a178, 0x005e5e5e, },
{W, 1, "", 0x4a17c, 0x005f5f5f, },
{W, 1, "", 0x4a180, 0x00606060, },
{W, 1, "", 0x4a184, 0x00616161, },
{W, 1, "", 0x4a188, 0x00626262, },
{W, 1, "", 0x4a18c, 0x00636363, },
{W, 1, "", 0x4a190, 0x00646464, },
{W, 1, "", 0x4a194, 0x00656565, },
{W, 1, "", 0x4a198, 0x00666666, },
{W, 1, "", 0x4a19c, 0x00676767, },
{W, 1, "", 0x4a1a0, 0x00686868, },
{W, 1, "", 0x4a1a4, 0x00696969, },
{W, 1, "", 0x4a1a8, 0x006a6a6a, },
{W, 1, "", 0x4a1ac, 0x006b6b6b, },
{W, 1, "", 0x4a1b0, 0x006c6c6c, },
{W, 1, "", 0x4a1b4, 0x006d6d6d, },
{W, 1, "", 0x4a1b8, 0x006e6e6e, },
{W, 1, "", 0x4a1bc, 0x006f6f6f, },
{W, 1, "", 0x4a1c0, 0x00707070, },
{W, 1, "", 0x4a1c4, 0x00717171, },
{W, 1, "", 0x4a1c8, 0x00727272, },
{W, 1, "", 0x4a1cc, 0x00737373, },
{W, 1, "", 0x4a1d0, 0x00747474, },
{W, 1, "", 0x4a1d4, 0x00757575, },
{W, 1, "", 0x4a1d8, 0x00767676, },
{W, 1, "", 0x4a1dc, 0x00777777, },
{W, 1, "", 0x4a1e0, 0x00787878, },
{W, 1, "", 0x4a1e4, 0x00797979, },
{W, 1, "", 0x4a1e8, 0x007a7a7a, },
{W, 1, "", 0x4a1ec, 0x007b7b7b, },
{W, 1, "", 0x4a1f0, 0x007c7c7c, },
{W, 1, "", 0x4a1f4, 0x007d7d7d, },
{W, 1, "", 0x4a1f8, 0x007e7e7e, },
{W, 1, "", 0x4a1fc, 0x007f7f7f, },
{W, 1, "", 0x4a200, 0x00808080, },
{W, 1, "", 0x4a204, 0x00818181, },
{W, 1, "", 0x4a208, 0x00828282, },
{W, 1, "", 0x4a20c, 0x00838383, },
{W, 1, "", 0x4a210, 0x00848484, },
{W, 1, "", 0x4a214, 0x00858585, },
{W, 1, "", 0x4a218, 0x00868686, },
{W, 1, "", 0x4a21c, 0x00878787, },
{W, 1, "", 0x4a220, 0x00888888, },
{W, 1, "", 0x4a224, 0x00898989, },
{W, 1, "", 0x4a228, 0x008a8a8a, },
{W, 1, "", 0x4a22c, 0x008b8b8b, },
{W, 1, "", 0x4a230, 0x008c8c8c, },
{W, 1, "", 0x4a234, 0x008d8d8d, },
{W, 1, "", 0x4a238, 0x008e8e8e, },
{W, 1, "", 0x4a23c, 0x008f8f8f, },
{W, 1, "", 0x4a240, 0x00909090, },
{W, 1, "", 0x4a244, 0x00919191, },
{W, 1, "", 0x4a248, 0x00929292, },
{W, 1, "", 0x4a24c, 0x00939393, },
{W, 1, "", 0x4a250, 0x00949494, },
{W, 1, "", 0x4a254, 0x00959595, },
{W, 1, "", 0x4a258, 0x00969696, },
{W, 1, "", 0x4a25c, 0x00979797, },
{W, 1, "", 0x4a260, 0x00989898, },
{W, 1, "", 0x4a264, 0x00999999, },
{W, 1, "", 0x4a268, 0x009a9a9a, },
{W, 1, "", 0x4a26c, 0x009b9b9b, },
{W, 1, "", 0x4a270, 0x009c9c9c, },
{W, 1, "", 0x4a274, 0x009d9d9d, },
{W, 1, "", 0x4a278, 0x009e9e9e, },
{W, 1, "", 0x4a27c, 0x009f9f9f, },
{W, 1, "", 0x4a280, 0x00a0a0a0, },
{W, 1, "", 0x4a284, 0x00a1a1a1, },
{W, 1, "", 0x4a288, 0x00a2a2a2, },
{W, 1, "", 0x4a28c, 0x00a3a3a3, },
{W, 1, "", 0x4a290, 0x00a4a4a4, },
{W, 1, "", 0x4a294, 0x00a5a5a5, },
{W, 1, "", 0x4a298, 0x00a6a6a6, },
{W, 1, "", 0x4a29c, 0x00a7a7a7, },
{W, 1, "", 0x4a2a0, 0x00a8a8a8, },
{W, 1, "", 0x4a2a4, 0x00a9a9a9, },
{W, 1, "", 0x4a2a8, 0x00aaaaaa, },
{W, 1, "", 0x4a2ac, 0x00ababab, },
{W, 1, "", 0x4a2b0, 0x00acacac, },
{W, 1, "", 0x4a2b4, 0x00adadad, },
{W, 1, "", 0x4a2b8, 0x00aeaeae, },
{W, 1, "", 0x4a2bc, 0x00afafaf, },
{W, 1, "", 0x4a2c0, 0x00b0b0b0, },
{W, 1, "", 0x4a2c4, 0x00b1b1b1, },
{W, 1, "", 0x4a2c8, 0x00b2b2b2, },
{W, 1, "", 0x4a2cc, 0x00b3b3b3, },
{W, 1, "", 0x4a2d0, 0x00b4b4b4, },
{W, 1, "", 0x4a2d4, 0x00b5b5b5, },
{W, 1, "", 0x4a2d8, 0x00b6b6b6, },
{W, 1, "", 0x4a2dc, 0x00b7b7b7, },
{W, 1, "", 0x4a2e0, 0x00b8b8b8, },
{W, 1, "", 0x4a2e4, 0x00b9b9b9, },
{W, 1, "", 0x4a2e8, 0x00bababa, },
{W, 1, "", 0x4a2ec, 0x00bbbbbb, },
{W, 1, "", 0x4a2f0, 0x00bcbcbc, },
{W, 1, "", 0x4a2f4, 0x00bdbdbd, },
{W, 1, "", 0x4a2f8, 0x00bebebe, },
{W, 1, "", 0x4a2fc, 0x00bfbfbf, },
{W, 1, "", 0x4a300, 0x00c0c0c0, },
{W, 1, "", 0x4a304, 0x00c1c1c1, },
{W, 1, "", 0x4a308, 0x00c2c2c2, },
{W, 1, "", 0x4a30c, 0x00c3c3c3, },
{W, 1, "", 0x4a310, 0x00c4c4c4, },
{W, 1, "", 0x4a314, 0x00c5c5c5, },
{W, 1, "", 0x4a318, 0x00c6c6c6, },
{W, 1, "", 0x4a31c, 0x00c7c7c7, },
{W, 1, "", 0x4a320, 0x00c8c8c8, },
{W, 1, "", 0x4a324, 0x00c9c9c9, },
{W, 1, "", 0x4a328, 0x00cacaca, },
{W, 1, "", 0x4a32c, 0x00cbcbcb, },
{W, 1, "", 0x4a330, 0x00cccccc, },
{W, 1, "", 0x4a334, 0x00cdcdcd, },
{W, 1, "", 0x4a338, 0x00cecece, },
{W, 1, "", 0x4a33c, 0x00cfcfcf, },
{W, 1, "", 0x4a340, 0x00d0d0d0, },
{W, 1, "", 0x4a344, 0x00d1d1d1, },
{W, 1, "", 0x4a348, 0x00d2d2d2, },
{W, 1, "", 0x4a34c, 0x00d3d3d3, },
{W, 1, "", 0x4a350, 0x00d4d4d4, },
{W, 1, "", 0x4a354, 0x00d5d5d5, },
{W, 1, "", 0x4a358, 0x00d6d6d6, },
{W, 1, "", 0x4a35c, 0x00d7d7d7, },
{W, 1, "", 0x4a360, 0x00d8d8d8, },
{W, 1, "", 0x4a364, 0x00d9d9d9, },
{W, 1, "", 0x4a368, 0x00dadada, },
{W, 1, "", 0x4a36c, 0x00dbdbdb, },
{W, 1, "", 0x4a370, 0x00dcdcdc, },
{W, 1, "", 0x4a374, 0x00dddddd, },
{W, 1, "", 0x4a378, 0x00dedede, },
{W, 1, "", 0x4a37c, 0x00dfdfdf, },
{W, 1, "", 0x4a380, 0x00e0e0e0, },
{W, 1, "", 0x4a384, 0x00e1e1e1, },
{W, 1, "", 0x4a388, 0x00e2e2e2, },
{W, 1, "", 0x4a38c, 0x00e3e3e3, },
{W, 1, "", 0x4a390, 0x00e4e4e4, },
{W, 1, "", 0x4a394, 0x00e5e5e5, },
{W, 1, "", 0x4a398, 0x00e6e6e6, },
{W, 1, "", 0x4a39c, 0x00e7e7e7, },
{W, 1, "", 0x4a3a0, 0x00e8e8e8, },
{W, 1, "", 0x4a3a4, 0x00e9e9e9, },
{W, 1, "", 0x4a3a8, 0x00eaeaea, },
{W, 1, "", 0x4a3ac, 0x00ebebeb, },
{W, 1, "", 0x4a3b0, 0x00ececec, },
{W, 1, "", 0x4a3b4, 0x00ededed, },
{W, 1, "", 0x4a3b8, 0x00eeeeee, },
{W, 1, "", 0x4a3bc, 0x00efefef, },
{W, 1, "", 0x4a3c0, 0x00f0f0f0, },
{W, 1, "", 0x4a3c4, 0x00f1f1f1, },
{W, 1, "", 0x4a3c8, 0x00f2f2f2, },
{W, 1, "", 0x4a3cc, 0x00f3f3f3, },
{W, 1, "", 0x4a3d0, 0x00f4f4f4, },
{W, 1, "", 0x4a3d4, 0x00f5f5f5, },
{W, 1, "", 0x4a3d8, 0x00f6f6f6, },
{W, 1, "", 0x4a3dc, 0x00f7f7f7, },
{W, 1, "", 0x4a3e0, 0x00f8f8f8, },
{W, 1, "", 0x4a3e4, 0x00f9f9f9, },
{W, 1, "", 0x4a3e8, 0x00fafafa, },
{W, 1, "", 0x4a3ec, 0x00fbfbfb, },
{W, 1, "", 0x4a3f0, 0x00fcfcfc, },
{W, 1, "", 0x4a3f4, 0x00fdfdfd, },
{W, 1, "", 0x4a3f8, 0x00fefefe, },
{W, 1, "", 0x4a3fc, 0x00ffffff, },
{R, 1, "", _PIPEACONF, 0x00000050, },
{W, 1, "", _PIPEACONF, 0x80000050, },
{R, 1, "", _PIPEASTAT, 0x00000000, },
{W, 1, "", _PIPEASTAT, 0x00000002, },
{R, 4533, "", _PIPEASTAT, 0x00000000, },
{M, 1, "[drm:intel_wait_for_vblank], vblank wait timed out"},
{R, 1, "", _PIPEACONF, 0xc0000050, },
{R, 1, "", _DSPACNTR, 0x58004000, },
{W, 1, "", _DSPACNTR, 0xd8004000, },
{R, 1, "", _DSPAADDR, 0x00000000, },
{W, 1, "", _DSPAADDR, 0x00000000, },
{R, 1, "", _DSPASIZE+0xc, 0x00000000, },
{W, 1, "", _DSPASIZE+0xc, 0x00000000, },
{R, 1, "", _PIPEASTAT, 0x00000000, },
{W, 1, "", _PIPEASTAT, 0x00000002, },
{R, 4392, "", _PIPEASTAT, 0x00000000, },
{M, 1, "[drm:intel_wait_for_vblank], vblank wait timed out"},
{M, 1, "[drm:ironlake_edp_panel_vdd_on], Turn eDP VDD on"},
{R, 1, "", PCH_PP_CONTROL, 0xabcd0008, },
{M, 1, "[drm:ironlake_edp_panel_on], Turn eDP power on"},
{R, 1, "", PCH_PP_STATUS, 0x00000000, },
{M, 1, "[drm:ironlake_wait_panel_power_cycle], Wait for panel power cycle"},
{M, 1, "[drm:ironlake_wait_panel_status], R PCH_PP_CONTROL:abcd0008"},
{R, 2, "", PCH_PP_STATUS, 0x00000000, },
{R, 1, "", PCH_PP_CONTROL, 0xabcd0008, },
{W, 1, "", PCH_PP_CONTROL, 0xabcd000b, },
{R, 1, "", PCH_PP_CONTROL, 0xabcd000b, },
{M, 1, "[drm:ironlake_wait_panel_on], Wait for panel power on"},
{M, 1, "[drm:ironlake_wait_panel_status], R PCH_PP_CONTROL:abcd000b"},
{R, 4, "", PCH_PP_STATUS, 0x0000000a, },
{R, 16983, "", PCH_PP_STATUS, 0x9000000a, },
{R, 17839, "", PCH_PP_STATUS, 0x90000009, },
{R, 1, "", PCH_PP_STATUS, 0x80000008, },
//{V, 7,},
{M, 1, "[drm:ironlake_edp_panel_vdd_off], Turn eDP VDD off 1"},
{R, 2, "", PCH_PP_CONTROL, 0xabcd000b, },
{W, 1, "", PCH_PP_CONTROL, 0xabcd0003, },
{R, 1, "", PCH_PP_CONTROL, 0xabcd0003, },
{M, 1, "[drm:ironlake_panel_vdd_off_sync], R PCH_PP_CONTROL:abcd0003"},
{R, 1, "", PCH_PP_STATUS, 0x80000008, },
{W, 1, "", 0x64000, 0x8e1c4104, },
{R, 1, "", 0x64000, 0x8e1c4104, },
{R, 2, "", PCH_PP_STATUS, 0x80000008, },
{R, 1, "", 0x64000, 0x8cdc4104, },
{M, 1, "[drm:intel_dp_link_down], "},
{W, 1, "", 0x64000, 0x8e1c0004, },
{R, 1, "", 0x64000, 0x8e1c0004,  100},
{W, 1, "", 0x64000, 0x8e1c0204, },
{R, 1, "", 0x64000, 0x8e1c0204, },
{W, 1, "", 0x64000, 0x0e1c0304, },
{R, 2, "", 0x64000, 0x0e1c0304, },
{R, 2, "", PCH_PP_STATUS, 0x80000008, },
{R, 1, "", DPA_AUX_CH_CTL, 0x007500c8, },
{W, 1, "", DPA_AUX_CH_DATA1, 0x80010008, },
{W, 1, "", DPA_AUX_CH_DATA2, 0x0a840000, },
{W, 1, "", DPA_AUX_CH_DATA3, 0x00000000, },
{W, 1, "", DPA_AUX_CH_DATA4, 0x01000000, },
{W, 1, "", DPA_AUX_CH_CTL, 0xd2d500c8, },
{R, 3, "", DPA_AUX_CH_CTL, 0x807500c8,  100},
{R, 1, "", DPA_AUX_CH_CTL, 0x401500c8, },
{W, 1, "", DPA_AUX_CH_CTL, 0x521500c8, },
{R, 1, "", DPA_AUX_CH_DATA1, 0x00000000, },
{W, 1, "", 0x64000, 0x891c4004, },
{R, 1, "", 0x64000, 0x891c4004, },
{R, 2, "", PCH_PP_STATUS, 0x80000008, },
{R, 1, "", DPA_AUX_CH_CTL, 0x001500c8, },
{W, 1, "", DPA_AUX_CH_DATA1, 0x80010200, },
{W, 1, "", DPA_AUX_CH_DATA2, 0x21000000, },
{W, 1, "", DPA_AUX_CH_CTL, 0xd25500c8, },
{R, 2, "", DPA_AUX_CH_CTL, 0x801500c8,  100},
{R, 1, "", DPA_AUX_CH_CTL, 0x401500c8, },
{W, 1, "", DPA_AUX_CH_CTL, 0x521500c8, },
{R, 1, "", DPA_AUX_CH_DATA1, 0x00000000, },
{R, 2, "", PCH_PP_STATUS, 0x80000008, },
{R, 1, "", DPA_AUX_CH_CTL, 0x001500c8, },
{W, 1, "", DPA_AUX_CH_DATA1, 0x80010303, },
{W, 1, "", DPA_AUX_CH_DATA2, 0x00000000, },
{W, 1, "", DPA_AUX_CH_CTL, 0xd28500c8, },
{R, 3, "", DPA_AUX_CH_CTL, 0x801500c8,  100},
{R, 1, "", DPA_AUX_CH_CTL, 0x401500c8, },
{W, 1, "", DPA_AUX_CH_CTL, 0x521500c8, },
{R, 1, "", DPA_AUX_CH_DATA1, 0x00000000,  100},
{R, 2, "", PCH_PP_STATUS, 0x80000008, },
{R, 1, "", DPA_AUX_CH_CTL, 0x001500c8, },
{W, 1, "", DPA_AUX_CH_DATA1, 0x90020205, },
{W, 1, "", DPA_AUX_CH_CTL, 0xd24500c8, },
{R, 2, "", DPA_AUX_CH_CTL, 0x801500c8,  100},
{R, 1, "", DPA_AUX_CH_CTL, 0x804500c8,  100},
{R, 1, "", DPA_AUX_CH_CTL, 0x407500c8, },
{W, 1, "", DPA_AUX_CH_CTL, 0x527500c8, },
{R, 1, "", DPA_AUX_CH_DATA1, 0x00111180, },
{R, 1, "", DPA_AUX_CH_DATA2, 0x02000000, },
{M, 1, "[drm:intel_dp_start_link_train], clock recovery OK"},
{W, 1, "", 0x64000, 0x891c4104, },
{R, 1, "", 0x64000, 0x891c4104, },
{R, 2, "", PCH_PP_STATUS, 0x80000008, },
{R, 1, "", DPA_AUX_CH_CTL, 0x007500c8, },
{W, 1, "", DPA_AUX_CH_DATA1, 0x80010200, },
{W, 1, "", DPA_AUX_CH_DATA2, 0x22000000, },
{W, 1, "", DPA_AUX_CH_CTL, 0xd25500c8, },
{R, 2, "", DPA_AUX_CH_CTL, 0x807500c8,  100},
{R, 1, "", DPA_AUX_CH_CTL, 0x401500c8, },
{W, 1, "", DPA_AUX_CH_CTL, 0x521500c8, },
{R, 1, "", DPA_AUX_CH_DATA1, 0x00000000, },
{R, 2, "", PCH_PP_STATUS, 0x80000008, },
{R, 1, "", DPA_AUX_CH_CTL, 0x001500c8, },
{W, 1, "", DPA_AUX_CH_DATA1, 0x80010303, },
{W, 1, "", DPA_AUX_CH_DATA2, 0x00000000, },
{W, 1, "", DPA_AUX_CH_CTL, 0xd28500c8, },
{R, 2, "", DPA_AUX_CH_CTL, 0x801500c8,  100},
{R, 1, "", DPA_AUX_CH_CTL, 0x800500c8,  100},
{R, 1, "", DPA_AUX_CH_CTL, 0x401500c8, },
{W, 1, "", DPA_AUX_CH_CTL, 0x521500c8, },
{R, 1, "", DPA_AUX_CH_DATA1, 0x00000000,  400},
{R, 2, "", PCH_PP_STATUS, 0x80000008, },
{R, 1, "", DPA_AUX_CH_CTL, 0x001500c8, },
{W, 1, "", DPA_AUX_CH_DATA1, 0x90020205, },
{W, 1, "", DPA_AUX_CH_CTL, 0xd24500c8, },
{R, 2, "", DPA_AUX_CH_CTL, 0x801500c8,  100},
{R, 1, "", DPA_AUX_CH_CTL, 0x804500c8,  100},
{R, 1, "", DPA_AUX_CH_CTL, 0x407500c8, },
{W, 1, "", DPA_AUX_CH_CTL, 0x527500c8, },
{R, 1, "", DPA_AUX_CH_DATA1, 0x00777781, },
{R, 1, "", DPA_AUX_CH_DATA2, 0x02000000, },
{W, 1, "", 0x64000, 0x891c4304, },
{R, 1, "", 0x64000, 0x891c4304, },
{R, 2, "", PCH_PP_STATUS, 0x80000008, },
{R, 1, "", DPA_AUX_CH_CTL, 0x007500c8, },
{W, 1, "", DPA_AUX_CH_DATA1, 0x80010200, },
{W, 1, "", DPA_AUX_CH_DATA2, 0x00000000, },
{W, 1, "", DPA_AUX_CH_CTL, 0xd25500c8, },
{R, 2, "", DPA_AUX_CH_CTL, 0x807500c8,  100},
{R, 1, "", DPA_AUX_CH_CTL, 0x401500c8, },
{W, 1, "", DPA_AUX_CH_CTL, 0x521500c8, },
{R, 1, "", DPA_AUX_CH_DATA1, 0x00000000, },
{M, 1, "[drm:ironlake_edp_backlight_on], "},
{R, 1, "", PCH_PP_CONTROL, 0xabcd0003, },
{W, 1, "", PCH_PP_CONTROL, 0xabcd0007, },
{R, 1, "", PCH_PP_CONTROL, 0xabcd0007, },
{R, 1, "", _PIPEADSL, 0x00000633,  500},
{R, 1, "", _PIPEADSL, 0x00000652, },
{R, 1, "", _PIPEASTAT, 0x00000000, },
{W, 1, "", _PIPEASTAT, 0x00000002, },
{R, 5085, "", _PIPEASTAT, 0x00000000, },
{M, 1, "[drm:intel_wait_for_vblank], vblank wait timed out"},
{M, 1, "[drm:intel_dp_mode_fixup], Display port link bw 0a lane count 4"
    "clock 270000"},
{M, 1, "[drm:drm_crtc_helper_set_mode], [CRTC:3]"},
{0,},
};

#include "buildregs.c"

int
morethanonebit(unsigned long x)
{
	return x & (x-1);
}
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0])) 
char *symname(struct iodef *id)
{
	static char name[512];
	char *cp;
	struct registers *r = NULL;
	unsigned long value;
	int i;
	name[0] = 0;
	/* chew up the bits. Each time you find one that works, then suck it out and replace it with a symbol. */
	if (id->addr < ARRAY_SIZE(reglist))
		r = reglist[id->addr];
	if (!r){
		sprintf(name, "0x%08lx", id->data);
		return name;
	}

	value = id->data;

	/* walk the list. Rip the bits out of addr. If something is left, print it. */
	for(i = 0, cp = name; r[i].name; i++){
		if (! (r[i].value & value))
			continue;
		if (! morethanonebit(r[i].value)){
			cp += sprintf(cp, "%s|", r[i].name);
		} else {
			cp += sprintf(cp, "(%s&0x%lx)|", r[i].name, value & r[i].value);
		}
		value &= ~r[i].value;
	}

	/* just print out hte original value. Useful for knowing what it was AND any bits we could not figure out. */
	sprintf(cp, "0x%08lx", id->data);
	return name;
	
}

int main(int argc, char *argv[])
{
	int i;
	struct iodef *id = iodefs;
	/* state machine! */
	for(i = 0; i < sizeof(iodefs)/sizeof(iodefs[0]); i++, id++){
		if ((id->op != W) && (id->op != R)){
			printf("{%s, %d, \"%s\", %s, 0x%lx, %ld},\n", 
			opnames[id->op], id->count, id->msg, regname(id->addr), id->data, id->udelay);
		} else {
			printf("{%s, %d, \"%s\", %s, %s, %ld},\n", 
			opnames[id->op], id->count, id->msg, regname(id->addr),symname(id), id->udelay);
		}
	}

}
// cc -g prettyregs.c