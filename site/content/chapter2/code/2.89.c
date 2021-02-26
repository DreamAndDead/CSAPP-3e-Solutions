/*
 * 2.89.c
 */
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include "lib/random.h"

/*
 * most important thing is that all double number come from ints
 */

/* right */
int A(int x, double dx) {
  return (float)x == (float)dx;
}

/* wrong when y is INT_MIN */
int B(int x, double dx, int y, double dy) {
  return dx-dy == (double)(x-y);
}

/* right */
int C(double dx, double dy, double dz) {
  return (dx+dy)+dz == dx+(dy+dz);
}

/*
 * wrong
 *
 * FIXME I don't know what conditions cause false
 */
int D(double dx, double dy, double dz) {
  return (dx*dy)*dz == dx*(dy*dz);
}

/* wrong when dx != 0 and dz == 0 */
int E(double dx, double dz) {
  return dx/dx == dz/dz;
}

int main(int argc, char* argv[]) {
  init_seed();

  int x = random_int();
  int y = random_int();
  int z = random_int();
  double dx = (double)x;
  double dy = (double)y;
  double dz = (double)z;

  printf("%x %x %x\n", x, y, z);

  assert(A(x, dx));
  assert(!B(0, (double)(int)0, INT_MIN, (double)(int)INT_MIN));
  assert(C(dx, dy, dz));
  /* magic number, brute force attack */
  assert(!D((double)(int)0x64e73387, (double)(int)0xd31cb264, (double)(int)0xd22f1fcd));
  assert(!E(dx, (double)(int)0));
  return 0;
}

