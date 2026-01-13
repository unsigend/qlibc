#include <utest.h>
#include <stdlib.h>
#include <limits.h>

UTEST_TEST_CASE(llabs){
    EXPECT_EQUAL_INT(llabs(0LL), 0LL);
    EXPECT_EQUAL_INT(llabs(1LL), 1LL);
    EXPECT_EQUAL_INT(llabs(-1LL), 1LL);
    EXPECT_EQUAL_INT(llabs(123LL), 123LL);
    EXPECT_EQUAL_INT(llabs(-123LL), 123LL);
    EXPECT_EQUAL_INT(llabs(456789LL), 456789LL);
    EXPECT_EQUAL_INT(llabs(-456789LL), 456789LL);
    EXPECT_EQUAL_INT(llabs(1000LL), 1000LL);
    EXPECT_EQUAL_INT(llabs(-1000LL), 1000LL);
    EXPECT_EQUAL_INT(llabs(32767LL), 32767LL);
    EXPECT_EQUAL_INT(llabs(-32767LL), 32767LL);
    EXPECT_EQUAL_INT(llabs(2147483647LL), 2147483647LL);
    EXPECT_EQUAL_INT(llabs(-2147483647LL), 2147483647LL);
    EXPECT_EQUAL_INT(llabs(9223372036854775807LL), 9223372036854775807LL);
    EXPECT_EQUAL_INT(llabs(-9223372036854775807LL), 9223372036854775807LL);
    EXPECT_EQUAL_INT(llabs(LLONG_MAX), LLONG_MAX);
    EXPECT_EQUAL_INT(llabs(-LLONG_MAX), LLONG_MAX);
    {
        long long val = 42LL;
        EXPECT_EQUAL_INT(llabs(val), 42LL);
        val = -42LL;
        EXPECT_EQUAL_INT(llabs(val), 42LL);
    }
    {
        long long val = 0LL;
        EXPECT_EQUAL_INT(llabs(val), 0LL);
    }
    {
        long long val = 1LL;
        EXPECT_EQUAL_INT(llabs(val), 1LL);
        EXPECT_EQUAL_INT(llabs(-val), 1LL);
    }
    {
        long long val = 999LL;
        EXPECT_EQUAL_INT(llabs(val), 999LL);
        EXPECT_EQUAL_INT(llabs(-val), 999LL);
    }
    {
        long long val = 10000LL;
        EXPECT_EQUAL_INT(llabs(val), 10000LL);
        EXPECT_EQUAL_INT(llabs(-val), 10000LL);
    }
    {
        long long val = 50000LL;
        EXPECT_EQUAL_INT(llabs(val), 50000LL);
        EXPECT_EQUAL_INT(llabs(-val), 50000LL);
    }
    {
        long long val = 100000LL;
        EXPECT_EQUAL_INT(llabs(val), 100000LL);
        EXPECT_EQUAL_INT(llabs(-val), 100000LL);
    }
    {
        long long val = 1000000LL;
        EXPECT_EQUAL_INT(llabs(val), 1000000LL);
        EXPECT_EQUAL_INT(llabs(-val), 1000000LL);
    }
    {
        long long val = 2000000000LL;
        EXPECT_EQUAL_INT(llabs(val), 2000000000LL);
        EXPECT_EQUAL_INT(llabs(-val), 2000000000LL);
    }
    {
        long long val = 9000000000LL;
        EXPECT_EQUAL_INT(llabs(val), 9000000000LL);
        EXPECT_EQUAL_INT(llabs(-val), 9000000000LL);
    }
    {
        long long val = 5000000000000LL;
        EXPECT_EQUAL_INT(llabs(val), 5000000000000LL);
        EXPECT_EQUAL_INT(llabs(-val), 5000000000000LL);
    }
    {
        long long val = 9000000000000000000LL;
        EXPECT_EQUAL_INT(llabs(val), 9000000000000000000LL);
        EXPECT_EQUAL_INT(llabs(-val), 9000000000000000000LL);
    }
}
