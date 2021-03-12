#
# makefile
#

all:
	(cd sim; make)
	(cd switch; make)
	(cd bubble-sort; make)
	(cd iaddq-seq; make)
	(cd iaddq-pipe; make)
	(cd pipe-1w; make)
	(cd pipe-btfnt; make)
	(cd pipe-lf; make)
	(cd pipe-nt; make)
	(cd pipe-stall; make)

test:
	(cd bubble-sort; make test)
	(cd switch; make test)
	(cd iaddq-seq; make test)
	(cd iaddq-pipe; make test)
	(cd pipe-1w; make test)
	(cd pipe-btfnt; make test)
	(cd pipe-lf; make test)
	(cd pipe-nt; make test)
	(cd pipe-stall; make test)

.PHONY: clean
clean:
	(cd sim; make clean)
	(cd bubble-sort; make clean)
	(cd switch; make clean)

# vim:ft=make
#
