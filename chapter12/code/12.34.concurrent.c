/*
 * 12.34.concurrent.c
 */
#include <stdio.h>
#include "csapp.h"
#include "12.34.h"

int M1[N][M];
int M2[N][M];

int MUL12[N][M];

void *thread_mul(void *vargp) {
  int idx = *(int*)vargp;
  int start = ROWS_PER_THREAD * idx;
  int i, j, k;
  for (i = start; i < start+ROWS_PER_THREAD; i++)
    for (j = 0; j < N; j++) {
      int sum = 0;
      for (k = 0; k < M; k++) {
        sum += M1[i][k] * M2[k][j];
      }
      MUL12[i][j] = sum;
    }
}

void concurrent_mul(void) {
  pthread_t tid[THREAD];
  int param[THREAD];
  int i;

  for (i = 0; i < THREAD; i++) {
    param[i] = i;
    Pthread_create(&tid[i], NULL, thread_mul, &param[i]);
  }
  for (i = 0; i < THREAD; i++) {
    Pthread_join(tid[i], NULL);
  }
}

int main(int argc, char* argv[]) {
  concurrent_mul();
  return 0;
}


