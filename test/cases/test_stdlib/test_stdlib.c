#include <utest.h>

#include "test_atoi.h"
#include "test_atol.h"
#include "test_atoll.h"
#include "test_strtol.h"
#include "test_strtoll.h"

UTEST_TEST_SUITE(stdlib){
    UTEST_RUN_TEST_CASE(atoi);
    UTEST_RUN_TEST_CASE(atol);
    UTEST_RUN_TEST_CASE(atoll);
    UTEST_RUN_TEST_CASE(strtol);
    UTEST_RUN_TEST_CASE(strtoll);
}
