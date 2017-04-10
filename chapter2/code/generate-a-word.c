#include <stdio.h>

int main(int argc, char* argv[]) {
  size_t mask = 0xff;
  size_t x = 0x89ABCDEF;
  size_t y = 0x76543210;

  size_t res = (x & mask) | (y & ~mask);
  printf("%zX", res);

  return 0;
}
