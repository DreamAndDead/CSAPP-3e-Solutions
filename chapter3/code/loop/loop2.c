/*
 * loop2.c
 */

long loop2(long x, int n) {
  long result = 0;
  long mask;
  for (mask = 1; mask != 0; mask <<= n) {
    result |= (x & mask);
  }
  return result;
}
