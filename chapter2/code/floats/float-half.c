/*
 * float-half.c
 */
#include <stdio.h>
#include <assert.h>
#include "float-half.h"

float_bits float_half(float_bits f) {
  unsigned sig = f >> 31;
  unsigned rest = f & 0x7FFFFFFF;
  unsigned exp = f >> 23 & 0xFF;
  unsigned frac = f & 0x7FFFFF;

  int is_NAN_or_oo = (exp == 0xFF);
  if (is_NAN_or_oo) {
    return f;
  }

  /*
   * round to even, we care about last 2 bits of frac
   *
   * 00 => 0 just >>1
   * 01 => 0 (round to even) just >>1
   * 10 => 1 just >>1
   * 11 => 1 + 1 (round to even) just >>1 and plus 1
   */
  int addition = (frac & 0x3) == 0x3;

  if (exp == 0) {
    /* Denormalized */
    frac >>= 1;
    frac += addition;
  } else if (exp == 1) {
    /* Normalized to denormalized */
    rest >>= 1;
    rest += addition;
    exp = rest >> 23 & 0xFF;
    frac = rest & 0x7FFFFF;
  } else {
    /* Normalized */
    exp -= 1;
  }

  return sig << 31 | exp << 23 | frac;
}

