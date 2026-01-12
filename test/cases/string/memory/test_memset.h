#include <utest.h>
#include <string.h>
#include <stddef.h>

UTEST_TEST_CASE(memset){
    {
        char arr[5];
        void *result = memset(arr, 'a', 5);
        EXPECT_TRUE(result == arr);
        for (int i = 0; i < 5; i++) {
            EXPECT_TRUE(arr[i] == 'a');
        }
    }

    {
        char arr[10];
        void *result = memset(arr, 'x', 10);
        EXPECT_TRUE(result == arr);
        for (int i = 0; i < 10; i++) {
            EXPECT_TRUE(arr[i] == 'x');
        }
    }

    {
        char arr[1];
        void *result = memset(arr, 'z', 1);
        EXPECT_TRUE(result == arr);
        EXPECT_TRUE(arr[0] == 'z');
    }

    {
        char arr[5];
        void *result = memset(arr, 0, 5);
        EXPECT_TRUE(result == arr);
        for (int i = 0; i < 5; i++) {
            EXPECT_TRUE(arr[i] == 0);
        }
    }

    {
        char arr[5];
        void *result = memset(arr, 'A', 0);
        EXPECT_TRUE(result == arr);
    }

    {
        unsigned char arr[5];
        void *result = memset(arr, 255, 5);
        EXPECT_TRUE(result == arr);
        for (int i = 0; i < 5; i++) {
            EXPECT_TRUE(arr[i] == 255);
        }
    }

    {
        unsigned char arr[5];
        void *result = memset(arr, 128, 5);
        EXPECT_TRUE(result == arr);
        for (int i = 0; i < 5; i++) {
            EXPECT_TRUE(arr[i] == 128);
        }
    }

    {
        unsigned char arr[5];
        void *result = memset(arr, 0, 5);
        EXPECT_TRUE(result == arr);
        for (int i = 0; i < 5; i++) {
            EXPECT_TRUE(arr[i] == 0);
        }
    }

    {
        char arr[100];
        void *result = memset(arr, 'X', 100);
        EXPECT_TRUE(result == arr);
        for (int i = 0; i < 100; i++) {
            EXPECT_TRUE(arr[i] == 'X');
        }
    }

    {
        char arr[] = {'a', 'b', 'c', 'd', 'e'};
        void *result = memset(arr, 'z', 3);
        EXPECT_TRUE(result == arr);
        EXPECT_TRUE(arr[0] == 'z');
        EXPECT_TRUE(arr[1] == 'z');
        EXPECT_TRUE(arr[2] == 'z');
        EXPECT_TRUE(arr[3] == 'd');
        EXPECT_TRUE(arr[4] == 'e');
    }

    {
        unsigned char arr[10];
        void *result = memset(arr, 42, 10);
        EXPECT_TRUE(result == arr);
        for (int i = 0; i < 10; i++) {
            EXPECT_TRUE(arr[i] == 42);
        }
    }

    {
        char arr[5];
        void *result = memset(arr, '1', 5);
        EXPECT_TRUE(result == arr);
        for (int i = 0; i < 5; i++) {
            EXPECT_TRUE(arr[i] == '1');
        }
    }

    {
        char arr[5];
        void *result = memset(arr, '\0', 5);
        EXPECT_TRUE(result == arr);
        for (int i = 0; i < 5; i++) {
            EXPECT_TRUE(arr[i] == '\0');
        }
    }

    {
        unsigned char arr[20];
        void *result = memset(arr, 200, 20);
        EXPECT_TRUE(result == arr);
        for (int i = 0; i < 20; i++) {
            EXPECT_TRUE(arr[i] == 200);
        }
    }

    {
        char arr[50];
        void *result = memset(arr, 'H', 50);
        EXPECT_TRUE(result == arr);
        for (int i = 0; i < 50; i++) {
            EXPECT_TRUE(arr[i] == 'H');
        }
    }

    {
        unsigned char arr[8];
        void *result = memset(arr, 0xFF, 8);
        EXPECT_TRUE(result == arr);
        for (int i = 0; i < 8; i++) {
            EXPECT_TRUE(arr[i] == 0xFF);
        }
    }

    {
        unsigned char arr[8];
        void *result = memset(arr, 0x00, 8);
        EXPECT_TRUE(result == arr);
        for (int i = 0; i < 8; i++) {
            EXPECT_TRUE(arr[i] == 0x00);
        }
    }

    {
        char arr[15];
        void *result = memset(arr, 'A', 10);
        EXPECT_TRUE(result == arr);
        for (int i = 0; i < 10; i++) {
            EXPECT_TRUE(arr[i] == 'A');
        }
    }

    {
        unsigned char arr[5];
        void *result = memset(arr, 1, 5);
        EXPECT_TRUE(result == arr);
        for (int i = 0; i < 5; i++) {
            EXPECT_TRUE(arr[i] == 1);
        }
    }

    {
        char arr[3];
        void *result = memset(arr, ' ', 3);
        EXPECT_TRUE(result == arr);
        for (int i = 0; i < 3; i++) {
            EXPECT_TRUE(arr[i] == ' ');
        }
    }
}
