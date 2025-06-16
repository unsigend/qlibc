#include <utest.h>

#include "test_atoi.h"
#include "test_atol.h"
#include "test_atoll.h"

UTEST_TEST_SUITE(stdlib){
    UTEST_RUN_TEST_CASE(atoi);
    UTEST_RUN_TEST_CASE(atol);
    UTEST_RUN_TEST_CASE(atoll);
}
