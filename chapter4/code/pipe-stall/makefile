#
# makefile
#

all:
	(cd ../sim/pipe; \
	  diff -u origin-pipe-stall.hcl pipe-stall.hcl > pipe-stall.diff; \
	  echo 'generate pipe-stall.diff')

test:
	(cd ../sim/pipe; make clean; make psim VERSION=stall)
	(cd ../sim/ptest; make SIM=../pipe/psim TFLAGS=)

debug:
	(cd ../sim/pipe; make clean; make psim VERSION=stall)
	(cd ../sim/pipe; ./psim -g ../y86-code/asum.yo)

# vim:ft=make
#
