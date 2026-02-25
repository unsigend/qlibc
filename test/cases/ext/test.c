#include "itoa/test_itoa.h"
#include "itoa/test_utoa.h"

UTEST_TEST_SUITE(ext) {
  UTEST_RUN_TEST_CASE(itoa);
  UTEST_RUN_TEST_CASE(utoa);
}