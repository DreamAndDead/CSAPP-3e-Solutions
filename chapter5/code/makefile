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

# vim:ft=make
#
