#
# makefile
#

CFLAGS = -pthread -m64
CSAPP = ../csapp.c

all:
	gcc main.c shell.c job.c $(CSAPP) $(CFLAGS) -o shell
	gcc loop.c $(CSAPP) $(CFLAGS) -o loop
	gcc sleep.c $(CSAPP) $(CFLAGS) -o sleep

test:

clean:
	find . -type f -executable -print0 | xargs -0 rm -f --

# vim:ft=make
#
