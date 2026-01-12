#include <utest.h>
#include <stdlib.h>
#include <limits.h>

UTEST_TEST_CASE(atoi){
    EXPECT_EQUAL_INT(atoi("0"), 0);
    EXPECT_EQUAL_INT(atoi("1"), 1);
    EXPECT_EQUAL_INT(atoi("123"), 123);
    EXPECT_EQUAL_INT(atoi("456789"), 456789);

    EXPECT_EQUAL_INT(atoi("-0"), 0);
    EXPECT_EQUAL_INT(atoi("-1"), -1);
    EXPECT_EQUAL_INT(atoi("-123"), -123);
    EXPECT_EQUAL_INT(atoi("-456789"), -456789);

    EXPECT_EQUAL_INT(atoi("+0"), 0);
    EXPECT_EQUAL_INT(atoi("+1"), 1);
    EXPECT_EQUAL_INT(atoi("+123"), 123);
    EXPECT_EQUAL_INT(atoi("+456789"), 456789);

    EXPECT_EQUAL_INT(atoi("  0"), 0);
    EXPECT_EQUAL_INT(atoi("  123"), 123);
    EXPECT_EQUAL_INT(atoi("  -123"), -123);
    EXPECT_EQUAL_INT(atoi("  +123"), 123);
    EXPECT_EQUAL_INT(atoi("\t123"), 123);
    EXPECT_EQUAL_INT(atoi("\n123"), 123);
    EXPECT_EQUAL_INT(atoi("\r123"), 123);
    EXPECT_EQUAL_INT(atoi("\v123"), 123);
    EXPECT_EQUAL_INT(atoi("\f123"), 123);
    EXPECT_EQUAL_INT(atoi("  \t  \n  123"), 123);

    EXPECT_EQUAL_INT(atoi("123abc"), 123);
    EXPECT_EQUAL_INT(atoi("123 456"), 123);
    EXPECT_EQUAL_INT(atoi("123+456"), 123);
    EXPECT_EQUAL_INT(atoi("123-456"), 123);
    EXPECT_EQUAL_INT(atoi("-123abc"), -123);

    EXPECT_EQUAL_INT(atoi(""), 0);
    EXPECT_EQUAL_INT(atoi("abc"), 0);
    EXPECT_EQUAL_INT(atoi("  "), 0);
    EXPECT_EQUAL_INT(atoi("  abc"), 0);
    EXPECT_EQUAL_INT(atoi("+"), 0);
    EXPECT_EQUAL_INT(atoi("-"), 0);
    EXPECT_EQUAL_INT(atoi("+abc"), 0);
    EXPECT_EQUAL_INT(atoi("-abc"), 0);

    {
        char str[] = "2147483647";
        EXPECT_EQUAL_INT(atoi(str), INT_MAX);
    }

    {
        char str[] = "-2147483648";
        EXPECT_EQUAL_INT(atoi(str), INT_MIN);
    }

    {
        char str[] = "2147483646";
        EXPECT_EQUAL_INT(atoi(str), 2147483646);
    }

    {
        char str[] = "-2147483647";
        EXPECT_EQUAL_INT(atoi(str), -2147483647);
    }

    EXPECT_EQUAL_INT(atoi("000"), 0);
    EXPECT_EQUAL_INT(atoi("000123"), 123);
    EXPECT_EQUAL_INT(atoi("0000"), 0);

    EXPECT_EQUAL_INT(atoi("9"), 9);
    EXPECT_EQUAL_INT(atoi("10"), 10);
    EXPECT_EQUAL_INT(atoi("99"), 99);
    EXPECT_EQUAL_INT(atoi("100"), 100);
    EXPECT_EQUAL_INT(atoi("999"), 999);
    EXPECT_EQUAL_INT(atoi("1000"), 1000);

    EXPECT_EQUAL_INT(atoi("-9"), -9);
    EXPECT_EQUAL_INT(atoi("-10"), -10);
    EXPECT_EQUAL_INT(atoi("-99"), -99);
    EXPECT_EQUAL_INT(atoi("-100"), -100);
}
