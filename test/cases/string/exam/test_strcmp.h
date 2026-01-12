#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(strcmp){
    EXPECT_EQUAL_INT(strcmp("", ""), 0);
    EXPECT_EQUAL_INT(strcmp("a", "a"), 0);
    EXPECT_EQUAL_INT(strcmp("ab", "ab"), 0);
    EXPECT_EQUAL_INT(strcmp("hello", "hello"), 0);
    EXPECT_EQUAL_INT(strcmp("Hello World", "Hello World"), 0);
    EXPECT_TRUE(strcmp("a", "b") < 0);
    EXPECT_TRUE(strcmp("b", "a") > 0);
    EXPECT_TRUE(strcmp("a", "aa") < 0);
    EXPECT_TRUE(strcmp("aa", "a") > 0);
    EXPECT_TRUE(strcmp("abc", "abd") < 0);
    EXPECT_TRUE(strcmp("abd", "abc") > 0);
    EXPECT_TRUE(strcmp("abc", "abcd") < 0);
    EXPECT_TRUE(strcmp("abcd", "abc") > 0);
    EXPECT_TRUE(strcmp("", "a") < 0);
    EXPECT_TRUE(strcmp("a", "") > 0);
    EXPECT_TRUE(strcmp("hello", "world") < 0);
    EXPECT_TRUE(strcmp("world", "hello") > 0);
    EXPECT_TRUE(strcmp("Hello", "hello") < 0);
    EXPECT_TRUE(strcmp("hello", "Hello") > 0);
    EXPECT_TRUE(strcmp("A", "B") < 0);
    EXPECT_TRUE(strcmp("B", "A") > 0);
    EXPECT_TRUE(strcmp("1", "2") < 0);
    EXPECT_TRUE(strcmp("2", "1") > 0);
    EXPECT_TRUE(strcmp("10", "2") < 0);
    EXPECT_TRUE(strcmp("2", "10") > 0);
    EXPECT_EQUAL_INT(strcmp("test", "test"), 0);
    EXPECT_TRUE(strcmp("test", "Test") != 0);
    EXPECT_TRUE(strcmp("Test", "test") != 0);
    {
        char str1[] = "abc";
        char str2[] = "abc";
        EXPECT_EQUAL_INT(strcmp(str1, str2), 0);
    }
    {
        char str1[] = "abc";
        char str2[] = "def";
        EXPECT_TRUE(strcmp(str1, str2) < 0);
    }
    {
        char str1[] = "def";
        char str2[] = "abc";
        EXPECT_TRUE(strcmp(str1, str2) > 0);
    }
    EXPECT_TRUE(strcmp("a", "z") < 0);
    EXPECT_TRUE(strcmp("z", "a") > 0);
    EXPECT_TRUE(strcmp("aa", "ab") < 0);
    EXPECT_TRUE(strcmp("ab", "aa") > 0);
    EXPECT_TRUE(strcmp("aaa", "aab") < 0);
    EXPECT_TRUE(strcmp("aab", "aaa") > 0);
    EXPECT_EQUAL_INT(strcmp("x", "x"), 0);
    EXPECT_TRUE(strcmp("x", "y") < 0);
    EXPECT_TRUE(strcmp("y", "x") > 0);
    EXPECT_TRUE(strcmp("prefix", "prefixsuffix") < 0);
    EXPECT_TRUE(strcmp("prefixsuffix", "prefix") > 0);
    EXPECT_EQUAL_INT(strcmp("same", "same"), 0);
    EXPECT_TRUE(strcmp("same", "different") > 0);
    EXPECT_TRUE(strcmp("different", "same") < 0);
    EXPECT_TRUE(strcmp("123", "456") < 0);
    EXPECT_TRUE(strcmp("456", "123") > 0);
    EXPECT_EQUAL_INT(strcmp("123", "123"), 0);
    EXPECT_TRUE(strcmp(" ", "a") < 0);
    EXPECT_TRUE(strcmp("a", " ") > 0);
    EXPECT_EQUAL_INT(strcmp(" ", " "), 0);
    EXPECT_TRUE(strcmp("apple", "banana") < 0);
    EXPECT_TRUE(strcmp("banana", "apple") > 0);
    EXPECT_TRUE(strcmp("zebra", "apple") > 0);
    EXPECT_TRUE(strcmp("apple", "zebra") < 0);
    EXPECT_EQUAL_INT(strcmp("identical", "identical"), 0);
    EXPECT_TRUE(strcmp("A", "a") < 0);
    EXPECT_TRUE(strcmp("a", "A") > 0);
    EXPECT_TRUE(strcmp("Z", "a") < 0);
    EXPECT_TRUE(strcmp("a", "Z") > 0);
    EXPECT_TRUE(strcmp("0", "1") < 0);
    EXPECT_TRUE(strcmp("1", "0") > 0);
    EXPECT_TRUE(strcmp("9", "A") < 0);
    EXPECT_TRUE(strcmp("A", "9") > 0);
    EXPECT_TRUE(strcmp("!", "0") < 0);
    EXPECT_TRUE(strcmp("0", "!") > 0);
    {
        char str1[] = "test1";
        char str2[] = "test2";
        EXPECT_TRUE(strcmp(str1, str2) < 0);
    }
    {
        char str1[] = "test2";
        char str2[] = "test1";
        EXPECT_TRUE(strcmp(str1, str2) > 0);
    }
    EXPECT_TRUE(strcmp("abc", "ABC") > 0);
    EXPECT_TRUE(strcmp("ABC", "abc") < 0);
    EXPECT_TRUE(strcmp("a", "aa") < 0);
    EXPECT_TRUE(strcmp("aa", "a") > 0);
    EXPECT_TRUE(strcmp("ab", "abc") < 0);
    EXPECT_TRUE(strcmp("abc", "ab") > 0);
}
