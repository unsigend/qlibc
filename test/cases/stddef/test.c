#include <utest.h>
#include <stddef.h>

UTEST_TEST_CASE(types){
    EXPECT_TRUE(sizeof(size_t));
    EXPECT_TRUE(sizeof(ptrdiff_t));
    EXPECT_TRUE(sizeof(size_t) == sizeof(ptrdiff_t));
    EXPECT_TRUE(sizeof(size_t) >= sizeof(void *));
    EXPECT_TRUE(sizeof(ptrdiff_t) >= sizeof(void *));
    
    {
        size_t s = 0;
        s++;
        EXPECT_TRUE(s == 1);
    }
    
    {
        ptrdiff_t p = 0;
        p--;
        EXPECT_TRUE(p < 0);
    }
    
    {
        size_t max_val = (size_t)-1;
        EXPECT_TRUE(max_val > 0);
    }
    
    {
        ptrdiff_t min_val = (ptrdiff_t)1 << (sizeof(ptrdiff_t) * 8 - 1);
        EXPECT_TRUE(min_val < 0);
    }
    
    {
        int arr[10];
        size_t index = 5;
        int *ptr = arr + index;
        ptrdiff_t diff = ptr - arr;
        EXPECT_TRUE(diff == 5);
    }
    
    {
        char str[] = "test";
        char *p1 = str;
        char *p2 = str + 2;
        ptrdiff_t diff = p2 - p1;
        EXPECT_TRUE(diff == 2);
    }
    
    {
        int arr[100];
        size_t len = sizeof(arr) / sizeof(arr[0]);
        EXPECT_EQUAL_UINT(len, 100);
    }
    
    {
        size_t size = sizeof(int);
        EXPECT_TRUE(size > 0);
        EXPECT_TRUE(size <= sizeof(long));
    }
}

UTEST_TEST_CASE(constants){
    void *null_ptr = NULL;
    EXPECT_NULL(null_ptr);
    
    int *int_ptr = NULL;
    EXPECT_NULL(int_ptr);
    
    char *char_ptr = NULL;
    EXPECT_NULL(char_ptr);
    
    {
        int x = 5;
        int *ptr = &x;
        EXPECT_NOT_NULL(ptr);
        ptr = NULL;
        EXPECT_NULL(ptr);
    }
    
    {
        int *p1 = NULL;
        int *p2 = NULL;
        EXPECT_TRUE(p1 == p2);
    }
    
    {
        int arr[5] = {1, 2, 3, 4, 5};
        int *p = arr;
        EXPECT_NOT_NULL(p);
        p = NULL;
        EXPECT_NULL(p);
    }
    
    {
        void *vp = NULL;
        EXPECT_NULL(vp);
        vp = (void *)0;
        EXPECT_NULL(vp);
    }
}

UTEST_TEST_CASE(macros){
    struct test_struct {
        char a;
        int b;
        char c;
        long d;
        double e;
    };
    
    EXPECT_EQUAL_UINT(offsetof(struct test_struct, a), 0);
    EXPECT_TRUE(offsetof(struct test_struct, b) >= sizeof(char));
    EXPECT_TRUE(offsetof(struct test_struct, c) >= offsetof(struct test_struct, b) + sizeof(int));
    EXPECT_TRUE(offsetof(struct test_struct, d) >= offsetof(struct test_struct, c) + sizeof(char));
    EXPECT_TRUE(offsetof(struct test_struct, e) >= offsetof(struct test_struct, d) + sizeof(long));
    
    {
        struct simple_struct {
            int first;
            int second;
        };
        
        EXPECT_EQUAL_UINT(offsetof(struct simple_struct, first), 0);
        EXPECT_TRUE(offsetof(struct simple_struct, second) >= sizeof(int));
    }
    
    {
        struct aligned_struct {
            char a;
            long b;
        };
        
        EXPECT_EQUAL_UINT(offsetof(struct aligned_struct, a), 0);
        EXPECT_TRUE(offsetof(struct aligned_struct, b) >= sizeof(char));
    }
    
    {
        struct nested_struct {
            struct {
                int x;
                int y;
            } inner;
            int z;
        };
        
        EXPECT_EQUAL_UINT(offsetof(struct nested_struct, inner), 0);
        EXPECT_TRUE(offsetof(struct nested_struct, z) >= sizeof(struct nested_struct) - sizeof(int));
    }
    
    {
        struct array_struct {
            int arr[10];
            int next;
        };
        
        EXPECT_EQUAL_UINT(offsetof(struct array_struct, arr), 0);
        EXPECT_TRUE(offsetof(struct array_struct, next) >= sizeof(int) * 10);
    }
}

UTEST_TEST_SUITE(stddef){
    UTEST_RUN_TEST_CASE(types);
    UTEST_RUN_TEST_CASE(constants);
    UTEST_RUN_TEST_CASE(macros);
}