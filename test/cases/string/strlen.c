#include <string.h>
#include <utest.h>

UTEST_CASE(strlen)
{
    EXPECT_EQ_UINT(strlen(""), 0);
    EXPECT_EQ_UINT(strlen("a"), 1);
    EXPECT_EQ_UINT(strlen("abcd"), 4);
}
