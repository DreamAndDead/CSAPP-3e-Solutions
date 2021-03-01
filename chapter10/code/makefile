#
# makefile
#
CC = gcc
CFLAGS = -m64 -pthread
SRCS = $(wildcard 10.*.c)
PROGS = $(patsubst %.c,%,$(SRCS))

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< csapp.c

test:
	./10.6
	./10.7 < 10.7.c
	./10.8 2
	./10.10 10.10.c

.PHONY : clean
clean:
	find . -type f -executable -print0 | xargs -0 rm -f --
