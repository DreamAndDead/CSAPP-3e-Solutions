/*
 * threeforths.c
 */
#include <stdio.h>
#include <assert.h>
#include <limits.h>

/*
 * calculate 3/4x, no overflow, round to zero
 *
 * no overflow means divide 4 first, then multiple 3, diffrent from 2.79 here
 *
 * rounding to zero is a little complicated.
 * every int x, equals f(first 30 bit number) plus l(last 2 bit number)
 *
 *   f = x & ~0x3
 *   l = x & 0x3
 *   x = f + l
 *   threeforths(x) = f/4*3 + l*3/4
 *
 * f doesn't care about round at all, we just care about rounding from l*3/4
 *
 *   lm3 = (l << 1) + l
 *
 * when x > 0, rounding to zero is easy
 *
 *   lm3d4 = lm3 >> 2
 *
 * when x < 0, rounding to zero acts like divide_power2 in 2.78
 *
 *   bias = 0x3    // (1 << 2) - 1
 *   lm3d4 = (lm3 + bias) >> 2
 */
int threeforths(int x) {
  int is_neg = x & INT_MIN;
  int f = x & ~0x3;
  int l = x & 0x3;

  int fd4 = f >> 2;
  int fd4m3 = (fd4 << 1) + fd4;

  int lm3 = (l << 1) + l;
  int bias = (1 << 2) - 1;
  (is_neg && (lm3 += bias));
  int lm3d4 = lm3 >> 2;

  return fd4m3 + lm3d4;
}

int main(int argc, char* argv[]) {
  assert(threeforths(8) == 6);
  assert(threeforths(9) == 6);
  assert(threeforths(10) == 7);
  assert(threeforths(11) == 8);
  assert(threeforths(12) == 9);

  assert(threeforths(-8) == -6);
  assert(threeforths(-9) == -6);
  assert(threeforths(-10) == -7);
  assert(threeforths(-11) == -8);
  assert(threeforths(-12) == -9);
  return 0;
}


