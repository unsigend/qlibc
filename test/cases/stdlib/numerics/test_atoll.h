#include <utest.h>
#include <stdlib.h>
#include <limits.h>

UTEST_TEST_CASE(atoll){
    EXPECT_TRUE(atoll("0") == 0);
    EXPECT_TRUE(atoll("1") == 1);
    EXPECT_TRUE(atoll("123") == 123);
    EXPECT_TRUE(atoll("456789") == 456789);
    EXPECT_TRUE(atoll("1234567890") == 1234567890LL);
    EXPECT_TRUE(atoll("123456789012345") == 123456789012345LL);

    EXPECT_TRUE(atoll("-0") == 0);
    EXPECT_TRUE(atoll("-1") == -1);
    EXPECT_TRUE(atoll("-123") == -123);
    EXPECT_TRUE(atoll("-456789") == -456789);
    EXPECT_TRUE(atoll("-1234567890") == -1234567890LL);
    EXPECT_TRUE(atoll("-123456789012345") == -123456789012345LL);

    EXPECT_TRUE(atoll("+0") == 0);
    EXPECT_TRUE(atoll("+1") == 1);
    EXPECT_TRUE(atoll("+123") == 123);
    EXPECT_TRUE(atoll("+456789") == 456789);
    EXPECT_TRUE(atoll("+1234567890") == 1234567890LL);
    EXPECT_TRUE(atoll("+123456789012345") == 123456789012345LL);

    EXPECT_TRUE(atoll("  0") == 0);
    EXPECT_TRUE(atoll("  123") == 123);
    EXPECT_TRUE(atoll("  -123") == -123);
    EXPECT_TRUE(atoll("  +123") == 123);
    EXPECT_TRUE(atoll("\t123") == 123);
    EXPECT_TRUE(atoll("\n123") == 123);
    EXPECT_TRUE(atoll("\r123") == 123);
    EXPECT_TRUE(atoll("\v123") == 123);
    EXPECT_TRUE(atoll("\f123") == 123);
    EXPECT_TRUE(atoll("  \t  \n  123") == 123);

    EXPECT_TRUE(atoll("123abc") == 123);
    EXPECT_TRUE(atoll("123 456") == 123);
    EXPECT_TRUE(atoll("123+456") == 123);
    EXPECT_TRUE(atoll("123-456") == 123);
    EXPECT_TRUE(atoll("-123abc") == -123);

    EXPECT_TRUE(atoll("") == 0);
    EXPECT_TRUE(atoll("abc") == 0);
    EXPECT_TRUE(atoll("  ") == 0);
    EXPECT_TRUE(atoll("  abc") == 0);
    EXPECT_TRUE(atoll("+") == 0);
    EXPECT_TRUE(atoll("-") == 0);
    EXPECT_TRUE(atoll("+abc") == 0);
    EXPECT_TRUE(atoll("-abc") == 0);

    {
        char str[] = "9223372036854775807";
        EXPECT_TRUE(atoll(str) == LLONG_MAX);
    }

    {
        char str[] = "-9223372036854775808";
        EXPECT_TRUE(atoll(str) == LLONG_MIN);
    }

    {
        char str[] = "9223372036854775806";
        EXPECT_TRUE(atoll(str) == 9223372036854775806LL);
    }

    {
        char str[] = "-9223372036854775807";
        EXPECT_TRUE(atoll(str) == -9223372036854775807LL);
    }

    EXPECT_TRUE(atoll("000") == 0);
    EXPECT_TRUE(atoll("000123") == 123);
    EXPECT_TRUE(atoll("0000") == 0);

    EXPECT_TRUE(atoll("9") == 9);
    EXPECT_TRUE(atoll("10") == 10);
    EXPECT_TRUE(atoll("99") == 99);
    EXPECT_TRUE(atoll("100") == 100);
    EXPECT_TRUE(atoll("999") == 999);
    EXPECT_TRUE(atoll("1000") == 1000);

    EXPECT_TRUE(atoll("-9") == -9);
    EXPECT_TRUE(atoll("-10") == -10);
    EXPECT_TRUE(atoll("-99") == -99);
    EXPECT_TRUE(atoll("-100") == -100);

    {
        char str[] = "1234567890123456789";
        long long result = atoll(str);
        EXPECT_TRUE(result > 0);
    }
}
