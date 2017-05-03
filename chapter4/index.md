# Processor Architecture

## yas simulation

this chapter focus on processor architecture and design a little simple
processor and yas assemble language designed running on it. we can access the
processor simulation code and simulation manual from csapp official site.

[download simulation code][code]

[download manual][manual]

I have store the simulation code in chapter4/code/sim directory. you should read
the manual and README in code to know how it works and how to test yas code.

## test

type:
- output: watch output to see if it's same with imaganation
- yas: run sim script to see if "processor" works fine

|solution|type|run|
|-|-|-|
|4.45|--|--|
|4.46|--|--|
|4.47|output|(cd chapter4/code/bubble-sort; make testA && make testB)|
|4.48|output|(cd chapter4/code/bubble-sort; make test4.48)|
|4.49|output|(cd chapter4/code/bubble-sort; make test4.49)|
|4.50|output|(cd chapter4/code/switch; make test)|
|4.51|--|--|
|4.52|yas|(cd chapter4/code/iaddq-seq; make test)|
|4.53|yas|(cd chapter4/code/pipe-stall; make test)|
|4.54|yas|(cd chapter4/code/iaddq-pipe; make test)|
|4.55|yas|(cd chapter4/code/pipe-nt; make test)|
|4.56|yas|(cd chapter4/code/pipe-btfnt; make test)|
|4.57|yas|(cd chapter4/code/pipe-lf; make test)|
|4.58|yas|(cd chapter4/code/pipe-1w; make test)|
|4.59|--|--|
