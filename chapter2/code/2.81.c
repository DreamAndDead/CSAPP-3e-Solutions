/*
 * 2.81.c
 */
#include <stdio.h>
#include <assert.h>

/* Assume 0 <= k < w */
int A(int k) {
  return -1 << k;
}

/* Assume 0 <= j,k < w */
int B(int k, int j) {
  return ~A(k) << j;
}

int main(int argc, char* argv[]) {
  assert(A(8) == 0xFFFFFF00);
  assert(B(16, 8) == 0x00FFFF00);
  return 0;
}


