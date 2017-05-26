#
# makefile
#
CC = gcc
CFLAGS = -m64 -pthread

all:
	$(CC) $(CFLAGS) main.c sbuf.c tiny.c ../csapp.c -o main

test:

.PHONY : clean
clean:
	find . -type f -executable -print0 | xargs -0 rm -f --

# vim:ft=make
#
