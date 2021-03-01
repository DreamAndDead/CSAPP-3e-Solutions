/*
 * float-negate.c
 */
#include <stdio.h>
#include <assert.h>
#include "float-negate.h"

float_bits float_negate(float_bits f) {
  unsigned sig = f >> 31;
  unsigned exp = f >> 23 & 0xFF;
  unsigned frac = f & 0x7FFFFF;

  int is_NAN = (exp == 0xFF) && (frac != 0);
  if (is_NAN) {
    return f;
  }

  return ~sig << 31 | exp << 23 | frac;
}



