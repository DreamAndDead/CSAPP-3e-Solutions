/*
 * sum-col2.c
 */

#define NR(n) n*3
#define NC(n) n*4

long sum_col2(long n, long A[NR(n)][NC(n)], long j) {
  long i;
  long result = 0;
  for (i = 0; i < NR(n); i++) {
    result += A[i][j];
  }
  return result;
}
