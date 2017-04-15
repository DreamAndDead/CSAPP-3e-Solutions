/*
 * 2.77.c
 */
#include <stdio.h>
#include <assert.h>

/* K = 17 */
int A(int x) {
  return (x << 4) + x;
}

/* K = -7 */
int B(int x) {
  return x - (x << 3);
}

/* K = 60 */
int C(int x) {
  return (x << 6) - (x << 2);
}

/* K = -112 */
int D(int x) {
  return (x << 4) - (x << 7);
}

int main(int argc, char* argv[]) {
  int x = 0x87654321;
  assert(A(x) == 17 * x);
  assert(B(x) == -7 * x);
  assert(C(x) == 60 * x);
  assert(D(x) == -112 * x);
  return 0;
}

