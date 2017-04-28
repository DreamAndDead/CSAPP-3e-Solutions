#
# makefile
#

all: test

test:
	(cd ../sim/pipe; make clean; make psim VERSION=stall)
	(cd ../sim/ptest; make SIM=../pipe/psim TFLAGS=)

# vim:ft=make
#
