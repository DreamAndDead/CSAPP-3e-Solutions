/*
 * 2.82.c
 */
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include "lib/random.h"

/* broken when x is INT_MIN */
int A(int x, int y) {
  return (x < y) == (-x > -y);
}

/*
 * correct
 *
 * ((x + y) << 4) + y - x
 *   =>
 * x << 4 - x + y << 4 + y
 *   =>
 * x*16 - x + y*16 + y
 *   whether overflow or not, =>
 * x*15 + y*17
 */
int B(int x, int y) {
  return ((x + y) << 4) + y - x == 17 * y + 15 * x;
}

/*
 * correct
 *
 * ~x + ~y + 1
 *   =>
 * ~x + 1 + ~y + 1 - 1
 *   =>
 * -x + -y - 1
 *   =>
 * -(x + y) - 1
 *   =>
 * ~(x + y) + 1 - 1
 *   =>
 * ~(x + y)
 */
int C(int x, int y) {
  return ~x + ~y + 1 == ~(x + y);
}

/*
 * correct
 *
 * (ux - uy) == -(unsigned) (y - x)
 *   =>
 * -(ux - uy) == (unsigned) (y - x)
 *   =>
 * (ux - uy) == (unsigned) (x - y)
 */
int D(int x, int y) {
  unsigned ux = (unsigned) x;
  unsigned uy = (unsigned) y;

  return (ux - uy) == -(unsigned) (y - x);
}

/*
 * correct
 *
 * x >> 2 << 2
 *   =>
 * x & ~0x3
 *   =>
 * x - num(00/01/10/11)
 *   =>
 * ((x >> 2) << 2) <= x
 */
int E(int x, int y) {
  return ((x >> 2) << 2) <= x;
}

int main(int argc, char* argv[]) {
  init_seed();
  int x = random_int();
  int y = random_int();

  assert(!A(INT_MIN, 0));
  assert(B(x, y));
  assert(C(x, y));
  assert(D(x, y));
  assert(E(x, y));
  return 0;
}


