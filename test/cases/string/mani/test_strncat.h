#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(strncat){
    {
        char dest[20] = "hello";
        char *result = strncat(dest, " world", 6);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "hello world") == 0);
    }

    {
        char dest[20] = "hello";
        char *result = strncat(dest, " world", 3);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "hello wo") == 0);
    }

    {
        char dest[20] = "";
        char *result = strncat(dest, "test", 4);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "test") == 0);
    }

    {
        char dest[20] = "";
        char *result = strncat(dest, "test", 2);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "te") == 0);
    }

    {
        char dest[20] = "hello";
        char *result = strncat(dest, "", 0);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "hello") == 0);
    }

    {
        char dest[20] = "a";
        char *result = strncat(dest, "b", 1);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "ab") == 0);
    }

    {
        char dest[20] = "a";
        char *result = strncat(dest, "bc", 1);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "ab") == 0);
    }

    {
        char dest[30] = "Hello";
        char *result = strncat(dest, " World", 6);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "Hello World") == 0);
    }

    {
        char dest[30] = "Hello";
        char *result = strncat(dest, " World", 10);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "Hello World") == 0);
    }

    {
        char dest[20] = "123";
        char *result = strncat(dest, "456", 3);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "123456") == 0);
    }

    {
        char dest[20] = "123";
        char *result = strncat(dest, "456", 2);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "12345") == 0);
    }

    {
        char dest[20] = "x";
        char *result = strncat(dest, "y", 1);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "xy") == 0);
    }

    {
        char dest[20] = "x";
        char *result = strncat(dest, "yz", 1);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "xy") == 0);
    }

    {
        char dest[30] = "first";
        char *result = strncat(dest, "second", 6);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "firstsecond") == 0);
    }

    {
        char dest[30] = "first";
        char *result = strncat(dest, "second", 3);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "firstsec") == 0);
    }

    {
        char dest[20] = "A";
        char *result = strncat(dest, "B", 1);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "AB") == 0);
    }

    {
        char dest[50] = "prefix";
        char *result = strncat(dest, "suffix", 6);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "prefixsuffix") == 0);
    }

    {
        char dest[50] = "prefix";
        char *result = strncat(dest, "suffix", 2);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "prefixsu") == 0);
    }

    {
        char dest[20] = "one";
        char *result = strncat(dest, "two", 3);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "onetwo") == 0);
    }

    {
        char dest[20] = "one";
        char *result = strncat(dest, "two", 1);
        EXPECT_TRUE(result == dest);
        EXPECT_TRUE(strcmp(dest, "onet") == 0);
    }
}
