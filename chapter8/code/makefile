#
# makefile
#
CC = gcc
CFLAGS = -m64 -pthread -g
SRCS = $(wildcard 8.*.c)
PROGS = $(patsubst %.c,%,$(SRCS))
PROGS_TEST = $(patsubst %.c,%.test,$(SRCS))

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< csapp.c

test: $(PROGS_TEST)

%.test: %
	./$<
