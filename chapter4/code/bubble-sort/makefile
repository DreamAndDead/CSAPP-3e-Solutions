#
# makefile
#

YAS = ../sim/misc/yas
YIS = ../sim/misc/yis

all: assemble
	gcc -std=c99 main.c bubble-sort-pointer.c \
		bubble-sort-array.c -o main

assemble:
	gcc -S -Og bubble-sort-pointer.c

pointer:
	$(YAS) bubble-sort-pointer.ys
	$(YIS) bubble-sort-pointer.yo

cmove-3:
	$(YAS) bubble-sort-pointer-3-cmove.ys
	$(YIS) bubble-sort-pointer-3-cmove.yo

cmove-1:
	$(YAS) bubble-sort-pointer-1-cmove.ys
	$(YIS) bubble-sort-pointer-1-cmove.yo

testA:
	./main

testB: pointer

test4.48: cmove-3

test4.49: cmove-1

test: testA testB test4.48 test4.49

.PHONY: clean
clean:
	rm main *.yo

# vim:ft=make
#
