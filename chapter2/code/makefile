#
# makefile
#
CC = gcc
CFLAGS = -m64 -std=c99
SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))
PROGS_TEST = $(patsubst %.c,%.test,$(SRCS))
LIBFILE = ./lib/random.c

all: $(PROGS)
	(cd floats; make)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBFILE)

test: $(PROGS_TEST)
	(cd floats; make test)

%.test: %
	./$<
