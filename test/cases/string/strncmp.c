#include <string.h>
#include <utest.h>

UTEST_CASE(strncmp)
{
    EXPECT_EQ_INT(strncmp("", "", 99), 0);
    EXPECT_EQ_INT(strncmp("a", "a", 99), 0);
    EXPECT_EQ_INT(strncmp("abc", "abc", 99), 0);
    EXPECT_TRUE(strncmp("abc", "abcd", 99) < 0);
    EXPECT_TRUE(strncmp("abcd", "abc", 99) > 0);
    EXPECT_TRUE(strncmp("abcd", "abce", 99) < 0);
    EXPECT_TRUE(strncmp("abce", "abcd", 99) > 0);
    EXPECT_TRUE(strncmp("a\203", "a", 2) > 0);
    EXPECT_TRUE(strncmp("a\203", "a\003", 2) > 0);
    EXPECT_EQ_INT(strncmp("abce", "abcd", 3), 0);
    EXPECT_EQ_INT(strncmp("abce", "abc", 3), 0);
    EXPECT_TRUE(strncmp("abcd", "abce", 4) < 0);
    EXPECT_EQ_INT(strncmp("abc", "def", 0), 0);
}
