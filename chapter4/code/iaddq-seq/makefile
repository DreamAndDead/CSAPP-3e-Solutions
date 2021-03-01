#
# makefile
#

all:
	(cd ../sim/seq; \
	  diff -u origin-seq-full.hcl seq-full.hcl > seq-full.diff; \
	  echo 'generate seq-full.diff')

test:
	(cd ../sim/seq; make clean && make ssim VERSION=full)
	(cd ../sim/ptest; make SIM=../seq/ssim TFLAGS=-i)

# vim:ft=make
#
