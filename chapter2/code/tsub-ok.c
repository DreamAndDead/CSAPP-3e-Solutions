/*
 * tsub-ok.c
 */
#include <stdio.h>
#include <limits.h>
#include <assert.h>

int tsub_ok(int x, int y)
{
    int is_ok = 1;

    is_ok &= (y != INT_MIN);

    int sub = x - y;
    int sig_mask = INT_MIN;

    int x_is_neg = x & sig_mask;
    int x_is_pos = !x_is_neg && x != 0;
    int y_is_neg = y & sig_mask;
    int y_is_pos = !y_is_neg && y != 0;
    int sub_is_not_neg = !(sub & sig_mask);
    int sub_is_not_pos = (sub & sig_mask) | sub == 0;

    int pos_over = x_is_pos && y_is_neg && sub_is_not_pos;
    int neg_over = x_is_neg && y_is_pos && sub_is_not_neg;

    is_ok &= !pos_over;
    is_ok &= !neg_over;

    return is_ok;
}

int main()
{

    // y 为 INT_MIN 导致溢出
    int x = 0x12345678;
    int y = INT_MIN;
    printf("tsub_ok(0x%08x, 0x%08x) = %d\n", x, y, tsub_ok(x, y));
    assert(!tsub_ok(x, y));

    // sub 为正溢出
    x = INT_MAX;
    y = INT_MIN + 1;
    printf("tsub_ok(0x%08x, 0x%08x) = %d\n", x, y, tsub_ok(x, y));
    assert(!tsub_ok(x, y));

    // sub 为负溢出
    x = INT_MIN;
    y = INT_MAX;
    printf("tsub_ok(0x%08x, 0x%08x) = %d\n", x, y, tsub_ok(x, y));
    assert(!tsub_ok(x, y));

    // sub is ok
    x = 0x77654321;
    y = 0x12345678;
    printf("tsub_ok(0x%08x, 0x%08x) = %d\n", x, y, tsub_ok(x, y));
    assert(tsub_ok(x, y));

    return 0;
}
