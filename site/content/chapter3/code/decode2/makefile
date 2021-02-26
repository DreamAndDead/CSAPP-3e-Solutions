all:
	gcc -c -m64 decode2.s -o decode2.o
	gcc -m64 main.c decode.c decode2.o -o main

test:
	./main

.PHONY: clean
clean:
	rm main
