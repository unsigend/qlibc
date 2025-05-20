#include <utest.h>
#include <assert.h>

int always_false(){
    return 0;
}
// test for assert
UTEST_TEST_CASE(assert){

#define NDEBUG
#include <assert.h>

// it should pass here
    assert(always_false());
}

UTEST_TEST_SUITE(assert){
    UTEST_RUN_TEST_CASE(assert);
}