/*
 * transpose.c
 */
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// a large prime number
#define MATRIX_N 9973
#define MEM_SIZE (sizeof(int) * MATRIX_N * MATRIX_N)
#define LOOP 1000
#define BLOCK 16

void randomize(void *mem, size_t size) {
  int rnd = open("/dev/urandom", O_RDONLY);
  read(rnd, mem, size);
  close(rnd);
}

void transpose(int *dst, int *src, int N) {
  int i, j;

  for (i = 0; i <= N - 1; i++)
    for (j = 0; j <= N - 1; j++)
      dst[j * N + i] = src[i * N + j];
}

void effective_transpose(int *dst, int *src, int N) {
  int i, j, a, b;

  for (i = 0; i <= N - BLOCK; i += BLOCK)
    for (j = 0; j <= N - BLOCK; j += BLOCK)
      for (a = i; a < i + BLOCK; a++)
        for (b = j; b < j + BLOCK; b++)
          dst[b * N + a] = src[a * N + b];

  int offset = i;

  for (i = offset; i <= N - 1; i++)
    for (j = 0; j < offset; j += BLOCK)
      for (b = j; b < j + BLOCK; b++)
          dst[b * N + i] = src[i * N + b];

  for (i = 0; i <= N - 1; i++)
    for (j = offset; j <= N - 1; j++)
      dst[j * N + i] = src[i * N + j];
}

void test(void) {
  int *d = (int *)malloc(MEM_SIZE);
  int *s = (int *)malloc(MEM_SIZE);
  randomize((void *)s, MEM_SIZE);

  transpose(d, s, MATRIX_N);

  for (int i = 0; i < MATRIX_N; i++)
    for (int j = 0; j < MATRIX_N; j++)
      assert(s[i * MATRIX_N + j] == d[j * MATRIX_N + i]);

  memset(d, 0, MEM_SIZE);
  effective_transpose(d, s, MATRIX_N);

  for (int i = 0; i < MATRIX_N; i++)
    for (int j = 0; j < MATRIX_N; j++)
      assert(s[i * MATRIX_N + j] == d[j * MATRIX_N + i]);

  free((void *)d);
  free((void *)s);
}

void prof(void) {
  int *d = (int *)malloc(MEM_SIZE);
  int *s = (int *)malloc(MEM_SIZE);

  for (int c = 0; c < LOOP; c++) transpose(d, s, MATRIX_N);

  free((void *)d);
  free((void *)s);
}

void prof_effect(void) {
  int *d = (int *)malloc(MEM_SIZE);
  int *s = (int *)malloc(MEM_SIZE);

  for (int c = 0; c < LOOP; c++) effective_transpose(d, s, MATRIX_N);

  free((void *)d);
  free((void *)s);
}

int main(int argc, char *argv[]) {
  test();

  /* prof(); */
  /* prof_effect(); */

  return 0;
}
