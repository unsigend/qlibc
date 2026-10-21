#include <string.h>
#include <utest.h>

UTEST_CASE(strcmp)
{
    EXPECT_EQ_INT(strcmp("", ""), 0);
    EXPECT_EQ_INT(strcmp("a", "a"), 0);
    EXPECT_EQ_INT(strcmp("abc", "abc"), 0);
    EXPECT_TRUE(strcmp("abc", "abcd") < 0);
    EXPECT_TRUE(strcmp("abcd", "abc") > 0);
    EXPECT_TRUE(strcmp("abcd", "abce") < 0);
    EXPECT_TRUE(strcmp("abce", "abcd") > 0);
    EXPECT_TRUE(strcmp("a\203", "a") > 0);
    EXPECT_TRUE(strcmp("a\203", "a\003") > 0);
}
