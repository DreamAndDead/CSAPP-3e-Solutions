/*
 * cread-alt.c
 */
#include <stdio.h>
#include <assert.h>

long cread(long *xp) {
  return (xp ? *xp : 0);
}

long cread_alt(long *xp) {
  return (!xp ? 0 : *xp);
}

int main(int argc, char* argv[]) {
  long a = 0;
  assert(cread(&a) == cread_alt(&a));
  assert(cread(NULL) == cread_alt(NULL));
  return 0;
}


