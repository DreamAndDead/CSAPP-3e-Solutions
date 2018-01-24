/*
 * main.c
 */
#include <stdio.h>
#include <assert.h>

#define NR(n) n*3
#define NC(n) n*4+1

long Array[6][9] = {
  { 0, 1, 2, 3, 4, 5, 6, 7, 8 },
  { 0, 1, 2, 3, 4, 5, 6, 7, 8 },
  { 0, 1, 2, 3, 4, 5, 6, 7, 8 },
  { 0, 1, 2, 3, 4, 5, 6, 7, 8 },
  { 0, 1, 2, 3, 4, 5, 6, 7, 8 },
  { 0, 1, 2, 3, 4, 5, 6, 7, 8 }
};
extern long sum_col(long n, long A[NR(n)][NC(n)], long  j);
extern long sum_col2(long n, long A[NR(n)][NC(n)], long  j);

int main(int argc, char* argv[]) {
  assert(sum_col(1, Array, 0) == sum_col2(1, Array, 0));
  assert(sum_col(1, Array, 4) == sum_col2(1, Array, 4));

  assert(sum_col(2, Array, 0) == sum_col2(2, Array, 0));
  assert(sum_col(2, Array, 2) == sum_col2(2, Array, 2));
  assert(sum_col(2, Array, 3) == sum_col2(2, Array, 3));
  assert(sum_col(2, Array, 8) == sum_col2(2, Array, 8));
  return 0;
}


