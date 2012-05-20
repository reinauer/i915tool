
CC = gcc
CFLAGS = -g -finstrument-functions

crumble: crumble.c ../src/ptrace.c
	$(CC) $(CFLAGS) -o crumble crumble.c ../src/ptrace.c

run:
	touch TRACE ;
	crumble
	../src/etrace crumble
	rm -f TRACE

clean:
	rm -f crumble TRACE
