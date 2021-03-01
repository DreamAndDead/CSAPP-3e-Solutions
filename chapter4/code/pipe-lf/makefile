#
# makefile
#

all:
	(cd ../sim/pipe; \
	  diff -u origin-pipe-lf.hcl pipe-lf.hcl > pipe-lf.diff; \
	  echo 'generate pipe-lf.diff')

test:
	(cd ../sim/pipe; make clean; make psim VERSION=lf)
	(cd ../sim/ptest; make SIM=../pipe/psim TFLAGS=)

debug:
	(cd ../sim/pipe; make clean; make psim VERSION=lf)
	(cd ../sim/pipe; ./psim -g ../y86-code/asum.yo)

# vim:ft=make
#
