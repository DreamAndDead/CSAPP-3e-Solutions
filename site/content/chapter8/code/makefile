#
# makefile
#
CC = gcc
CFLAGS = -m64 -pthread
SRCS = $(wildcard 8.*.c)
PROGS = $(patsubst %.c,%,$(SRCS))
PROGS_TEST = $(patsubst %.c,%.test,$(SRCS))

all: $(PROGS)
	(cd shell; make)
	$(CC) $(CFLAGS) -o mysystem mysystem.c csapp.c
	$(CC) $(CFLAGS) -o exit-code exit-code.c
	$(CC) $(CFLAGS) -o wait-sig wait-sig.c

%: %.c
	$(CC) $(CFLAGS) -o $@ $< csapp.c

test: $(PROGS_TEST)
	(cd shell; make test)

%.test: %
	./$<

.PHONY : clean
clean:
	(cd shell; make clean)
	find . -type f -executable -print0 | xargs -0 rm -f --
