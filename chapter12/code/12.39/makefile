#
# makefile
#
CC = gcc
CFLAGS = -m64 -pthread

all:
	$(CC) $(CFLAGS) proxy.c ../csapp.c -o proxy
	$(CC) $(CFLAGS) proxy-thread.c ../csapp.c -o proxy-thread

# vim:ft=make
#
