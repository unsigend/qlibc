#include <utest.h>
#include <stdlib.h>
#include <limits.h>

UTEST_TEST_CASE(atol){
    EXPECT_TRUE(atol("0") == 0);
    EXPECT_TRUE(atol("1") == 1);
    EXPECT_TRUE(atol("123") == 123);
    EXPECT_TRUE(atol("456789") == 456789);
    EXPECT_TRUE(atol("1234567890") == 1234567890L);

    EXPECT_TRUE(atol("-0") == 0);
    EXPECT_TRUE(atol("-1") == -1);
    EXPECT_TRUE(atol("-123") == -123);
    EXPECT_TRUE(atol("-456789") == -456789);
    EXPECT_TRUE(atol("-1234567890") == -1234567890L);

    EXPECT_TRUE(atol("+0") == 0);
    EXPECT_TRUE(atol("+1") == 1);
    EXPECT_TRUE(atol("+123") == 123);
    EXPECT_TRUE(atol("+456789") == 456789);
    EXPECT_TRUE(atol("+1234567890") == 1234567890L);

    EXPECT_TRUE(atol("  0") == 0);
    EXPECT_TRUE(atol("  123") == 123);
    EXPECT_TRUE(atol("  -123") == -123);
    EXPECT_TRUE(atol("  +123") == 123);
    EXPECT_TRUE(atol("\t123") == 123);
    EXPECT_TRUE(atol("\n123") == 123);
    EXPECT_TRUE(atol("\r123") == 123);
    EXPECT_TRUE(atol("\v123") == 123);
    EXPECT_TRUE(atol("\f123") == 123);
    EXPECT_TRUE(atol("  \t  \n  123") == 123);

    EXPECT_TRUE(atol("123abc") == 123);
    EXPECT_TRUE(atol("123 456") == 123);
    EXPECT_TRUE(atol("123+456") == 123);
    EXPECT_TRUE(atol("123-456") == 123);
    EXPECT_TRUE(atol("-123abc") == -123);

    EXPECT_TRUE(atol("") == 0);
    EXPECT_TRUE(atol("abc") == 0);
    EXPECT_TRUE(atol("  ") == 0);
    EXPECT_TRUE(atol("  abc") == 0);
    EXPECT_TRUE(atol("+") == 0);
    EXPECT_TRUE(atol("-") == 0);
    EXPECT_TRUE(atol("+abc") == 0);
    EXPECT_TRUE(atol("-abc") == 0);

    {
        char str[] = "2147483647";
        EXPECT_TRUE(atol(str) == 2147483647L);
    }

    {
        char str[] = "-2147483648";
        EXPECT_TRUE(atol(str) == -2147483648L);
    }

    {
        char str[] = "9223372036854775807";
        EXPECT_TRUE(atol(str) == LONG_MAX);
    }

    {
        char str[] = "-9223372036854775808";
        EXPECT_TRUE(atol(str) == LONG_MIN);
    }

    {
        char str[] = "9223372036854775806";
        EXPECT_TRUE(atol(str) == 9223372036854775806L);
    }

    {
        char str[] = "-9223372036854775807";
        EXPECT_TRUE(atol(str) == -9223372036854775807L);
    }

    EXPECT_TRUE(atol("000") == 0);
    EXPECT_TRUE(atol("000123") == 123);
    EXPECT_TRUE(atol("0000") == 0);

    EXPECT_TRUE(atol("9") == 9);
    EXPECT_TRUE(atol("10") == 10);
    EXPECT_TRUE(atol("99") == 99);
    EXPECT_TRUE(atol("100") == 100);
    EXPECT_TRUE(atol("999") == 999);
    EXPECT_TRUE(atol("1000") == 1000);

    EXPECT_TRUE(atol("-9") == -9);
    EXPECT_TRUE(atol("-10") == -10);
    EXPECT_TRUE(atol("-99") == -99);
    EXPECT_TRUE(atol("-100") == -100);

    {
        char str[] = "123456789012345";
        long result = atol(str);
        EXPECT_TRUE(result > 0);
    }
}
