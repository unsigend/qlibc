#ifndef _QLIBC_SOURCE
#define _GNU_SOURCE
#endif

#include <utest.h>

// numerics
#include "numerics/test_abs.h"
#include "numerics/test_atoi.h"
#include "numerics/test_atol.h"
#include "numerics/test_atoll.h"
#include "numerics/test_div.h"
#include "numerics/test_strtol.h"
#include "numerics/test_strtoll.h"
#include "numerics/test_strtoul.h"
#include "numerics/test_strtoull.h"

// algorithm
#include "algo/test_bsearch.h"

#include "program/test_env.h"

UTEST_TEST_SUITE(stdlib) {
  // ASCII to integer conversions
  UTEST_RUN_TEST_CASE(atoi);
  UTEST_RUN_TEST_CASE(atol);
  UTEST_RUN_TEST_CASE(atoll);

  UTEST_RUN_TEST_CASE(abs);
  UTEST_RUN_TEST_CASE(div);

  // algorithm
  UTEST_RUN_TEST_CASE(bsearch);

  // string to integer conversions
  UTEST_RUN_TEST_CASE(strtol);
  UTEST_RUN_TEST_CASE(strtoll);
  UTEST_RUN_TEST_CASE(strtoul);
  UTEST_RUN_TEST_CASE(strtoull);

  // environment variables
  UTEST_RUN_TEST_CASE(getenv);
  UTEST_RUN_TEST_CASE(putenv);
  UTEST_RUN_TEST_CASE(setenv);
  UTEST_RUN_TEST_CASE(unsetenv);
  UTEST_RUN_TEST_CASE(clearenv);
}