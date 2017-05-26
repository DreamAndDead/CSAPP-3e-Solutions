/*
 * main.c
 */
#include <stdio.h>
#include <assert.h>

#define NR(n) n*3
#define NC(n) n*4

long Array[32][32];
extern long sum_col(long n, long A[NR(n)][NC(n)], long  j);
extern long sum_col2(long n, long A[NR(n)][NC(n)], long  j);

int main(int argc, char* argv[]) {
  assert(sum_col(8, Array, 4) == sum_col2(8, Array, 4));
  return 0;
}


