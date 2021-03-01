/*
 * 12.34.non.concurrent.c
 */
#include <stdio.h>
#include "csapp.h"
#include "12.34.h"

int M1[N][M];
int M2[N][M];

int MUL12[N][M];

void non_concurrent_mul(void) {
  int i, j, k;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++) {
      int sum = 0;
      for (k = 0; k < M; k++) {
        sum += M1[i][k] * M2[k][j];
      }
      MUL12[i][j] = sum;
    }
}

int main(int argc, char* argv[]) {
  non_concurrent_mul();
  return 0;
}


