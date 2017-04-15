#
# makefile
#
CC = gcc
CFLAGS = -m64 -std=c99
SLIBS = ./lib/librandom.a
SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))
PROGS_TEST = $(patsubst %.c,%.test,$(SRCS))

all: static-lib $(PROGS)

static-lib:
	(cd lib; make)
	(cd floats; make)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(SLIBS)

test: $(PROGS_TEST)
	(cd floats; make test)

%.test: %
	./$<
