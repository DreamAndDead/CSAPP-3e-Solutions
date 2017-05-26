#
# makefile
#

all:
	gcc -c -m64 sum-col.s -o sum-col.o
	gcc main.c sum-col2.c sum-col.o -o main

test:
	./main

.PHONY: clean
clean:
	rm main

# vim:ft=make
#
