CC = gcc
CFLAGS = -m64 -pthread -DCUS_MALLOC
SRCS = mm.c memlib.c csapp.c

all: origin custom diff

measure:
	time ./origin.main
	time ./custom.main

origin:
	$(CC) -m64 main.c -o origin.main

custom:
	$(CC) $(CFLAGS) $(SRCS) main.c -o custom.main

diff:
	(diff -u ../vm/mm.h mm.h > mm.h.diff; cd .)
	(diff -u ../vm/memlib.c memlib.c > memlib.c.diff; cd .)

