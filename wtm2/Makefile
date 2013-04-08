# we compile each time because we're using the c compiler
# to do a lot of parsing of .h files for us. Seems weird, works well.

CFLAGS=-I.. -g
TARGET=/usr/local/src/firmware/src/third_party/coreboot/src/mainboard/intel/wtm2/i915io.c

all: i915io.c
	echo "DO NOT FORGET TO COPY TO THE COREBOOT TREE"
i915io.c:wtm2io_step5.c coreboot_start coreboot_end
	#cat coreboot_start $< coreboot_end > $@
# comment this out or change to suit. 
	cp $@ $(TARGET)

wtm2io_step5.c: wtm2io_step4.c auxcode.c
	cc $(CFLAGS) -o auxcode auxcode.c
	./auxcode < $< > $@

wtm2io_step4.c: wtm2io_step3.c
	grep -v PCH_GMBUS < $< | grep -v PCH_GPIOE > $@

wtm2io_step3.c: wtm2io_step2.c symbolic.c
	cc $(CFLAGS) -o symbolic symbolic.c
	./symbolic < $< > $@

wtm2io_step2.c: wtm2io_step1.ops ops2c.c
	cc -o ops2c ops2c.c
	./ops2c < $< > $@

wtm2io_step1.ops: coreboot.log step1.sh
	./step1.sh coreboot.log wtm2io_step1.ops

clean:
	rm -f wtm2io_* symbolic auxcode ops2c *~ i915io.c
