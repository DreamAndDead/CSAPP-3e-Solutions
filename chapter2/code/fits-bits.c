/*
 * fits-bits.c
 */
#include <stdio.h>
#include <assert.h>

int fits_bits(int x, int n) {
  /*
   * 1 <= n <= w
   *
   * assume w = 8, n = 3
   * if x > 0
   *   0b00000010 is ok, 0b00001010 is not, and 0b00000110 is not yet (thanks itardc@163.com)
   * if x < 0
   *   0b11111100 is ok, 0b10111100 is not, and 0b11111000 is not yet
   *
   * the point is
   *   x << (w-n) >> (w-n) must be equal to x itself.
   *
   */
  int w = sizeof(int) << 3;
  int offset = w - n;
  return (x << offset >> offset) == x;
}

int main(int argc, char* argv[]) {
  assert(!fits_bits(0xFF, 8));
  assert(!fits_bits(~0xFF, 8));

  assert(fits_bits(0b0010, 3));
  assert(!fits_bits(0b1010, 3));
  assert(!fits_bits(0b0110, 3));

  assert(fits_bits(~0b11, 3));
  assert(!fits_bits(~0b01000011, 3));
  assert(!fits_bits(~0b111, 3));
  return 0;
}


