#include <errno.h>
#include <ext/itoa.h>
#include <limits.h>
#include <utest.h>

#ifndef ITOA_BUFSZ
#define ITOA_BUFSZ 128
#endif

UTEST_TEST_CASE(utoa) {
  char buf[ITOA_BUFSZ];

  EXPECT_TRUE(ulltoa(0ULL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "0");
  EXPECT_TRUE(ulltoa(1ULL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "1");
  EXPECT_TRUE(ulltoa(9ULL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "9");
  EXPECT_TRUE(ulltoa(10ULL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(ulltoa(42ULL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "42");
  EXPECT_TRUE(ulltoa(99ULL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "99");
  EXPECT_TRUE(ulltoa(100ULL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "100");
  EXPECT_TRUE(ulltoa(999ULL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "999");
  EXPECT_TRUE(ulltoa(1000ULL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "1000");
  EXPECT_TRUE(ulltoa(999999ULL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "999999");
  EXPECT_TRUE(ulltoa(1234567890ULL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "1234567890");
  EXPECT_TRUE(ulltoa(ULLONG_MAX, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "18446744073709551615");
  EXPECT_TRUE(ulltoa(ULLONG_MAX - 1ULL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "18446744073709551614");

  EXPECT_TRUE(ulltoa(0ULL, buf, 2) == buf);
  EXPECT_EQUAL_STRING(buf, "0");
  EXPECT_TRUE(ulltoa(1ULL, buf, 2) == buf);
  EXPECT_EQUAL_STRING(buf, "1");
  EXPECT_TRUE(ulltoa(2ULL, buf, 2) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(ulltoa(3ULL, buf, 2) == buf);
  EXPECT_EQUAL_STRING(buf, "11");
  EXPECT_TRUE(ulltoa(4ULL, buf, 2) == buf);
  EXPECT_EQUAL_STRING(buf, "100");
  EXPECT_TRUE(ulltoa(7ULL, buf, 2) == buf);
  EXPECT_EQUAL_STRING(buf, "111");
  EXPECT_TRUE(ulltoa(15ULL, buf, 2) == buf);
  EXPECT_EQUAL_STRING(buf, "1111");
  EXPECT_TRUE(ulltoa(255ULL, buf, 2) == buf);
  EXPECT_EQUAL_STRING(buf, "11111111");
  EXPECT_TRUE(ulltoa(1023ULL, buf, 2) == buf);
  EXPECT_EQUAL_STRING(buf, "1111111111");
  EXPECT_TRUE(ulltoa(ULLONG_MAX, buf, 2) == buf);
  EXPECT_EQUAL_STRING(
      buf, "1111111111111111111111111111111111111111111111111111111111111111");

  EXPECT_TRUE(ulltoa(0ULL, buf, 3) == buf);
  EXPECT_EQUAL_STRING(buf, "0");
  EXPECT_TRUE(ulltoa(3ULL, buf, 3) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(ulltoa(0ULL, buf, 4) == buf);
  EXPECT_EQUAL_STRING(buf, "0");
  EXPECT_TRUE(ulltoa(4ULL, buf, 4) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(ulltoa(0ULL, buf, 5) == buf);
  EXPECT_EQUAL_STRING(buf, "0");
  EXPECT_TRUE(ulltoa(5ULL, buf, 5) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(ulltoa(0ULL, buf, 6) == buf);
  EXPECT_EQUAL_STRING(buf, "0");
  EXPECT_TRUE(ulltoa(6ULL, buf, 6) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(ulltoa(0ULL, buf, 7) == buf);
  EXPECT_EQUAL_STRING(buf, "0");
  EXPECT_TRUE(ulltoa(7ULL, buf, 7) == buf);
  EXPECT_EQUAL_STRING(buf, "10");

  EXPECT_TRUE(ulltoa(0ULL, buf, 8) == buf);
  EXPECT_EQUAL_STRING(buf, "0");
  EXPECT_TRUE(ulltoa(7ULL, buf, 8) == buf);
  EXPECT_EQUAL_STRING(buf, "7");
  EXPECT_TRUE(ulltoa(8ULL, buf, 8) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(ulltoa(511ULL, buf, 8) == buf);
  EXPECT_EQUAL_STRING(buf, "777");
  EXPECT_TRUE(ulltoa(0777ULL, buf, 8) == buf);
  EXPECT_EQUAL_STRING(buf, "777");
  EXPECT_TRUE(ulltoa(ULLONG_MAX, buf, 8) == buf);
  EXPECT_EQUAL_STRING(buf, "1777777777777777777777");

  EXPECT_TRUE(ulltoa(0ULL, buf, 9) == buf);
  EXPECT_EQUAL_STRING(buf, "0");
  EXPECT_TRUE(ulltoa(9ULL, buf, 9) == buf);
  EXPECT_EQUAL_STRING(buf, "10");

  EXPECT_TRUE(ulltoa(0ULL, buf, 16) == buf);
  EXPECT_EQUAL_STRING(buf, "0");
  EXPECT_TRUE(ulltoa(15ULL, buf, 16) == buf);
  EXPECT_EQUAL_STRING(buf, "f");
  EXPECT_TRUE(ulltoa(255ULL, buf, 16) == buf);
  EXPECT_EQUAL_STRING(buf, "ff");
  EXPECT_TRUE(ulltoa(0xffULL, buf, 16) == buf);
  EXPECT_EQUAL_STRING(buf, "ff");
  EXPECT_TRUE(ulltoa(0x100ULL, buf, 16) == buf);
  EXPECT_EQUAL_STRING(buf, "100");
  EXPECT_TRUE(ulltoa(0xdeadbeefULL, buf, 16) == buf);
  EXPECT_EQUAL_STRING(buf, "deadbeef");
  EXPECT_TRUE(ulltoa(0xffffffffULL, buf, 16) == buf);
  EXPECT_EQUAL_STRING(buf, "ffffffff");
  EXPECT_TRUE(ulltoa(ULLONG_MAX, buf, 16) == buf);
  EXPECT_EQUAL_STRING(buf, "ffffffffffffffff");

  EXPECT_TRUE(ulltoa(10ULL, buf, 11) == buf);
  EXPECT_EQUAL_STRING(buf, "a");
  EXPECT_TRUE(ulltoa(11ULL, buf, 11) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(ulltoa(11ULL, buf, 12) == buf);
  EXPECT_EQUAL_STRING(buf, "b");
  EXPECT_TRUE(ulltoa(12ULL, buf, 12) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(ulltoa(12ULL, buf, 13) == buf);
  EXPECT_EQUAL_STRING(buf, "c");
  EXPECT_TRUE(ulltoa(13ULL, buf, 13) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(ulltoa(20ULL, buf, 20) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(ulltoa(24ULL, buf, 24) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(ulltoa(28ULL, buf, 28) == buf);
  EXPECT_EQUAL_STRING(buf, "10");

  EXPECT_TRUE(ulltoa(29ULL, buf, 30) == buf);
  EXPECT_EQUAL_STRING(buf, "t");
  EXPECT_TRUE(ulltoa(30ULL, buf, 30) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(ulltoa(31ULL, buf, 32) == buf);
  EXPECT_EQUAL_STRING(buf, "v");
  EXPECT_TRUE(ulltoa(32ULL, buf, 32) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(ulltoa(35ULL, buf, 36) == buf);
  EXPECT_EQUAL_STRING(buf, "z");
  EXPECT_TRUE(ulltoa(36ULL, buf, 36) == buf);
  EXPECT_EQUAL_STRING(buf, "10");
  EXPECT_TRUE(ulltoa(1295ULL, buf, 36) == buf);
  EXPECT_EQUAL_STRING(buf, "zz");
  EXPECT_TRUE(ulltoa(36ULL * 36ULL - 1ULL, buf, 36) == buf);
  EXPECT_EQUAL_STRING(buf, "zz");
  EXPECT_TRUE(ulltoa(ULLONG_MAX, buf, 36) == buf);
  EXPECT_EQUAL_STRING(buf, "3w5e11264sgsf");

  EXPECT_TRUE(utoa(0u, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "0");
  EXPECT_TRUE(utoa(1u, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "1");
  EXPECT_TRUE(utoa(255u, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "255");
  EXPECT_TRUE(utoa(65535u, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "65535");
  EXPECT_TRUE(utoa(UINT_MAX, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "4294967295");
  EXPECT_TRUE(utoa(UINT_MAX - 1u, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "4294967294");
  EXPECT_TRUE(utoa(255u, buf, 16) == buf);
  EXPECT_EQUAL_STRING(buf, "ff");
#if UINT_MAX == 0xffffffffu
  EXPECT_TRUE(utoa(UINT_MAX, buf, 2) == buf);
  EXPECT_EQUAL_STRING(buf, "11111111111111111111111111111111");
  EXPECT_TRUE(utoa(UINT_MAX, buf, 8) == buf);
  EXPECT_EQUAL_STRING(buf, "37777777777");
#endif

  EXPECT_TRUE(ultoa(0UL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "0");
  EXPECT_TRUE(ultoa(1UL, buf, 10) == buf);
  EXPECT_EQUAL_STRING(buf, "1");
  EXPECT_TRUE(ultoa(ULONG_MAX, buf, 10) == buf);
#if ULONG_MAX == 0xffffffffUL
  EXPECT_EQUAL_STRING(buf, "4294967295");
#else
  EXPECT_EQUAL_STRING(buf, "18446744073709551615");
#endif
  EXPECT_TRUE(ultoa(ULONG_MAX, buf, 16) == buf);
#if ULONG_MAX == 0xffffffffUL
  EXPECT_EQUAL_STRING(buf, "ffffffff");
#else
  EXPECT_EQUAL_STRING(buf, "ffffffffffffffff");
#endif
  EXPECT_TRUE(ultoa(255UL, buf, 16) == buf);
  EXPECT_EQUAL_STRING(buf, "ff");
#if ULONG_MAX == 0xffffffffUL
  EXPECT_TRUE(ultoa(ULONG_MAX, buf, 2) == buf);
  EXPECT_EQUAL_STRING(buf, "11111111111111111111111111111111");
  EXPECT_TRUE(ultoa(ULONG_MAX, buf, 8) == buf);
  EXPECT_EQUAL_STRING(buf, "37777777777");
#else
  EXPECT_TRUE(ultoa(ULONG_MAX, buf, 2) == buf);
  EXPECT_EQUAL_STRING(
      buf, "1111111111111111111111111111111111111111111111111111111111111111");
  EXPECT_TRUE(ultoa(ULONG_MAX, buf, 8) == buf);
  EXPECT_EQUAL_STRING(buf, "1777777777777777777777");
#endif

  buf[0] = 'x';
  buf[1] = '\0';
  errno = 0;
  EXPECT_TRUE(utoa(1u, buf, 0) == buf);
  EXPECT_TRUE(errno == EINVAL);
  errno = 0;
  EXPECT_TRUE(utoa(1u, buf, 37) == buf);
  EXPECT_TRUE(errno == EINVAL);
  errno = 0;
  EXPECT_TRUE(ultoa(1UL, buf, 0) == buf);
  EXPECT_TRUE(errno == EINVAL);
  errno = 0;
  EXPECT_TRUE(ulltoa(1ULL, buf, 0) == buf);
  EXPECT_TRUE(errno == EINVAL);
  errno = 0;
  EXPECT_TRUE(ulltoa(1ULL, buf, 1) == buf);
  EXPECT_TRUE(errno == EINVAL);
  errno = 0;
  EXPECT_TRUE(ulltoa(1ULL, buf, 37) == buf);
  EXPECT_TRUE(errno == EINVAL);
  errno = 0;
  EXPECT_TRUE(ulltoa(1ULL, buf, -1) == buf);
  EXPECT_TRUE(errno == EINVAL);
}
