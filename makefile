SHELL := /bin/bash

UID=$(shell id -u)
GID=$(shell id -g)
DOCKER_CMD=sudo docker run -it --rm -v ${PWD}:/src -u ${UID}:${GID}
DOCKER_IMAGE=dreamanddead/csapp-3e-solutions:latest

MAKE_ENV=${DOCKER_CMD} ${DOCKER_IMAGE}

all:
	${MAKE_ENV} make -f makefile.code

test:
	${MAKE_ENV} make -f makefile.code test

.PHONY : clean
clean:
	${MAKE_ENV} make -f makefile.code clean

dev-clean:
	make -f makefile.code clean

serve:
	(cd site; hugo server -b http://localhost:1313/CSAPP-3e-Solutions/; cd ..)

