#include <limits.h>
#include <stdlib.h>
#include <utest.h>

UTEST_CASE(div)
{
    div_t r;

    r = div(7, 3);
    EXPECT_EQ_INT(r.quot, 2);
    EXPECT_EQ_INT(r.rem, 1);
    EXPECT_EQ_INT(r.quot * 3 + r.rem, 7);

    r = div(-7, 3);
    EXPECT_EQ_INT(r.quot, -2);
    EXPECT_EQ_INT(r.rem, -1);
    EXPECT_EQ_INT(r.quot * 3 + r.rem, -7);

    r = div(7, -3);
    EXPECT_EQ_INT(r.quot, -2);
    EXPECT_EQ_INT(r.rem, 1);
    EXPECT_EQ_INT(r.quot * (-3) + r.rem, 7);

    r = div(-7, -3);
    EXPECT_EQ_INT(r.quot, 2);
    EXPECT_EQ_INT(r.rem, -1);
    EXPECT_EQ_INT(r.quot * (-3) + r.rem, -7);

    r = div(6, 3);
    EXPECT_EQ_INT(r.quot, 2);
    EXPECT_EQ_INT(r.rem, 0);

    r = div(0, 5);
    EXPECT_EQ_INT(r.quot, 0);
    EXPECT_EQ_INT(r.rem, 0);

    r = div(INT_MAX, 1);
    EXPECT_EQ_INT(r.quot, INT_MAX);
    EXPECT_EQ_INT(r.rem, 0);

    r = div(INT_MAX, INT_MAX);
    EXPECT_EQ_INT(r.quot, 1);
    EXPECT_EQ_INT(r.rem, 0);

    r = div(-INT_MAX, INT_MAX);
    EXPECT_EQ_INT(r.quot, -1);
    EXPECT_EQ_INT(r.rem, 0);
}
