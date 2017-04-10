#include <stdio.h>
#include <assert.h>

unsigned srl(unsigned x, int k) {
  unsigned xsra = (int) x >> k;

  int w = sizeof(int) << 3;
  int mask = (int) -1 << (w - k);
  return xsra & ~mask;
}

int sra(int x, int k) {
  int xsrl = (unsigned) x >> k;

  int w = sizeof(int) << 3;
  int mask = (int) -1 << (w - k);
  if (x < 0) {
    return xsrl | mask;
  }
  return xsrl;
}

int main(int argc, char* argv[]) {
  unsigned test_unsigned = 0x12345678;
  int test_int = 0x12345678;

  assert(srl(test_unsigned, 4) == test_unsigned >> 4);
  assert(sra(test_int, 4) == test_int >> 4);

  return 0;
}
