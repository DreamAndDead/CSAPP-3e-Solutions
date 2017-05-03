#
# makefile
#

YAS = ../sim/misc/yas
YIS = ../sim/misc/yis

all: assemble

pointer:
	$(YAS) bubble-sort-pointer.ys
	$(YIS) bubble-sort-pointer.yo

cmove-3:
	$(YAS) bubble-sort-pointer-3-cmove.ys
	$(YIS) bubble-sort-pointer-3-cmove.yo

cmove-1:
	$(YAS) bubble-sort-pointer-1-cmove.ys
	$(YIS) bubble-sort-pointer-1-cmove.yo

assemble:
	gcc -S -Og bubble-sort-pointer.c

test: pointer cmove-3 cmove-1
	gcc -std=c99 main.c bubble-sort-pointer.c \
		bubble-sort-array.c -o main
	./main

# vim:ft=make
#
