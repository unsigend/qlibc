#include <utest.h>
#include <stdalign.h>
#include <stddef.h>

UTEST_TEST_CASE(constants){
    EXPECT_EQUAL_INT(__alignas_is_defined, 1);
    EXPECT_EQUAL_INT(__alignof_is_defined, 1);
}

UTEST_TEST_CASE(macros){
    EXPECT_TRUE(alignof(char) > 0);
    EXPECT_TRUE(alignof(char) <= sizeof(char));
    
    EXPECT_TRUE(alignof(short) > 0);
    EXPECT_TRUE(alignof(short) <= sizeof(short));
    
    EXPECT_TRUE(alignof(int) > 0);
    EXPECT_TRUE(alignof(int) <= sizeof(int));
    
    EXPECT_TRUE(alignof(long) > 0);
    EXPECT_TRUE(alignof(long) <= sizeof(long));
    
    EXPECT_TRUE(alignof(long long) > 0);
    EXPECT_TRUE(alignof(long long) <= sizeof(long long));
    
    EXPECT_TRUE(alignof(float) > 0);
    EXPECT_TRUE(alignof(float) <= sizeof(float));
    
    EXPECT_TRUE(alignof(double) > 0);
    EXPECT_TRUE(alignof(double) <= sizeof(double));
    
    EXPECT_TRUE(alignof(long double) > 0);
    EXPECT_TRUE(alignof(long double) <= sizeof(long double));
    
    EXPECT_TRUE(alignof(void *) > 0);
    EXPECT_TRUE(alignof(void *) <= sizeof(void *));
    
    EXPECT_TRUE(alignof(size_t) > 0);
    EXPECT_TRUE(alignof(size_t) <= sizeof(size_t));
    
    EXPECT_TRUE(alignof(ptrdiff_t) > 0);
    EXPECT_TRUE(alignof(ptrdiff_t) <= sizeof(ptrdiff_t));
    
    {
        struct test_struct {
            char a;
            int b;
        };
        EXPECT_TRUE(alignof(struct test_struct) > 0);
        EXPECT_TRUE(alignof(struct test_struct) <= sizeof(struct test_struct));
    }
    
    {
        struct aligned_struct {
            alignas(16) char data[16];
        };
        EXPECT_TRUE(alignof(struct aligned_struct) >= 16);
    }
    
    {
        struct double_aligned {
            alignas(double) char c;
        };
        EXPECT_TRUE(alignof(struct double_aligned) >= alignof(double));
    }
    
    {
        EXPECT_TRUE(alignof(int[10]) == alignof(int));
    }
    
    {
        EXPECT_TRUE(alignof(char *) == alignof(void *));
    }
    
    {
        EXPECT_TRUE(alignof(char) == 1);
    }
    
    {
        EXPECT_TRUE(alignof(int) >= alignof(char));
        EXPECT_TRUE(alignof(long) >= alignof(int));
        EXPECT_TRUE(alignof(long long) >= alignof(long));
    }
    
    {
        EXPECT_TRUE(alignof(double) >= alignof(float));
        EXPECT_TRUE(alignof(long double) >= alignof(double));
    }
    
    {
        alignas(1) char c1;
        EXPECT_TRUE(alignof(c1) >= 1);
    }
    
    {
        alignas(2) char c2;
        EXPECT_TRUE(alignof(c2) >= 2);
    }
    
    {
        alignas(4) int i;
        EXPECT_TRUE(alignof(i) >= 4);
    }
    
    {
        alignas(8) long l;
        EXPECT_TRUE(alignof(l) >= 8);
    }
    
    {
        alignas(16) double d;
        EXPECT_TRUE(alignof(d) >= 16);
    }
    
    {
        alignas(int) char c;
        EXPECT_TRUE(alignof(c) >= alignof(int));
    }
    
    {
        alignas(long) int i;
        EXPECT_TRUE(alignof(i) >= alignof(long));
    }
}

UTEST_TEST_SUITE(stdalign){
    UTEST_RUN_TEST_CASE(constants);
    UTEST_RUN_TEST_CASE(macros);
}