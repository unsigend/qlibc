#include <string.h>
#include <utest.h>

UTEST_CASE(strrchr)
{
    char one[16];

    EXPECT_NULL(strrchr("abcd", 'z'));
    strcpy(one, "abcd");
    EXPECT_EQ_PTR(strrchr(one, 'c'), one + 2);
    EXPECT_EQ_PTR(strrchr(one, 'd'), one + 3);
    EXPECT_EQ_PTR(strrchr(one, 'a'), one);
    EXPECT_EQ_PTR(strrchr(one, '\0'), one + 4);
    strcpy(one, "ababa");
    EXPECT_EQ_PTR(strrchr(one, 'b'), one + 3);
    strcpy(one, "");
    EXPECT_NULL(strrchr(one, 'b'));
    EXPECT_EQ_PTR(strrchr(one, '\0'), one);
}
