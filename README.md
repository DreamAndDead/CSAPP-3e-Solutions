# CSAPP-3e-Solutions

**Computer Systems: A Programmer's Perspective Third Edition Solutions**

![csapp3e-cover](./assets/csapp3e-cover.jpg)

## at first

Almost all solutions has its own code piece in c/gas/yas and every code piece
is tested!

Code files are classified by chapter. Please visit the index page of every chapter to see more info.

## issues

> Hurry makes faulty work and no improvement makes it disappointed.

Thanks every improvement makes the project better.

|issue|from |by|status|
|-----|-----|--|------|
|solution 2.84 seems to have a problem|[github issue#1](https://github.com/DreamAndDead/CSAPP-3e-Solutions/issues/1)|[littlecoke](https://github.com/littlecoke)|open|
|Problem 3.66|[github issue#5](https://github.com/DreamAndDead/CSAPP-3e-Solutions/issues/5)|[gonglinyuan](https://github.com/gonglinyuan**|open|


## build

### prerequisite
- x64 linux system
- docker

pull env image

    sudo docker pull dreamanddead/csapp-3e-solutions

### code

clone code

    git clone https://github.com/DreamAndDead/CSAPP-3e-Solutions.git
    cd CSAPP-3e-Solutions

compile

    make

test

    make test

clean

    make clean

### gitbook

**must** install gitbook plugins first before other gitbook actions

    make plugin

serve book in http://localhost:4000

    make serve

generate site in ./_book/

    make html

generate E-books in ./

    make pdf
    make mobi
    make epub

## feedback

If you encounter some problem, you can [email me][gmail] or comment on disqus
in specific solution page

[gmail]: mailto:aquairain@gmail.com

## license

GPLv3

## at last

I'll be :) if this little book helps you and make your life more convenient.

Long Live Open Source.
