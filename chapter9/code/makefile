#
# makefile
#
CC = gcc
CFLAGS = -m64 -pthread
SRCS = $(wildcard 9.*.c)
PROGS = $(patsubst %.c,%,$(SRCS))
PROGS_TEST = $(patsubst %.c,%.test,$(SRCS))

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< vm/csapp.c

test: $(PROGS_TEST)

%.test: %
	./$<

.PHONY : clean
clean:
	find . -type f -executable -print0 | xargs -0 rm --
