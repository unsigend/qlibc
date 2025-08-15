#include <utest.h>

// conversions to and from numeric formats
#include "test_atoi.h"
#include "test_atol.h"
#include "test_atoll.h"
// #include "test_strtol.h"
// #include "test_strtoll.h"

// memory management
#include "test_malloc.h"

// algorithm
#include "test_bsearch.h"
#include "test_qsort.h"

UTEST_TEST_SUITE(stdlib){
    UTEST_RUN_TEST_CASE(atoi);
    UTEST_RUN_TEST_CASE(atol);
    UTEST_RUN_TEST_CASE(atoll);
    // UTEST_RUN_TEST_CASE(strtol);
    // UTEST_RUN_TEST_CASE(strtoll);

    UTEST_RUN_TEST_CASE(malloc);

    UTEST_RUN_TEST_CASE(bsearch);
    UTEST_RUN_TEST_CASE(qsort);
}
