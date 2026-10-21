#include <stdalign.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <utest.h>

UTEST_CASE(calloc)
{
    unsigned char *p;
    size_t i;

    p = calloc(1, 1);
    EXPECT_NOTNULL(p);
    EXPECT_EQ_UINT((uintptr_t)p % alignof(max_align_t), 0);
    EXPECT_EQ_UCHAR(p[0], 0);
    p[0] = 7;
    EXPECT_EQ_UCHAR(p[0], 7);
    free(p);

    p = calloc(8, 4);
    EXPECT_NOTNULL(p);
    EXPECT_EQ_UINT((uintptr_t)p % alignof(max_align_t), 0);
    for (i = 0; i < 32; i++)
        EXPECT_EQ_UCHAR(p[i], 0);
    p[0] = 1;
    p[31] = 2;
    EXPECT_EQ_UCHAR(p[0], 1);
    EXPECT_EQ_UCHAR(p[31], 2);
    free(p);

    p = calloc(3, sizeof(int));
    EXPECT_NOTNULL(p);
    EXPECT_EQ_UINT((uintptr_t)p % alignof(max_align_t), 0);
    EXPECT_EQ_INT(((int *)p)[0], 0);
    EXPECT_EQ_INT(((int *)p)[1], 0);
    EXPECT_EQ_INT(((int *)p)[2], 0);
    free(p);
}
