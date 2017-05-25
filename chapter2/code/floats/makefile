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

.PHONY : clean
clean:
	find . -type f -executable -print0 | xargs -0 rm --

# vim:ft=make
#
