#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <utest.h>

UTEST_CASE(in_i)
{
    int n, v, a, b, c;
    long ld;
    long long lld;
    short hd;
    signed char hhd;
    ptrdiff_t zd;

    n = sscanf("42", "%i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 42);
    n = sscanf("0", "%i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 0);
    n = sscanf("-42", "%i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, -42);
    n = sscanf("+99", "%i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 99);
    n = sscanf("0x10", "%i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 16);
    n = sscanf("0X10", "%i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 16);
    n = sscanf("0x1a", "%i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 26);
    n = sscanf("0xff", "%i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 255);
    n = sscanf("0xFF", "%i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 255);
    n = sscanf("-0x10", "%i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, -16);
    n = sscanf("+0x20", "%i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 32);
    n = sscanf("  0x1a", "%i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 26);
    n = sscanf("010", "%i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 8);
    n = sscanf("012", "%i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 10);
    n = sscanf("07", "%i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 7);
    n = sscanf("08", "%i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 0);
    n = sscanf("0177", "%i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 127);
    n = sscanf("-010", "%i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, -8);
    n = sscanf("  077", "%i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 63);

    if (INT_MAX == 2147483647) {
        n = sscanf("0x7fffffff", "%i", &v);
        EXPECT_EQ_INT(n, 1);
        EXPECT_EQ_INT(v, INT_MAX);
    }

    n = sscanf("x42", "%i", &v);
    EXPECT_EQ_INT(n, 0);
    n = sscanf("", "%i", &v);
    EXPECT_EQ_INT(n, -1);
    n = sscanf("   ", "%i", &v);
    EXPECT_EQ_INT(n, -1);
    n = sscanf("0x", "%i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 0);
    n = sscanf("0xg", "%i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 0);
    n = sscanf("42abc", "%i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 42);
    n = sscanf("0x10g", "%i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 16);
    n = sscanf("n=0x1a", "n=%i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 26);

    n = sscanf("0x10 010 10", "%i %i %i", &a, &b, &c);
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_INT(a, 16);
    EXPECT_EQ_INT(b, 8);
    EXPECT_EQ_INT(c, 10);

    n = sscanf("0x10", "%5i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 16);
    n = sscanf("0x123", "%3i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 1);
    n = sscanf("010", "%4i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 8);

    n = sscanf("0x10", "%li", &ld);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(ld, 16L);
    n = sscanf("010", "%li", &ld);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(ld, 8L);
    n = sscanf("0x10", "%lli", &lld);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(lld, 16LL);
    n = sscanf("0x10", "%hi", &hd);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(hd, 16);
    n = sscanf("0x1a", "%hhi", &hhd);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(hhd, 26);
    n = sscanf("0x10", "%zi", &zd);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(zd, 16);

    n = sscanf("1 2", "%*i %i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 2);
    n = sscanf("0x10 20", "%*i %i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 20);
    n = sscanf("12345", "%*3i %i", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(v, 45);
}
