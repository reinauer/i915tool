# habit from go: I just recompile everything always. 
# And at some point want to experiment with combining anyway.

goodsource=pci.c final/intel_bios.c final/drm_modes.c final/i915_drv.c  final/intel_i2c.c common.c hexdump.c fake.c  final/i2c-algo-bit.c
brokensource=final/intel_display.c final/intel_dp.c final/intel_panel.c final/drm_dp_i2c_helper.c final/i915_dma.c final/intel_lvds.c final/drm_edid.c final/drm_crtc.c final/drm_crtc_helper.c final/intel_modes.c \
	  i2c.c 

OBJ=ptrace.o

CFLAGS=
CFLAGS+=-O2
CFLAGS+=-finstrument-functions 

all: probe gttdump dumpscreen gttbreak gttset edid video timegttsetup ports panel dpms

timegttsetup: timegttsetup.c $(goodsource) $(brokensource) video.h $(OBJ)
	cc $(CFLAGS) -g -include video.h -Iinputs -static -g -o timegttsetup timegttsetup.c $(goodsource) $(brokensource)  $(OBJ) -lpci  -lrt

dpms: dpms.c $(goodsource) $(brokensource) video.h $(OBJ)
	cc $(CFLAGS) -g -include video.h -Iinputs -static -g -o dpms dpms.c $(goodsource) $(brokensource)  $(OBJ) -lpci  -lrt

edid: edid.c $(goodsource) $(brokensource) video.h $(OBJ)
	cc $(CFLAGS) -g -include video.h -Iinputs -static -g -o edid edid.c $(goodsource) $(brokensource)  $(OBJ) -lpci  -lrt

panel: panel.c $(goodsource) $(brokensource) video.h $(OBJ)
	cc $(CFLAGS) -g -include video.h -Iinputs -static -g -o panel panel.c $(goodsource) $(brokensource)  $(OBJ) -lpci  -lrt

ports: ports.c $(goodsource) $(brokensource) video.h $(OBJ)
	cc $(CFLAGS) -g -include video.h -Iinputs -static -g -o ports ports.c $(goodsource) $(brokensource)  $(OBJ) -lpci  -lrt

video: video.c $(goodsource) $(brokensource) video.h $(OBJ)
	cc $(CFLAGS) -g -include video.h -Iinputs -static -g -o video video.c $(goodsource) $(brokensource)  $(OBJ) -lpci  -lrt

probe: probe.c $(goodsource) video.h $(OBJ)
	cc $(CFLAGS) -include video.h -Iinputs -static -g -o probe probe.c $(goodsource)  $(OBJ) -lpci -lrt

gttdump: gttdump.c $(goodsource) video.h $(OBJ)
	cc $(CFLAGS) -include video.h -Iinputs -static -g -o gttdump gttdump.c $(goodsource)  $(OBJ) -lpci -lrt
gttbreak: gttbreak.c $(goodsource) video.h $(OBJ)
	cc $(CFLAGS) -include video.h -Iinputs -static -g -o gttbreak gttbreak.c $(goodsource)  $(OBJ) -lpci -lrt
gttset: gttset.c $(goodsource) video.h $(OBJ)
	cc $(CFLAGS) -include video.h -Iinputs -static -g -o gttset gttset.c $(goodsource)  $(OBJ) -lpci -lrt
dumpscreen: dumpscreen.c $(goodsource) video.h $(OBJ)
	cc $(CFLAGS) -include video.h -Iinputs -static -g -o dumpscreen dumpscreen.c $(goodsource)  $(OBJ) -lpci -lrt

ptrace.o: etrace-2.1/src/ptrace.c
	cc -c $<

alltags: 
	ctags *.[ch] final/*.[ch]
	etags.emacs *.[ch] final/*.[ch]

clean:
	rm -f *.o video probe gttdump dumpscreen gttbreak gttset
	rm -f edid timegttsetup ports panel dpms

moreclean:  clean
	rm -f final/* per-file-changes/* tmp/* tags

superclean: moreclean
	rm -f inputs/*
