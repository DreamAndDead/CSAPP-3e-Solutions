#
# makefile
#

all:
	(cd ../sim/pipe; \
	  diff -u origin-pipe-nt.hcl pipe-nt.hcl > pipe-nt.diff; \
	  echo 'generate pipe-nt.diff')

test:
	(cd ../sim/pipe; make clean; make psim VERSION=nt)
	(cd ../sim/ptest; make SIM=../pipe/psim TFLAGS=)

debug:
	(cd ../sim/pipe; make clean; make psim VERSION=nt)
	(cd ../sim/pipe; ./psim -g ../y86-code/asum.yo)

# vim:ft=make
#
