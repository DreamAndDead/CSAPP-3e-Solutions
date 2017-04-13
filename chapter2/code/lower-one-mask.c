/*
 * lower-one-mask.c
 */
#include <stdio.h>
#include <assert.h>

/*
 * Mask with least signficant n bits set to 1
 * Example: n = 6 -> 0x3F, n = 17 -> 0x1FFFF
 * Assume 1 <= n <= w
 */
int lower_one_mask(int n) {
  int w = sizeof(int) << 3;
  return (unsigned) -1 >> (w - n);
}

int main(int argc, char* argv[]) {
  assert(lower_one_mask(6) == 0x3F);
  assert(lower_one_mask(17) == 0x1FFFF);
  assert(lower_one_mask(32) == 0xFFFFFFFF);
  return 0;
}


