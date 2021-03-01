#
# makefile
#

all:
	(cd ../sim/pipe; \
	  diff -u origin-pipe-btfnt.hcl pipe-btfnt.hcl > pipe-btfnt.diff; \
	  echo 'generate pipe-btfnt.diff')

test:
	(cd ../sim/pipe; make clean; make psim VERSION=btfnt)
	(cd ../sim/ptest; make SIM=../pipe/psim TFLAGS=)

debug:
	(cd ../sim/pipe; make clean; make psim VERSION=btfnt)
	(cd ../sim/pipe; ./psim -g ../y86-code/asum.yo)

# vim:ft=make
#
