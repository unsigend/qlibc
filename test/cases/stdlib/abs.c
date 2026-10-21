#include <limits.h>
#include <stdlib.h>
#include <utest.h>

UTEST_CASE(abs)
{
    EXPECT_EQ_INT(abs(0), 0);
    EXPECT_EQ_INT(abs(1), 1);
    EXPECT_EQ_INT(abs(-1), 1);
    EXPECT_EQ_INT(abs(123), 123);
    EXPECT_EQ_INT(abs(-123), 123);
    EXPECT_EQ_INT(abs(INT_MAX), INT_MAX);
    EXPECT_EQ_INT(abs(-INT_MAX), INT_MAX);
    EXPECT_EQ_INT(abs(42), 42);
    EXPECT_EQ_INT(abs(-42), 42);
    if (INT_MAX >= 2000000000) {
        EXPECT_EQ_INT(abs(2000000000), 2000000000);
        EXPECT_EQ_INT(abs(-2000000000), 2000000000);
    }
}
