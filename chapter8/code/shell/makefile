#
# makefile
#

CFLAGS = -pthread -m64 -g
CSAPP = ../csapp.c

all:
	gcc main.c shell.c job.c $(CSAPP) $(CFLAGS) -o shell
	gcc loop.c $(CSAPP) $(CFLAGS) -o loop
	gcc sleep.c $(CSAPP) $(CFLAGS) -o sleep

# vim:ft=make
#
