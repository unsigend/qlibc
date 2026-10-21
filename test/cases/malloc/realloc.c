#include <stdalign.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <utest.h>

UTEST_CASE(realloc)
{
    unsigned char *p;
    unsigned char *q;
    size_t i;

    p = realloc(NULL, 16);
    EXPECT_NOTNULL(p);
    EXPECT_EQ_UINT((uintptr_t)p % alignof(max_align_t), 0);
    for (i = 0; i < 16; i++)
        p[i] = (unsigned char)(0x10 + i);

    q = realloc(p, 32);
    EXPECT_NOTNULL(q);
    EXPECT_EQ_UINT((uintptr_t)q % alignof(max_align_t), 0);
    for (i = 0; i < 16; i++)
        EXPECT_EQ_UCHAR(q[i], (unsigned char)(0x10 + i));
    q[16] = 0xaa;
    q[31] = 0xbb;
    EXPECT_EQ_UCHAR(q[16], 0xaa);
    EXPECT_EQ_UCHAR(q[31], 0xbb);

    p = realloc(q, 8);
    EXPECT_NOTNULL(p);
    EXPECT_EQ_UINT((uintptr_t)p % alignof(max_align_t), 0);
    for (i = 0; i < 8; i++)
        EXPECT_EQ_UCHAR(p[i], (unsigned char)(0x10 + i));
    free(p);
}
