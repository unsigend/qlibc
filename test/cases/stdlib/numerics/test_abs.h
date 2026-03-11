#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <utest.h>
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#include <inttypes.h>
#endif

UTEST_TEST_CASE(abs)
{
  EXPECT_EQUAL_INT(llabs(0LL), 0);
  EXPECT_EQUAL_INT(llabs(1LL), 1);
  EXPECT_EQUAL_INT(llabs(-1LL), 1);
  EXPECT_EQUAL_INT(llabs(123LL), 123);
  EXPECT_EQUAL_INT(llabs(-123LL), 123);
  EXPECT_EQUAL_INT(llabs(456789LL), 456789);
  EXPECT_EQUAL_INT(llabs(-456789LL), 456789);
  EXPECT_EQUAL_INT(llabs(1000LL), 1000);
  EXPECT_EQUAL_INT(llabs(-1000LL), 1000);
  EXPECT_EQUAL_INT(llabs(32767LL), 32767);
  EXPECT_EQUAL_INT(llabs(-32767LL), 32767);
  EXPECT_EQUAL_INT(llabs(2147483647LL), 2147483647);
  EXPECT_EQUAL_INT(llabs(-2147483647LL), 2147483647);
  EXPECT_EQUAL_INT(llabs(9223372036854775807LL), 9223372036854775807LL);
  EXPECT_EQUAL_INT(llabs(-9223372036854775807LL), 9223372036854775807LL);
  EXPECT_EQUAL_INT(llabs(LLONG_MAX), LLONG_MAX);
  EXPECT_EQUAL_INT(llabs(-LLONG_MAX), LLONG_MAX);
  {
    long long val = 42LL;
    EXPECT_EQUAL_INT(llabs(val), 42);
    val = -42LL;
    EXPECT_EQUAL_INT(llabs(val), 42);
  }
  {
    long long val = 999LL;
    EXPECT_EQUAL_INT(llabs(val), 999);
    EXPECT_EQUAL_INT(llabs(-val), 999);
  }
  {
    long long val = 2000000000LL;
    EXPECT_EQUAL_INT(llabs(val), 2000000000);
    EXPECT_EQUAL_INT(llabs(-val), 2000000000);
  }
  {
    long long val = 9000000000LL;
    EXPECT_EQUAL_INT(llabs(val), 9000000000LL);
    EXPECT_EQUAL_INT(llabs(-val), 9000000000LL);
  }
  {
    long long val = 5000000000000LL;
    EXPECT_EQUAL_INT(llabs(val), 5000000000000LL);
    EXPECT_EQUAL_INT(llabs(-val), 5000000000000LL);
  }
  {
    long long val = 9000000000000000000LL;
    EXPECT_EQUAL_INT(llabs(val), 9000000000000000000LL);
    EXPECT_EQUAL_INT(llabs(-val), 9000000000000000000LL);
  }

  EXPECT_EQUAL_INT(abs(0), 0);
  EXPECT_EQUAL_INT(abs(1), 1);
  EXPECT_EQUAL_INT(abs(-1), 1);
  EXPECT_EQUAL_INT(abs(123), 123);
  EXPECT_EQUAL_INT(abs(-123), 123);
  EXPECT_EQUAL_INT(abs(INT_MAX), INT_MAX);
  EXPECT_EQUAL_INT(abs(-INT_MAX), INT_MAX);
  {
    int val = 42;
    EXPECT_EQUAL_INT(abs(val), 42);
    val = -42;
    EXPECT_EQUAL_INT(abs(val), 42);
  }
  {
    int val = 2000000000;
    EXPECT_EQUAL_INT(abs(val), 2000000000);
    EXPECT_EQUAL_INT(abs(-val), 2000000000);
  }

  EXPECT_EQUAL_INT(labs(0L), 0);
  EXPECT_EQUAL_INT(labs(1L), 1);
  EXPECT_EQUAL_INT(labs(-1L), 1);
  EXPECT_EQUAL_INT(labs(123L), 123);
  EXPECT_EQUAL_INT(labs(-123L), 123);
  EXPECT_EQUAL_INT(labs(LONG_MAX), LONG_MAX);
  EXPECT_EQUAL_INT(labs(-LONG_MAX), LONG_MAX);
  {
    long val = 42L;
    EXPECT_EQUAL_INT(labs(val), 42);
    val = -42L;
    EXPECT_EQUAL_INT(labs(val), 42);
  }
  {
    long val = 2000000000L;
    EXPECT_EQUAL_INT(labs(val), 2000000000L);
    EXPECT_EQUAL_INT(labs(-val), 2000000000L);
  }
#if LONG_MAX > 0x7fffffffL
  {
    long val = 9000000000000000000L;
    EXPECT_EQUAL_INT(labs(val), 9000000000000000000L);
    EXPECT_EQUAL_INT(labs(-val), 9000000000000000000L);
  }
#endif

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
  EXPECT_EQUAL_INT(imaxabs(0), 0);
  EXPECT_EQUAL_INT(imaxabs(1), 1);
  EXPECT_EQUAL_INT(imaxabs(-1), 1);
  EXPECT_EQUAL_INT(imaxabs(123), 123);
  EXPECT_EQUAL_INT(imaxabs(-123), 123);
  EXPECT_EQUAL_INT(imaxabs(INTMAX_MAX), INTMAX_MAX);
  EXPECT_EQUAL_INT(imaxabs(-INTMAX_MAX), INTMAX_MAX);
  {
    intmax_t val = 42;
    EXPECT_EQUAL_INT(imaxabs(val), 42);
    val = -42;
    EXPECT_EQUAL_INT(imaxabs(val), 42);
  }
  {
    intmax_t val = 2000000000;
    EXPECT_EQUAL_INT(imaxabs(val), 2000000000);
    EXPECT_EQUAL_INT(imaxabs(-val), 2000000000);
  }
#if INTMAX_MAX > 0x7fffffff
  {
    intmax_t val = 9000000000000000000;
    EXPECT_EQUAL_INT(imaxabs(val), 9000000000000000000);
    EXPECT_EQUAL_INT(imaxabs(-val), 9000000000000000000);
  }
#endif
#endif
}
