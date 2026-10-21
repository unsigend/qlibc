#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <utest.h>

UTEST_CASE(atoll)
{
    char lim[32];

    EXPECT_EQ_INT(atoll("0"), 0LL);
    EXPECT_EQ_INT(atoll("1"), 1LL);
    EXPECT_EQ_INT(atoll("9"), 9LL);
    EXPECT_EQ_INT(atoll("10"), 10LL);
    EXPECT_EQ_INT(atoll("99"), 99LL);
    EXPECT_EQ_INT(atoll("100"), 100LL);
    EXPECT_EQ_INT(atoll("123"), 123LL);
    EXPECT_EQ_INT(atoll("999"), 999LL);
    EXPECT_EQ_INT(atoll("1000"), 1000LL);
    EXPECT_EQ_INT(atoll("456789"), 456789LL);
    EXPECT_EQ_INT(atoll("1234567890"), 1234567890LL);
    EXPECT_EQ_INT(atoll("123456789012345"), 123456789012345LL);
    EXPECT_EQ_INT(atoll("-0"), 0LL);
    EXPECT_EQ_INT(atoll("-1"), -1LL);
    EXPECT_EQ_INT(atoll("-9"), -9LL);
    EXPECT_EQ_INT(atoll("-10"), -10LL);
    EXPECT_EQ_INT(atoll("-99"), -99LL);
    EXPECT_EQ_INT(atoll("-100"), -100LL);
    EXPECT_EQ_INT(atoll("-123"), -123LL);
    EXPECT_EQ_INT(atoll("-456789"), -456789LL);
    EXPECT_EQ_INT(atoll("-1234567890"), -1234567890LL);
    EXPECT_EQ_INT(atoll("-123456789012345"), -123456789012345LL);
    EXPECT_EQ_INT(atoll("+0"), 0LL);
    EXPECT_EQ_INT(atoll("+1"), 1LL);
    EXPECT_EQ_INT(atoll("+123"), 123LL);
    EXPECT_EQ_INT(atoll("+456789"), 456789LL);
    EXPECT_EQ_INT(atoll("+1234567890"), 1234567890LL);
    EXPECT_EQ_INT(atoll("+123456789012345"), 123456789012345LL);
    EXPECT_EQ_INT(atoll("  0"), 0LL);
    EXPECT_EQ_INT(atoll("  123"), 123LL);
    EXPECT_EQ_INT(atoll("  -123"), -123LL);
    EXPECT_EQ_INT(atoll("  +123"), 123LL);
    EXPECT_EQ_INT(atoll("\t123"), 123LL);
    EXPECT_EQ_INT(atoll("\n123"), 123LL);
    EXPECT_EQ_INT(atoll("\r123"), 123LL);
    EXPECT_EQ_INT(atoll("\v123"), 123LL);
    EXPECT_EQ_INT(atoll("\f123"), 123LL);
    EXPECT_EQ_INT(atoll("  \t  \n  123"), 123LL);
    EXPECT_EQ_INT(atoll("123abc"), 123LL);
    EXPECT_EQ_INT(atoll("123 456"), 123LL);
    EXPECT_EQ_INT(atoll("123+456"), 123LL);
    EXPECT_EQ_INT(atoll("123-456"), 123LL);
    EXPECT_EQ_INT(atoll("-123abc"), -123LL);
    EXPECT_EQ_INT(atoll(""), 0LL);
    EXPECT_EQ_INT(atoll("abc"), 0LL);
    EXPECT_EQ_INT(atoll("  "), 0LL);
    EXPECT_EQ_INT(atoll("  abc"), 0LL);
    EXPECT_EQ_INT(atoll("+"), 0LL);
    EXPECT_EQ_INT(atoll("-"), 0LL);
    EXPECT_EQ_INT(atoll("+abc"), 0LL);
    EXPECT_EQ_INT(atoll("-abc"), 0LL);
    EXPECT_EQ_INT(atoll("000"), 0LL);
    EXPECT_EQ_INT(atoll("0000"), 0LL);
    EXPECT_EQ_INT(atoll("000123"), 123LL);
    EXPECT_EQ_INT(atoll("2147483647"), 2147483647LL);
    EXPECT_EQ_INT(atoll("-2147483648"), -2147483648LL);
    sprintf(lim, "%lld", LLONG_MAX);
    EXPECT_EQ_INT(atoll(lim), LLONG_MAX);
    sprintf(lim, "%lld", LLONG_MIN);
    EXPECT_EQ_INT(atoll(lim), LLONG_MIN);
    sprintf(lim, "%lld", LLONG_MAX - 1);
    EXPECT_EQ_INT(atoll(lim), LLONG_MAX - 1);
    sprintf(lim, "%lld", LLONG_MIN + 1);
    EXPECT_EQ_INT(atoll(lim), LLONG_MIN + 1);
}
