#include <utest.h>
#include <string.h>
#include <stddef.h>

UTEST_TEST_CASE(memchr){
    {
        char arr[] = {'a', 'b', 'c', 'd', 'e'};
        void *result = memchr(arr, 'c', 5);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(char *)result == 'c');
    }

    {
        char arr[] = {'a', 'b', 'c', 'd', 'e'};
        void *result = memchr(arr, 'a', 5);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(char *)result == 'a');
        EXPECT_TRUE(result == arr);
    }

    {
        char arr[] = {'a', 'b', 'c', 'd', 'e'};
        void *result = memchr(arr, 'e', 5);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(char *)result == 'e');
    }

    {
        char arr[] = {'a', 'b', 'c', 'd', 'e'};
        void *result = memchr(arr, 'z', 5);
        EXPECT_NULL(result);
    }

    {
        char arr[] = {'a', 'b', 'c', 'd', 'e'};
        void *result = memchr(arr, 'c', 0);
        EXPECT_NULL(result);
    }

    {
        char arr[] = {'a', 'b', 'c', 'd', 'e'};
        void *result = memchr(arr, 'c', 2);
        EXPECT_NULL(result);
    }

    {
        char arr[] = {'a', 'b', 'c', 'd', 'e'};
        void *result = memchr(arr, 'c', 3);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(char *)result == 'c');
    }

    {
        char arr[] = {0, 1, 2, 3, 4};
        void *result = memchr(arr, 0, 5);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(unsigned char *)result == 0);
        EXPECT_TRUE(result == arr);
    }

    {
        char arr[] = {1, 2, 3, 0, 5};
        void *result = memchr(arr, 0, 5);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(unsigned char *)result == 0);
    }

    {
        char arr[] = {1, 2, 3, 4, 5};
        void *result = memchr(arr, 0, 5);
        EXPECT_NULL(result);
    }

    {
        char arr[] = {'x', 'x', 'x', 'x', 'x'};
        void *result = memchr(arr, 'x', 5);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(char *)result == 'x');
        EXPECT_TRUE(result == arr);
    }

    {
        char arr[] = {'a', 'b', 'c', 'c', 'd'};
        void *result = memchr(arr, 'c', 5);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(char *)result == 'c');
    }

    {
        unsigned char arr[] = {255, 128, 64, 32, 16};
        void *result = memchr(arr, 128, 5);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(unsigned char *)result == 128);
    }

    {
        char arr[] = {'H', 'e', 'l', 'l', 'o'};
        void *result = memchr(arr, 'l', 5);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(char *)result == 'l');
    }

    {
        char arr[] = {'A', 'B', 'C'};
        void *result = memchr(arr, 'B', 3);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(char *)result == 'B');
    }

    {
        char arr[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
        void *result = memchr(arr, '5', 10);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(char *)result == '5');
    }

    {
        char arr[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
        void *result = memchr(arr, 'A', 10);
        EXPECT_NULL(result);
    }

    {
        unsigned char arr[100];
        for (int i = 0; i < 100; i++) {
            arr[i] = (unsigned char)(i % 256);
        }
        void *result = memchr(arr, 50, 100);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(unsigned char *)result == 50);
    }

    {
        unsigned char arr[256];
        for (int i = 0; i < 256; i++) {
            arr[i] = (unsigned char)i;
        }
        void *result = memchr(arr, 200, 256);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(unsigned char *)result == 200);
    }

    {
        unsigned char arr[256];
        for (int i = 0; i < 256; i++) {
            arr[i] = (unsigned char)i;
        }
        void *result = memchr(arr, 255, 256);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(unsigned char *)result == 255);
    }

    {
        unsigned char arr[100];
        for (int i = 0; i < 100; i++) {
            arr[i] = (unsigned char)(i % 256);
        }
        void *result = memchr(arr, 200, 100);
        EXPECT_NULL(result);
    }

    {
        char arr[] = {'a', 'b', 'c'};
        void *result = memchr(arr, 'a', 1);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(char *)result == 'a');
    }

    {
        char arr[] = {'a', 'b', 'c'};
        void *result = memchr(arr, 'b', 1);
        EXPECT_NULL(result);
    }

    {
        char arr[] = {'a', 'b', 'c'};
        void *result = memchr(arr, 'c', 2);
        EXPECT_NULL(result);
    }

    {
        char arr[] = {'a', 'b', 'c'};
        void *result = memchr(arr, 'c', 3);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(char *)result == 'c');
    }

    {
        unsigned char arr[] = {0, 0, 0, 0, 0};
        void *result = memchr(arr, 0, 5);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(unsigned char *)result == 0);
        EXPECT_TRUE(result == arr);
    }

    {
        unsigned char arr[] = {1, 1, 1, 1, 1};
        void *result = memchr(arr, 0, 5);
        EXPECT_NULL(result);
    }

    {
        unsigned char arr[] = {100, 101, 102, 103, 104};
        void *result = memchr(arr, 102, 5);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(unsigned char *)result == 102);
    }

    {
        unsigned char arr[] = {100, 101, 102, 103, 104};
        void *result = memchr(arr, 99, 5);
        EXPECT_NULL(result);
    }

    {
        unsigned char arr[] = {100, 101, 102, 103, 104};
        void *result = memchr(arr, 105, 5);
        EXPECT_NULL(result);
    }
}
