#include <utest.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

UTEST_TEST_CASE(strtol){
    char *endptr;
    long result;
    
    {
        char str[] = "0";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, 0);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 1);
    }
    
    {
        char str[] = "123";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, 123);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 3);
    }
    
    {
        char str[] = "-123";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, -123);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 4);
    }
    
    {
        char str[] = "+123";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, 123);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 4);
    }
    
    {
        char str[] = "  123";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, 123);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 5);
    }
    
    {
        char str[] = "\t123";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, 123);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 4);
    }
    
    {
        char str[] = "\n123";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, 123);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 4);
    }
    
    {
        char str[] = "\r123";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, 123);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 4);
    }
    
    {
        char str[] = "\v123";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, 123);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 4);
    }
    
    {
        char str[] = "\f123";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, 123);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 4);
    }
    
    {
        char str[] = "123abc";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, 123);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 3);
    }
    
    {
        char str[] = "123 456";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, 123);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 3);
    }
    
    {
        char str[] = "";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, 0);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str);
    }
    
    {
        char str[] = "abc";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, 0);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str);
    }
    
    {
        char str[] = "  ";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, 0);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str);
    }
    
    {
        char str[] = "  abc";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, 0);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str);
    }
    
    {
        char str[] = "+";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, 0);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str);
    }
    
    {
        char str[] = "-";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, 0);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str);
    }
    
    {
        char str[] = "+abc";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, 0);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str);
    }
    
    {
        char str[] = "-abc";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, 0);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str);
    }
    
    {
        errno = 0;
        result = strtol("123", NULL, 10);
        EXPECT_EQUAL_INT(result, 123);
        EXPECT_TRUE(errno == 0);
    }
    
    {
        char str[] = "0";
        errno = 0;
        result = strtol(str, &endptr, 0);
        EXPECT_EQUAL_INT(result, 0);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 1);
    }
    
    {
        char str[] = "0123";
        errno = 0;
        result = strtol(str, &endptr, 0);
        EXPECT_EQUAL_INT(result, 83);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 4);
    }
    
    {
        char str[] = "0x123";
        errno = 0;
        result = strtol(str, &endptr, 0);
        EXPECT_EQUAL_INT(result, 291);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 5);
    }
    
    {
        char str[] = "0X123";
        errno = 0;
        result = strtol(str, &endptr, 0);
        EXPECT_EQUAL_INT(result, 291);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 5);
    }
    
    {
        char str[] = "123";
        errno = 0;
        result = strtol(str, &endptr, 0);
        EXPECT_EQUAL_INT(result, 123);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 3);
    }
    
    {
        char str[] = "0123";
        errno = 0;
        result = strtol(str, &endptr, 8);
        EXPECT_EQUAL_INT(result, 83);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 4);
    }
    
    {
        char str[] = "123";
        errno = 0;
        result = strtol(str, &endptr, 8);
        EXPECT_EQUAL_INT(result, 83);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 3);
    }
    
    {
        char str[] = "0x123";
        errno = 0;
        result = strtol(str, &endptr, 16);
        EXPECT_EQUAL_INT(result, 291);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 5);
    }
    
    {
        char str[] = "0X123";
        errno = 0;
        result = strtol(str, &endptr, 16);
        EXPECT_EQUAL_INT(result, 291);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 5);
    }
    
    {
        char str[] = "123";
        errno = 0;
        result = strtol(str, &endptr, 16);
        EXPECT_EQUAL_INT(result, 291);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 3);
    }
    
    {
        char str[] = "aBc";
        errno = 0;
        result = strtol(str, &endptr, 16);
        EXPECT_EQUAL_INT(result, 2748);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 3);
    }
    
    {
        char str[] = "z";
        errno = 0;
        result = strtol(str, &endptr, 36);
        EXPECT_EQUAL_INT(result, 35);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 1);
    }
    
    {
        char str[] = "Z";
        errno = 0;
        result = strtol(str, &endptr, 36);
        EXPECT_EQUAL_INT(result, 35);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 1);
    }
    
    {
        char str[] = "10";
        errno = 0;
        result = strtol(str, &endptr, 2);
        EXPECT_EQUAL_INT(result, 2);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 2);
    }
    
    {
        char str[] = "1010";
        errno = 0;
        result = strtol(str, &endptr, 2);
        EXPECT_EQUAL_INT(result, 10);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 4);
    }
    
    {
        char str[] = "9223372036854775807";
        errno = 0;
        result = strtol(str, &endptr, 10);
        if (sizeof(long) == 8) {
            EXPECT_EQUAL_INT(result, 9223372036854775807);
            EXPECT_TRUE(errno == 0);
        } else {
            EXPECT_EQUAL_INT(result, LONG_MAX);
            EXPECT_TRUE(errno == ERANGE);
        }
        EXPECT_TRUE(endptr == str + 19);
    }
    
    {
        char str[] = "-9223372036854775808";
        errno = 0;
        result = strtol(str, &endptr, 10);
        if (sizeof(long) == 8) {
            EXPECT_EQUAL_INT(result, LONG_MIN);
            EXPECT_TRUE(errno == 0);
        } else {
            EXPECT_EQUAL_INT(result, LONG_MIN);
            EXPECT_TRUE(errno == ERANGE);
        }
        EXPECT_TRUE(endptr == str + 20);
    }
    
    {
        char str[64];
        long max_val = LONG_MAX;
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
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, LONG_MAX);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + len);
    }
    
    {
        char str[64];
        long min_val = LONG_MIN;
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
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, LONG_MIN);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + len);
    }
    
    {
        char str[] = "999999999999999999999";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, LONG_MAX);
        EXPECT_TRUE(errno == ERANGE);
        EXPECT_TRUE(endptr == str + 21);
    }
    
    {
        char str[] = "-999999999999999999999";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, LONG_MIN);
        EXPECT_TRUE(errno == ERANGE);
        EXPECT_TRUE(endptr == str + 22);
    }
    
    {
        char str[] = "000";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, 0);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 3);
    }
    
    {
        char str[] = "000123";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, 123);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 6);
    }
    
    {
        char str[] = "-0";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, 0);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 2);
    }
    
    {
        char str[] = "+0";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, 0);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 2);
    }
    
    {
        char str[] = "0x";
        errno = 0;
        result = strtol(str, &endptr, 0);
        EXPECT_EQUAL_INT(result, 0);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 1);
    }
    
    {
        char str[] = "0x";
        errno = 0;
        result = strtol(str, &endptr, 16);
        EXPECT_EQUAL_INT(result, 0);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 1);
    }
    
    {
        char str[] = "0X";
        errno = 0;
        result = strtol(str, &endptr, 16);
        EXPECT_EQUAL_INT(result, 0);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 1);
    }
    
    {
        char str[] = "0xG";
        errno = 0;
        result = strtol(str, &endptr, 16);
        EXPECT_EQUAL_INT(result, 0);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 1);
    }
    
    {
        char str[] = "08";
        errno = 0;
        result = strtol(str, &endptr, 8);
        EXPECT_EQUAL_INT(result, 0);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 1);
    }
    
    {
        char str[] = "08";
        errno = 0;
        result = strtol(str, &endptr, 0);
        EXPECT_EQUAL_INT(result, 0);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 1);
    }
    
    {
        char str[] = "0x8";
        errno = 0;
        result = strtol(str, &endptr, 0);
        EXPECT_EQUAL_INT(result, 8);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 3);
    }
    
    {
        char str[] = "2147483647";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, 2147483647);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 10);
    }
    
    {
        char str[] = "-2147483648";
        errno = 0;
        result = strtol(str, &endptr, 10);
        EXPECT_EQUAL_INT(result, -2147483648);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 11);
    }
    
    {
        char str[] = "7FFFFFFF";
        errno = 0;
        result = strtol(str, &endptr, 16);
        EXPECT_EQUAL_INT(result, 2147483647);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 8);
    }
    
    {
        char str[] = "-80000000";
        errno = 0;
        result = strtol(str, &endptr, 16);
        EXPECT_EQUAL_INT(result, -2147483648);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 9);
    }
    
    {
        char str[] = "102";
        errno = 0;
        result = strtol(str, &endptr, 3);
        EXPECT_EQUAL_INT(result, 11);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 3);
    }
    
    {
        char str[] = "123";
        errno = 0;
        result = strtol(str, &endptr, 4);
        EXPECT_EQUAL_INT(result, 27);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 3);
    }
    
    {
        char str[] = "1234";
        errno = 0;
        result = strtol(str, &endptr, 5);
        EXPECT_EQUAL_INT(result, 194);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 4);
    }
    
    {
        char str[] = "12345";
        errno = 0;
        result = strtol(str, &endptr, 6);
        EXPECT_EQUAL_INT(result, 1865);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 5);
    }
    
    {
        char str[] = "123456";
        errno = 0;
        result = strtol(str, &endptr, 7);
        EXPECT_EQUAL_INT(result, 22875);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 6);
    }
    
    {
        char str[] = "1234567";
        errno = 0;
        result = strtol(str, &endptr, 9);
        EXPECT_EQUAL_INT(result, 672604);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 7);
    }
    
    {
        char str[] = "A";
        errno = 0;
        result = strtol(str, &endptr, 11);
        EXPECT_EQUAL_INT(result, 10);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 1);
    }
    
    {
        char str[] = "a";
        errno = 0;
        result = strtol(str, &endptr, 11);
        EXPECT_EQUAL_INT(result, 10);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 1);
    }
    
    {
        char str[] = "1A";
        errno = 0;
        result = strtol(str, &endptr, 11);
        EXPECT_EQUAL_INT(result, 21);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 2);
    }
    
    {
        char str[] = "Y";
        errno = 0;
        result = strtol(str, &endptr, 35);
        EXPECT_EQUAL_INT(result, 34);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 1);
    }
    
    {
        char str[] = "10";
        errno = 0;
        result = strtol(str, &endptr, 35);
        EXPECT_EQUAL_INT(result, 35);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 2);
    }
    
    {
        char str[] = "0xABCD";
        errno = 0;
        result = strtol(str, &endptr, 0);
        EXPECT_EQUAL_INT(result, 43981);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 6);
    }
    
    {
        char str[] = "0Xabcd";
        errno = 0;
        result = strtol(str, &endptr, 0);
        EXPECT_EQUAL_INT(result, 43981);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 6);
    }
    
    {
        char str[] = "0777";
        errno = 0;
        result = strtol(str, &endptr, 0);
        EXPECT_EQUAL_INT(result, 511);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 4);
    }
    
    {
        char str[] = "0";
        errno = 0;
        result = strtol(str, &endptr, 0);
        EXPECT_EQUAL_INT(result, 0);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 1);
    }
    
    {
        char str[] = "00";
        errno = 0;
        result = strtol(str, &endptr, 0);
        EXPECT_EQUAL_INT(result, 0);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 2);
    }
    
    {
        char str[] = "0x0";
        errno = 0;
        result = strtol(str, &endptr, 0);
        EXPECT_EQUAL_INT(result, 0);
        EXPECT_TRUE(errno == 0);
        EXPECT_TRUE(endptr == str + 3);
    }
}
