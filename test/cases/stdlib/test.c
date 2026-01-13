#include <utest.h>

// numerics
#include "numerics/test_atoi.h"
#include "numerics/test_atol.h"
#include "numerics/test_atoll.h"
#include "numerics/test_abs.h"
#include "numerics/test_labs.h"
#include "numerics/test_llabs.h"
#include "numerics/test_imaxabs.h"

// algorithm
#include "algo/test_bsearch.h"

UTEST_TEST_SUITE(stdlib){
    UTEST_RUN_TEST_CASE(atoi);
    UTEST_RUN_TEST_CASE(atol);
    UTEST_RUN_TEST_CASE(atoll);
    UTEST_RUN_TEST_CASE(abs);
    UTEST_RUN_TEST_CASE(labs);
    UTEST_RUN_TEST_CASE(llabs);
    UTEST_RUN_TEST_CASE(imaxabs);
    UTEST_RUN_TEST_CASE(bsearch);
}