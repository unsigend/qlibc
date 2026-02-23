#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <utest.h>

UTEST_TEST_CASE(strtoull) {
  char *endptr;
  unsigned long long result;

  {
    char str[] = "0";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_EQUAL_UINT(result, 0);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 1);
  }

  {
    char str[] = "123";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_EQUAL_UINT(result, 123);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 3);
  }

  {
    char str[] = "+123";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_EQUAL_UINT(result, 123);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 4);
  }

  {
    char str[] = "  123";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_EQUAL_UINT(result, 123);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 5);
  }

  {
    char str[] = "\t123";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_EQUAL_UINT(result, 123);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 4);
  }

  {
    char str[] = "\n123";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_EQUAL_UINT(result, 123);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 4);
  }

  {
    char str[] = "\r123";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_EQUAL_UINT(result, 123);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 4);
  }

  {
    char str[] = "\v123";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_EQUAL_UINT(result, 123);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 4);
  }

  {
    char str[] = "\f123";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_EQUAL_UINT(result, 123);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 4);
  }

  {
    char str[] = "123abc";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_EQUAL_UINT(result, 123);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 3);
  }

  {
    char str[] = "123 456";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_EQUAL_UINT(result, 123);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 3);
  }

  {
    char str[] = "";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_EQUAL_UINT(result, 0);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str);
  }

  {
    char str[] = "abc";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_EQUAL_UINT(result, 0);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str);
  }

  {
    char str[] = "  ";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_EQUAL_UINT(result, 0);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str);
  }

  {
    char str[] = "  abc";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_EQUAL_UINT(result, 0);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str);
  }

  {
    char str[] = "+";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_EQUAL_UINT(result, 0);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str);
  }

  {
    char str[] = "-";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_EQUAL_UINT(result, 0);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str);
  }

  {
    char str[] = "+abc";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_EQUAL_UINT(result, 0);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str);
  }

  {
    char str[] = "-abc";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_EQUAL_UINT(result, 0);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str);
  }

  {
    errno = 0;
    result = strtoull("123", NULL, 10);
    EXPECT_EQUAL_UINT(result, 123);
    EXPECT_TRUE(errno == 0);
  }

  {
    char str[] = "-1";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_TRUE(result == ULLONG_MAX);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 2);
  }

  {
    char str[] = "-0";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_EQUAL_UINT(result, 0);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 2);
  }

  {
    char str[] = "0";
    errno = 0;
    result = strtoull(str, &endptr, 0);
    EXPECT_EQUAL_UINT(result, 0);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 1);
  }

  {
    char str[] = "0123";
    errno = 0;
    result = strtoull(str, &endptr, 0);
    EXPECT_EQUAL_UINT(result, 83);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 4);
  }

  {
    char str[] = "0x123";
    errno = 0;
    result = strtoull(str, &endptr, 0);
    EXPECT_EQUAL_UINT(result, 291);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 5);
  }

  {
    char str[] = "0X123";
    errno = 0;
    result = strtoull(str, &endptr, 0);
    EXPECT_EQUAL_UINT(result, 291);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 5);
  }

  {
    char str[] = "123";
    errno = 0;
    result = strtoull(str, &endptr, 0);
    EXPECT_EQUAL_UINT(result, 123);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 3);
  }

  {
    char str[] = "0123";
    errno = 0;
    result = strtoull(str, &endptr, 8);
    EXPECT_EQUAL_UINT(result, 83);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 4);
  }

  {
    char str[] = "123";
    errno = 0;
    result = strtoull(str, &endptr, 8);
    EXPECT_EQUAL_UINT(result, 83);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 3);
  }

  {
    char str[] = "0x123";
    errno = 0;
    result = strtoull(str, &endptr, 16);
    EXPECT_EQUAL_UINT(result, 291);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 5);
  }

  {
    char str[] = "0X123";
    errno = 0;
    result = strtoull(str, &endptr, 16);
    EXPECT_EQUAL_UINT(result, 291);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 5);
  }

  {
    char str[] = "123";
    errno = 0;
    result = strtoull(str, &endptr, 16);
    EXPECT_EQUAL_UINT(result, 291);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 3);
  }

  {
    char str[] = "aBc";
    errno = 0;
    result = strtoull(str, &endptr, 16);
    EXPECT_EQUAL_UINT(result, 2748);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 3);
  }

  {
    char str[] = "z";
    errno = 0;
    result = strtoull(str, &endptr, 36);
    EXPECT_EQUAL_UINT(result, 35);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 1);
  }

  {
    char str[] = "Z";
    errno = 0;
    result = strtoull(str, &endptr, 36);
    EXPECT_EQUAL_UINT(result, 35);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 1);
  }

  {
    char str[] = "10";
    errno = 0;
    result = strtoull(str, &endptr, 2);
    EXPECT_EQUAL_UINT(result, 2);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 2);
  }

  {
    char str[] = "1010";
    errno = 0;
    result = strtoull(str, &endptr, 2);
    EXPECT_EQUAL_UINT(result, 10);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 4);
  }

  {
    char str[] = "18446744073709551615";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_TRUE(result == ULLONG_MAX);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 20);
  }

  {
    char str[64];
    unsigned long long max_val = ULLONG_MAX;
    int len = 0;
    unsigned long long val = max_val;
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
    result = strtoull(str, &endptr, 10);
    EXPECT_TRUE(result == ULLONG_MAX);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + len);
  }

  {
    char str[] = "999999999999999999999999999999";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_TRUE(result == ULLONG_MAX);
    EXPECT_TRUE(errno == ERANGE);
    EXPECT_TRUE(endptr == str + 30);
  }

  {
    char str[] = "000";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_EQUAL_UINT(result, 0);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 3);
  }

  {
    char str[] = "000123";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_EQUAL_UINT(result, 123);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 6);
  }

  {
    char str[] = "-0";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_EQUAL_UINT(result, 0);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 2);
  }

  {
    char str[] = "+0";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_EQUAL_UINT(result, 0);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 2);
  }

  {
    char str[] = "0x";
    errno = 0;
    result = strtoull(str, &endptr, 0);
    EXPECT_EQUAL_UINT(result, 0);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 1);
  }

  {
    char str[] = "0x";
    errno = 0;
    result = strtoull(str, &endptr, 16);
    EXPECT_EQUAL_UINT(result, 0);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 1);
  }

  {
    char str[] = "0X";
    errno = 0;
    result = strtoull(str, &endptr, 16);
    EXPECT_EQUAL_UINT(result, 0);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 1);
  }

  {
    char str[] = "0xG";
    errno = 0;
    result = strtoull(str, &endptr, 16);
    EXPECT_EQUAL_UINT(result, 0);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 1);
  }

  {
    char str[] = "08";
    errno = 0;
    result = strtoull(str, &endptr, 8);
    EXPECT_EQUAL_UINT(result, 0);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 1);
  }

  {
    char str[] = "08";
    errno = 0;
    result = strtoull(str, &endptr, 0);
    EXPECT_EQUAL_UINT(result, 0);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 1);
  }

  {
    char str[] = "0x8";
    errno = 0;
    result = strtoull(str, &endptr, 0);
    EXPECT_EQUAL_UINT(result, 8);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 3);
  }

  {
    char str[] = "123456789012345";
    errno = 0;
    result = strtoull(str, &endptr, 10);
    EXPECT_EQUAL_UINT64(result, 123456789012345ULL);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 15);
  }

  {
    char str[] = "FFFFFFFFFFFFFFFF";
    errno = 0;
    result = strtoull(str, &endptr, 16);
    EXPECT_TRUE(result == ULLONG_MAX);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 16);
  }

  {
    char str[] = "102";
    errno = 0;
    result = strtoull(str, &endptr, 3);
    EXPECT_EQUAL_UINT(result, 11);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 3);
  }

  {
    char str[] = "123";
    errno = 0;
    result = strtoull(str, &endptr, 4);
    EXPECT_EQUAL_UINT(result, 27);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 3);
  }

  {
    char str[] = "1234";
    errno = 0;
    result = strtoull(str, &endptr, 5);
    EXPECT_EQUAL_UINT(result, 194);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 4);
  }

  {
    char str[] = "12345";
    errno = 0;
    result = strtoull(str, &endptr, 6);
    EXPECT_EQUAL_UINT(result, 1865);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 5);
  }

  {
    char str[] = "123456";
    errno = 0;
    result = strtoull(str, &endptr, 7);
    EXPECT_EQUAL_UINT(result, 22875);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 6);
  }

  {
    char str[] = "1234567";
    errno = 0;
    result = strtoull(str, &endptr, 9);
    EXPECT_EQUAL_UINT(result, 672604);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 7);
  }

  {
    char str[] = "A";
    errno = 0;
    result = strtoull(str, &endptr, 11);
    EXPECT_EQUAL_UINT(result, 10);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 1);
  }

  {
    char str[] = "a";
    errno = 0;
    result = strtoull(str, &endptr, 11);
    EXPECT_EQUAL_UINT(result, 10);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 1);
  }

  {
    char str[] = "1A";
    errno = 0;
    result = strtoull(str, &endptr, 11);
    EXPECT_EQUAL_UINT(result, 21);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 2);
  }

  {
    char str[] = "Y";
    errno = 0;
    result = strtoull(str, &endptr, 35);
    EXPECT_EQUAL_UINT(result, 34);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 1);
  }

  {
    char str[] = "10";
    errno = 0;
    result = strtoull(str, &endptr, 35);
    EXPECT_EQUAL_UINT(result, 35);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 2);
  }

  {
    char str[] = "0xABCD";
    errno = 0;
    result = strtoull(str, &endptr, 0);
    EXPECT_EQUAL_UINT(result, 43981);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 6);
  }

  {
    char str[] = "0Xabcd";
    errno = 0;
    result = strtoull(str, &endptr, 0);
    EXPECT_EQUAL_UINT(result, 43981);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 6);
  }

  {
    char str[] = "0777";
    errno = 0;
    result = strtoull(str, &endptr, 0);
    EXPECT_EQUAL_UINT(result, 511);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 4);
  }

  {
    char str[] = "0";
    errno = 0;
    result = strtoull(str, &endptr, 0);
    EXPECT_EQUAL_UINT(result, 0);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 1);
  }

  {
    char str[] = "00";
    errno = 0;
    result = strtoull(str, &endptr, 0);
    EXPECT_EQUAL_UINT(result, 0);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 2);
  }

  {
    char str[] = "0x0";
    errno = 0;
    result = strtoull(str, &endptr, 0);
    EXPECT_EQUAL_UINT(result, 0);
    EXPECT_TRUE(errno == 0);
    EXPECT_TRUE(endptr == str + 3);
  }
}
