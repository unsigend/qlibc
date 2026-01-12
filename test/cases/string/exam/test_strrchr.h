#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(strrchr){
    {
        char str[] = "hello";
        char *result = strrchr(str, 'h');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'h');
    }
    {
        char str[] = "hello";
        char *result = strrchr(str, 'e');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'e');
    }
    {
        char str[] = "hello";
        char *result = strrchr(str, 'l');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'l');
        EXPECT_TRUE(result == str + 3);
    }
    {
        char str[] = "hello";
        char *result = strrchr(str, 'o');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'o');
    }
    {
        char str[] = "hello";
        char *result = strrchr(str, 'z');
        EXPECT_NULL(result);
    }
    {
        char str[] = "hello";
        char *result = strrchr(str, '\0');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == '\0');
        EXPECT_TRUE(result == str + 5);
    }
    {
        char str[] = "";
        char *result = strrchr(str, '\0');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == '\0');
    }
    {
        char str[] = "";
        char *result = strrchr(str, 'a');
        EXPECT_NULL(result);
    }
    {
        char str[] = "a";
        char *result = strrchr(str, 'a');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'a');
    }
    {
        char str[] = "a";
        char *result = strrchr(str, 'b');
        EXPECT_NULL(result);
    }
    {
        char str[] = "a";
        char *result = strrchr(str, '\0');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == '\0');
    }
    {
        char str[] = "abc";
        char *result = strrchr(str, 'a');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "abc";
        char *result = strrchr(str, 'b');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'b');
    }
    {
        char str[] = "abc";
        char *result = strrchr(str, 'c');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'c');
    }
    {
        char str[] = "aabbcc";
        char *result = strrchr(str, 'a');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'a');
        EXPECT_TRUE(result == str + 1);
    }
    {
        char str[] = "aabbcc";
        char *result = strrchr(str, 'b');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'b');
        EXPECT_TRUE(result == str + 3);
    }
    {
        char str[] = "aabbcc";
        char *result = strrchr(str, 'c');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'c');
        EXPECT_TRUE(result == str + 5);
    }
    {
        char str[] = "Hello World";
        char *result = strrchr(str, ' ');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == ' ');
    }
    {
        char str[] = "Hello World";
        char *result = strrchr(str, 'l');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'l');
        EXPECT_TRUE(result == str + 9);
    }
    {
        char str[] = "Hello World";
        char *result = strrchr(str, 'W');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'W');
    }
    {
        char str[] = "12345";
        char *result = strrchr(str, '3');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == '3');
    }
    {
        char str[] = "12345";
        char *result = strrchr(str, '5');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == '5');
    }
    {
        char str[] = "12345";
        char *result = strrchr(str, '0');
        EXPECT_NULL(result);
    }
    {
        char str[] = "test";
        char *result = strrchr(str, 't');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 't');
        EXPECT_TRUE(result == str + 3);
    }
    {
        char str[] = "test";
        char *result = strrchr(str, 'e');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'e');
    }
    {
        char str[] = "test";
        char *result = strrchr(str, 's');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 's');
    }
    {
        char str[] = "xxxxx";
        char *result = strrchr(str, 'x');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'x');
        EXPECT_TRUE(result == str + 4);
    }
    {
        char str[] = "xxxxx";
        char *result = strrchr(str, 'y');
        EXPECT_NULL(result);
    }
    {
        char str[] = "prefixsuffix";
        char *result = strrchr(str, 's');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 's');
        EXPECT_TRUE(result == str + 6);
    }
    {
        char str[] = "prefixsuffix";
        char *result = strrchr(str, 'x');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'x');
        EXPECT_TRUE(result == str + 11);
    }
    {
        char str[] = "ABC";
        char *result = strrchr(str, 'A');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "ABC";
        char *result = strrchr(str, 'B');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'B');
    }
    {
        char str[] = "ABC";
        char *result = strrchr(str, 'C');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'C');
    }
    {
        char str[] = "one\0two";
        char *result = strrchr(str, 'o');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "one\0two";
        char *result = strrchr(str, 't');
        EXPECT_NULL(result);
    }
    {
        char str[] = "one\0two";
        char *result = strrchr(str, '\0');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == '\0');
    }
    {
        char str[] = "ababab";
        char *result = strrchr(str, 'a');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'a');
        EXPECT_TRUE(result == str + 4);
    }
    {
        char str[] = "ababab";
        char *result = strrchr(str, 'b');
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'b');
        EXPECT_TRUE(result == str + 5);
    }
}
