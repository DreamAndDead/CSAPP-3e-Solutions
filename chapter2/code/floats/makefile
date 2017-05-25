#
# makefile
#
CFLAGS = -m64 -std=c99
SRCS = $(wildcard *.c)
LIBFILE = ../lib/random.c

all:
	gcc $(CFLAGS) $(SRCS) $(LIBFILE) -o main

test:
	./main

# vim:ft=make
#
