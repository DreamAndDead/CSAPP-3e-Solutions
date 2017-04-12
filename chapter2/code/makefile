#
# makefile
#
CC = gcc
CFLAGS = -m64 -std=c99
SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))
PROGS_TEST = $(patsubst %.c,%.test,$(SRCS))

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

test: $(PROGS_TEST)

%.test: %
	./$<
