/*
 * decode2.c
 */
#include <assert.h>

extern long decode(long x, long y, long z);
extern long decode2(long x, long y, long z);

int main(int argc, char* argv[]) {
  assert(decode(1,2,3) == decode2(1,2,3));
  return 0;
}


