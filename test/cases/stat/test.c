#include <sys/stat.h>
#ifdef __GNUC__
#include <sys/types.h>
#endif
#include <utest.h>

UTEST_TEST_CASE(types) {
  EXPECT_EQUAL_UINT(sizeof(mode_t), sizeof(unsigned int));
}

UTEST_TEST_SUITE(sys_stat) { UTEST_RUN_TEST_CASE(types); }