/*
 * main.c
 */
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "float-negate.h"

unsigned f2u(float f) {
  return *(unsigned*) &f;
}

float u2f(unsigned u) {
  return *(float*) &u;
}

void test(int n) {
  float f = u2f(n);

  if (isnan(f)) {
    assert(float_negate(n) == n);
  } else {
    assert(u2f(float_negate(n)) == -f);
  }
}

void test_suite(void) {
  for (unsigned n = 0; n < 0xFFFFFFFF; n++) {
    if (n % 0x10000000 != 0) {
      continue;
    }
    printf("processing: %x\n", n);

    test(n);
  }
  test(0xFFFFFFFF);
}

int main(int argc, char* argv[]) {
  test_suite();
  return 0;
}

