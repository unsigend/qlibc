#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(strcpy){
    {
        char dest[10];
        char *result = strcpy(dest, "hello");
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "hello") == 0);
    }

    {
        char dest[10];
        char *result = strcpy(dest, "");
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "") == 0);
        EXPECT_TRUE(dest[0] == '\0');
    }

    {
        char dest[20];
        char *result = strcpy(dest, "a");
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "a") == 0);
    }

    {
        char dest[100];
        char *result = strcpy(dest, "test");
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "test") == 0);
    }

    {
        char dest[50];
        char *result = strcpy(dest, "Hello World");
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "Hello World") == 0);
    }

    {
        char dest[10];
        char *result = strcpy(dest, "12345");
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "12345") == 0);
    }

    {
        char dest[20];
        char *result = strcpy(dest, "ABC");
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "ABC") == 0);
    }

    {
        char dest[30];
        char src[] = "source";
        char *result = strcpy(dest, src);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "source") == 0);
    }

    {
        char dest[10];
        char *result = strcpy(dest, "x");
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(dest[0] == 'x');
        EXPECT_TRUE(dest[1] == '\0');
    }

    {
        char dest[5];
        char *result = strcpy(dest, "ab");
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "ab") == 0);
    }
}
