/*
 * unsigned-high-prod.c
 */
#include <stdio.h>
#include <assert.h>
#include <inttypes.h>

int signed_high_prod(int x, int y) {
  int64_t mul = (int64_t) x * y;
  return mul >> 32;
}

unsigned unsigned_high_prod(unsigned x, unsigned y) {
  /* TODO calculations */
  int sig_x = x >> 31;
  int sig_y = y >> 31;
  int signed_prod = signed_high_prod(x, y);
  return signed_prod + x * sig_y + y * sig_x;
}

/* a theorically correct version to test unsigned_high_prod func */
unsigned another_unsigned_high_prod(unsigned x, unsigned y) {
  uint64_t mul = (uint64_t) x * y;
  return mul >> 32;
}

int main(int argc, char* argv[]) {
  unsigned x = 0x12345678;
  unsigned y = 0xFFFFFFFF;

  assert(another_unsigned_high_prod(x, y) == unsigned_high_prod(x, y));
  return 0;
}


