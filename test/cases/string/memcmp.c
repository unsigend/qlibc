#include <string.h>
#include <utest.h>

UTEST_CASE(memcmp)
{
    EXPECT_EQ_INT(memcmp("a", "a", 1), 0);
    EXPECT_EQ_INT(memcmp("abc", "abc", 3), 0);
    EXPECT_TRUE(memcmp("abcd", "abcf", 4) < 0);
    EXPECT_TRUE(memcmp("abcf", "abcd", 4) > 0);
    EXPECT_TRUE(memcmp("a\203", "a\003", 2) > 0);
    EXPECT_TRUE(memcmp("a\003", "a\203", 2) < 0);
    EXPECT_EQ_INT(memcmp("abcf", "abcd", 3), 0);
    EXPECT_EQ_INT(memcmp("abc", "def", 0), 0);
}
