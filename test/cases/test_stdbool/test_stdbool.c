#include <stdbool.h>
#include <utest.h>

UTEST_TEST_CASE(stdbool_macro){
    EXPECT_TRUE(__bool_true_false_are_defined);
    EXPECT_EQUAL_UINT(sizeof(bool), sizeof(char));

    EXPECT_TRUE(true);
    EXPECT_FALSE(false);
}

UTEST_TEST_SUITE(stdbool){
    UTEST_RUN_TEST_CASE(stdbool_macro);
}