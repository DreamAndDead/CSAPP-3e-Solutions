/*
 * tsub-ok.c
 */
#include <stdio.h>
#include <assert.h>
#include <limits.h>

/* Determine whether arguments can be substracted without overflow */
int tsub_ok(int x, int y)
{
    int res = 1;
    int sub = x - y;
    int sign_mask = INT_MIN;
    /*
     * if x >= 0, y < 0 and res < 0, it's a positive overflow
     * if x < 0, y > 0 and res > 0, it's a negetive overflow
     */
    int pos_over = !(x & sign_mask) && (y & sign_mask)
        && (sub & sign_mask);
    int neg_over = (x & sign_mask) && !(y & sign_mask)
        && !(sub & sign_mask);

    res = res && !(pos_over || neg_over);

    return res;
}

int main(int argc, char* argv[]) {
  assert(!tsub_ok(0x00, INT_MIN));
  assert(tsub_ok(0x00, 0x00));
  return 0;
}


