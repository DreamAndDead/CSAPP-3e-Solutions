#
# makefile
#

all:
	gcc -c -m64 loop.s -o loop.o
	gcc loop.o loop2.c main.c -o main

test:
	./main

.PHONY: clean
clean:
	rm main


# vim:ft=make
#
