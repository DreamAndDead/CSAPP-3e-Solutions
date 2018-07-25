/*
 * unsigned-high-prod.c
 */
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <inttypes.h>

int signed_high_prod(int x, int y)
{
    int64_t mul = (int64_t)x * y;
    int res = mul >> 32;
    return res;
}

unsigned unsigned_high_prod(unsigned x, unsigned y)
{

    unsigned hp = signed_high_prod(x, y);

    int sig_mask = INT_MIN;

    /**
     * 68 页的 (2-18) 中
     * 带有 2^w 权重的项会出现在高 w 位中
     */

    (x & sig_mask) && (hp += y);
    (y & sig_mask) && (hp += x);

    return hp;
}

unsigned unsigned_high_prod_2(unsigned x, unsigned y)
{
    uint64_t mul = (uint64_t)x * y;
    return mul >> 32;
}

int main(int argc, char *argv[])
{
    unsigned x = 0x12345678;
    unsigned y = 0xFFFFFFFF;

    printf("unsigned(%X, %X) = %X\n", x, y, unsigned_high_prod(x, y));
    assert(unsigned_high_prod_2(x, y) == unsigned_high_prod(x, y));

    return 0;
}
