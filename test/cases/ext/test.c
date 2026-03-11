#include <utest.h>
#if defined(_QLIBC) || defined(__QLIBC__) || defined(_QLIBC_SOURCE)
/* itoa test */
#include "itoa/test_itoa.h"
#include "itoa/test_utoa.h"
#endif

UTEST_TEST_SUITE(ext)
{
#if defined(_QLIBC) || defined(__QLIBC__) || defined(_QLIBC_SOURCE)
  /* itoa test */
  UTEST_RUN_TEST_CASE(itoa);
  UTEST_RUN_TEST_CASE(utoa);
#endif
}