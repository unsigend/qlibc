#include <limits.h>
#include <stdlib.h>
#include <utest.h>

UTEST_CASE(ldiv)
{
    ldiv_t r;

    r = ldiv(7L, 3L);
    EXPECT_EQ_INT(r.quot, 2L);
    EXPECT_EQ_INT(r.rem, 1L);
    EXPECT_EQ_INT(r.quot * 3L + r.rem, 7L);

    r = ldiv(-7L, 3L);
    EXPECT_EQ_INT(r.quot, -2L);
    EXPECT_EQ_INT(r.rem, -1L);
    EXPECT_EQ_INT(r.quot * 3L + r.rem, -7L);

    r = ldiv(7L, -3L);
    EXPECT_EQ_INT(r.quot, -2L);
    EXPECT_EQ_INT(r.rem, 1L);
    EXPECT_EQ_INT(r.quot * (-3L) + r.rem, 7L);

    r = ldiv(-7L, -3L);
    EXPECT_EQ_INT(r.quot, 2L);
    EXPECT_EQ_INT(r.rem, -1L);
    EXPECT_EQ_INT(r.quot * (-3L) + r.rem, -7L);

    r = ldiv(6L, 3L);
    EXPECT_EQ_INT(r.quot, 2L);
    EXPECT_EQ_INT(r.rem, 0L);

    r = ldiv(0L, 5L);
    EXPECT_EQ_INT(r.quot, 0L);
    EXPECT_EQ_INT(r.rem, 0L);

    r = ldiv(LONG_MAX, 1L);
    EXPECT_EQ_INT(r.quot, LONG_MAX);
    EXPECT_EQ_INT(r.rem, 0L);

    r = ldiv(LONG_MAX, LONG_MAX);
    EXPECT_EQ_INT(r.quot, 1L);
    EXPECT_EQ_INT(r.rem, 0L);

    r = ldiv(-LONG_MAX, LONG_MAX);
    EXPECT_EQ_INT(r.quot, -1L);
    EXPECT_EQ_INT(r.rem, 0L);
}
