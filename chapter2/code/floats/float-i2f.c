/*
 * float-i2f.c
 */
#include <stdio.h>
#include <assert.h>
#include "float-i2f.h"

/*
 * Assume i > 0
 * calculate i's bit length
 *
 * e.g.
 * 0x3 => 2
 * 0xFF => 8
 * 0x80 => 8
 */
int bits_length(int i) {
  int length = 0;
  while (i >= (1<<length)) {
    length++;
  }
  return length;
}

/*
 * generate mask
 * 00000...(32-l) 11111....(l)
 *
 * e.g.
 * 3  => 0x00000007
 * 16 => 0x0000FFFF
 */
unsigned bits_mask(int l) {
  return (unsigned) -1 >> (32-l);
}

/*
 * Compute (float) i
 */
float_bits float_i2f(int i) {
  unsigned sig, exp, frac, rest;
  unsigned bits, fbits;
  unsigned bias = 0x7F;

  if (i == 0) {
    sig = 0;
    exp = 0;
    frac = 0;
    return sig << 31 | exp << 23 | frac;
  }
  if (i == INT_MIN) {
    sig = 1;
    exp = bias + 31;
    frac = 0;
    return sig << 31 | exp << 23 | frac;
  }

  sig = 0;
  /* 2's complatation */
  if (i < 0) {
    sig = 1;
    i = -i;
  }

  bits = bits_length(i);
  fbits = bits - 1;
  exp = bias + fbits;

  rest = i & bits_mask(fbits);
  if (fbits < 23) {
    frac = rest << (23 - fbits);
  } else {
    frac = rest >> (fbits - 23);
  }

  return sig << 31 | exp << 23 | frac;
}
