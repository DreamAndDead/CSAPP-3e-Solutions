/*
 * fit-bits.c
 */
#include <stdio.h>
#include <assert.h>

int fits_bits(int x, int n) {
  /*
   * Assume w = 8, n = 3
   * if x > 0
   *   0b00000110 is ok, 0b00001010 is not
   *   first w-n bits must be 0
   * if x < 0
   *   0b11111100 is ok, 0b10111100 is not, and 0b11111000 is not yet
   *   first w-n+1 bits must be 1
   */
  int w = sizeof(int) << 3;
  x >>= n - 1;
  /*
   * !(x >> 1) return 1 only when all bits are 0,
   * !~x == 1 only when all bits are 1
   */
  return !(x >> 1) || !~x;
}

int main(int argc, char* argv[]) {
  assert(fits_bits(0xFF, 8));
  assert(!fits_bits(0xFFFFFF00, 8));
  return 0;
}


