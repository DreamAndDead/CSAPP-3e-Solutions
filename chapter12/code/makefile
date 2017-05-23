#
# makefile
#
CC = gcc
CFLAGS = -m64 -pthread -g
SRCS = $(wildcard 12.*.c)
PROGS = $(patsubst %.c,%,$(SRCS))
PROGS_TEST = $(patsubst %.c,%.test,$(SRCS))

all: $(PROGS) diff

%: %.c
	$(CC) $(CFLAGS) -o $@ $< csapp.c

test: $(PROGS_TEST)

%.test: %
	./$<

diff:
	(diff -u 12.23.bug.c 12.23.c > 12.23.c.diff; cd .)

measure:
	(time ./12.34.non.concurrent)
	(time ./12.34.concurrent)

clean:
	rm -rf 12.34.non.concurrent
	rm -rf 12.34.concurrent
