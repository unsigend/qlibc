#include <limits.h>
#include <utest.h>

UTEST_TEST_CASE(macros) {
  EXPECT_EQUAL_INT(CHAR_BIT, 8);
  EXPECT_TRUE(MB_LEN_MAX > 0);
  EXPECT_TRUE(MB_LEN_MAX >= 1);

  EXPECT_EQUAL_INT(SCHAR_MIN, CHAR_MIN);
  EXPECT_EQUAL_INT(SCHAR_MAX, CHAR_MAX);
  EXPECT_TRUE(SCHAR_MIN < 0);
  EXPECT_TRUE(SCHAR_MAX > 0);
  EXPECT_TRUE(SCHAR_MAX == 127);
  EXPECT_TRUE(SCHAR_MIN == -128);
  EXPECT_TRUE(sizeof(signed char) * CHAR_BIT == 8);

  EXPECT_TRUE(CHAR_MIN <= 0);
  EXPECT_TRUE(CHAR_MAX >= 0);
  EXPECT_TRUE(CHAR_MAX >= CHAR_MIN);
  EXPECT_TRUE(sizeof(char) * CHAR_BIT == CHAR_BIT);

  EXPECT_TRUE(SHRT_MIN < 0);
  EXPECT_TRUE(SHRT_MAX > 0);
  EXPECT_TRUE(SHRT_MAX == 0x7fff);
  EXPECT_TRUE(SHRT_MIN == -1 - SHRT_MAX);
  EXPECT_TRUE(sizeof(short) * CHAR_BIT >= 16);
  EXPECT_TRUE(sizeof(short) * CHAR_BIT <= 32);

  EXPECT_TRUE(INT_MIN < 0);
  EXPECT_TRUE(INT_MAX > 0);
  EXPECT_TRUE(INT_MAX == 0x7fffffff);
  EXPECT_TRUE(INT_MIN == -1 - INT_MAX);
  EXPECT_TRUE(sizeof(int) * CHAR_BIT >= 16);
  EXPECT_TRUE(sizeof(int) * CHAR_BIT <= 64);

  EXPECT_TRUE(LONG_MIN < 0);
  EXPECT_TRUE(LONG_MAX > 0);
  EXPECT_TRUE(LONG_MIN == -1 - LONG_MAX);
  EXPECT_TRUE(sizeof(long) * CHAR_BIT >= 32);
  EXPECT_TRUE(sizeof(long) * CHAR_BIT <= 64);

  EXPECT_TRUE(LLONG_MIN < 0);
  EXPECT_TRUE(LLONG_MAX > 0);
  EXPECT_TRUE(LLONG_MAX == 0x7fffffffffffffffLL);
  EXPECT_TRUE(LLONG_MIN == -1 - LLONG_MAX);
  EXPECT_TRUE(sizeof(long long) * CHAR_BIT >= 64);

  EXPECT_EQUAL_INT(UCHAR_MAX, 0xff);
  EXPECT_TRUE(UCHAR_MAX > 0);
  EXPECT_TRUE(UCHAR_MAX == 255);
  EXPECT_TRUE(sizeof(unsigned char) * CHAR_BIT == 8);

  EXPECT_EQUAL_INT(USHRT_MAX, 0xffff);
  EXPECT_TRUE(USHRT_MAX > 0);
  EXPECT_TRUE(USHRT_MAX == 65535);
  EXPECT_TRUE(sizeof(unsigned short) * CHAR_BIT >= 16);
  EXPECT_TRUE(sizeof(unsigned short) * CHAR_BIT <= 32);

  EXPECT_EQUAL_INT(UINT_MAX, 0xffffffffU);
  EXPECT_TRUE(UINT_MAX > 0);
  EXPECT_TRUE(UINT_MAX == 4294967295U);
  EXPECT_TRUE(sizeof(unsigned int) * CHAR_BIT >= 16);
  EXPECT_TRUE(sizeof(unsigned int) * CHAR_BIT <= 64);

  EXPECT_TRUE(ULONG_MAX > 0);
  EXPECT_TRUE(sizeof(unsigned long) * CHAR_BIT >= 32);
  EXPECT_TRUE(sizeof(unsigned long) * CHAR_BIT <= 64);

  EXPECT_EQUAL_INT(ULLONG_MAX, 0xffffffffffffffffULL);
  EXPECT_TRUE(ULLONG_MAX > 0);
  EXPECT_TRUE(sizeof(unsigned long long) * CHAR_BIT >= 64);
}

