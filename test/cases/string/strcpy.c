#include <string.h>
#include <utest.h>

UTEST_CASE(strcpy)
{
    char one[32];
    char two[32];

    EXPECT_EQ_PTR(strcpy(one, "abcd"), one);
    EXPECT_EQ_STR(one, "abcd");
    strcpy(one, "x");
    EXPECT_EQ_STR(one, "x");
    EXPECT_EQ_STR(one + 2, "cd");
    strcpy(two, "hi there");
    strcpy(one, two);
    EXPECT_EQ_STR(one, "hi there");
    EXPECT_EQ_STR(two, "hi there");
    strcpy(one, "");
    EXPECT_EQ_STR(one, "");
}
