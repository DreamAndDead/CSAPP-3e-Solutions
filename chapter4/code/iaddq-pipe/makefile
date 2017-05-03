#
# makefile
#


all:
	(cd ../sim/pipe; \
	  diff -u origin-pipe-full.hcl pipe-full.hcl > pipe-full.diff; \
	  echo 'generate pipe-full.diff')

test:
	(cd ../sim/pipe; make clean; make psim VERSION=full)
	(cd ../sim/ptest; make SIM=../pipe/psim TFLAGS=-i)

# vim:ft=make
