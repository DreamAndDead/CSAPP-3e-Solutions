# Optimizing Program Performance

5.1 - 5.12 visit book

5.13 - 5.19 visit here

## test

code directory: `./code`

test way:

- assert means assert function from `<assert.h>`
- output means to watch code output to judge if it works right

|solution|code file|test way|
|:------:|:-------:|:------:|
|5.13|5.13.c|assert|
|5.14|5.14.c|assert|
|5.15|5.15.c|assert|
|5.16|5.16.c|assert|
|5.17|5.17.c|assert|
|5.18|5.18.c|assert|
|5.19|5.19.c|assert|

## prof

**prerequisite**

- google [gperftools](https://github.com/gperftools/gperftools)

to 5.18 & 5.19, you can measure its performance.

    (cd chapter5/code; make 5.18.prof)
    (cd chapter5/code; make 5.18.prof)
