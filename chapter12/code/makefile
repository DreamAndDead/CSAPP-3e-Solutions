#
# makefile
#
CC = gcc
CFLAGS = -m64 -pthread
SRCS = $(wildcard 12.*.c)
PROGS = $(patsubst %.c,%,$(SRCS))
PROGS_TEST = $(patsubst %.c,%.test,$(SRCS))

all: $(PROGS) diff
	(cd cgi-bin; make)
	(cd 12.36; make)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< csapp.c

test: $(PROGS_TEST)

%.test: %
	./$<

diff:
	(diff -u 12.23.bug.c 12.23.c > 12.23.c.diff; cd .)
	(diff -u 12.tiny.c 12.35.c > 12.35.c.diff; cd .)

measure:
	(time ./12.34.non.concurrent)
	(time ./12.34.concurrent)

clean:
	rm -rf 12.34.non.concurrent
	rm -rf 12.34.concurrent

benchmark:
	wrk -d4 http://localhost:5000
