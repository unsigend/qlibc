#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <utest.h>

UTEST_CASE(in_d)
{
    int n, v, a, b, c;
    long ld;
    long long lld;
    short hd;
    signed char hhd;
    ptrdiff_t zd;

    n = sscanf("0", "%d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 0);
    n = sscanf("1", "%d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 1);
    n = sscanf("42", "%d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 42);
    n = sscanf("-1", "%d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, -1);
    n = sscanf("-42", "%d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, -42);
    n = sscanf("+99", "%d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 99);
    n = sscanf("  123", "%d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 123);
    n = sscanf("\t\n  -7", "%d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, -7);
    n = sscanf("9", "%d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 9);
    n = sscanf("99", "%d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 99);
    n = sscanf("100", "%d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 100);
    n = sscanf("-9", "%d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, -9);
    n = sscanf("-100", "%d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, -100);
    n = sscanf("1234567890", "%d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 1234567890);
    n = sscanf("-1234567890", "%d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, -1234567890);

    if (INT_MAX == 2147483647) {
        n = sscanf("2147483647", "%d", &v);
        EXPECT_EQ_INT(n, 1);
        EXPECT_EQ_INT(v, INT_MAX);
    }
    if (INT_MIN == (-2147483647 - 1)) {
        n = sscanf("-2147483648", "%d", &v);
        EXPECT_EQ_INT(n, 1);
        EXPECT_EQ_INT(v, INT_MIN);
    }

    n = sscanf("x42", "%d", &v);
    EXPECT_EQ_INT(n, 0);
    n = sscanf("", "%d", &v);
    EXPECT_EQ_INT(n, -1);
    n = sscanf("   ", "%d", &v);
    EXPECT_EQ_INT(n, -1);
    n = sscanf("abc", "%d", &v);
    EXPECT_EQ_INT(n, 0);
    n = sscanf("42abc", "%d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 42);
    n = sscanf("0x10", "%d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 0);
    n = sscanf("x42", "x%d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 42);
    n = sscanf("x42y", "x%dy", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 42);
    n = sscanf("n=42", "n=%d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 42);

    n = sscanf("12 34", "%d %d", &a, &b);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_INT(a, 12);
    EXPECT_EQ_INT(b, 34);
    n = sscanf("1 2 3", "%d%d%d", &a, &b, &c);
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_INT(a, 1);
    EXPECT_EQ_INT(b, 2);
    EXPECT_EQ_INT(c, 3);
    n = sscanf("1", "%d %d", &a, &b);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(a, 1);

    n = sscanf("42", "%3d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 42);
    n = sscanf("12345", "%3d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 123);
    n = sscanf("12345", "%5d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 12345);
    n = sscanf("-99", "%5d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, -99);
    n = sscanf("-123", "%4d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, -123);
    n = sscanf("12", "%10d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 12);
    n = sscanf("  42", "%5d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 42);

    n = sscanf("42", "%ld", &ld);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(ld, 42L);
    n = sscanf("-123", "%ld", &ld);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(ld, -123L);
    n = sscanf("42", "%lld", &lld);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(lld, 42LL);
    n = sscanf("-123", "%lld", &lld);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(lld, -123LL);
    n = sscanf("42", "%hd", &hd);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(hd, 42);
    n = sscanf("-123", "%hd", &hd);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(hd, -123);
    n = sscanf("42", "%hhd", &hhd);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(hhd, 42);
    n = sscanf("42", "%zd", &zd);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(zd, 42);

    n = sscanf("1 2", "%*d %d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 2);
    n = sscanf("99 42", "%*d %d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 42);
    n = sscanf("12345", "%*3d %d", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 45);
}
