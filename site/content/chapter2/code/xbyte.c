/*
 * xbyte.c
 */
#include <stdio.h>
#include <assert.h>

typedef unsigned packet_t;

int xbyte(packet_t word, int bytenum) {
  /*
   * pay attention when byte we want is negetive
   *
   * Assume sizeof(unsigned) is 4
   * first shift left 8 * (4 - 1 - bytenum)
   * then arthemetic shift right 8 * (4 - 1) reserve signficant bit
   */
  int size = sizeof(unsigned);
  int shift_left_val = (size - 1 - bytenum) << 3;
  int shift_right_val = (size - 1) << 3;
  return (int) word << shift_left_val >> shift_right_val;
}

int main(int argc, char* argv[]) {
  assert(xbyte(0xAABBCCDD, 1) == 0xFFFFFFCC);
  assert(xbyte(0x00112233, 2) == 0x11);
  return 0;
}


