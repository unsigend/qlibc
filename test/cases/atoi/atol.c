#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <utest.h>

UTEST_CASE(atol)
{
    char lim[32];

    EXPECT_EQ_INT(atol("0"), 0L);
    EXPECT_EQ_INT(atol("1"), 1L);
    EXPECT_EQ_INT(atol("9"), 9L);
    EXPECT_EQ_INT(atol("10"), 10L);
    EXPECT_EQ_INT(atol("99"), 99L);
    EXPECT_EQ_INT(atol("100"), 100L);
    EXPECT_EQ_INT(atol("123"), 123L);
    EXPECT_EQ_INT(atol("999"), 999L);
    EXPECT_EQ_INT(atol("1000"), 1000L);
    EXPECT_EQ_INT(atol("456789"), 456789L);
    EXPECT_EQ_INT(atol("1234567890"), 1234567890L);
    EXPECT_EQ_INT(atol("-0"), 0L);
    EXPECT_EQ_INT(atol("-1"), -1L);
    EXPECT_EQ_INT(atol("-9"), -9L);
    EXPECT_EQ_INT(atol("-10"), -10L);
    EXPECT_EQ_INT(atol("-99"), -99L);
    EXPECT_EQ_INT(atol("-100"), -100L);
    EXPECT_EQ_INT(atol("-123"), -123L);
    EXPECT_EQ_INT(atol("-456789"), -456789L);
    EXPECT_EQ_INT(atol("-1234567890"), -1234567890L);
    EXPECT_EQ_INT(atol("+0"), 0L);
    EXPECT_EQ_INT(atol("+1"), 1L);
    EXPECT_EQ_INT(atol("+123"), 123L);
    EXPECT_EQ_INT(atol("+456789"), 456789L);
    EXPECT_EQ_INT(atol("+1234567890"), 1234567890L);
    EXPECT_EQ_INT(atol("  0"), 0L);
    EXPECT_EQ_INT(atol("  123"), 123L);
    EXPECT_EQ_INT(atol("  -123"), -123L);
    EXPECT_EQ_INT(atol("  +123"), 123L);
    EXPECT_EQ_INT(atol("\t123"), 123L);
    EXPECT_EQ_INT(atol("\n123"), 123L);
    EXPECT_EQ_INT(atol("\r123"), 123L);
    EXPECT_EQ_INT(atol("\v123"), 123L);
    EXPECT_EQ_INT(atol("\f123"), 123L);
    EXPECT_EQ_INT(atol("  \t  \n  123"), 123L);
    EXPECT_EQ_INT(atol("123abc"), 123L);
    EXPECT_EQ_INT(atol("123 456"), 123L);
    EXPECT_EQ_INT(atol("123+456"), 123L);
    EXPECT_EQ_INT(atol("123-456"), 123L);
    EXPECT_EQ_INT(atol("-123abc"), -123L);
    EXPECT_EQ_INT(atol(""), 0L);
    EXPECT_EQ_INT(atol("abc"), 0L);
    EXPECT_EQ_INT(atol("  "), 0L);
    EXPECT_EQ_INT(atol("  abc"), 0L);
    EXPECT_EQ_INT(atol("+"), 0L);
    EXPECT_EQ_INT(atol("-"), 0L);
    EXPECT_EQ_INT(atol("+abc"), 0L);
    EXPECT_EQ_INT(atol("-abc"), 0L);
    EXPECT_EQ_INT(atol("000"), 0L);
    EXPECT_EQ_INT(atol("0000"), 0L);
    EXPECT_EQ_INT(atol("000123"), 123L);
    EXPECT_EQ_INT(atol("2147483647"), 2147483647L);
    EXPECT_EQ_INT(atol("-2147483648"), -2147483648L);
    sprintf(lim, "%ld", LONG_MAX);
    EXPECT_EQ_INT(atol(lim), LONG_MAX);
    sprintf(lim, "%ld", LONG_MIN);
    EXPECT_EQ_INT(atol(lim), LONG_MIN);
    if (LONG_MAX >= 123456789012345L)
        EXPECT_EQ_INT(atol("123456789012345"), 123456789012345L);
}
