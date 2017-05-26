
CC = gcc
CFLAGS = -m64 -pthread -g
SRCS.9.17 = mm.9.17.c memlib.c csapp.c 9.17.c
SRCS.9.18 = mm.9.18.c memlib.c csapp.c 9.18.c

all: diff
	$(CC) $(CFLAGS) $(SRCS.9.17) -o 9.17
	$(CC) $(CFLAGS) $(SRCS.9.18) -o 9.18

test:
	./9.17
	./9.18

diff:
	(diff -u mm.c mm.9.17.c > mm.9.17.diff; cd .)
	(diff -u mm.c mm.9.18.c > mm.9.18.diff; cd .)

.PHONY: clean
clean:
	find . -type f -executable -print0 | xargs -0 rm -f --
