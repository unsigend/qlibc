#include <utest.h>

// numerics
#include "numerics/test_atoi.h"
#include "numerics/test_atol.h"
#include "numerics/test_atoll.h"

// algorithm
#include "algo/test_bsearch.h"

UTEST_TEST_SUITE(stdlib){
    UTEST_RUN_TEST_CASE(atoi);
    UTEST_RUN_TEST_CASE(atol);
    UTEST_RUN_TEST_CASE(atoll);
    UTEST_RUN_TEST_CASE(bsearch);
}