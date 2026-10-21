#include <string.h>
#include <utest.h>

UTEST_CASE(memcpy)
{
    char one[32];
    char two[32];

    EXPECT_EQ_PTR(memcpy(one, "abc", 4), one);
    EXPECT_EQ_STR(one, "abc");
    strcpy(one, "abcdefgh");
    memcpy(one + 1, "xyz", 2);
    EXPECT_EQ_STR(one, "axydefgh");
    strcpy(one, "abc");
    memcpy(one, "xyz", 0);
    EXPECT_EQ_STR(one, "abc");
    strcpy(one, "hi there");
    strcpy(two, "foo");
    memcpy(two, one, 9);
    EXPECT_EQ_STR(two, "hi there");
    EXPECT_EQ_STR(one, "hi there");
}
