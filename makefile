#
# makefile
#

all:
	(cd chapter2/code; make)
	(cd chapter4/code; make)

test:
	(cd chapter2/code; make test)
	(cd chapter4/code; make test)
