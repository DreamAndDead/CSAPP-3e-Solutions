#
# makefile
#

all:
	(cd chapter2/code; make)
	(cd chapter3/code; make)
	(cd chapter4/code; make)
	(cd chapter5/code; make)
	(cd chapter6/code; make)
	(cd chapter7/code; make)
	(cd chapter8/code; make)
	(cd chapter9/code; make)
	(cd chapter10/code; make)
	(cd chapter11/code; make)
	(cd chapter12/code; make)

test:
	(cd chapter2/code; make test)
	(cd chapter3/code; make test)
	(cd chapter4/code; make test)
	(cd chapter5/code; make test)
	(cd chapter6/code; make test)
	(cd chapter7/code; make test)
	(cd chapter8/code; make test)
	(cd chapter9/code; make test)
	(cd chapter10/code; make test)
	(cd chapter11/code; make test)
	(cd chapter12/code; make test)
