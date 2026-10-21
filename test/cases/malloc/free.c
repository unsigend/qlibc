#include <stdlib.h>
#include <utest.h>

UTEST_CASE(free)
{
    void *p;

    free(NULL);

    p = malloc(8);
    EXPECT_NOTNULL(p);
    free(p);

    p = calloc(4, 4);
    EXPECT_NOTNULL(p);
    free(p);

    p = realloc(NULL, 8);
    EXPECT_NOTNULL(p);
    free(p);
}
