#include <utest.h>
#include <stdlib.h>
#include <limits.h>

UTEST_TEST_CASE(labs){
    EXPECT_EQUAL_INT(labs(0L), 0L);
    EXPECT_EQUAL_INT(labs(1L), 1L);
    EXPECT_EQUAL_INT(labs(-1L), 1L);
    EXPECT_EQUAL_INT(labs(123L), 123L);
    EXPECT_EQUAL_INT(labs(-123L), 123L);
    EXPECT_EQUAL_INT(labs(456789L), 456789L);
    EXPECT_EQUAL_INT(labs(-456789L), 456789L);
    EXPECT_EQUAL_INT(labs(1000L), 1000L);
    EXPECT_EQUAL_INT(labs(-1000L), 1000L);
    EXPECT_EQUAL_INT(labs(32767L), 32767L);
    EXPECT_EQUAL_INT(labs(-32767L), 32767L);
    EXPECT_EQUAL_INT(labs(2147483647L), 2147483647L);
    EXPECT_EQUAL_INT(labs(-2147483647L), 2147483647L);
    EXPECT_EQUAL_INT(labs(LONG_MAX), LONG_MAX);
    EXPECT_EQUAL_INT(labs(-LONG_MAX), LONG_MAX);
    {
        long val = 42L;
        EXPECT_EQUAL_INT(labs(val), 42L);
        val = -42L;
        EXPECT_EQUAL_INT(labs(val), 42L);
    }
    {
        long val = 0L;
        EXPECT_EQUAL_INT(labs(val), 0L);
    }
    {
        long val = 1L;
        EXPECT_EQUAL_INT(labs(val), 1L);
        EXPECT_EQUAL_INT(labs(-val), 1L);
    }
    {
        long val = 999L;
        EXPECT_EQUAL_INT(labs(val), 999L);
        EXPECT_EQUAL_INT(labs(-val), 999L);
    }
    {
        long val = 10000L;
        EXPECT_EQUAL_INT(labs(val), 10000L);
        EXPECT_EQUAL_INT(labs(-val), 10000L);
    }
    {
        long val = 50000L;
        EXPECT_EQUAL_INT(labs(val), 50000L);
        EXPECT_EQUAL_INT(labs(-val), 50000L);
    }
    {
        long val = 100000L;
        EXPECT_EQUAL_INT(labs(val), 100000L);
        EXPECT_EQUAL_INT(labs(-val), 100000L);
    }
    {
        long val = 1000000L;
        EXPECT_EQUAL_INT(labs(val), 1000000L);
        EXPECT_EQUAL_INT(labs(-val), 1000000L);
    }
    {
        long val = 2000000000L;
        EXPECT_EQUAL_INT(labs(val), 2000000000L);
        EXPECT_EQUAL_INT(labs(-val), 2000000000L);
    }
    {
        long val = LONG_MAX - 1;
        EXPECT_EQUAL_INT(labs(val), LONG_MAX - 1);
        EXPECT_EQUAL_INT(labs(-val), LONG_MAX - 1);
    }
}
