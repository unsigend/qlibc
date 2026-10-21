#include <stdalign.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <utest.h>

UTEST_CASE(malloc)
{
    unsigned char *p;
    unsigned char *q;
    size_t i;

    p = malloc(1);
    EXPECT_NOTNULL(p);
    EXPECT_EQ_UINT((uintptr_t)p % alignof(max_align_t), 0);
    p[0] = 0xa5;
    EXPECT_EQ_UCHAR(p[0], 0xa5);
    free(p);

    p = malloc(16);
    EXPECT_NOTNULL(p);
    EXPECT_EQ_UINT((uintptr_t)p % alignof(max_align_t), 0);
    for (i = 0; i < 16; i++)
        p[i] = (unsigned char)i;
    for (i = 0; i < 16; i++)
        EXPECT_EQ_UCHAR(p[i], (unsigned char)i);
    free(p);

    p = malloc(64);
    q = malloc(64);
    EXPECT_NOTNULL(p);
    EXPECT_NOTNULL(q);
    EXPECT_EQ_UINT((uintptr_t)p % alignof(max_align_t), 0);
    EXPECT_EQ_UINT((uintptr_t)q % alignof(max_align_t), 0);
    EXPECT_NE_PTR(p, q);
    p[0] = 1;
    q[0] = 2;
    EXPECT_EQ_UCHAR(p[0], 1);
    EXPECT_EQ_UCHAR(q[0], 2);
    free(p);
    free(q);
}
