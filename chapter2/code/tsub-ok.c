/*
 * tsub-ok.c
 */
#include <stdio.h>
#include <assert.h>
#include <limits.h>

/* Determine whether arguments can be substracted without overflow */
int tsub_ok(int x, int y) {
  if (y == INT_MIN) {
    return 0;
  }

  int neg_y = -y;
  int sum = x + neg_y;
  int pos_over = x > 0 && neg_y > 0 && sum < 0;
  int neg_over = x < 0 && neg_y < 0 && sum >= 0;

  return !(pos_over || neg_over);
}

int main(int argc, char* argv[]) {
  assert(!tsub_ok(0x00, INT_MIN));
  assert(tsub_ok(0x00, 0x00));
  return 0;
}


