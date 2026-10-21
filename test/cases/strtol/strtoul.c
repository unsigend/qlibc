#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <utest.h>

#define CHECK(s, base, exp, left)                                              \
    do {                                                                       \
        char *ep;                                                              \
        unsigned long v = strtoul((s), &ep, (base));                           \
        EXPECT_EQ_UINT(v, (unsigned long)(exp));                               \
        EXPECT_EQ_CHAR(*ep, (left));                                           \
    } while (0)

UTEST_CASE(strtoul)
{
    char *ep;
    char lim[64];
    unsigned long v;

    CHECK("  0", 0, 0UL, '\0');
    CHECK("123", 0, 123UL, '\0');
    CHECK("+123", 0, 123UL, '\0');
    CHECK("  123", 0, 123UL, '\0');
    CHECK(" 123 ", 0, 123UL, ' ');
    CHECK("0123", 0, 0123UL, '\0');
    CHECK("0123a", 0, 0123UL, 'a');
    CHECK("01239", 0, 0123UL, '9');
    CHECK("0x123", 0, 0x123UL, '\0');
    CHECK("0x0xc", 0, 0UL, 'x');
    CHECK(" +0x123fg", 0, 0x123fUL, 'g');
    CHECK("123", 16, 0x123UL, '\0');
    CHECK("0x123", 16, 0x123UL, '\0');
    CHECK("123", 8, 0123UL, '\0');
    CHECK("0123", 8, 0123UL, '\0');
    CHECK("0123", 10, 123UL, '\0');
    CHECK("0x123", 10, 0UL, 'x');
    CHECK("abcd", 16, 0xabcdUL, '\0');
    CHECK("AbCd", 16, 0xabcdUL, '\0');
    CHECK("0xABCD", 16, 0xabcdUL, '\0');
    CHECK("0Xabcd", 16, 0xabcdUL, '\0');
    CHECK("0xyz", 35, 33UL * 35UL + 34UL, 'z');
    CHECK("yz!", 36, 34UL * 36UL + 35UL, '!');
    CHECK("GhI4", 20, ((16UL * 20UL + 17UL) * 20UL + 18UL) * 20UL + 4UL, '\0');
    CHECK("0xffffffffg", 0, 0xffffffffUL, 'g');
    CHECK("0", 10, 0UL, '\0');
    CHECK("000123", 10, 123UL, '\0');
    CHECK("\t123", 10, 123UL, '\0');
    CHECK("\n123", 10, 123UL, '\0');
    CHECK("\r123", 10, 123UL, '\0');
    CHECK("\v123", 10, 123UL, '\0');
    CHECK("\f123", 10, 123UL, '\0');
    CHECK("123abc", 10, 123UL, 'a');
    CHECK("123 456", 10, 123UL, ' ');
    CHECK("1010", 2, 10UL, '\0');
    CHECK("2", 2, 0UL, '2');
    CHECK("0x", 0, 0UL, 'x');
    CHECK("0x", 16, 0UL, 'x');
    CHECK("0xG", 16, 0UL, 'x');
    CHECK("08", 8, 0UL, '8');
    CHECK("08", 0, 0UL, '8');
    CHECK("0x8", 0, 8UL, '\0');
    CHECK("", 10, 0UL, '\0');
    CHECK("abc", 10, 0UL, 'a');
    CHECK("  ", 10, 0UL, ' ');
    CHECK("+", 10, 0UL, '+');
    CHECK("-", 10, 0UL, '-');
    CHECK("+abc", 10, 0UL, '+');
    CHECK("-abc", 10, 0UL, '-');
    CHECK("-0", 10, 0UL, '\0');
    CHECK("-1", 10, 0UL - 1UL, '\0');
    CHECK("-123", 10, 0UL - 123UL, '\0');

    ep = (char *)0x1;
    v = strtoul("abc", &ep, 10);
    EXPECT_EQ_UINT(v, 0UL);
    EXPECT_EQ_STR(ep, "abc");

    EXPECT_EQ_UINT(strtoul("123", NULL, 10), 123UL);

    sprintf(lim, "%lu", ULONG_MAX);
    CHECK(lim, 10, ULONG_MAX, '\0');

    sprintf(lim, "%lu0", ULONG_MAX);
    errno = 0;
    v = strtoul(lim, &ep, 10);
    EXPECT_EQ_UINT(v, ULONG_MAX);
    EXPECT_EQ_INT(errno, ERANGE);
    EXPECT_EQ_CHAR(*ep, '\0');

    sprintf(lim, "-%lu0", ULONG_MAX);
    errno = 0;
    v = strtoul(lim, &ep, 10);
    EXPECT_EQ_UINT(v, ULONG_MAX);
    EXPECT_EQ_INT(errno, ERANGE);
    EXPECT_EQ_CHAR(*ep, '\0');
}
