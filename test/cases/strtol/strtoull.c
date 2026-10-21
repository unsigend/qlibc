#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <utest.h>

#define CHECK(s, base, exp, left)                                              \
    do {                                                                       \
        char *ep;                                                              \
        unsigned long long v = strtoull((s), &ep, (base));                     \
        EXPECT_EQ_UINT(v, (unsigned long long)(exp));                          \
        EXPECT_EQ_CHAR(*ep, (left));                                           \
    } while (0)

UTEST_CASE(strtoull)
{
    char *ep;
    char lim[64];
    unsigned long long v;

    CHECK("  0", 0, 0ULL, '\0');
    CHECK("123", 0, 123ULL, '\0');
    CHECK("+123", 0, 123ULL, '\0');
    CHECK("  123", 0, 123ULL, '\0');
    CHECK(" 123 ", 0, 123ULL, ' ');
    CHECK("0123", 0, 0123ULL, '\0');
    CHECK("0123a", 0, 0123ULL, 'a');
    CHECK("01239", 0, 0123ULL, '9');
    CHECK("0x123", 0, 0x123ULL, '\0');
    CHECK("0x0xc", 0, 0ULL, 'x');
    CHECK(" +0x123fg", 0, 0x123fULL, 'g');
    CHECK("123", 16, 0x123ULL, '\0');
    CHECK("0x123", 16, 0x123ULL, '\0');
    CHECK("123", 8, 0123ULL, '\0');
    CHECK("0123", 8, 0123ULL, '\0');
    CHECK("0123", 10, 123ULL, '\0');
    CHECK("0x123", 10, 0ULL, 'x');
    CHECK("abcd", 16, 0xabcdULL, '\0');
    CHECK("AbCd", 16, 0xabcdULL, '\0');
    CHECK("0xABCD", 16, 0xabcdULL, '\0');
    CHECK("0Xabcd", 16, 0xabcdULL, '\0');
    CHECK("0xyz", 35, 33ULL * 35ULL + 34ULL, 'z');
    CHECK("yz!", 36, 34ULL * 36ULL + 35ULL, '!');
    CHECK("GhI4", 20, ((16ULL * 20ULL + 17ULL) * 20ULL + 18ULL) * 20ULL + 4ULL,
          '\0');
    CHECK("0xffffffffg", 0, 0xffffffffULL, 'g');
    CHECK("0", 10, 0ULL, '\0');
    CHECK("000123", 10, 123ULL, '\0');
    CHECK("\t123", 10, 123ULL, '\0');
    CHECK("\n123", 10, 123ULL, '\0');
    CHECK("\r123", 10, 123ULL, '\0');
    CHECK("\v123", 10, 123ULL, '\0');
    CHECK("\f123", 10, 123ULL, '\0');
    CHECK("123abc", 10, 123ULL, 'a');
    CHECK("123 456", 10, 123ULL, ' ');
    CHECK("1010", 2, 10ULL, '\0');
    CHECK("2", 2, 0ULL, '2');
    CHECK("0x", 0, 0ULL, 'x');
    CHECK("0x", 16, 0ULL, 'x');
    CHECK("0xG", 16, 0ULL, 'x');
    CHECK("08", 8, 0ULL, '8');
    CHECK("08", 0, 0ULL, '8');
    CHECK("0x8", 0, 8ULL, '\0');
    CHECK("", 10, 0ULL, '\0');
    CHECK("abc", 10, 0ULL, 'a');
    CHECK("  ", 10, 0ULL, ' ');
    CHECK("+", 10, 0ULL, '+');
    CHECK("-", 10, 0ULL, '-');
    CHECK("+abc", 10, 0ULL, '+');
    CHECK("-abc", 10, 0ULL, '-');
    CHECK("-0", 10, 0ULL, '\0');
    CHECK("-1", 10, 0ULL - 1ULL, '\0');
    CHECK("-123", 10, 0ULL - 123ULL, '\0');
    CHECK("99000000001", 0, 1000000000ULL * 99ULL + 1ULL, '\0');

    ep = (char *)0x1;
    v = strtoull("abc", &ep, 10);
    EXPECT_EQ_UINT(v, 0ULL);
    EXPECT_EQ_STR(ep, "abc");

    EXPECT_EQ_UINT(strtoull("123", NULL, 10), 123ULL);

    sprintf(lim, "%llu", ULLONG_MAX);
    CHECK(lim, 10, ULLONG_MAX, '\0');

    sprintf(lim, "%llu0", ULLONG_MAX);
    errno = 0;
    v = strtoull(lim, &ep, 10);
    EXPECT_EQ_UINT(v, ULLONG_MAX);
    EXPECT_EQ_INT(errno, ERANGE);
    EXPECT_EQ_CHAR(*ep, '\0');

    sprintf(lim, "-%llu0", ULLONG_MAX);
    errno = 0;
    v = strtoull(lim, &ep, 10);
    EXPECT_EQ_UINT(v, ULLONG_MAX);
    EXPECT_EQ_INT(errno, ERANGE);
    EXPECT_EQ_CHAR(*ep, '\0');
}
