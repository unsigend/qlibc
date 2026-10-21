#include <string.h>
#include <utest.h>

UTEST_CASE(memchr)
{
    char one[16];

    EXPECT_NULL(memchr("abcd", 'z', 4));
    strcpy(one, "abcd");
    EXPECT_EQ_PTR(memchr(one, 'c', 4), one + 2);
    EXPECT_EQ_PTR(memchr(one, ~0xff | 'c', 4), one + 2);
    EXPECT_EQ_PTR(memchr(one, 'd', 4), one + 3);
    EXPECT_EQ_PTR(memchr(one, 'a', 4), one);
    EXPECT_EQ_PTR(memchr(one, '\0', 5), one + 4);
    strcpy(one, "ababa");
    EXPECT_EQ_PTR(memchr(one, 'b', 5), one + 1);
    EXPECT_NULL(memchr(one, 'b', 0));
    EXPECT_EQ_PTR(memchr(one, 'a', 1), one);
    strcpy(one, "a\203b");
    EXPECT_EQ_PTR(memchr(one, 0203, 3), one + 1);
}
