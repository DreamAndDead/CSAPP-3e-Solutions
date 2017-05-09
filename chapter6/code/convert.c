/*
 * convert.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define LOOP 1000
#define MAX  1024
#define LEN  MAX*MAX
#define BLOCK 16

void convert(int* src, int N) {
  int i, j;

  for (i = 0; i <= N-1; i++)
    for (j = 0; j <= N-1; j++)
      src[j*N+i] = src[i*N+j] || src[j*N+i];
}

void effective_convert(int* src, int N) {
  int i, j, a, b, tmp;

  for (i = 0; i <= N-BLOCK; i+=BLOCK)
    /* not j = 0 here */
    for (j = i; j <= N-BLOCK; j+=BLOCK)
      for (a = i; a < i+BLOCK; a++)
        for (b = j; b < j+BLOCK; b++) {
          /* store two value in one loop */
          tmp = src[b*N+a] || src[a*N+b];
          src[b*N+a] = tmp;
          src[a*N+b] = tmp;
        }

  for (; i <= N-1; i++)
    for (; j <= N-1; j++)
      src[j*N+i] = src[i*N+j] || src[j*N+i];
}

void test(void) {
  int* s = (int*)malloc(sizeof(int)*LEN);
  int* e = (int*)malloc(sizeof(int)*LEN);

  convert(s, MAX);
  effective_convert(e, MAX);

  for (int i = 0; i < MAX; i++)
    for (int j = 0; j < MAX; j++)
      assert(s[i*MAX+j] == e[i*MAX+j]);

  free((void*)s);
  free((void*)e);
}

void prof(void) {
  int* s = (int*)malloc(sizeof(int)*LEN);

  for (int c = 0; c < LOOP; c++)
    convert(s, MAX);

  free((void*)s);
}

void prof_effect(void) {
  int* s = (int*)malloc(sizeof(int)*LEN);

  for (int c = 0; c < LOOP; c++)
    effective_convert(s, MAX);

  free((void*)s);
}

int main(int argc, char* argv[]) {
  /*test();*/

  /*prof();*/

  prof_effect();

  return 0;
}


