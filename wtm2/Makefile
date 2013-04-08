wtm2io_step1.c: wtm2io_step1.ops ops2c.c
	cc -o ops2c ops2c.c
	./ops2c < $< > $@

wtm2io_step1.ops: coreboot.log step1
	./step1.sh coreboot.log wtm2io_step1.ops
