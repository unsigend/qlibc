#include <string.h>
#include <utest.h>

UTEST_CASE(strncpy)
{
    char one[32];
    char two[32];

    EXPECT_EQ_PTR(strncpy(one, "abc", 4), one);
    EXPECT_EQ_STR(one, "abc");
    strcpy(one, "abcdefgh");
    strncpy(one, "xyz", 2);
    EXPECT_EQ_STR(one, "xycdefgh");
    strcpy(one, "abcdefgh");
    strncpy(one, "xyz", 3);
    EXPECT_EQ_STR(one, "xyzdefgh");
    strcpy(one, "abcdefgh");
    strncpy(one, "xyz", 4);
    EXPECT_EQ_STR(one, "xyz");
    EXPECT_EQ_STR(one + 4, "efgh");
    strcpy(one, "abcdefgh");
    strncpy(one, "xyz", 5);
    EXPECT_EQ_STR(one, "xyz");
    EXPECT_EQ_STR(one + 4, "");
    EXPECT_EQ_STR(one + 5, "fgh");
    strcpy(one, "abc");
    strncpy(one, "xyz", 0);
    EXPECT_EQ_STR(one, "abc");
    strncpy(one, "", 2);
    EXPECT_EQ_STR(one, "");
    EXPECT_EQ_STR(one + 1, "");
    EXPECT_EQ_STR(one + 2, "c");
    strcpy(one, "hi there");
    strncpy(two, one, 9);
    EXPECT_EQ_STR(two, "hi there");
    EXPECT_EQ_STR(one, "hi there");
}
