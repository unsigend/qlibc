#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(strncpy){
    {
        char dest[10] = {0};
        char *result = strncpy(dest, "hello", 5);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(memcmp(dest, "hello", 5) == 0);
        EXPECT_TRUE(dest[5] == '\0');
    }

    {
        char dest[10] = {0};
        char *result = strncpy(dest, "hello", 10);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "hello") == 0);
    }

    {
        char dest[10] = {0};
        char *result = strncpy(dest, "hello", 3);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(memcmp(dest, "hel", 3) == 0);
        EXPECT_TRUE(dest[3] == '\0');
        EXPECT_TRUE(dest[4] == '\0');
        EXPECT_TRUE(dest[5] == '\0');
    }

    {
        char dest[10] = {0};
        char *result = strncpy(dest, "", 5);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(dest[0] == '\0');
        EXPECT_TRUE(dest[1] == '\0');
        EXPECT_TRUE(dest[2] == '\0');
        EXPECT_TRUE(dest[3] == '\0');
        EXPECT_TRUE(dest[4] == '\0');
    }

    {
        char dest[10] = {0};
        char *result = strncpy(dest, "a", 1);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(dest[0] == 'a');
        EXPECT_TRUE(dest[1] == '\0');
    }

    {
        char dest[10] = {0};
        char *result = strncpy(dest, "a", 3);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(dest[0] == 'a');
        EXPECT_TRUE(dest[1] == '\0');
        EXPECT_TRUE(dest[2] == '\0');
    }

    {
        char dest[10] = {0};
        char *result = strncpy(dest, "test", 0);
        EXPECT_TRUE(result == dest);
    }

    {
        char dest[10] = {0};
        char *result = strncpy(dest, "abc", 2);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(dest[0] == 'a');
        EXPECT_TRUE(dest[1] == 'b');
        EXPECT_TRUE(dest[2] == '\0');
    }

    {
        char dest[20] = {0};
        char *result = strncpy(dest, "Hello World", 5);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(memcmp(dest, "Hello", 5) == 0);
        EXPECT_TRUE(dest[5] == '\0');
    }

    {
        char dest[20] = {0};
        char *result = strncpy(dest, "Hello World", 11);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "Hello World") == 0);
    }

    {
        char dest[20] = {0};
        char *result = strncpy(dest, "Hello World", 20);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "Hello World") == 0);
    }

    {
        char dest[10] = {0};
        char *result = strncpy(dest, "12345", 3);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(memcmp(dest, "123", 3) == 0);
        EXPECT_TRUE(dest[3] == '\0');
    }

    {
        char dest[10] = {0};
        char *result = strncpy(dest, "x", 5);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(dest[0] == 'x');
        EXPECT_TRUE(dest[1] == '\0');
        EXPECT_TRUE(dest[2] == '\0');
        EXPECT_TRUE(dest[3] == '\0');
        EXPECT_TRUE(dest[4] == '\0');
    }

    {
        char dest[5] = {0};
        char *result = strncpy(dest, "ab", 4);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "ab") == 0);
    }
}
