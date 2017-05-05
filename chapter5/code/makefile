#
# makefile
#
CC = gcc
CFLAGS = -m64 -std=c99
LIB = ./lib/vec.c

SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))
PROGS_TEST = $(patsubst %.c,%.test,$(SRCS))

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $(LIB) -o $@ $<

test: $(PROGS_TEST)

%.test: %
	./$<

5.18.prof:
	gcc -std=c99 -lprofiler 5.18.c -o prof.5.18
	env CPUPROFILE=/tmp/prof.out ./prof.5.18
	pprof prof.5.18 /tmp/prof.out --text

5.19.prof:
	gcc -std=c99 -lprofiler 5.19.c -o prof.5.19
	env CPUPROFILE=/tmp/prof.out ./prof.5.19
	pprof prof.5.19 /tmp/prof.out --text

# vim:ft=make
#
