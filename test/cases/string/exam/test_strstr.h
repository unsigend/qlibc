#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(strstr){
    {
        char str[] = "hello";
        char *result = strstr(str, "hello");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "hello") == 0);
    }
    {
        char str[] = "hello";
        char *result = strstr(str, "hell");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strncmp(result, "hell", 4) == 0);
    }
    {
        char str[] = "hello";
        char *result = strstr(str, "ello");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "ello") == 0);
    }
    {
        char str[] = "hello";
        char *result = strstr(str, "lo");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "lo") == 0);
    }
    {
        char str[] = "hello";
        char *result = strstr(str, "h");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "hello") == 0);
    }
    {
        char str[] = "hello";
        char *result = strstr(str, "e");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "ello") == 0);
    }
    {
        char str[] = "hello";
        char *result = strstr(str, "l");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "llo") == 0);
    }
    {
        char str[] = "hello";
        char *result = strstr(str, "o");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "o") == 0);
    }
    {
        char str[] = "hello";
        char *result = strstr(str, "");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "hello") == 0);
    }
    {
        char str[] = "hello";
        char *result = strstr(str, "world");
        EXPECT_NULL(result);
    }
    {
        char str[] = "hello";
        char *result = strstr(str, "x");
        EXPECT_NULL(result);
    }
    {
        char str[] = "";
        char *result = strstr(str, "");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "") == 0);
    }
    {
        char str[] = "";
        char *result = strstr(str, "a");
        EXPECT_NULL(result);
    }
    {
        char str[] = "a";
        char *result = strstr(str, "");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "a") == 0);
    }
    {
        char str[] = "a";
        char *result = strstr(str, "a");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "a") == 0);
    }
    {
        char str[] = "a";
        char *result = strstr(str, "b");
        EXPECT_NULL(result);
    }
    {
        char str[] = "abc";
        char *result = strstr(str, "abc");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "abc") == 0);
    }
    {
        char str[] = "abc";
        char *result = strstr(str, "ab");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strncmp(result, "ab", 2) == 0);
    }
    {
        char str[] = "abc";
        char *result = strstr(str, "bc");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "bc") == 0);
    }
    {
        char str[] = "abc";
        char *result = strstr(str, "a");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "abc") == 0);
    }
    {
        char str[] = "abc";
        char *result = strstr(str, "b");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "bc") == 0);
    }
    {
        char str[] = "abc";
        char *result = strstr(str, "c");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "c") == 0);
    }
    {
        char str[] = "abc";
        char *result = strstr(str, "d");
        EXPECT_NULL(result);
    }
    {
        char str[] = "Hello World";
        char *result = strstr(str, "Hello");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strncmp(result, "Hello", 5) == 0);
    }
    {
        char str[] = "Hello World";
        char *result = strstr(str, "World");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "World") == 0);
    }
    {
        char str[] = "Hello World";
        char *result = strstr(str, " ");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, " World") == 0);
    }
    {
        char str[] = "Hello World";
        char *result = strstr(str, "lo");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "lo World") == 0);
    }
    {
        char str[] = "Hello World";
        char *result = strstr(str, "Wor");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strncmp(result, "Wor", 3) == 0);
    }
    {
        char str[] = "aabbcc";
        char *result = strstr(str, "bb");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "bbcc") == 0);
    }
    {
        char str[] = "aabbcc";
        char *result = strstr(str, "aa");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strncmp(result, "aa", 2) == 0);
    }
    {
        char str[] = "aabbcc";
        char *result = strstr(str, "cc");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "cc") == 0);
    }
    {
        char str[] = "test";
        char *result = strstr(str, "test");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "test") == 0);
    }
    {
        char str[] = "test";
        char *result = strstr(str, "tes");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strncmp(result, "tes", 3) == 0);
    }
    {
        char str[] = "test";
        char *result = strstr(str, "est");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "est") == 0);
    }
    {
        char str[] = "test";
        char *result = strstr(str, "st");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "st") == 0);
    }
    {
        char str[] = "test";
        char *result = strstr(str, "t");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "test") == 0);
    }
    {
        char str[] = "testtest";
        char *result = strstr(str, "test");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strncmp(result, "test", 4) == 0);
    }
    {
        char str[] = "prefixsuffix";
        char *result = strstr(str, "prefix");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strncmp(result, "prefix", 6) == 0);
    }
    {
        char str[] = "prefixsuffix";
        char *result = strstr(str, "suffix");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "suffix") == 0);
    }
    {
        char str[] = "prefixsuffix";
        char *result = strstr(str, "fix");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "fixsuffix") == 0);
    }
    {
        char str[] = "12345";
        char *result = strstr(str, "123");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strncmp(result, "123", 3) == 0);
    }
    {
        char str[] = "12345";
        char *result = strstr(str, "234");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "2345") == 0);
    }
    {
        char str[] = "12345";
        char *result = strstr(str, "345");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "345") == 0);
    }
    {
        char str[] = "12345";
        char *result = strstr(str, "45");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "45") == 0);
    }
    {
        char str[] = "12345";
        char *result = strstr(str, "678");
        EXPECT_NULL(result);
    }
    {
        char str[] = "hello";
        char *result = strstr(str, "ell");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "ello") == 0);
    }
    {
        char str[] = "hello";
        char *result = strstr(str, "xyz");
        EXPECT_NULL(result);
    }
    {
        char str[] = "xxxxx";
        char *result = strstr(str, "xx");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strncmp(result, "xx", 2) == 0);
    }
    {
        char str[] = "xxxxx";
        char *result = strstr(str, "xxx");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strncmp(result, "xxx", 3) == 0);
    }
    {
        char str[] = "ababab";
        char *result = strstr(str, "ab");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strncmp(result, "ab", 2) == 0);
    }
    {
        char str[] = "ababab";
        char *result = strstr(str, "ba");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "babab") == 0);
    }
}
