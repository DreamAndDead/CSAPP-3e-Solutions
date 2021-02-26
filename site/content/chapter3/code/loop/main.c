/*
 * main.c
 */
#include <assert.h>

extern long loop(long x, int n);
extern long loop2(long x, int n);

int main(int argc, char* argv[]) {
  long x = 0xABCD1234;
  assert(loop(x, 3) == loop2(x, 3));
  return 0;
}


