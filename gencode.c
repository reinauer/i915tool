#include "video.h"
#include <stdio.h>

FILE *gf;

void gengmbus(struct intel_gmbus *gm, char *myname, char *container)
 {
	 int i;
	 for(i = 0; i < GMBUS_NUM_PORTS; i++) {
		 fprintf(gf, "{\n\t\t.dev_priv = %s\n\t\t", container);
		 fprintf(gf, 
			 ".reg0 = %ulx, .gpio_reg = %ulx, .force_bit = %d\n\t\t",
			 gm->reg0, gm->gpio_reg, gm->force_bit);
	 }
 }

void gendrmprivate(struct drm_i915_private *dev, char *myname, char *container)
{
	fprintf(gf, "{\n\t.dev = %s\n\t", container);
	if (dev){
		fprintf(gf, ".regs = %p\n", dev->regs);
	}
	fprintf(gf, "\n};");
 }
 void
 gendrmdevice(struct drm_device *dev)
 {
	 char *privname = NULL;

	 /* skip the pci device and the bios_bin  */
	 if (! dev)
		 return;
	 fprintf(gf, "struct drm_i915_private drmi915 = ");
	 gendrmprivate(dev->dev_private, "drmi915", "drmdevice");
	 fprintf(gf, "};");
	 fprintf(gf, "struct drm_device x = {\n\t.dev_private = drmi915\n");
	 fprintf(gf, ".mode_config = ");
	 genmodeconfig(dev->mode_config, "drmdevice.mode_config", "drmdevice");
	 fprintf(gf, "},");
	 /* the rest of this nonsense is not needed */
}
