#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(strncmp){
    EXPECT_EQUAL_INT(strncmp("", "", 0), 0);
    EXPECT_EQUAL_INT(strncmp("", "", 1), 0);
    EXPECT_EQUAL_INT(strncmp("a", "a", 1), 0);
    EXPECT_EQUAL_INT(strncmp("a", "a", 10), 0);
    EXPECT_EQUAL_INT(strncmp("ab", "ab", 2), 0);
    EXPECT_EQUAL_INT(strncmp("ab", "ab", 10), 0);
    EXPECT_EQUAL_INT(strncmp("hello", "hello", 5), 0);
    EXPECT_EQUAL_INT(strncmp("hello", "hello", 10), 0);
    EXPECT_EQUAL_INT(strncmp("Hello World", "Hello World", 11), 0);
    EXPECT_EQUAL_INT(strncmp("Hello World", "Hello World", 20), 0);
    EXPECT_EQUAL_INT(strncmp("abc", "abc", 3), 0);
    EXPECT_EQUAL_INT(strncmp("abc", "abc", 2), 0);
    EXPECT_EQUAL_INT(strncmp("abc", "abc", 1), 0);
    EXPECT_TRUE(strncmp("a", "b", 1) < 0);
    EXPECT_TRUE(strncmp("b", "a", 1) > 0);
    EXPECT_TRUE(strncmp("abc", "abd", 3) < 0);
    EXPECT_TRUE(strncmp("abd", "abc", 3) > 0);
    EXPECT_EQUAL_INT(strncmp("abc", "abd", 2), 0);
    EXPECT_EQUAL_INT(strncmp("abc", "abd", 1), 0);
    EXPECT_TRUE(strncmp("abc", "abcd", 4) < 0);
    EXPECT_TRUE(strncmp("abcd", "abc", 4) > 0);
    EXPECT_EQUAL_INT(strncmp("abc", "abcd", 3), 0);
    EXPECT_EQUAL_INT(strncmp("abcd", "abc", 3), 0);
    EXPECT_TRUE(strncmp("", "a", 1) < 0);
    EXPECT_TRUE(strncmp("a", "", 1) > 0);
    EXPECT_EQUAL_INT(strncmp("", "a", 0), 0);
    EXPECT_EQUAL_INT(strncmp("a", "", 0), 0);
    EXPECT_TRUE(strncmp("hello", "world", 5) < 0);
    EXPECT_TRUE(strncmp("world", "hello", 5) > 0);
    EXPECT_EQUAL_INT(strncmp("hello", "world", 0), 0);
    EXPECT_TRUE(strncmp("Hello", "hello", 5) < 0);
    EXPECT_TRUE(strncmp("hello", "Hello", 5) > 0);
    EXPECT_EQUAL_INT(strncmp("Hello", "hello", 0), 0);
    {
        char str1[] = "abc";
        char str2[] = "abc";
        EXPECT_EQUAL_INT(strncmp(str1, str2, 3), 0);
    }
    {
        char str1[] = "abc";
        char str2[] = "def";
        EXPECT_TRUE(strncmp(str1, str2, 3) < 0);
    }
    {
        char str1[] = "abc";
        char str2[] = "def";
        EXPECT_EQUAL_INT(strncmp(str1, str2, 0), 0);
    }
    EXPECT_TRUE(strncmp("a", "z", 1) < 0);
    EXPECT_TRUE(strncmp("z", "a", 1) > 0);
    EXPECT_TRUE(strncmp("aa", "ab", 2) < 0);
    EXPECT_TRUE(strncmp("ab", "aa", 2) > 0);
    EXPECT_EQUAL_INT(strncmp("aa", "ab", 1), 0);
    EXPECT_EQUAL_INT(strncmp("ab", "aa", 1), 0);
    EXPECT_TRUE(strncmp("aaa", "aab", 3) < 0);
    EXPECT_TRUE(strncmp("aab", "aaa", 3) > 0);
    EXPECT_EQUAL_INT(strncmp("aaa", "aab", 2), 0);
    EXPECT_EQUAL_INT(strncmp("aab", "aaa", 2), 0);
    EXPECT_EQUAL_INT(strncmp("x", "x", 1), 0);
    EXPECT_TRUE(strncmp("x", "y", 1) < 0);
    EXPECT_TRUE(strncmp("y", "x", 1) > 0);
    EXPECT_EQUAL_INT(strncmp("prefix", "prefixsuffix", 6), 0);
    EXPECT_TRUE(strncmp("prefix", "prefixsuffix", 7) < 0);
    EXPECT_EQUAL_INT(strncmp("prefixsuffix", "prefix", 6), 0);
    EXPECT_TRUE(strncmp("prefixsuffix", "prefix", 7) > 0);
    EXPECT_EQUAL_INT(strncmp("same", "same", 4), 0);
    EXPECT_TRUE(strncmp("same", "different", 4) > 0);
    EXPECT_TRUE(strncmp("different", "same", 4) < 0);
    EXPECT_EQUAL_INT(strncmp("same", "different", 0), 0);
    EXPECT_TRUE(strncmp("123", "456", 3) < 0);
    EXPECT_TRUE(strncmp("456", "123", 3) > 0);
    EXPECT_EQUAL_INT(strncmp("123", "123", 3), 0);
    EXPECT_EQUAL_INT(strncmp("123", "456", 0), 0);
    EXPECT_TRUE(strncmp(" ", "a", 1) < 0);
    EXPECT_TRUE(strncmp("a", " ", 1) > 0);
    EXPECT_EQUAL_INT(strncmp(" ", " ", 1), 0);
    EXPECT_EQUAL_INT(strncmp("test", "test", 100), 0);
    EXPECT_EQUAL_INT(strncmp("test", "test", 4), 0);
    EXPECT_EQUAL_INT(strncmp("test", "test", 3), 0);
    EXPECT_EQUAL_INT(strncmp("test", "test", 2), 0);
    EXPECT_EQUAL_INT(strncmp("test", "test", 1), 0);
    EXPECT_EQUAL_INT(strncmp("test", "test", 0), 0);
    EXPECT_TRUE(strncmp("apple", "banana", 5) < 0);
    EXPECT_TRUE(strncmp("banana", "apple", 5) > 0);
    EXPECT_EQUAL_INT(strncmp("apple", "banana", 0), 0);
    EXPECT_TRUE(strncmp("zebra", "apple", 1) > 0);
    EXPECT_TRUE(strncmp("apple", "zebra", 1) < 0);
    EXPECT_EQUAL_INT(strncmp("identical", "identical", 9), 0);
    EXPECT_TRUE(strncmp("A", "a", 1) < 0);
    EXPECT_TRUE(strncmp("a", "A", 1) > 0);
    EXPECT_TRUE(strncmp("Z", "a", 1) < 0);
    EXPECT_TRUE(strncmp("a", "Z", 1) > 0);
    EXPECT_TRUE(strncmp("0", "1", 1) < 0);
    EXPECT_TRUE(strncmp("1", "0", 1) > 0);
    EXPECT_TRUE(strncmp("9", "A", 1) < 0);
    EXPECT_TRUE(strncmp("A", "9", 1) > 0);
    {
        char str1[] = "test1";
        char str2[] = "test2";
        EXPECT_TRUE(strncmp(str1, str2, 5) < 0);
        EXPECT_EQUAL_INT(strncmp(str1, str2, 4), 0);
    }
    {
        char str1[] = "test2";
        char str2[] = "test1";
        EXPECT_TRUE(strncmp(str1, str2, 5) > 0);
        EXPECT_EQUAL_INT(strncmp(str1, str2, 4), 0);
    }
    EXPECT_TRUE(strncmp("abc", "ABC", 3) > 0);
    EXPECT_TRUE(strncmp("ABC", "abc", 3) < 0);
    EXPECT_EQUAL_INT(strncmp("abc", "ABC", 0), 0);
    EXPECT_TRUE(strncmp("a", "aa", 2) < 0);
    EXPECT_TRUE(strncmp("aa", "a", 2) > 0);
    EXPECT_TRUE(strncmp("ab", "abc", 3) < 0);
    EXPECT_TRUE(strncmp("abc", "ab", 3) > 0);
    EXPECT_EQUAL_INT(strncmp("ab", "abc", 2), 0);
    EXPECT_EQUAL_INT(strncmp("abc", "ab", 2), 0);
}
