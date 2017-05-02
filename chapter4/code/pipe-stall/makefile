#
# makefile
#

all: test

test:
	(cd ../sim/pipe; make clean; make psim VERSION=stall)
	(cd ../sim/ptest; make SIM=../pipe/psim TFLAGS=)

debug:
	(cd ../sim/pipe; make clean; make psim VERSION=stall)
	(cd ../sim/pipe; ./psim -g ../y86-code/asum.yo)

# vim:ft=make
#
