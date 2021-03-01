#
# makefile
#
CC = gcc
CFLAGS = -m64 -pthread

all: diff
	$(CC) $(CFLAGS) adder.c ../csapp.c -o adder
	$(CC) $(CFLAGS) form-adder.c ../csapp.c -o form-adder
	$(CC) $(CFLAGS) head-adder.c ../csapp.c -o head-adder
	$(CC) $(CFLAGS) post-adder.c ../csapp.c -o post-adder

diff:
	(diff -u adder.c form-adder.c > form-adder.c.diff; cd .)
	(diff -u adder.c head-adder.c > head-adder.c.diff; cd .)
	(diff -u adder.c post-adder.c > post-adder.c.diff; cd .)

test:

.PHONY: clean
clean:
	find . -type f -executable -print0 | xargs -0 rm -f --

# vim:ft=make
#