UTEST_TEST_CASE(relationships) {
  EXPECT_TRUE(SCHAR_MAX <= UCHAR_MAX);
  EXPECT_TRUE(SHRT_MAX <= USHRT_MAX);
  EXPECT_TRUE(INT_MAX <= UINT_MAX);
  EXPECT_TRUE(LONG_MAX <= ULONG_MAX);
  EXPECT_TRUE(LLONG_MAX <= ULLONG_MAX);

  EXPECT_TRUE(UCHAR_MAX == (unsigned char)-1);
  EXPECT_TRUE(USHRT_MAX == (unsigned short)-1);
  EXPECT_TRUE(UINT_MAX == (unsigned int)-1);
  EXPECT_TRUE(ULONG_MAX == (unsigned long)-1);
  EXPECT_TRUE(ULLONG_MAX == (unsigned long long)-1);

  EXPECT_TRUE(SCHAR_MIN == -SCHAR_MAX - 1);
  EXPECT_TRUE(SHRT_MIN == -SHRT_MAX - 1);
  EXPECT_TRUE(INT_MIN == -INT_MAX - 1);
  EXPECT_TRUE(LONG_MIN == -LONG_MAX - 1);
  EXPECT_TRUE(LLONG_MIN == -LLONG_MAX - 1);

  EXPECT_TRUE(sizeof(char) <= sizeof(short));
  EXPECT_TRUE(sizeof(short) <= sizeof(int));
  EXPECT_TRUE(sizeof(int) <= sizeof(long));
  EXPECT_TRUE(sizeof(long) <= sizeof(long long));
}

UTEST_TEST_CASE(size_consistency) {
  {
    unsigned char max = 0;
    max = ~max;
    EXPECT_EQUAL_INT(UCHAR_MAX, max);
  }

  {
    unsigned short max = 0;
    max = ~max;
    EXPECT_EQUAL_INT(USHRT_MAX, max);
  }

  {
    unsigned int max = 0;
    max = ~max;
    EXPECT_EQUAL_INT(UINT_MAX, max);
  }

  {
    unsigned long max = 0;
    max = ~max;
    EXPECT_EQUAL_INT(ULONG_MAX, max);
  }

  {
    unsigned long long max = 0;
    max = ~max;
    EXPECT_EQUAL_INT(ULLONG_MAX, max);
  }

  EXPECT_TRUE(sizeof(unsigned char) * CHAR_BIT == 8);
  EXPECT_TRUE(sizeof(unsigned short) * CHAR_BIT >= 16);
  EXPECT_TRUE(sizeof(unsigned int) * CHAR_BIT >= 16);
  EXPECT_TRUE(sizeof(unsigned long) * CHAR_BIT >= 32);
  EXPECT_TRUE(sizeof(unsigned long long) * CHAR_BIT >= 64);

  EXPECT_TRUE(sizeof(signed char) == sizeof(unsigned char));
  EXPECT_TRUE(sizeof(short) == sizeof(unsigned short));
  EXPECT_TRUE(sizeof(int) == sizeof(unsigned int));
  EXPECT_TRUE(sizeof(long) == sizeof(unsigned long));
  EXPECT_TRUE(sizeof(long long) == sizeof(unsigned long long));
}

UTEST_TEST_SUITE(limits) {
  UTEST_RUN_TEST_CASE(macros);
  UTEST_RUN_TEST_CASE(relationships);
  UTEST_RUN_TEST_CASE(size_consistency);
}
