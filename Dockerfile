FROM ubuntu:16.04
MAINTAINER DreamAndDead <favorofife@yeah.net>

RUN apt-get update \
    && apt-get install -y --no-install-recommends make gcc \
    tcl8.5-dev tk8.5-dev flex bison nodejs nodejs-legacy npm calibre \
    && npm install -g gitbook-cli \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

RUN umask 0000; mkdir /gitbook
ENV HOME=/gitbook
VOLUME /gitbook

VOLUME /src
WORKDIR /src
