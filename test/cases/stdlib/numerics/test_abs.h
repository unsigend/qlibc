#include <utest.h>
#include <stdlib.h>
#include <limits.h>

UTEST_TEST_CASE(abs){
    EXPECT_EQUAL_INT(abs(0), 0);
    EXPECT_EQUAL_INT(abs(1), 1);
    EXPECT_EQUAL_INT(abs(-1), 1);
    EXPECT_EQUAL_INT(abs(123), 123);
    EXPECT_EQUAL_INT(abs(-123), 123);
    EXPECT_EQUAL_INT(abs(456789), 456789);
    EXPECT_EQUAL_INT(abs(-456789), 456789);
    EXPECT_EQUAL_INT(abs(1000), 1000);
    EXPECT_EQUAL_INT(abs(-1000), 1000);
    EXPECT_EQUAL_INT(abs(32767), 32767);
    EXPECT_EQUAL_INT(abs(-32767), 32767);
    EXPECT_EQUAL_INT(abs(INT_MAX), INT_MAX);
    EXPECT_EQUAL_INT(abs(-INT_MAX), INT_MAX);
    EXPECT_EQUAL_INT(abs(2147483647), 2147483647);
    EXPECT_EQUAL_INT(abs(-2147483647), 2147483647);
    {
        int val = 42;
        EXPECT_EQUAL_INT(abs(val), 42);
        val = -42;
        EXPECT_EQUAL_INT(abs(val), 42);
    }
    {
        int val = 0;
        EXPECT_EQUAL_INT(abs(val), 0);
    }
    {
        int val = 1;
        EXPECT_EQUAL_INT(abs(val), 1);
        EXPECT_EQUAL_INT(abs(-val), 1);
    }
    {
        int val = 999;
        EXPECT_EQUAL_INT(abs(val), 999);
        EXPECT_EQUAL_INT(abs(-val), 999);
    }
    {
        int val = 10000;
        EXPECT_EQUAL_INT(abs(val), 10000);
        EXPECT_EQUAL_INT(abs(-val), 10000);
    }
    {
        int val = 50000;
        EXPECT_EQUAL_INT(abs(val), 50000);
        EXPECT_EQUAL_INT(abs(-val), 50000);
    }
    {
        int val = 100000;
        EXPECT_EQUAL_INT(abs(val), 100000);
        EXPECT_EQUAL_INT(abs(-val), 100000);
    }
    {
        int val = 1000000;
        EXPECT_EQUAL_INT(abs(val), 1000000);
        EXPECT_EQUAL_INT(abs(-val), 1000000);
    }
    {
        int val = 2000000000;
        EXPECT_EQUAL_INT(abs(val), 2000000000);
        EXPECT_EQUAL_INT(abs(-val), 2000000000);
    }
}
