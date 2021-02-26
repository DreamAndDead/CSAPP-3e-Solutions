/*
 * random.c
 */
#include <stdlib.h>
#include <time.h>
#include "random.h"

void init_seed(void) {
  srand(time(NULL));
}

int random_int(void) {
  int int_bits = sizeof(int) * 8;
  int i;
  int random = 0;
  for (i = 0; i < int_bits; i++) {
    random |= rand()%2;
    random <<= 1;
  }
  return random;
}





