/*
 * decode.c
 */
long decode(long x, long y, long z) {
  long tmp = y - z;
  return (tmp * x) ^ (tmp << 63 >> 63);
}
