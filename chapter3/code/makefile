#
# makefile
#
CC = gcc
CFLAGS = -m64 -std=c99

all:
	(cd cread; make)
	(cd decode2; make)
	(cd good-echo; make)
	(cd loop; make)
	(cd store-ele; make)
	(cd sum-col; make)

test:
	(cd cread; make test)
	(cd decode2; make test)
	(cd good-echo; make test)
	(cd loop; make test)
	(cd store-ele; make test)
	(cd sum-col; make test)

.PHONY : clean
clean:
	(cd cread; make clean)
	(cd decode2; make clean)
	(cd good-echo; make clean)
	(cd loop; make clean)
	(cd store-ele; make clean)
	(cd sum-col; make clean)
