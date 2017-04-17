/*
 * main.c
 */
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <criterion/criterion.h>
#include "float-negate.h"
#include "float-absval.h"
#include "float-twice.h"
#include "float-half.h"
#include "float-f2i.h"
#include "float-i2f.h"

unsigned f2u(float f) {
  return *(unsigned*) &f;
}

float u2f(unsigned u) {
  return *(float*) &u;
}

void test(unsigned n) {
  float f = u2f(n);

  if (isnan(f)) {
    assert(float_negate(n) == n);
    assert(float_absval(n) == n);
    assert(float_twice(n) == n);
    assert(float_half(n) == n);
    assert(float_f2i(n) == 0x80000000);
  } else {
    assert(u2f(float_negate(n)) == -f);
    assert(u2f(float_absval(n)) == fabsf(f));
    assert(u2f(float_twice(n)) == f * 2.0);
    assert(u2f(float_half(n)) == f * 0.5);
    if (f > (float)INT_MAX || f < (float)INT_MIN) {
      assert(float_f2i(n) == 0x80000000);
    } else {
      assert(float_f2i(n) == (int)f);
    }
    assert(u2f(float_i2f(n)) == (float)n);
  }
}

void test_suite(void) {
  for (unsigned n = 0; n < 0xFFFFFFFF; n++) {
    printf("processing: 0x%.8x\n", n);

    test(n);
  }
  test(0xFFFFFFFF);
}

Test(simple, test) {
  cr_assert(0, "hello world");
}
