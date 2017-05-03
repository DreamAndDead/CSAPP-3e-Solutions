#
# makefile
#

all:

test:
	(cd ../sim/pipe; make clean; make psim VERSION=1w)
	(cd ../sim/ptest; make SIM=../pipe/psim TFLAGS=)

debug:
	(cd ../sim/pipe; make clean; make psim VERSION=1w)
	(cd ../sim/pipe; ./psim -g ../y86-code/poptest.yo)

# vim:ft=make
#
