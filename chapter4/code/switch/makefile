#
# makefile
#
YAS = ../sim/misc/yas
YIS = ../sim/misc/yis
SEQ_DIR = ../sim/seq/
YO_FILE = ../../switch/switch.yo

all:
	gcc switch.c -o main
	$(YAS) switch.ys

test:
	./main
	$(YIS) switch.yo

debug:
	(cd $(SEQ_DIR); ./ssim -g $(YO_FILE))

.PHONY: clean
clean:
	rm main *.yo

# vim:ft=make
#
