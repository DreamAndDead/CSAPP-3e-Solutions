#
# makefile
# zdw, 2017-04-10 11:12
#
CC = gcc
CFLAGS =
SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<
