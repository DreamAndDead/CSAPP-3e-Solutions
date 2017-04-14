#
# makefile
#

all: float-negate.o main.o
	gcc float-negate.o main.o -o main

main.o: main.c
	gcc -c main.c

float-negate.o: float-negate.c float-negate.h
	gcc -c float-negate.c

test:
	./main

# vim:ft=make
#
