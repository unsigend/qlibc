#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(strchr){
    {
        char str[] = "hello";
        char *result = strchr(str, 'h');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'h');
    }
    {
        char str[] = "hello";
        char *result = strchr(str, 'e');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'e');
    }
    {
        char str[] = "hello";
        char *result = strchr(str, 'l');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'l');
    }
    {
        char str[] = "hello";
        char *result = strchr(str, 'o');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'o');
    }
    {
        char str[] = "hello";
        char *result = strchr(str, 'z');
        EXPECT_NULL(result);
    }
    {
        char str[] = "hello";
        char *result = strchr(str, 'A');
        EXPECT_NULL(result);
    }
    {
        char str[] = "hello";
        char *result = strchr(str, '\0');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == '\0');
    }
    {
        char str[] = "";
        char *result = strchr(str, '\0');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == '\0');
    }
    {
        char str[] = "";
        char *result = strchr(str, 'a');
        EXPECT_NULL(result);
    }
    {
        char str[] = "a";
        char *result = strchr(str, 'a');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'a');
    }
    {
        char str[] = "a";
        char *result = strchr(str, 'b');
        EXPECT_NULL(result);
    }
    {
        char str[] = "a";
        char *result = strchr(str, '\0');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == '\0');
    }
    {
        char str[] = "abc";
        char *result = strchr(str, 'a');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "abc";
        char *result = strchr(str, 'b');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'b');
    }
    {
        char str[] = "abc";
        char *result = strchr(str, 'c');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'c');
    }
    {
        char str[] = "aabbcc";
        char *result = strchr(str, 'a');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'a');
    }
    {
        char str[] = "aabbcc";
        char *result = strchr(str, 'b');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'b');
    }
    {
        char str[] = "aabbcc";
        char *result = strchr(str, 'c');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'c');
    }
    {
        char str[] = "Hello World";
        char *result = strchr(str, ' ');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == ' ');
    }
    {
        char str[] = "Hello World";
        char *result = strchr(str, 'W');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'W');
    }
    {
        char str[] = "12345";
        char *result = strchr(str, '3');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == '3');
    }
    {
        char str[] = "12345";
        char *result = strchr(str, '0');
        EXPECT_NULL(result);
    }
    {
        char str[] = "test";
        char *result = strchr(str, 't');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 't');
    }
    {
        char str[] = "test";
        char *result = strchr(str, 'e');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'e');
    }
    {
        char str[] = "test";
        char *result = strchr(str, 's');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 's');
    }
    {
        char str[] = "xxxxx";
        char *result = strchr(str, 'x');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'x');
    }
    {
        char str[] = "xxxxx";
        char *result = strchr(str, 'y');
        EXPECT_NULL(result);
    }
    {
        char str[] = "prefixsuffix";
        char *result = strchr(str, 's');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 's');
    }
    {
        char str[] = "prefixsuffix";
        char *result = strchr(str, 'x');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'x');
    }
    {
        char str[] = "ABC";
        char *result = strchr(str, 'A');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "ABC";
        char *result = strchr(str, 'B');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'B');
    }
    {
        char str[] = "ABC";
        char *result = strchr(str, 'C');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'C');
    }
    {
        char str[] = "one\0two";
        char *result = strchr(str, 'o');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "one\0two";
        char *result = strchr(str, 't');
        EXPECT_NULL(result);
    }
    {
        char str[] = "one\0two";
        char *result = strchr(str, '\0');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == '\0');
    }
}
