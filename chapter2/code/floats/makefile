#
# makefile
#
CFLAGS = -m64 -std=c99
SRCS = $(wildcard *.c)

all:
	gcc $(CFLAGS) $(SRCS) ../lib/librandom.a -o main

test:
	./main

# vim:ft=make
#
