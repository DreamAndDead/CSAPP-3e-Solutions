#include <stdio.h>
#include <assert.h>

typedef unsigned packet_t;

int xbyte(packet_t word, int bytenum) {
  int max_bytenum = 3;
  return (int) word << ((max_bytenum - bytenum) << 3) >> (max_bytenum << 3);
}

int main(int argc, char* argv[]) {
  assert(xbyte(0x00112233, 0) == 0x33);
  assert(xbyte(0x00112233, 1) == 0x22);
  assert(xbyte(0x00112233, 2) == 0x11);
  assert(xbyte(0x00112233, 3) == 0x00);

  assert(xbyte(0xAABBCCDD, 0) == 0xFFFFFFDD);
  assert(xbyte(0xAABBCCDD, 1) == 0xFFFFFFCC);
  assert(xbyte(0xAABBCCDD, 2) == 0xFFFFFFBB);
  assert(xbyte(0xAABBCCDD, 3) == 0xFFFFFFAA);

  return 0;
}

