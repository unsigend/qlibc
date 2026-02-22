#include <signal.h>
#include <utest.h>

UTEST_TEST_CASE(types) {
  EXPECT_EQUAL_UINT(sizeof(sig_atomic_t), sizeof(int));
#ifdef __GNUC__
  EXPECT_EQUAL_UINT(sizeof(__sighandler_t), sizeof(void *));
#elif defined(_QLIBC_SOURCE) || defined(__QLIBC__)
  EXPECT_EQUAL_UINT(sizeof(sighandler_t), sizeof(void *));
#endif
}

UTEST_TEST_CASE(macros) {}

UTEST_TEST_SUITE(signal) {
  UTEST_RUN_TEST_CASE(types);
  UTEST_RUN_TEST_CASE(macros);
}