# Processor Architecture

> **Quote**
> The speed at which modern CPUs perform computations still blows my mind daily.
> 
> by Markus Persson

4.1 - 4.44 visit book

4.45 - 4.59 visit here

## yas simulation

This chapter focus on processor architecture and design a little simple
processor and yas -- a assemble language -- designed running on it.

you can access the
processor simulation code and simulation manual from csapp official site.

[simulation code][code]

[simulator manual][manual]

[code]: http://csapp.cs.cmu.edu/3e/sim.tar
[manual]: http://csapp.cs.cmu.edu/3e/simguide.pdf

I have saved the simulation code in directory chapter4/code/sim.

Highly recommend you read
the manual and README in code to know how it works and how to test yas code.

## test

code directory: `./code`

test way:
- assert means assert function from `<assert.h>`
- output means to watch code output to judge if it works right
- yas means using simulator test script to test simulator itself

|solution|code file|test way|
|:------:|:-------:|:------:|
|4.45|--|--|
|4.46|--|--|
|4.47|bubble-sort/bubble-sort-pointer.*|output, assert|
|4.48|bubble-sort/bubble-sort-pointer-3-cmove.*|output|
|4.49|bubble-sort/bubble-sort-pointer-1-cmove.*|output|
|4.50|switch/*|output|
|4.51|--|--|
|4.52|sim/seq/seq-full.hcl|yas|
|4.53|sim/pipe/pip-stall.hcl|yas|
|4.54|sim/pipe/pip-full.hcl|yas|
|4.55|sim/pipe/pip-nt.hcl|yas|
|4.56|sim/pipe/pip-btfnt.hcl|yas|
|4.57|sim/pipe/pip-lf.hcl|yas|
|4.58|sim/pipe/pip-1w.hcl|yas|
|4.59|--|--|

