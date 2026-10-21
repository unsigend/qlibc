#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <utest.h>

UTEST_CASE(atoi)
{
    char lim[32];

    EXPECT_EQ_INT(atoi("0"), 0);
    EXPECT_EQ_INT(atoi("1"), 1);
    EXPECT_EQ_INT(atoi("9"), 9);
    EXPECT_EQ_INT(atoi("10"), 10);
    EXPECT_EQ_INT(atoi("99"), 99);
    EXPECT_EQ_INT(atoi("100"), 100);
    EXPECT_EQ_INT(atoi("123"), 123);
    EXPECT_EQ_INT(atoi("999"), 999);
    EXPECT_EQ_INT(atoi("1000"), 1000);
    EXPECT_EQ_INT(atoi("456789"), 456789);
    EXPECT_EQ_INT(atoi("-0"), 0);
    EXPECT_EQ_INT(atoi("-1"), -1);
    EXPECT_EQ_INT(atoi("-9"), -9);
    EXPECT_EQ_INT(atoi("-10"), -10);
    EXPECT_EQ_INT(atoi("-99"), -99);
    EXPECT_EQ_INT(atoi("-100"), -100);
    EXPECT_EQ_INT(atoi("-123"), -123);
    EXPECT_EQ_INT(atoi("-456789"), -456789);
    EXPECT_EQ_INT(atoi("+0"), 0);
    EXPECT_EQ_INT(atoi("+1"), 1);
    EXPECT_EQ_INT(atoi("+123"), 123);
    EXPECT_EQ_INT(atoi("+456789"), 456789);
    EXPECT_EQ_INT(atoi("  0"), 0);
    EXPECT_EQ_INT(atoi("  123"), 123);
    EXPECT_EQ_INT(atoi("  -123"), -123);
    EXPECT_EQ_INT(atoi("  +123"), 123);
    EXPECT_EQ_INT(atoi("\t123"), 123);
    EXPECT_EQ_INT(atoi("\n123"), 123);
    EXPECT_EQ_INT(atoi("\r123"), 123);
    EXPECT_EQ_INT(atoi("\v123"), 123);
    EXPECT_EQ_INT(atoi("\f123"), 123);
    EXPECT_EQ_INT(atoi("  \t  \n  123"), 123);
    EXPECT_EQ_INT(atoi("123abc"), 123);
    EXPECT_EQ_INT(atoi("123 456"), 123);
    EXPECT_EQ_INT(atoi("123+456"), 123);
    EXPECT_EQ_INT(atoi("123-456"), 123);
    EXPECT_EQ_INT(atoi("-123abc"), -123);
    EXPECT_EQ_INT(atoi(""), 0);
    EXPECT_EQ_INT(atoi("abc"), 0);
    EXPECT_EQ_INT(atoi("  "), 0);
    EXPECT_EQ_INT(atoi("  abc"), 0);
    EXPECT_EQ_INT(atoi("+"), 0);
    EXPECT_EQ_INT(atoi("-"), 0);
    EXPECT_EQ_INT(atoi("+abc"), 0);
    EXPECT_EQ_INT(atoi("-abc"), 0);
    EXPECT_EQ_INT(atoi("000"), 0);
    EXPECT_EQ_INT(atoi("0000"), 0);
    EXPECT_EQ_INT(atoi("000123"), 123);
    sprintf(lim, "%d", INT_MAX);
    EXPECT_EQ_INT(atoi(lim), INT_MAX);
    sprintf(lim, "%d", INT_MIN);
    EXPECT_EQ_INT(atoi(lim), INT_MIN);
    if (INT_MAX >= 2147483646)
        EXPECT_EQ_INT(atoi("2147483646"), 2147483646);
    if (INT_MIN <= -2147483647)
        EXPECT_EQ_INT(atoi("-2147483647"), -2147483647);
}
