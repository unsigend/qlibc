#include <time.h>
#include <utest.h>

UTEST_TEST_CASE(type)
{
  EXPECT_TRUE(sizeof(time_t) == sizeof(long));
  EXPECT_TRUE(sizeof(clock_t) == sizeof(long));
#if __USE_ISO_C11
  EXPECT_TRUE(sizeof(struct timespec) == (sizeof(long) + sizeof(long)));
#endif
}

UTEST_TEST_SUITE(time) { UTEST_RUN_TEST_CASE(type); }