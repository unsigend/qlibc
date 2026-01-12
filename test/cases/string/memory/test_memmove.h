#include <utest.h>
#include <string.h>
#include <stddef.h>

UTEST_TEST_CASE(memmove){
    {
        char src[] = {'a', 'b', 'c', 'd', 'e'};
        char dest[5];
        void *result = memmove(dest, src, 5);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(memcmp(dest, src, 5) == 0);
    }

    {
        char src[] = {'a', 'b', 'c'};
        char dest[3];
        void *result = memmove(dest, src, 3);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(memcmp(dest, src, 3) == 0);
    }

    {
        char src[] = {'x'};
        char dest[1];
        void *result = memmove(dest, src, 1);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(memcmp(dest, src, 1) == 0);
    }

    {
        char src[] = {'a', 'b', 'c', 'd', 'e'};
        char dest[5];
        void *result = memmove(dest, src, 0);
        EXPECT_TRUE(result == dest);
    }

    {
        char arr[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
        void *result = memmove(arr + 2, arr, 4);
        EXPECT_TRUE(result == arr + 2);
        EXPECT_TRUE(arr[2] == 'a');
        EXPECT_TRUE(arr[3] == 'b');
        EXPECT_TRUE(arr[4] == 'c');
        EXPECT_TRUE(arr[5] == 'd');
    }

    {
        char arr[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
        void *result = memmove(arr, arr + 2, 4);
        EXPECT_TRUE(result == arr);
        EXPECT_TRUE(arr[0] == 'c');
        EXPECT_TRUE(arr[1] == 'd');
        EXPECT_TRUE(arr[2] == 'e');
        EXPECT_TRUE(arr[3] == 'f');
    }

    {
        char arr[] = {'1', '2', '3', '4', '5'};
        void *result = memmove(arr + 1, arr, 3);
        EXPECT_TRUE(result == arr + 1);
        EXPECT_TRUE(arr[1] == '1');
        EXPECT_TRUE(arr[2] == '2');
        EXPECT_TRUE(arr[3] == '3');
    }

    {
        char arr[] = {'1', '2', '3', '4', '5'};
        void *result = memmove(arr, arr + 1, 3);
        EXPECT_TRUE(result == arr);
        EXPECT_TRUE(arr[0] == '2');
        EXPECT_TRUE(arr[1] == '3');
        EXPECT_TRUE(arr[2] == '4');
    }

    {
        char arr[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
        void *result = memmove(arr + 3, arr, 5);
        EXPECT_TRUE(result == arr + 3);
        EXPECT_TRUE(arr[3] == 'a');
        EXPECT_TRUE(arr[4] == 'b');
        EXPECT_TRUE(arr[5] == 'c');
        EXPECT_TRUE(arr[6] == 'd');
        EXPECT_TRUE(arr[7] == 'e');
    }

    {
        char arr[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
        void *result = memmove(arr, arr + 3, 5);
        EXPECT_TRUE(result == arr);
        EXPECT_TRUE(arr[0] == 'd');
        EXPECT_TRUE(arr[1] == 'e');
        EXPECT_TRUE(arr[2] == 'f');
        EXPECT_TRUE(arr[3] == 'g');
        EXPECT_TRUE(arr[4] == 'h');
    }

    {
        char arr[] = {'x', 'y', 'z'};
        void *result = memmove(arr, arr, 3);
        EXPECT_TRUE(result == arr);
        EXPECT_TRUE(arr[0] == 'x');
        EXPECT_TRUE(arr[1] == 'y');
        EXPECT_TRUE(arr[2] == 'z');
    }

    {
        char arr[] = {'1', '2', '3', '4', '5', '6', '7', '8'};
        void *result = memmove(arr + 1, arr, 6);
        EXPECT_TRUE(result == arr + 1);
        EXPECT_TRUE(arr[1] == '1');
        EXPECT_TRUE(arr[2] == '2');
        EXPECT_TRUE(arr[3] == '3');
        EXPECT_TRUE(arr[4] == '4');
        EXPECT_TRUE(arr[5] == '5');
        EXPECT_TRUE(arr[6] == '6');
    }

    {
        char arr[] = {'1', '2', '3', '4', '5', '6', '7', '8'};
        void *result = memmove(arr, arr + 1, 6);
        EXPECT_TRUE(result == arr);
        EXPECT_TRUE(arr[0] == '2');
        EXPECT_TRUE(arr[1] == '3');
        EXPECT_TRUE(arr[2] == '4');
        EXPECT_TRUE(arr[3] == '5');
        EXPECT_TRUE(arr[4] == '6');
        EXPECT_TRUE(arr[5] == '7');
    }

    {
        unsigned char arr[] = {0, 1, 2, 3, 4, 5, 6, 7};
        void *result = memmove(arr + 2, arr, 4);
        EXPECT_TRUE(result == arr + 2);
        EXPECT_TRUE(arr[2] == 0);
        EXPECT_TRUE(arr[3] == 1);
        EXPECT_TRUE(arr[4] == 2);
        EXPECT_TRUE(arr[5] == 3);
    }

    {
        unsigned char arr[] = {0, 1, 2, 3, 4, 5, 6, 7};
        void *result = memmove(arr, arr + 2, 4);
        EXPECT_TRUE(result == arr);
        EXPECT_TRUE(arr[0] == 2);
        EXPECT_TRUE(arr[1] == 3);
        EXPECT_TRUE(arr[2] == 4);
        EXPECT_TRUE(arr[3] == 5);
    }

    {
        char arr[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
        void *result = memmove(arr + 4, arr, 4);
        EXPECT_TRUE(result == arr + 4);
        EXPECT_TRUE(arr[4] == 'A');
        EXPECT_TRUE(arr[5] == 'B');
        EXPECT_TRUE(arr[6] == 'C');
        EXPECT_TRUE(arr[7] == 'D');
    }

    {
        char arr[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
        void *result = memmove(arr, arr + 4, 4);
        EXPECT_TRUE(result == arr);
        EXPECT_TRUE(arr[0] == 'E');
        EXPECT_TRUE(arr[1] == 'F');
        EXPECT_TRUE(arr[2] == 'G');
        EXPECT_TRUE(arr[3] == 'H');
    }

    {
        char arr[100];
        for (int i = 0; i < 100; i++) {
            arr[i] = (char)(i % 256);
        }
        void *result = memmove(arr + 10, arr, 50);
        EXPECT_TRUE(result == arr + 10);
        for (int i = 0; i < 50; i++) {
            EXPECT_TRUE(arr[10 + i] == (char)(i % 256));
        }
    }

    {
        char arr[100];
        for (int i = 0; i < 100; i++) {
            arr[i] = (char)(i % 256);
        }
        void *result = memmove(arr, arr + 10, 50);
        EXPECT_TRUE(result == arr);
        for (int i = 0; i < 50; i++) {
            EXPECT_TRUE(arr[i] == (char)((10 + i) % 256));
        }
    }

    {
        char arr[] = {'a', 'b', 'c', 'd', 'e'};
        char dest[5];
        void *result = memmove(dest, arr, 5);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(memcmp(dest, arr, 5) == 0);
    }
}
