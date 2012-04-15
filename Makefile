goodsource=pci.c final/intel_bios.c final/drm_modes.c final/i915_drv.c  final/intel_i2c.c common.c hexdump.c
brokensource=final/intel_display.c final/intel_dp.c final/intel_panel.c final/drm_dp_i2c_helper.c final/i915_dma.c final/intel_lvds.c final/drm_edid.c final/drm_crtc.c final/drm_crtc_helper.c \
	  i2c.c 


all: probe gttdump dumpscreen gttbreak gttset

# b is for broken and it is less typing.
b: video

video: video.c $(goodsource) $(brokensource) video.h
	cc -O2 -g -include video.h -Iinputs -static -g -o video video.c $(goodsource) $(brokensource) fake.c -lpci  -lrt

probe: probe.c $(goodsource) video.h
	cc -O2 -include video.h -Iinputs -static -g -o probe probe.c $(goodsource) -lpci -lrt

gttdump: gttdump.c $(goodsource) video.h
	cc -O2 -include video.h -Iinputs -static -g -o gttdump gttdump.c $(goodsource) -lpci -lrt
gttbreak: gttbreak.c $(goodsource) video.h
	cc -O2 -include video.h -Iinputs -static -g -o gttbreak gttbreak.c $(goodsource) -lpci -lrt
gttset: gttset.c $(goodsource) video.h
	cc -O2 -include video.h -Iinputs -static -g -o gttset gttset.c $(goodsource) -lpci -lrt
dumpscreen: dumpscreen.c $(goodsource) video.h
	cc -O2 -include video.h -Iinputs -static -g -o dumpscreen dumpscreen.c $(goodsource) -lpci -lrt
clean:
	rm -f *.o video probe gttdump dumpscreen gttbreak gttset

moreclean:  clean
	rm -f final/* per-file-changes/* tmp/*

superclean: moreclean
	rm -f inputs/*
