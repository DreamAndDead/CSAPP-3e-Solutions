#
# makefile
#

all:

test:
	(cd ../sim/seq; make ssim VERSION=full)
	(cd ../sim/ptest; make SIM=../seq/ssim TFLAGS=-i)


# vim:ft=make
#
