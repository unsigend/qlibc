#include <string.h>
#include <utest.h>

UTEST_CASE(memmove)
{
    char one[32];
    char two[32];

    EXPECT_EQ_PTR(memmove(one, "abc", 4), one);
    EXPECT_EQ_STR(one, "abc");
    strcpy(one, "abcdefgh");
    memmove(one + 1, "xyz", 2);
    EXPECT_EQ_STR(one, "axydefgh");
    strcpy(one, "abc");
    memmove(one, "xyz", 0);
    EXPECT_EQ_STR(one, "abc");
    strcpy(one, "hi there");
    strcpy(two, "foo");
    memmove(two, one, 9);
    EXPECT_EQ_STR(two, "hi there");
    EXPECT_EQ_STR(one, "hi there");
    strcpy(one, "abcdefgh");
    memmove(one + 1, one, 9);
    EXPECT_EQ_STR(one, "aabcdefgh");
    strcpy(one, "abcdefgh");
    memmove(one + 1, one + 2, 7);
    EXPECT_EQ_STR(one, "acdefgh");
    strcpy(one, "abcdefgh");
    memmove(one, one, 9);
    EXPECT_EQ_STR(one, "abcdefgh");
}
