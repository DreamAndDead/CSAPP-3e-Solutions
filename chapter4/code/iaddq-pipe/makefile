#
# makefile
#


all:

test:
	(cd ../sim/pipe; make clean; make psim VERSION=full)
	(cd ../sim/ptest; make SIM=../pipe/psim TFLAGS=-i)

# vim:ft=make
