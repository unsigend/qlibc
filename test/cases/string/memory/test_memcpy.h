#include <utest.h>
#include <string.h>
#include <stddef.h>

UTEST_TEST_CASE(memcpy){
    {
        char src[] = {'a', 'b', 'c', 'd', 'e'};
        char dest[5];
        void *result = memcpy(dest, src, 5);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(memcmp(dest, src, 5) == 0);
    }

    {
        char src[] = {'a', 'b', 'c'};
        char dest[3];
        void *result = memcpy(dest, src, 3);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(memcmp(dest, src, 3) == 0);
    }

    {
        char src[] = {'x'};
        char dest[1];
        void *result = memcpy(dest, src, 1);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(memcmp(dest, src, 1) == 0);
    }

    {
        char src[] = {'a', 'b', 'c', 'd', 'e'};
        char dest[5];
        void *result = memcpy(dest, src, 0);
        EXPECT_TRUE(result == dest);
    }

    {
        unsigned char src[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        unsigned char dest[10];
        void *result = memcpy(dest, src, 10);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(memcmp(dest, src, 10) == 0);
    }

    {
        unsigned char src[] = {255, 128, 64, 32, 16};
        unsigned char dest[5];
        void *result = memcpy(dest, src, 5);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(memcmp(dest, src, 5) == 0);
    }

    {
        char src[] = {'H', 'e', 'l', 'l', 'o'};
        char dest[5];
        void *result = memcpy(dest, src, 5);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(memcmp(dest, src, 5) == 0);
    }

    {
        char src[] = {'a', 'a', 'a', 'a', 'a'};
        char dest[5];
        void *result = memcpy(dest, src, 5);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(memcmp(dest, src, 5) == 0);
    }

    {
        char src[100];
        char dest[100];
        for (int i = 0; i < 100; i++) {
            src[i] = (char)(i % 256);
        }
        void *result = memcpy(dest, src, 100);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(memcmp(dest, src, 100) == 0);
    }

    {
        char src[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
        char dest[10];
        void *result = memcpy(dest, src, 10);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(memcmp(dest, src, 10) == 0);
    }

    {
        char src[] = {'a', 'b', 'c', 'd', 'e'};
        char dest[10];
        void *result = memcpy(dest, src, 3);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(memcmp(dest, src, 3) == 0);
    }

    {
        unsigned char src[] = {0, 1, 2, 3, 4};
        unsigned char dest[5];
        void *result = memcpy(dest, src, 5);
        EXPECT_TRUE(result == dest);
        for (int i = 0; i < 5; i++) {
            EXPECT_TRUE(dest[i] == src[i]);
        }
    }

    {
        char src[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
        char dest[10];
        void *result = memcpy(dest, src, 10);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(memcmp(dest, src, 10) == 0);
    }

    {
        char src[] = {'x', 'y', 'z'};
        char dest[5] = {'a', 'b', 'c', 'd', 'e'};
        void *result = memcpy(dest, src, 3);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(dest[0] == 'x');
        EXPECT_TRUE(dest[1] == 'y');
        EXPECT_TRUE(dest[2] == 'z');
    }
}
