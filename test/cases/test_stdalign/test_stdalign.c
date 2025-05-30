#include <stdalign.h>
#include <utest.h>

UTEST_TEST_CASE(stdalign_macro){
    EXPECT_TRUE(__alignas_is_defined);
    EXPECT_TRUE(__alignof_is_defined);
}

UTEST_TEST_CASE(stdalign_alignof){
    EXPECT_EQUAL_UINT(alignof(char), 1);
    EXPECT_EQUAL_UINT(alignof(short), 2);
    EXPECT_EQUAL_UINT(alignof(int), 4);
    
#ifdef __i386__
    EXPECT_EQUAL_UINT(alignof(long), 4);
#else
    EXPECT_EQUAL_UINT(alignof(long), 8);
#endif

    EXPECT_EQUAL_UINT(alignof(float), 4);

#ifdef __i386__
    EXPECT_EQUAL_UINT(alignof(void *), 4);
    EXPECT_EQUAL_UINT(alignof(double), 4);
#else
    EXPECT_EQUAL_UINT(alignof(void *), 8);
    EXPECT_EQUAL_UINT(alignof(double), 8);
#endif

}
UTEST_TEST_SUITE(stdalign){
    UTEST_RUN_TEST_CASE(stdalign_macro);
    UTEST_RUN_TEST_CASE(stdalign_alignof);
}