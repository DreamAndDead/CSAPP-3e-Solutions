/*
 * 3.72.c
 */

#include <alloca.h>

long aframe(long n, long idx, long *q) {
  long i;
  long **p = alloca(n * sizeof(long*));
  p[0] = &i;
  for (i = 1; i < n; i++) {
    p[i] = q;
  }
  return *p[idx];
}
