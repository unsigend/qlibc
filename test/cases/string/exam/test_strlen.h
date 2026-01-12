#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(strlen){
    EXPECT_EQUAL_UINT(strlen(""), 0);
    EXPECT_EQUAL_UINT(strlen("a"), 1);
    EXPECT_EQUAL_UINT(strlen("ab"), 2);
    EXPECT_EQUAL_UINT(strlen("abc"), 3);
    EXPECT_EQUAL_UINT(strlen("hello"), 5);
    EXPECT_EQUAL_UINT(strlen("Hello World"), 11);
    EXPECT_EQUAL_UINT(strlen("12345"), 5);
    EXPECT_EQUAL_UINT(strlen("A"), 1);
    EXPECT_EQUAL_UINT(strlen("x"), 1);
    {
        char str[] = "test";
        EXPECT_EQUAL_UINT(strlen(str), 4);
    }
    {
        char str[] = "";
        EXPECT_EQUAL_UINT(strlen(str), 0);
    }
    {
        char str[] = "a";
        EXPECT_EQUAL_UINT(strlen(str), 1);
    }
    {
        char str[10] = "hello";
        EXPECT_EQUAL_UINT(strlen(str), 5);
    }
    {
        char str[100] = "Hello World";
        EXPECT_EQUAL_UINT(strlen(str), 11);
    }
    EXPECT_EQUAL_UINT(strlen("abcdefghijklmnopqrstuvwxyz"), 26);
    EXPECT_EQUAL_UINT(strlen("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), 26);
    EXPECT_EQUAL_UINT(strlen("0123456789"), 10);
    {
        char str[] = "one\0two";
        EXPECT_EQUAL_UINT(strlen(str), 3);
    }
    {
        char str[] = "\0";
        EXPECT_EQUAL_UINT(strlen(str), 0);
    }
    {
        char str[] = "a\0b";
        EXPECT_EQUAL_UINT(strlen(str), 1);
    }
    EXPECT_EQUAL_UINT(strlen(" "), 1);
    EXPECT_EQUAL_UINT(strlen("  "), 2);
    EXPECT_EQUAL_UINT(strlen("\t"), 1);
    EXPECT_EQUAL_UINT(strlen("\n"), 1);
    EXPECT_EQUAL_UINT(strlen("a b c"), 5);
    EXPECT_EQUAL_UINT(strlen("a\tb\tc"), 5);
    EXPECT_EQUAL_UINT(strlen("a\nb\nc"), 5);
    {
        char str[] = "prefixsuffix";
        EXPECT_EQUAL_UINT(strlen(str), 12);
    }
    {
        char str[] = "1234567890";
        EXPECT_EQUAL_UINT(strlen(str), 10);
    }
    EXPECT_EQUAL_UINT(strlen("!@#$%^&*()"), 10);
    {
        char str[50] = "test";
        EXPECT_EQUAL_UINT(strlen(str), 4);
    }
    {
        char str[5] = "abcd";
        EXPECT_EQUAL_UINT(strlen(str), 4);
    }
}
