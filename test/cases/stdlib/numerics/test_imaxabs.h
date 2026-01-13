#include <utest.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#ifdef __GNUC__
#include <inttypes.h>
#endif

UTEST_TEST_CASE(imaxabs){
    EXPECT_EQUAL_INT(imaxabs(0), 0);
    EXPECT_EQUAL_INT(imaxabs(1), 1);
    EXPECT_EQUAL_INT(imaxabs(-1), 1);
    EXPECT_EQUAL_INT(imaxabs(123), 123);
    EXPECT_EQUAL_INT(imaxabs(-123), 123);
    EXPECT_EQUAL_INT(imaxabs(456789), 456789);
    EXPECT_EQUAL_INT(imaxabs(-456789), 456789);
    EXPECT_EQUAL_INT(imaxabs(1000), 1000);
    EXPECT_EQUAL_INT(imaxabs(-1000), 1000);
    EXPECT_EQUAL_INT(imaxabs(32767), 32767);
    EXPECT_EQUAL_INT(imaxabs(-32767), 32767);
    EXPECT_EQUAL_INT(imaxabs(2147483647), 2147483647);
    EXPECT_EQUAL_INT(imaxabs(-2147483647), 2147483647);
    EXPECT_EQUAL_INT(imaxabs(INTMAX_MAX), INTMAX_MAX);
    EXPECT_EQUAL_INT(imaxabs(-INTMAX_MAX), INTMAX_MAX);
    {
        intmax_t val = 42;
        EXPECT_EQUAL_INT(imaxabs(val), 42);
        val = -42;
        EXPECT_EQUAL_INT(imaxabs(val), 42);
    }
    {
        intmax_t val = 0;
        EXPECT_EQUAL_INT(imaxabs(val), 0);
    }
    {
        intmax_t val = 1;
        EXPECT_EQUAL_INT(imaxabs(val), 1);
        EXPECT_EQUAL_INT(imaxabs(-val), 1);
    }
    {
        intmax_t val = 999;
        EXPECT_EQUAL_INT(imaxabs(val), 999);
        EXPECT_EQUAL_INT(imaxabs(-val), 999);
    }
    {
        intmax_t val = 10000;
        EXPECT_EQUAL_INT(imaxabs(val), 10000);
        EXPECT_EQUAL_INT(imaxabs(-val), 10000);
    }
    {
        intmax_t val = 50000;
        EXPECT_EQUAL_INT(imaxabs(val), 50000);
        EXPECT_EQUAL_INT(imaxabs(-val), 50000);
    }
    {
        intmax_t val = 100000;
        EXPECT_EQUAL_INT(imaxabs(val), 100000);
        EXPECT_EQUAL_INT(imaxabs(-val), 100000);
    }
    {
        intmax_t val = 1000000;
        EXPECT_EQUAL_INT(imaxabs(val), 1000000);
        EXPECT_EQUAL_INT(imaxabs(-val), 1000000);
    }
    {
        intmax_t val = 2000000000;
        EXPECT_EQUAL_INT(imaxabs(val), 2000000000);
        EXPECT_EQUAL_INT(imaxabs(-val), 2000000000);
    }
    {
        intmax_t val = 9000000000;
        EXPECT_EQUAL_INT(imaxabs(val), 9000000000);
        EXPECT_EQUAL_INT(imaxabs(-val), 9000000000);
    }
    {
        intmax_t val = 5000000000000;
        EXPECT_EQUAL_INT(imaxabs(val), 5000000000000);
        EXPECT_EQUAL_INT(imaxabs(-val), 5000000000000);
    }
    {
        intmax_t val = 9000000000000000000;
        EXPECT_EQUAL_INT(imaxabs(val), 9000000000000000000);
        EXPECT_EQUAL_INT(imaxabs(-val), 9000000000000000000);
    }
}
