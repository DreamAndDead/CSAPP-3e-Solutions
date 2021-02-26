/*
 * main.c
 */
#include <stdio.h>
#include <assert.h>

extern long* A;
extern long A2[7][5][13];
extern long store_ele(long i, long j, long k, long* dest);
extern long store_ele2(long i, long j, long k, long* dest);

int main(int argc, char* argv[]) {
  A2[1][2][3] = 242;
  long e1, e2;
  long r1 = store_ele(1,2,3,&e1);
  long r2 = store_ele2(1,2,3,&e2);

  assert(r1 == r2);
  assert(e1 == 121);
  assert(e2 == 242);
  return 0;
}


