#include "video.h"

extern int verbose;
extern struct drm_device *i915;
int cangencode = 0;

int main(int argc, char *argv[])
{
	struct drm_i915_private *dp;

	init(&argc, &argv);
	devinit();
	intel_setup_bios(i915);
	if (i915->bios_bin)
		intel_parse_bios(i915);
	intel_panel_enable_backlight(i915, 0);
	i915_driver_load(i915, (unsigned long)i915->dev_private->info);

	/* now walk the connector list, dumping connector type 
	 * and EDID
	 */
	dp = i915->dev_private;

	if (dp->int_lvds_connector) {
		if (verbose){
			fprintf(stderr, "We have an lvds: \n");
		}
		dumpeld("LVDS Raw: ", 
			dp->int_lvds_connector->display_info.raw_edid);
		if (dp->int_lvds_connector->eld)
			dumpeld("LVDS:", dp->int_lvds_connector->eld);
	}
	
	if (dp->int_edp_connector) {
		if (verbose)
			fprintf(stderr, "We have an edp: \n");
		if (dp->int_edp_connector->display_info.raw_edid) {
			dumpeld("EDP Raw: ", 
				dp->int_edp_connector->display_info.raw_edid);
		} else printf("NO EDP connector\n");
		if (dp->int_edp_connector->eld)
			dumpeld("EDP:", dp->int_edp_connector->eld);
	}


	struct drm_connector *connector;
        list_for_each_entry(connector, &i915->mode_config.connector_list, head){
		printf("connector %p\n", connector);
		printf("EDID blob is %p\n", connector->edid_blob_ptr);
		if (connector->edid_blob_ptr && connector->edid_blob_ptr->data)
			dumpeld("EDID:", connector->edid_blob_ptr->data);
		printf("EDID-like-data (ELD):\n");
		dumpeld("ELD:", connector->eld);
	}

}
