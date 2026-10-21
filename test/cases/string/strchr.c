#include <string.h>
#include <utest.h>

UTEST_CASE(strchr)
{
    char one[16];

    EXPECT_NULL(strchr("abcd", 'z'));
    strcpy(one, "abcd");
    EXPECT_EQ_PTR(strchr(one, 'c'), one + 2);
    EXPECT_EQ_PTR(strchr(one, 'd'), one + 3);
    EXPECT_EQ_PTR(strchr(one, 'a'), one);
    EXPECT_EQ_PTR(strchr(one, '\0'), one + 4);
    strcpy(one, "ababa");
    EXPECT_EQ_PTR(strchr(one, 'b'), one + 1);
    strcpy(one, "");
    EXPECT_NULL(strchr(one, 'b'));
    EXPECT_EQ_PTR(strchr(one, '\0'), one);
}
