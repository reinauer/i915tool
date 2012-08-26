#include "video.h"
#include <stdio.h>

void genintelcrtc(struct intel_crtc *c, char *decl, char *container)
{
  if (! c){
	  fprintf(gf, "%s = {};\n", decl);
	  return;
  }
  fprintf(gf, "%s = {\n", decl);
	fprintf(gf, "\t.pipe = %d\n", c->pipe);
	fprintf(gf, "\t.plane = %d\n", c->plane);
	/* skip for now 
	u8 lut_r[256], lut_g[256], lut_b[256];
	*/
	fprintf(gf, "\t.dpms_mode = %d\n", c->dpms_mode);
	/* never active ... */
	
	fprintf(gf, "\t.active = %d\n", c->active);
	fprintf(gf, "\t.busy = %d\n", c->busy);
	fprintf(gf, "\t.lowfreq_avail = %d\n", c->lowfreq_avail);
	fprintf(gf, "\t.fdi_lanes = %d\n", c->fdi_lanes);
	/* matters not
	uint32_t cursor_addr;
	int16_t cursor_x, cursor_y;
	int16_t cursor_width, cursor_height;
	bool cursor_visible;
	*/
	fprintf(gf, "\t.bpp = %d\n", c->bpp);
	fprintf(gf, "\t.no_pll = %d\n", c->no_pll);
	fprintf(gf, "\t.use_pll_a = %d\n", c->use_pll_a);
	fprintf(gf, "};\n");

}

void genmodeconfig(struct drm_display_mode *m, char *decl, char *container)
{
	if (! m){
		return;
	}
	fprintf(gf, "%s .name = \"%s\",\n", decl, m->name);

	fprintf(gf, ".status = %d,.type = %d,\n", m->status, m->type);

	/* Proposed mode values */
	fprintf(gf, "\t.clock = %d,\n", m->clock);		/* in kHz */
	fprintf(gf, "\t.hdisplay = %d,\n", m->hdisplay);
	fprintf(gf, "\t.hsync_start = %d,\n", m->hsync_start);
	fprintf(gf, "\t.hsync_end = %d,\n", m->hsync_end);
	fprintf(gf, "\t.htotal = %d,\n", m->htotal);
	fprintf(gf, "\t.hskew = %d,\n", m->hskew);
	fprintf(gf, "\t.vdisplay = %d,\n", m->vdisplay);
	fprintf(gf, "\t.vsync_start = %d,\n", m->vsync_start);
	fprintf(gf, "\t.vsync_end = %d,\n", m->vsync_end);
	fprintf(gf, "\t.vtotal = %d,\n", m->vtotal);
	fprintf(gf, "\t.vscan = %d,\n", m->vscan);
	fprintf(gf, "\t.flags = %ld,\n", m->flags);

	/* Addressable image size (may be 0 for projectors, etc.); */
	fprintf(gf, "\t.width_mm = %d,\n", m->width_mm);
	fprintf(gf, "\t.height_mm = %d,\n", m->height_mm);

	/* Actual mode we give to hw */
	fprintf(gf, "\t.clock_index = %d,\n", m->clock_index);
	fprintf(gf, "\t.synth_clock = %d,\n", m->synth_clock);
	fprintf(gf, "\t.crtc_hdisplay = %d,\n", m->crtc_hdisplay);
	fprintf(gf, "\t.crtc_hblank_start = %d,\n", m->crtc_hblank_start);
	fprintf(gf, "\t.crtc_hblank_end = %d,\n", m->crtc_hblank_end);
	fprintf(gf, "\t.crtc_hsync_start = %d,\n", m->crtc_hsync_start);
	fprintf(gf, "\t.crtc_hsync_end = %d,\n", m->crtc_hsync_end);
	fprintf(gf, "\t.crtc_htotal = %d,\n", m->crtc_htotal);
	fprintf(gf, "\t.crtc_hskew = %d,\n", m->crtc_hskew);
	fprintf(gf, "\t.crtc_vdisplay = %d,\n", m->crtc_vdisplay);
	fprintf(gf, "\t.crtc_vblank_start = %d,\n", m->crtc_vblank_start);
	fprintf(gf, "\t.crtc_vblank_end = %d,\n", m->crtc_vblank_end);
	fprintf(gf, "\t.crtc_vsync_start = %d,\n", m->crtc_vsync_start);
	fprintf(gf, "\t.crtc_vsync_end = %d,\n", m->crtc_vsync_end);
	fprintf(gf, "\t.crtc_vtotal = %d,\n", m->crtc_vtotal);
	fprintf(gf, "\t.crtc_hadjusted = %d,\n", m->crtc_hadjusted);
	fprintf(gf, "\t.crtc_vadjusted = %d,\n", m->crtc_vadjusted);

	fprintf(gf, "\t.vrefresh = %d,\n", m->vrefresh);		/* in Hz */
	fprintf(gf, "\t.hsync = %d,\n", m->hsync);		/* in kHz */
	fprintf(gf, "},\n");
}

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

/* we likely won't need this. */
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
//	 fprintf(gf, ".mode_config = ");
//	 genmodeconfig(&dev->mode_config, "drmdevice.mode_config", "drmdevice");
	 fprintf(gf, "},");
	 /* the rest of this nonsense is not needed */
}

static void gencrtc(struct drm_crtc *c, char *decl, char *container)
{
	/* sigh. Skip the list for now. */

	if (!c ){
		fprintf(gf, "%s = {};\n", decl);
		return;
	}
	genintelcrtc(to_intel_crtc(c), "intelcrtc", container);
	fprintf(gf, "%s ", decl);
	genmodeconfig(&c->mode, ".mode = {",  NULL);
	genmodeconfig(&c->hwmode, ".hwmode = {", NULL);
	fprintf(gf, "\t.x=%d,.y=%d\n", c->x, c->y);
	fprintf(gf, "\t.fb = &framebuffer\n");
	fprintf(gf, "};\n");
	
}

void genintelencoder(struct intel_encoder *i, char *decl, char *container)
{
	if (!i){
		fprintf(gf, "%s };\n", decl);
		return;
	}
	fprintf(gf, "%s .base = %s\n", decl, container);
	fprintf(gf, "\t.type=%d\n", i->type);
	fprintf(gf, "\t.needs_tv_clock=%d\n", i->needs_tv_clock);
	fprintf(gf, "\t.crtc_mask=%d\n", i->needs_tv_clock);
	fprintf(gf, "\t.clone_mask=%d\n", i->needs_tv_clock);
	fprintf(gf, "};\n");
}
void genencoder(struct drm_encoder *e, char *myname, char *container)
{
	if (! e)
		return;
	genintelencoder(to_intel_encoder(e), "struct intel_encoder intel_encoder = {", myname);
	gencrtc(e->crtc, "struct drm_crtc crtc = {", container);
	fprintf(gf, "struct drm_encoder %s = {.dev = %s\n", myname, container);
	fprintf(gf, "\t.encoder_type = %d\n", e->encoder_type);
	fprintf(gf, "\t.crtc = crtc\n");
	fprintf(gf, "\t.possible_crtcs=%ld, .possible_clones=%d\n",
		e->possible_crtcs, e->possible_clones);
	fprintf(gf, "};\n");
	/* no idea now to do the functions yet */
}
