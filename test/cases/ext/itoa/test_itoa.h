#include <errno.h>
#include <ext/itoa.h>
#include <limits.h>
#include <utest.h>

#ifndef ITOA_BUFSZ
#define ITOA_BUFSZ 128
#endif

UTEST_TEST_CASE(itoa) {
  char buf[ITOA_BUFSZ];

  EXPECT_TRUE(lltoa(0LL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "0");
  EXPECT_TRUE(lltoa(1LL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "1");
  EXPECT_TRUE(lltoa(-1LL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "-1");
  EXPECT_TRUE(lltoa(9LL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "9");
  EXPECT_TRUE(lltoa(10LL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(lltoa(42LL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "42");
  EXPECT_TRUE(lltoa(-42LL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "-42");
  EXPECT_TRUE(lltoa(99LL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "99");
  EXPECT_TRUE(lltoa(100LL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "100");
  EXPECT_TRUE(lltoa(999LL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "999");
  EXPECT_TRUE(lltoa(1000LL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "1000");
  EXPECT_TRUE(lltoa(1234567890LL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "1234567890");
  EXPECT_TRUE(lltoa(-1234567890LL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "-1234567890");
  EXPECT_TRUE(lltoa(LLONG_MAX, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "9223372036854775807");
  EXPECT_TRUE(lltoa(LLONG_MIN, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "-9223372036854775808");

  EXPECT_TRUE(lltoa(0LL, buf, 2) == buf);
  EXPECT_EQUAL_STRING(buf, "0");
  EXPECT_TRUE(lltoa(1LL, buf, 2) == buf);
  EXPECT_EQUAL_STRING(buf, "1");
  EXPECT_TRUE(lltoa(2LL, buf, 2) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(lltoa(3LL, buf, 2) == buf);
  EXPECT_EQUAL_STRING(buf, "11");
  EXPECT_TRUE(lltoa(4LL, buf, 2) == buf);
  EXPECT_EQUAL_STRING(buf, "100");
  EXPECT_TRUE(lltoa(7LL, buf, 2) == buf);
  EXPECT_EQUAL_STRING(buf, "111");
  EXPECT_TRUE(lltoa(15LL, buf, 2) == buf);
  EXPECT_EQUAL_STRING(buf, "1111");
  EXPECT_TRUE(lltoa(255LL, buf, 2) == buf);
  EXPECT_EQUAL_STRING(buf, "11111111");
  EXPECT_TRUE(lltoa(1023LL, buf, 2) == buf);
  EXPECT_EQUAL_STRING(buf, "1111111111");
  EXPECT_TRUE(lltoa(LLONG_MAX, buf, 2) == buf);
  EXPECT_EQUAL_STRING(
      buf, "111111111111111111111111111111111111111111111111111111111111111");

  EXPECT_TRUE(lltoa(0LL, buf, 3) == buf);
  EXPECT_EQUAL_STRING(buf, "0");
  EXPECT_TRUE(lltoa(2LL, buf, 3) == buf);
  EXPECT_EQUAL_STRING(buf, "2");
  EXPECT_TRUE(lltoa(3LL, buf, 3) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(lltoa(8LL, buf, 3) == buf);
  EXPECT_EQUAL_STRING(buf, "22");
  EXPECT_TRUE(lltoa(0LL, buf, 4) == buf);
  EXPECT_EQUAL_STRING(buf, "0");
  EXPECT_TRUE(lltoa(4LL, buf, 4) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(lltoa(0LL, buf, 5) == buf);
  EXPECT_EQUAL_STRING(buf, "0");
  EXPECT_TRUE(lltoa(5LL, buf, 5) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(lltoa(0LL, buf, 6) == buf);
  EXPECT_EQUAL_STRING(buf, "0");
  EXPECT_TRUE(lltoa(6LL, buf, 6) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(lltoa(0LL, buf, 7) == buf);
  EXPECT_EQUAL_STRING(buf, "0");
  EXPECT_TRUE(lltoa(7LL, buf, 7) == buf);
  EXPECT_EQUAL_STRING(buf, "10");

  EXPECT_TRUE(lltoa(0LL, buf, 8) == buf);
  EXPECT_EQUAL_STRING(buf, "0");
  EXPECT_TRUE(lltoa(7LL, buf, 8) == buf);
  EXPECT_EQUAL_STRING(buf, "7");
  EXPECT_TRUE(lltoa(8LL, buf, 8) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(lltoa(511LL, buf, 8) == buf);
  EXPECT_EQUAL_STRING(buf, "777");
  EXPECT_TRUE(lltoa(0777LL, buf, 8) == buf);
  EXPECT_EQUAL_STRING(buf, "777");
  EXPECT_TRUE(lltoa(LLONG_MAX, buf, 8) == buf);
  EXPECT_EQUAL_STRING(buf, "777777777777777777777");

  EXPECT_TRUE(lltoa(0LL, buf, 9) == buf);
  EXPECT_EQUAL_STRING(buf, "0");
  EXPECT_TRUE(lltoa(9LL, buf, 9) == buf);
  EXPECT_EQUAL_STRING(buf, "10");

  EXPECT_TRUE(lltoa(0LL, buf, 16) == buf);
  EXPECT_EQUAL_STRING(buf, "0");
  EXPECT_TRUE(lltoa(15LL, buf, 16) == buf);
  EXPECT_EQUAL_STRING(buf, "f");
  EXPECT_TRUE(lltoa(255LL, buf, 16) == buf);
  EXPECT_EQUAL_STRING(buf, "ff");
  EXPECT_TRUE(lltoa(256LL, buf, 16) == buf);
  EXPECT_EQUAL_STRING(buf, "100");
  EXPECT_TRUE(lltoa(0xdeadbeefLL, buf, 16) == buf);
  EXPECT_EQUAL_STRING(buf, "deadbeef");
  EXPECT_TRUE(lltoa(-1LL, buf, 16) == buf);
  EXPECT_EQUAL_STRING(buf, "ffffffffffffffff");
  EXPECT_TRUE(lltoa(LLONG_MAX, buf, 16) == buf);
  EXPECT_EQUAL_STRING(buf, "7fffffffffffffff");

  EXPECT_TRUE(lltoa(10LL, buf, 11) == buf);
  EXPECT_EQUAL_STRING(buf, "a");
  EXPECT_TRUE(lltoa(11LL, buf, 11) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(lltoa(11LL, buf, 12) == buf);
  EXPECT_EQUAL_STRING(buf, "b");
  EXPECT_TRUE(lltoa(12LL, buf, 12) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(lltoa(12LL, buf, 13) == buf);
  EXPECT_EQUAL_STRING(buf, "c");
  EXPECT_TRUE(lltoa(13LL, buf, 13) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(lltoa(20LL, buf, 20) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(lltoa(24LL, buf, 24) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(lltoa(28LL, buf, 28) == buf);
  EXPECT_EQUAL_STRING(buf, "10");

  EXPECT_TRUE(lltoa(29LL, buf, 30) == buf);
  EXPECT_EQUAL_STRING(buf, "t");
  EXPECT_TRUE(lltoa(30LL, buf, 30) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(lltoa(31LL, buf, 32) == buf);
  EXPECT_EQUAL_STRING(buf, "v");
  EXPECT_TRUE(lltoa(32LL, buf, 32) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(lltoa(35LL, buf, 36) == buf);
  EXPECT_EQUAL_STRING(buf, "z");
  EXPECT_TRUE(lltoa(36LL, buf, 36) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(lltoa(1295LL, buf, 36) == buf);
  EXPECT_EQUAL_STRING(buf, "zz");
  EXPECT_TRUE(lltoa(LLONG_MAX, buf, 36) == buf);
  EXPECT_EQUAL_STRING(buf, "1y2p0ij32e8e7");

  EXPECT_TRUE(itoa(0, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "0");
  EXPECT_TRUE(itoa(1, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "1");
  EXPECT_TRUE(itoa(-1, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "-1");
  EXPECT_TRUE(itoa(32767, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "32767");
  EXPECT_TRUE(itoa(INT_MAX, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "2147483647");
  EXPECT_TRUE(itoa(INT_MIN, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "-2147483648");
  EXPECT_TRUE(itoa(255, buf, 16) == buf);
  EXPECT_EQUAL_STRING(buf, "ff");
  EXPECT_TRUE(itoa(-1, buf, 16) == buf);
#if INT_MAX == 0x7fffffff
  EXPECT_EQUAL_STRING(buf, "ffffffff");
#else
  EXPECT_EQUAL_STRING(buf, "ffffffffffffffff");
#endif
  EXPECT_TRUE(itoa(INT_MAX, buf, 2) == buf);
  EXPECT_EQUAL_STRING(buf, "1111111111111111111111111111111");
  EXPECT_TRUE(itoa(INT_MAX, buf, 8) == buf);
  EXPECT_EQUAL_STRING(buf, "17777777777");
  EXPECT_TRUE(itoa(INT_MIN, buf, 16) == buf);
  EXPECT_EQUAL_STRING(buf, "80000000");

  EXPECT_TRUE(ltoa(0L, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "0");
  EXPECT_TRUE(ltoa(-1L, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "-1");
  EXPECT_TRUE(ltoa(LONG_MAX, buf, 10) == buf);
#if LONG_MAX == 0x7fffffffL
  EXPECT_EQUAL_STRING(buf, "2147483647");
#else
  EXPECT_EQUAL_STRING(buf, "9223372036854775807");
#endif
  EXPECT_TRUE(ltoa(LONG_MIN, buf, 10) == buf);
#if LONG_MIN == (-0x7fffffffL - 1L)
  EXPECT_EQUAL_STRING(buf, "-2147483648");
#else
  EXPECT_EQUAL_STRING(buf, "-9223372036854775808");
#endif
  EXPECT_TRUE(ltoa(255L, buf, 16) == buf);
  EXPECT_EQUAL_STRING(buf, "ff");
  EXPECT_TRUE(ltoa(-1L, buf, 16) == buf);
#if LONG_MAX == 0x7fffffffL
  EXPECT_EQUAL_STRING(buf, "ffffffff");
#else
  EXPECT_EQUAL_STRING(buf, "ffffffffffffffff");
#endif
#if LONG_MAX == 0x7fffffffL
  EXPECT_TRUE(ltoa(LONG_MAX, buf, 2) == buf);
  EXPECT_EQUAL_STRING(buf, "1111111111111111111111111111111");
  EXPECT_TRUE(ltoa(LONG_MIN, buf, 16) == buf);
  EXPECT_EQUAL_STRING(buf, "80000000");
#else
  EXPECT_TRUE(ltoa(LONG_MAX, buf, 2) == buf);
  EXPECT_EQUAL_STRING(
      buf, "111111111111111111111111111111111111111111111111111111111111111");
  EXPECT_TRUE(ltoa(LONG_MIN, buf, 16) == buf);
  EXPECT_EQUAL_STRING(buf, "8000000000000000");
#endif
  buf[0] = 'x';
  buf[1] = '\0';
  errno = 0;
  EXPECT_TRUE(itoa(1, buf, 0) == buf);
  EXPECT_TRUE(errno == EINVAL);
  errno = 0;
  EXPECT_TRUE(itoa(1, buf, 37) == buf);
  EXPECT_TRUE(errno == EINVAL);
  errno = 0;
  EXPECT_TRUE(ltoa(1L, buf, 0) == buf);
  EXPECT_TRUE(errno == EINVAL);
  errno = 0;
  EXPECT_TRUE(lltoa(1LL, buf, 0) == buf);
  EXPECT_TRUE(errno == EINVAL);
  errno = 0;
  EXPECT_TRUE(lltoa(1LL, buf, 1) == buf);
  EXPECT_TRUE(errno == EINVAL);
  errno = 0;
  EXPECT_TRUE(lltoa(1LL, buf, 37) == buf);
  EXPECT_TRUE(errno == EINVAL);
  errno = 0;
  EXPECT_TRUE(lltoa(1LL, buf, -1) == buf);
  EXPECT_TRUE(errno == EINVAL);
}
