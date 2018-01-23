SHELL := /bin/bash

UID=$(shell id -u)
GID=$(shell id -g)
DOCKER_CMD=sudo docker run -it --rm -v ${PWD}:/src -u ${UID}:${GID}
DOCKER_IMAGE=dreamanddead/csapp-3e-solutions:latest
GITBOOK_VOLUME=-v gitbook:/gitbook
GITBOOK_PORT=-p 4000:4000

MAKE_ENV=${DOCKER_CMD} ${DOCKER_IMAGE}
BOOK_ENV=${DOCKER_CMD} ${GITBOOK_VOLUME} ${DOCKER_IMAGE}
BOOK_SERVE_ENV=${DOCKER_CMD} ${GITBOOK_VOLUME} ${GITBOOK_PORT} ${DOCKER_IMAGE}

all:
	${MAKE_ENV} make -f makefile.code

test:
	${MAKE_ENV} make -f makefile.code test

.PHONY : clean
clean:
	${MAKE_ENV} make -f makefile.code clean


plugin:
	${BOOK_ENV} gitbook install

serve:
	${BOOK_SERVE_ENV} gitbook serve --no-watch

html:
	${BOOK_ENV} gitbook build

pdf:
	${BOOK_ENV} gitbook pdf ./ ./csapp-3e-solutions.pdf

mobi:
	${BOOK_ENV} gitbook mobi ./ ./csapp-3e-solutions.mobi

epub:
	${BOOK_ENV} gitbook epub ./ ./csapp-3e-solutions.epub


env:
	${BOOK_ENV} bash
