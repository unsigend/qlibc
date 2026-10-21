#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <utest.h>

#define CHECK(s, base, exp, left)                                              \
    do {                                                                       \
        char *ep;                                                              \
        long v = strtol((s), &ep, (base));                                     \
        EXPECT_EQ_INT(v, (long)(exp));                                         \
        EXPECT_EQ_CHAR(*ep, (left));                                           \
    } while (0)

UTEST_CASE(strtol)
{
    char *ep;
    char lim[64];
    long v;

    CHECK("123", 0, 123L, '\0');
    CHECK("+123", 0, 123L, '\0');
    CHECK("  123", 0, 123L, '\0');
    CHECK(" 123 ", 0, 123L, ' ');
    CHECK("   -17", 0, -17L, '\0');
    CHECK("0123", 0, 0123L, '\0');
    CHECK("0123a", 0, 0123L, 'a');
    CHECK("01239", 0, 0123L, '9');
    CHECK("0x123", 0, 0x123L, '\0');
    CHECK("-0x123", 0, -0x123L, '\0');
    CHECK("0x0xc", 0, 0L, 'x');
    CHECK(" +0x123fg", 0, 0x123fL, 'g');
    CHECK("123", 16, 0x123L, '\0');
    CHECK("0x123", 16, 0x123L, '\0');
    CHECK("123", 8, 0123L, '\0');
    CHECK("0123", 8, 0123L, '\0');
    CHECK("0123", 10, 123L, '\0');
    CHECK("0x123", 10, 0L, 'x');
    CHECK("abcd", 16, 0xabcdL, '\0');
    CHECK("AbCd", 16, 0xabcdL, '\0');
    CHECK("0xABCD", 16, 0xabcdL, '\0');
    CHECK("0Xabcd", 16, 0xabcdL, '\0');
    CHECK("0xyz", 35, 33L * 35L + 34L, 'z');
    CHECK("yz!", 36, 34L * 36L + 35L, '!');
    CHECK("-yz", 36, -(34L * 36L + 35L), '\0');
    CHECK("GhI4", 20, ((16L * 20L + 17L) * 20L + 18L) * 20L + 4L, '\0');
    CHECK("0", 10, 0L, '\0');
    CHECK("-0", 10, 0L, '\0');
    CHECK("+0", 10, 0L, '\0');
    CHECK("000123", 10, 123L, '\0');
    CHECK("\t123", 10, 123L, '\0');
    CHECK("\n123", 10, 123L, '\0');
    CHECK("\r123", 10, 123L, '\0');
    CHECK("\v123", 10, 123L, '\0');
    CHECK("\f123", 10, 123L, '\0');
    CHECK("123abc", 10, 123L, 'a');
    CHECK("123 456", 10, 123L, ' ');
    CHECK("123+456", 10, 123L, '+');
    CHECK("-123abc", 10, -123L, 'a');
    CHECK("1010", 2, 10L, '\0');
    CHECK("2", 2, 0L, '2');
    CHECK("10", 3, 3L, '\0');
    CHECK("13", 4, 7L, '\0');
    CHECK("0x", 0, 0L, 'x');
    CHECK("0x", 16, 0L, 'x');
    CHECK("0xG", 16, 0L, 'x');
    CHECK("08", 8, 0L, '8');
    CHECK("08", 0, 0L, '8');
    CHECK("0x8", 0, 8L, '\0');
    CHECK("", 10, 0L, '\0');
    CHECK("abc", 10, 0L, 'a');
    CHECK("  ", 10, 0L, ' ');
    CHECK("  abc", 10, 0L, ' ');
    CHECK("+", 10, 0L, '+');
    CHECK("-", 10, 0L, '-');
    CHECK("+abc", 10, 0L, '+');
    CHECK("-abc", 10, 0L, '-');

    ep = (char *)0x1;
    v = strtol("abc", &ep, 10);
    EXPECT_EQ_INT(v, 0L);
    EXPECT_EQ_STR(ep, "abc");

    ep = (char *)0x1;
    v = strtol("", &ep, 10);
    EXPECT_EQ_INT(v, 0L);
    EXPECT_EQ_STR(ep, "");

    ep = (char *)0x1;
    v = strtol("  ", &ep, 10);
    EXPECT_EQ_INT(v, 0L);
    EXPECT_EQ_STR(ep, "  ");

    ep = (char *)0x1;
    v = strtol("+", &ep, 10);
    EXPECT_EQ_INT(v, 0L);
    EXPECT_EQ_STR(ep, "+");

    EXPECT_EQ_INT(strtol("123", NULL, 10), 123L);

    sprintf(lim, "%ld", LONG_MAX);
    CHECK(lim, 10, LONG_MAX, '\0');
    sprintf(lim, "%ld", LONG_MIN);
    CHECK(lim, 10, LONG_MIN, '\0');

    sprintf(lim, "%ld0", LONG_MAX);
    errno = 0;
    v = strtol(lim, &ep, 10);
    EXPECT_EQ_INT(v, LONG_MAX);
    EXPECT_EQ_INT(errno, ERANGE);
    EXPECT_EQ_CHAR(*ep, '\0');

    sprintf(lim, "%ld0", LONG_MIN);
    errno = 0;
    v = strtol(lim, &ep, 10);
    EXPECT_EQ_INT(v, LONG_MIN);
    EXPECT_EQ_INT(errno, ERANGE);
    EXPECT_EQ_CHAR(*ep, '\0');
}
