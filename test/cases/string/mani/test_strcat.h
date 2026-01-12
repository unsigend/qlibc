#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(strcat){
    {
        char dest[20] = "hello";
        char *result = strcat(dest, " world");
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "hello world") == 0);
    }

    {
        char dest[20] = "";
        char *result = strcat(dest, "test");
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "test") == 0);
    }

    {
        char dest[20] = "hello";
        char *result = strcat(dest, "");
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "hello") == 0);
    }

    {
        char dest[20] = "a";
        char *result = strcat(dest, "b");
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "ab") == 0);
    }

    {
        char dest[30] = "Hello";
        char *result = strcat(dest, " World");
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "Hello World") == 0);
    }

    {
        char dest[20] = "123";
        char *result = strcat(dest, "456");
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "123456") == 0);
    }

    {
        char dest[20] = "x";
        char *result = strcat(dest, "y");
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "xy") == 0);
    }

    {
        char dest[30] = "first";
        char *result = strcat(dest, "second");
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "firstsecond") == 0);
    }

    {
        char dest[20] = "A";
        char *result = strcat(dest, "B");
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "AB") == 0);
    }

    {
        char dest[50] = "prefix";
        char *result = strcat(dest, "suffix");
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "prefixsuffix") == 0);
    }

    {
        char dest[20] = "one";
        char *result = strcat(dest, "two");
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "onetwo") == 0);
    }
}
