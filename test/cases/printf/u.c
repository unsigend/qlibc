#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <utest.h>

UTEST_CASE(u)
{
    char buf[256];
    int n;

    n = snprintf(buf, sizeof(buf), "%u", 0);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "0");
    n = snprintf(buf, sizeof(buf), "%u", 1);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "1");
    n = snprintf(buf, sizeof(buf), "%u", 9);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "9");
    n = snprintf(buf, sizeof(buf), "%u", 10);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_STR(buf, "10");
    n = snprintf(buf, sizeof(buf), "%u", 99);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_STR(buf, "99");
    n = snprintf(buf, sizeof(buf), "%u", 100);
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "100");
    n = snprintf(buf, sizeof(buf), "%u", 999999);
    EXPECT_EQ_INT(n, 6);
    EXPECT_EQ_STR(buf, "999999");
    n = snprintf(buf, sizeof(buf), "%u", UINT_MAX);
    if (UINT_MAX == 4294967295u) {
        EXPECT_EQ_INT(n, 10);
        EXPECT_EQ_STR(buf, "4294967295");
    }
    n = snprintf(buf, sizeof(buf), "%u", UINT_MAX - 1);
    if (UINT_MAX == 4294967295u)
        EXPECT_EQ_STR(buf, "4294967294");
    n = snprintf(buf, sizeof(buf), "%.0u", 0);
    EXPECT_EQ_INT(n, 0);
    EXPECT_EQ_STR(buf, "");
    n = snprintf(buf, sizeof(buf), "%.0u", 1);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "1");
    n = snprintf(buf, sizeof(buf), "%.3u", 1);
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "001");
    n = snprintf(buf, sizeof(buf), "%.5u", 42);
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "00042");
    n = snprintf(buf, sizeof(buf), "%.1u", 0);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "0");
    n = snprintf(buf, sizeof(buf), "%.2u", 123);
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "123");
    n = snprintf(buf, sizeof(buf), "%.12u", UINT_MAX);
    if (UINT_MAX == 4294967295u) {
        EXPECT_EQ_INT(n, 12);
        EXPECT_EQ_STR(buf, "004294967295");
    }
    n = snprintf(buf, sizeof(buf), "x%u y", 42);
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "x42 y");
    n = snprintf(buf, sizeof(buf), "%u%u", 1, 2);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_STR(buf, "12");
    n = snprintf(buf, 1, "%u", 42);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_STR(buf, "");
    n = snprintf(buf, 0, "%u", 42);
    EXPECT_EQ_INT(n, 2);
    n = snprintf(buf, sizeof(buf), "%.10u", 1);
    EXPECT_EQ_INT(n, 10);
    EXPECT_EQ_STR(buf, "0000000001");
    n = snprintf(buf, sizeof(buf), "%u", (unsigned)-1);
    if (UINT_MAX == 4294967295u)
        EXPECT_EQ_STR(buf, "4294967295");
    n = snprintf(buf, sizeof(buf), "%u", USHRT_MAX);
    if (USHRT_MAX == 65535)
        EXPECT_EQ_STR(buf, "65535");
    n = snprintf(buf, sizeof(buf), "%u", UCHAR_MAX);
    if (UCHAR_MAX == 255)
        EXPECT_EQ_STR(buf, "255");
    n = snprintf(buf, sizeof(buf), "%5u", 42);
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "   42");
    n = snprintf(buf, sizeof(buf), "%-5u", 42);
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "42   ");
    n = snprintf(buf, sizeof(buf), "%5u", 0);
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "    0");
    n = snprintf(buf, sizeof(buf), "%-5u", 0);
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "0    ");
    n = snprintf(buf, sizeof(buf), "%05u", 42);
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "00042");
    n = snprintf(buf, sizeof(buf), "%05u", 0);
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "00000");
    n = snprintf(buf, sizeof(buf), "%08u", 123);
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "00000123");
    n = snprintf(buf, sizeof(buf), "%5.3u", 1);
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "  001");
    n = snprintf(buf, sizeof(buf), "%8.4u", 42);
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "    0042");
    n = snprintf(buf, sizeof(buf), "%*u", 5, 42);
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "   42");
    n = snprintf(buf, sizeof(buf), "%.*u", 3, 1);
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "001");
    n = snprintf(buf, sizeof(buf), "%*.*u", 8, 4, 42);
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "    0042");
    n = snprintf(buf, sizeof(buf), "%-5.3u", 1);
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "001  ");
    n = snprintf(buf, sizeof(buf), "%-*.*u", 8, 4, 42);
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "0042    ");
    n = snprintf(buf, sizeof(buf), "%lu", 42UL);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_STR(buf, "42");
    n = snprintf(buf, sizeof(buf), "%lu", ULONG_MAX);
    if (ULONG_MAX == 0xffffffffffffffffUL) {
        EXPECT_EQ_STR(buf, "18446744073709551615");
    } else if (ULONG_MAX == 4294967295UL) {
        EXPECT_EQ_STR(buf, "4294967295");
    }
    n = snprintf(buf, sizeof(buf), "%llu", 42ULL);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_STR(buf, "42");
    n = snprintf(buf, sizeof(buf), "%llu", ULLONG_MAX);
    if (ULLONG_MAX == 18446744073709551615ULL)
        EXPECT_EQ_STR(buf, "18446744073709551615");
    n = snprintf(buf, sizeof(buf), "%zu", (size_t)42);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_STR(buf, "42");
    n = snprintf(buf, sizeof(buf), "%5lu", 42UL);
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "   42");
    n = snprintf(buf, sizeof(buf), "%-5zu", (size_t)42);
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "42   ");
    n = snprintf(buf, sizeof(buf), "%.3lu", 1UL);
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "001");
    n = snprintf(buf, sizeof(buf), "%08lu", 123UL);
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "00000123");
    n = snprintf(buf, sizeof(buf), "%.3llu", 1ULL);
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "001");
    n = snprintf(buf, sizeof(buf), "%08zu", (size_t)123);
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "00000123");
    n = snprintf(buf, sizeof(buf), "%hu", (unsigned short)42);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_STR(buf, "42");
    n = snprintf(buf, sizeof(buf), "%5hu", (unsigned short)42);
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "   42");
    n = snprintf(buf, sizeof(buf), "%-5hu", (unsigned short)42);
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "42   ");
    n = snprintf(buf, sizeof(buf), "%.3hu", (unsigned short)1);
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "001");
    n = snprintf(buf, sizeof(buf), "%08hu", (unsigned short)123);
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "00000123");
    n = snprintf(buf, sizeof(buf), "%hhu", (unsigned char)42);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_STR(buf, "42");
    n = snprintf(buf, sizeof(buf), "%*u", 0, 42);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_STR(buf, "42");
    n = snprintf(buf, sizeof(buf), "%*u", -5, 42);
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "42   ");
    n = snprintf(buf, sizeof(buf), "%.*u", 0, 0);
    EXPECT_EQ_INT(n, 0);
    EXPECT_EQ_STR(buf, "");
    n = snprintf(buf, sizeof(buf), "%.*u", 0, 5);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "5");
    n = snprintf(buf, sizeof(buf), "%*.*u", 10, 0, 0);
    EXPECT_EQ_INT(n, 10);
    EXPECT_EQ_STR(buf, "          ");
    n = snprintf(buf, sizeof(buf), "%-*.*u", 10, 0, 0);
    EXPECT_EQ_INT(n, 10);
    EXPECT_EQ_STR(buf, "          ");
    n = snprintf(buf, sizeof(buf), "%*.*u", 6, -1, 42);
    EXPECT_EQ_INT(n, 6);
    EXPECT_EQ_STR(buf, "    42");
    n = snprintf(buf, sizeof(buf), "%010u", 42);
    EXPECT_EQ_INT(n, 10);
    EXPECT_EQ_STR(buf, "0000000042");
    n = snprintf(buf, sizeof(buf), "%010u", 0);
    EXPECT_EQ_INT(n, 10);
    EXPECT_EQ_STR(buf, "0000000000");
    n = snprintf(buf, sizeof(buf), "%0.5u", 1);
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "00001");
    n = snprintf(buf, sizeof(buf), "%0.5u", 0);
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "00000");
    n = snprintf(buf, sizeof(buf), "%hu", USHRT_MAX);
    if (USHRT_MAX == 65535)
        EXPECT_EQ_STR(buf, "65535");
    n = snprintf(buf, sizeof(buf), "%1u", 12345);
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "12345");
    n = snprintf(buf, sizeof(buf), "%-1u", 12345);
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "12345");
    n = snprintf(buf, sizeof(buf), "%zu", (size_t)0);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "0");
}
