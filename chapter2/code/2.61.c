#include <string.h>
#include <criterion/criterion.h>

Test(sample, test) {
    cr_assert(strlen("") == 0);
}
