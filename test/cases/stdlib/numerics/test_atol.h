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
        long max_val = LONG_MAX;
        char str[32];
        int len = 0;
        long val = max_val;
        while (val > 0) {
            str[len++] = '0' + (val % 10);
            val /= 10;
        }
        for (int i = 0; i < len / 2; i++) {
            char tmp = str[i];
            str[i] = str[len - 1 - i];
            str[len - 1 - i] = tmp;
        }
        str[len] = '\0';
        EXPECT_TRUE(atol(str) == LONG_MAX);
    }

    {
        long min_val = LONG_MIN;
        char str[32];
        int len = 0;
        str[len++] = '-';
        unsigned long abs_val;
        if (min_val == LONG_MIN) {
            abs_val = (unsigned long)LONG_MAX + 1;
        } else {
            abs_val = (unsigned long)(-min_val);
        }
        int digits[32];
        int digit_count = 0;
        while (abs_val > 0) {
            digits[digit_count++] = abs_val % 10;
            abs_val /= 10;
        }
        for (int i = digit_count - 1; i >= 0; i--) {
            str[len++] = '0' + digits[i];
        }
        str[len] = '\0';
        EXPECT_TRUE(atol(str) == LONG_MIN);
    }

    {
        EXPECT_TRUE(atol("2147483647") == 2147483647L);
    }

    {
        EXPECT_TRUE(atol("-2147483648") == -2147483648L);
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
        if (LONG_MAX >= 123456789012345L) {
            EXPECT_TRUE(atol("123456789012345") == 123456789012345L);
        }
    }
}
