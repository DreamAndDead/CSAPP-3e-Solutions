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
	(cd 12.38; make)
	(cd 12.39; make)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< csapp.c

test:
	(cd cgi-bin; make test)
	(cd 12.36; make test)
	(cd 12.38; make test)
	(cd 12.39; make test)
	./12.16
	./12.17
	./12.19
	./12.20
	./12.21
	./12.26

diff:
	(diff -u 12.23.bug.c 12.23.c > 12.23.c.diff; cd .)
	(diff -u 12.tiny.c 12.35.c > 12.35.c.diff; cd .)
	(diff -u 12.tiny.c 12.37.c > 12.37.c.diff; cd .)

measure:
	(time ./12.34.non.concurrent)
	(time ./12.34.concurrent)

.PHONY : clean
clean:
	(cd cgi-bin; make clean)
	(cd 12.36; make clean)
	(cd 12.38; make clean)
	(cd 12.39; make clean)
	find . -type f -executable -print0 | xargs -0 rm -f --

benchmark:
	wrk -d4 http://localhost:5000
