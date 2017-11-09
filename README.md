# CSAPP-3e-Solutions

**Computer Systems: A Programmer's Perspective Third Edition Solutions**

![csapp3e-cover](./assets/csapp3e-cover.jpg)

## code

github: [DreamAndDead/CSAPP-3e-Solutions](https://github.com/DreamAndDead/CSAPP-3e-Solutions)

Almost all solutions has its own code piece in c/gas/yas and every code piece
is tested!

Code files are classified by chapter. More info visit index page of every chapter.

## serve locally

clone code

    git clone https://github.com/DreamAndDead/CSAPP-3e-Solutions.git
    cd CSAPP-3e-Solutions

install `gitbook-cli`

    npm i -g gitbook-cli

install plugins

    gitbook install

serve

    gitbook serve --no-watch

visit link

    http://localhost:4000

## make

**prerequisite**

- 64bit linux machine, required by `gcc -m64`
- package `tcl8.5-dev` & `tk8.5-dev`, required by chapter4 processor simulator

clone code

    git clone https://github.com/DreamAndDead/CSAPP-3e-Solutions.git
    cd CSAPP-3e-Solutions

compile

    make

test

    make test

clean

    make clean

## generate ebook

**prerequisite**

- ebook-convert, install by `apt install calibre`

generate book

    gitbook pdf ./ ./csapp-3e-solutions.pdf
    gitbook mobi ./ ./csapp-3e-solutions.mobi
    gitbook epub ./ ./csapp-3e-solutions.epub

ref: [gitbook toolchain: ebook](https://toolchain.gitbook.com/ebook.html)


## feedback

If you encounter some problem, you can [email me][gmail] or comment on disqus
in specific solution page:)

[gmail]: mailto:aquairain@gmail.com

## license

GPLv3

## donation

I'll be :) if this little book helps you and make your life more convenient.

Would you like to offer me a cup of coffee for a better life? Whether or not, it's
a choice. Choice means freedom. Freedom is the core of Open Source. Long Live
Open Source.
