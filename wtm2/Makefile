CFLAGS=-I.. -g
all: i915io.c
i915io.c:wtm2io_step3.c
	cat coreboot_start $< coreboot_end > $@

wtm2io_step3.c: wtm2io_step2.c symbolic.c
	cc $(CFLAGS) -o symbolic symbolic.c
	./symbolic < $< > $@

wtm2io_step2.c: wtm2io_step1.ops ops2c.c
	cc -o ops2c ops2c.c
	./ops2c < $< > $@

wtm2io_step1.ops: coreboot.log step1
	./step1.sh coreboot.log wtm2io_step1.ops

clean:
	rm -f wtm2io_* symbolic ops2c *~
