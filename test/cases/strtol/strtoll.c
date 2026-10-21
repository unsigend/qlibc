#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <utest.h>

#define CHECK(s, base, exp, left)                                              \
    do {                                                                       \
        char *ep;                                                              \
        long long v = strtoll((s), &ep, (base));                               \
        EXPECT_EQ_INT(v, (long long)(exp));                                    \
        EXPECT_EQ_CHAR(*ep, (left));                                           \
    } while (0)

UTEST_CASE(strtoll)
{
    char *ep;
    char lim[64];
    long long v;

    CHECK("123", 0, 123LL, '\0');
    CHECK("+123", 0, 123LL, '\0');
    CHECK("  123", 0, 123LL, '\0');
    CHECK(" 123 ", 0, 123LL, ' ');
    CHECK("   -17", 0, -17LL, '\0');
    CHECK("0123", 0, 0123LL, '\0');
    CHECK("0123a", 0, 0123LL, 'a');
    CHECK("01239", 0, 0123LL, '9');
    CHECK("0x123", 0, 0x123LL, '\0');
    CHECK("-0x123", 0, -0x123LL, '\0');
    CHECK("0x0xc", 0, 0LL, 'x');
    CHECK(" +0x123fg", 0, 0x123fLL, 'g');
    CHECK("123", 16, 0x123LL, '\0');
    CHECK("0x123", 16, 0x123LL, '\0');
    CHECK("123", 8, 0123LL, '\0');
    CHECK("0123", 8, 0123LL, '\0');
    CHECK("0123", 10, 123LL, '\0');
    CHECK("0x123", 10, 0LL, 'x');
    CHECK("abcd", 16, 0xabcdLL, '\0');
    CHECK("AbCd", 16, 0xabcdLL, '\0');
    CHECK("0xABCD", 16, 0xabcdLL, '\0');
    CHECK("0Xabcd", 16, 0xabcdLL, '\0');
    CHECK("0xyz", 35, 33LL * 35LL + 34LL, 'z');
    CHECK("yz!", 36, 34LL * 36LL + 35LL, '!');
    CHECK("-yz", 36, -(34LL * 36LL + 35LL), '\0');
    CHECK("GhI4", 20, ((16LL * 20LL + 17LL) * 20LL + 18LL) * 20LL + 4LL, '\0');
    CHECK("99000000001", 0, 1000000000LL * 99LL + 1LL, '\0');
    CHECK("0", 10, 0LL, '\0');
    CHECK("-0", 10, 0LL, '\0');
    CHECK("000123", 10, 123LL, '\0');
    CHECK("\t123", 10, 123LL, '\0');
    CHECK("\n123", 10, 123LL, '\0');
    CHECK("\r123", 10, 123LL, '\0');
    CHECK("\v123", 10, 123LL, '\0');
    CHECK("\f123", 10, 123LL, '\0');
    CHECK("123abc", 10, 123LL, 'a');
    CHECK("123 456", 10, 123LL, ' ');
    CHECK("-123abc", 10, -123LL, 'a');
    CHECK("1010", 2, 10LL, '\0');
    CHECK("2", 2, 0LL, '2');
    CHECK("0x", 0, 0LL, 'x');
    CHECK("0x", 16, 0LL, 'x');
    CHECK("0xG", 16, 0LL, 'x');
    CHECK("08", 8, 0LL, '8');
    CHECK("08", 0, 0LL, '8');
    CHECK("0x8", 0, 8LL, '\0');
    CHECK("", 10, 0LL, '\0');
    CHECK("abc", 10, 0LL, 'a');
    CHECK("  ", 10, 0LL, ' ');
    CHECK("+", 10, 0LL, '+');
    CHECK("-", 10, 0LL, '-');
    CHECK("+abc", 10, 0LL, '+');
    CHECK("-abc", 10, 0LL, '-');
    CHECK("2147483647", 10, 2147483647LL, '\0');
    CHECK("-2147483648", 10, -2147483648LL, '\0');

    ep = (char *)0x1;
    v = strtoll("abc", &ep, 10);
    EXPECT_EQ_INT(v, 0LL);
    EXPECT_EQ_STR(ep, "abc");

    EXPECT_EQ_INT(strtoll("123", NULL, 10), 123LL);

    sprintf(lim, "%lld", LLONG_MAX);
    CHECK(lim, 10, LLONG_MAX, '\0');
    sprintf(lim, "%lld", LLONG_MIN);
    CHECK(lim, 10, LLONG_MIN, '\0');

    sprintf(lim, "%lld0", LLONG_MAX);
    errno = 0;
    v = strtoll(lim, &ep, 10);
    EXPECT_EQ_INT(v, LLONG_MAX);
    EXPECT_EQ_INT(errno, ERANGE);
    EXPECT_EQ_CHAR(*ep, '\0');

    sprintf(lim, "%lld0", LLONG_MIN);
    errno = 0;
    v = strtoll(lim, &ep, 10);
    EXPECT_EQ_INT(v, LLONG_MIN);
    EXPECT_EQ_INT(errno, ERANGE);
    EXPECT_EQ_CHAR(*ep, '\0');
}
