/*
 * main.c
 */
#include <stdio.h>
#include <assert.h>
#include "bubble-sort.h"

int main(int argc, char* argv[]) {
  long data4a[4] = { 1, 4, 3, 2 };
  long data4p[4] = { 4, 2, 1, 3 };
  bubble_a(data4a, 4);
  bubble_p(data4p, 4);

  for (int i = 0; i < 4; i++) {
    assert(data4a[i] == data4p[i]);
  }
  return 0;
}


