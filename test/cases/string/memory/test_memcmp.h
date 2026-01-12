#include <utest.h>
#include <string.h>
#include <stddef.h>

UTEST_TEST_CASE(memcmp){
    {
        char arr1[] = {'a', 'b', 'c'};
        char arr2[] = {'a', 'b', 'c'};
        int result = memcmp(arr1, arr2, 3);
        EXPECT_EQUAL_INT(result, 0);
    }

    {
        char arr1[] = {'a', 'b', 'c'};
        char arr2[] = {'a', 'b', 'd'};
        int result = memcmp(arr1, arr2, 3);
        EXPECT_TRUE(result < 0);
    }

    {
        char arr1[] = {'a', 'b', 'd'};
        char arr2[] = {'a', 'b', 'c'};
        int result = memcmp(arr1, arr2, 3);
        EXPECT_TRUE(result > 0);
    }

    {
        char arr1[] = {'a', 'b', 'c'};
        char arr2[] = {'a', 'b', 'c'};
        int result = memcmp(arr1, arr2, 0);
        EXPECT_EQUAL_INT(result, 0);
    }

    {
        char arr1[] = {'a', 'b', 'c'};
        char arr2[] = {'a', 'b', 'c', 'd'};
        int result = memcmp(arr1, arr2, 3);
        EXPECT_EQUAL_INT(result, 0);
    }

    {
        char arr1[] = {'a', 'b', 'c', 'd'};
        char arr2[] = {'a', 'b', 'c'};
        int result = memcmp(arr1, arr2, 3);
        EXPECT_EQUAL_INT(result, 0);
    }

    {
        char arr1[] = {'a', 'b', 'c'};
        char arr2[] = {'x', 'b', 'c'};
        int result = memcmp(arr1, arr2, 3);
        EXPECT_TRUE(result < 0);
    }

    {
        char arr1[] = {'x', 'b', 'c'};
        char arr2[] = {'a', 'b', 'c'};
        int result = memcmp(arr1, arr2, 3);
        EXPECT_TRUE(result > 0);
    }

    {
        unsigned char arr1[] = {0, 1, 2, 3, 4};
        unsigned char arr2[] = {0, 1, 2, 3, 4};
        int result = memcmp(arr1, arr2, 5);
        EXPECT_EQUAL_INT(result, 0);
    }

    {
        unsigned char arr1[] = {0, 1, 2, 3, 4};
        unsigned char arr2[] = {0, 1, 2, 5, 4};
        int result = memcmp(arr1, arr2, 5);
        EXPECT_TRUE(result < 0);
    }

    {
        unsigned char arr1[] = {0, 1, 2, 5, 4};
        unsigned char arr2[] = {0, 1, 2, 3, 4};
        int result = memcmp(arr1, arr2, 5);
        EXPECT_TRUE(result > 0);
    }

    {
        unsigned char arr1[] = {255, 128, 64};
        unsigned char arr2[] = {255, 128, 64};
        int result = memcmp(arr1, arr2, 3);
        EXPECT_EQUAL_INT(result, 0);
    }

    {
        unsigned char arr1[] = {255, 128, 64};
        unsigned char arr2[] = {255, 128, 65};
        int result = memcmp(arr1, arr2, 3);
        EXPECT_TRUE(result < 0);
    }

    {
        unsigned char arr1[] = {255, 128, 65};
        unsigned char arr2[] = {255, 128, 64};
        int result = memcmp(arr1, arr2, 3);
        EXPECT_TRUE(result > 0);
    }

    {
        char arr1[] = {'H', 'e', 'l', 'l', 'o'};
        char arr2[] = {'H', 'e', 'l', 'l', 'o'};
        int result = memcmp(arr1, arr2, 5);
        EXPECT_EQUAL_INT(result, 0);
    }

    {
        char arr1[] = {'H', 'e', 'l', 'l', 'o'};
        char arr2[] = {'H', 'e', 'l', 'l', 'p'};
        int result = memcmp(arr1, arr2, 5);
        EXPECT_TRUE(result < 0);
    }

    {
        char arr1[] = {'H', 'e', 'l', 'l', 'p'};
        char arr2[] = {'H', 'e', 'l', 'l', 'o'};
        int result = memcmp(arr1, arr2, 5);
        EXPECT_TRUE(result > 0);
    }

    {
        char arr1[] = {'a', 'a', 'a', 'a', 'a'};
        char arr2[] = {'a', 'a', 'a', 'a', 'a'};
        int result = memcmp(arr1, arr2, 5);
        EXPECT_EQUAL_INT(result, 0);
    }

    {
        char arr1[] = {'a', 'a', 'a', 'a', 'a'};
        char arr2[] = {'a', 'a', 'a', 'a', 'b'};
        int result = memcmp(arr1, arr2, 5);
        EXPECT_TRUE(result < 0);
    }

    {
        char arr1[100];
        char arr2[100];
        for (int i = 0; i < 100; i++) {
            arr1[i] = (char)(i % 256);
            arr2[i] = (char)(i % 256);
        }
        int result = memcmp(arr1, arr2, 100);
        EXPECT_EQUAL_INT(result, 0);
    }

    {
        char arr1[100];
        char arr2[100];
        for (int i = 0; i < 100; i++) {
            arr1[i] = (char)(i % 256);
            arr2[i] = (char)(i % 256);
        }
        arr1[50] = 100;
        arr2[50] = 101;
        int result = memcmp(arr1, arr2, 100);
        EXPECT_TRUE(result < 0);
    }

    {
        char arr1[] = {1, 2, 3};
        char arr2[] = {1, 2, 4};
        int result = memcmp(arr1, arr2, 2);
        EXPECT_EQUAL_INT(result, 0);
    }

    {
        char arr1[] = {1, 2, 3};
        char arr2[] = {1, 2, 4};
        int result = memcmp(arr1, arr2, 3);
        EXPECT_TRUE(result < 0);
    }
}
