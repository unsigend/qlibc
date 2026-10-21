#include <string.h>
#include <stdlib.h>
#include <utest.h>

UTEST_CASE(strdup)
{
    char *p = strdup("abcdef");
    char *e = strdup("");

    EXPECT_NOTNULL(p);
    EXPECT_EQ_STR(p, "abcdef");
    EXPECT_NOTNULL(e);
    EXPECT_EQ_STR(e, "");
    free(p);
    free(e);
}
