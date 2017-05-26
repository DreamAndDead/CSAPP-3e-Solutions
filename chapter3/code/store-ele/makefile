#
# makefile
#

all:
	gcc -c -m64 store-ele.s -o store-ele.o
	gcc main.c store-ele2.c store-ele.o -o main

test:
	./main

.PHONY: clean
clean:
	rm main

# vim:ft=make
#
