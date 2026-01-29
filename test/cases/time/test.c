#include <time.h>
#include <utest.h>

UTEST_TEST_CASE(type) {
  EXPECT_TRUE(sizeof(time_t) == sizeof(long));
  EXPECT_TRUE(sizeof(struct timespec) == (sizeof(long) + sizeof(long)));
}

UTEST_TEST_SUITE(time) { UTEST_RUN_TEST_CASE(type); }