/*
 * any-odd-one.c
 */
#include <stdio.h>
#include <assert.h>

int any_odd_one(unsigned x) {
  return !!(0xAAAAAAAA & x);
}

int main(int argc, char* argv[]) {
  assert(any_odd_one(0x2));
  assert(!any_odd_one(0x4));
  return 0;
}


