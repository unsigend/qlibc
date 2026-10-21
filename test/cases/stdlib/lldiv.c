#include <limits.h>
#include <stdlib.h>
#include <utest.h>

UTEST_CASE(lldiv)
{
    lldiv_t r;

    r = lldiv(7LL, 3LL);
    EXPECT_EQ_INT(r.quot, 2LL);
    EXPECT_EQ_INT(r.rem, 1LL);
    EXPECT_EQ_INT(r.quot * 3LL + r.rem, 7LL);

    r = lldiv(-7LL, 3LL);
    EXPECT_EQ_INT(r.quot, -2LL);
    EXPECT_EQ_INT(r.rem, -1LL);
    EXPECT_EQ_INT(r.quot * 3LL + r.rem, -7LL);

    r = lldiv(7LL, -3LL);
    EXPECT_EQ_INT(r.quot, -2LL);
    EXPECT_EQ_INT(r.rem, 1LL);
    EXPECT_EQ_INT(r.quot * (-3LL) + r.rem, 7LL);

    r = lldiv(-7LL, -3LL);
    EXPECT_EQ_INT(r.quot, 2LL);
    EXPECT_EQ_INT(r.rem, -1LL);
    EXPECT_EQ_INT(r.quot * (-3LL) + r.rem, -7LL);

    r = lldiv(6LL, 3LL);
    EXPECT_EQ_INT(r.quot, 2LL);
    EXPECT_EQ_INT(r.rem, 0LL);

    r = lldiv(0LL, 5LL);
    EXPECT_EQ_INT(r.quot, 0LL);
    EXPECT_EQ_INT(r.rem, 0LL);

    r = lldiv(LLONG_MAX, 1LL);
    EXPECT_EQ_INT(r.quot, LLONG_MAX);
    EXPECT_EQ_INT(r.rem, 0LL);

    r = lldiv(LLONG_MAX, LLONG_MAX);
    EXPECT_EQ_INT(r.quot, 1LL);
    EXPECT_EQ_INT(r.rem, 0LL);

    r = lldiv(-LLONG_MAX, LLONG_MAX);
    EXPECT_EQ_INT(r.quot, -1LL);
    EXPECT_EQ_INT(r.rem, 0LL);

    r = lldiv(9223372036854775807LL, 1000000000LL);
    EXPECT_EQ_INT(r.quot, 9223372036854775807LL / 1000000000LL);
    EXPECT_EQ_INT(r.rem, 9223372036854775807LL % 1000000000LL);
    EXPECT_EQ_INT(r.quot * 1000000000LL + r.rem, 9223372036854775807LL);
}
