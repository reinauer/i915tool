struct  drm_display_mode linkmode = {
	"2560x1700",
	60,
	285250,
	2560,
	2608,
	2640,
	2720,
	1700,
	1703,
	1713,
	1749,
	0x48,
	0xa,
};

void gfxstartup(void){

	/* we know it's aa pantherpoint. We're going to just call
	 * the correction functions. 
	intel_detect_pch], Found PatherPoint PCH
	 */
init_vbt_defaults], Set default to SSC at 120MHz
i915_load_modeset_init], failed to find VBIOS tables
intel_init_display], Using MT version of forcewake
intel_modeset_init], 3 display pipes available.
intel_dp_init], cur t1_t3 2000 t8 2000 t9 2000 t10 500 t11_t12 6
000
intel_dp_init], vbt t1_t3 0 t8 0 t9 0 t10 0 t11_t12 0
intel_dp_init], panel power up delay 200, power down delay 50, p
ower cycle delay 600
intel_dp_init], backlight on delay 200, off delay 200
ironlake_edp_panel_vdd_on], Turn eDP VDD on
ironlake_wait_panel_power_cycle], Wait for panel power cycle
ironlake_wait_panel_status], mask b800000f value 00000000 status
 00000000 control 00000000
ironlake_edp_panel_vdd_on], PCH_PP_STATUS: 0x00000000 PCH_PP_CON
TROL: 0xabcd0008
ironlake_edp_panel_vdd_on], eDP was not running
ironlake_edp_panel_vdd_off], Turn eDP VDD off 1
intel_dp_i2c_init], i2c_init DPDDC-A
ironlake_edp_panel_vdd_on], Turn eDP VDD on
ironlake_edp_panel_vdd_on], eDP VDD already on
ironlake_edp_panel_vdd_off], Turn eDP VDD off 1
intel_panel_get_backlight], get backlight PWM = 4302
intel_hdmi_init called
