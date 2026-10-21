#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <utest.h>

UTEST_CASE(in_x)
{
    int n;
    unsigned v, a, b;
    unsigned long lu;
    unsigned long long llu;
    unsigned short hu;
    unsigned char hhu;
    size_t zu;

    n = sscanf("0", "%x", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 0u);
    n = sscanf("1", "%x", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 1u);
    n = sscanf("a", "%x", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 10u);
    n = sscanf("A", "%x", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 10u);
    n = sscanf("f", "%x", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 15u);
    n = sscanf("F", "%X", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 15u);
    n = sscanf("10", "%x", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 16u);
    n = sscanf("ff", "%x", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 255u);
    n = sscanf("FF", "%X", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 255u);
    n = sscanf("0x10", "%x", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 16u);
    n = sscanf("0X1a", "%x", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 26u);
    n = sscanf("0XABC", "%X", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 0xabcu);
    n = sscanf("abcdef", "%x", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 0xabcdefu);
    n = sscanf("ABCDEF", "%x", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 0xabcdefu);
    n = sscanf("aBcDeF", "%x", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 0xabcdefu);
    n = sscanf("  0x20", "%x", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 32u);
    n = sscanf("  0X20", "%X", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 32u);

    if (INT_MAX == 2147483647) {
        n = sscanf("7fffffff", "%x", &v);
        EXPECT_EQ_INT(n, 1);
        EXPECT_EQ_UINT(v, (unsigned)INT_MAX);
        n = sscanf("7FFFFFFF", "%X", &v);
        EXPECT_EQ_INT(n, 1);
        EXPECT_EQ_UINT(v, (unsigned)INT_MAX);
    }
    if (UINT_MAX == 4294967295u) {
        n = sscanf("ffffffff", "%x", &v);
        EXPECT_EQ_INT(n, 1);
        EXPECT_EQ_UINT(v, UINT_MAX);
        n = sscanf("FFFFFFFF", "%X", &v);
        EXPECT_EQ_INT(n, 1);
        EXPECT_EQ_UINT(v, UINT_MAX);
        n = sscanf("DEADBEEF", "%x", &v);
        EXPECT_EQ_INT(n, 1);
        EXPECT_EQ_UINT(v, 0xdeadbeefu);
    }

    n = sscanf("x42", "%x", &v);
    EXPECT_EQ_INT(n, 0);
    n = sscanf("", "%x", &v);
    EXPECT_EQ_INT(n, -1);
    n = sscanf("   ", "%x", &v);
    EXPECT_EQ_INT(n, -1);
    n = sscanf("0x", "%x", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 0u);
    n = sscanf("42g", "%x", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 0x42u);
    n = sscanf("42G", "%X", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 0x42u);
    n = sscanf("n=0x1a", "n=%x", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 26u);
    n = sscanf("n=0X1A", "n=%X", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 26u);

    n = sscanf("10 ff", "%x %x", &a, &b);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_UINT(a, 16u);
    EXPECT_EQ_UINT(b, 255u);
    n = sscanf("10 FF", "%X %X", &a, &b);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_UINT(a, 16u);
    EXPECT_EQ_UINT(b, 255u);

    n = sscanf("0x123", "%5x", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 0x123u);

    n = sscanf("ff", "%lx", &lu);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(lu, 255UL);
    n = sscanf("FF", "%lX", &lu);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(lu, 255UL);
    n = sscanf("ff", "%hx", &hu);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(hu, 255u);
    n = sscanf("ff", "%hhx", &hhu);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(hhu, 255u);
    n = sscanf("deadbeef", "%llx", &llu);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(llu, 0xdeadbeefULL);
    n = sscanf("ff", "%zx", &zu);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(zu, 255u);

    n = sscanf("10 ff", "%*x %x", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 255u);
    n = sscanf("0x123 ab", "%*5x %x", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 0xabu);
}
