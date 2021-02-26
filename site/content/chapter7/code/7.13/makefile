#
# makefile
#

all:
	gcc -Og little.c -o og-little
	gcc -Og -g little.c -o dog-little

test:

.PHONY: clean
clean:
	rm og-little dog-little

dump-exe-code:
	objdump -d og-little
	objdump -d dog-little

# vim:ft=make
#
