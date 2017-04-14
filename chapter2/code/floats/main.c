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

void test_float_negate(void) {
  for (unsigned n = 0; n <= 0xFFFFFFFF; n++) {
    if (n % 0x08000000 == 0) {
      printf("processing: %x\n", n);
    }

    float f = u2f(n);

    if (isnan(f)) {
      assert(float_negate(n) == n);
    } else {
      assert(u2f(float_negate(n)) == -f);
    }

    if (n == 0xFFFFFFFF) {
      break;
    }
  }
}

int main(int argc, char* argv[]) {
  test_float_negate();
  return 0;
}

