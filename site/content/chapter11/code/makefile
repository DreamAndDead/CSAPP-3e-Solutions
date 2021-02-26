#
# makefile
#
CC = gcc
CFLAGS = -m64 -pthread
SRCS = $(wildcard tiny.*.c)
PROGS = $(patsubst %.c,%,$(SRCS))
PROGS_TEST = $(patsubst %.c,%.test,$(SRCS))

all: $(PROGS) diff
	(cd cgi-bin; make)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< csapp.c

test:
	(cd cgi-bin; make test)

diff:
	(diff -u tiny.origin.c tiny.6.c > tiny.6.c.diff; cd .)
	(diff -u tiny.origin.c tiny.7.c > tiny.7.c.diff; cd .)
	(diff -u tiny.origin.c tiny.8.c > tiny.8.c.diff; cd .)
	(diff -u tiny.origin.c tiny.9.c > tiny.9.c.diff; cd .)
	(diff -u tiny.origin.c tiny.11.c > tiny.11.c.diff; cd .)
	(diff -u tiny.origin.c tiny.12.c > tiny.12.c.diff; cd .)
	(diff -u tiny.origin.c tiny.13.c > tiny.13.c.diff; cd .)

.PHONY : clean
clean:
	(cd cgi-bin; make clean)
	find . -type f -executable -print0 | xargs -0 rm -f --
