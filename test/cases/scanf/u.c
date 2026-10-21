#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <utest.h>

UTEST_CASE(in_u)
{
    int n;
    unsigned v, a, b;
    unsigned long lu;
    unsigned long long llu;
    unsigned short hu;
    unsigned char hhu;
    size_t zu;

    n = sscanf("0", "%u", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 0u);
    n = sscanf("1", "%u", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 1u);
    n = sscanf("42", "%u", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 42u);
    n = sscanf("  123", "%u", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 123u);
    n = sscanf("\t\n  99", "%u", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 99u);
    n = sscanf("1234567890", "%u", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 1234567890u);

    if (UINT_MAX == 4294967295u) {
        n = sscanf("4294967295", "%u", &v);
        EXPECT_EQ_INT(n, 1);
        EXPECT_EQ_UINT(v, UINT_MAX);
    }

    n = sscanf("x42", "%u", &v);
    EXPECT_EQ_INT(n, 0);
    n = sscanf("", "%u", &v);
    EXPECT_EQ_INT(n, -1);
    n = sscanf("   ", "%u", &v);
    EXPECT_EQ_INT(n, -1);
    n = sscanf("abc", "%u", &v);
    EXPECT_EQ_INT(n, 0);
    n = sscanf("42abc", "%u", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 42u);
    n = sscanf("x42", "x%u", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 42u);

    n = sscanf("12 34", "%u %u", &a, &b);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_UINT(a, 12u);
    EXPECT_EQ_UINT(b, 34u);

    n = sscanf("42", "%3u", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 42u);
    n = sscanf("12345", "%3u", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 123u);

    n = sscanf("42", "%lu", &lu);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(lu, 42UL);
    n = sscanf("42", "%llu", &llu);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(llu, 42ULL);
    n = sscanf("42", "%hu", &hu);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(hu, 42u);
    n = sscanf("42", "%hhu", &hhu);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(hhu, 42u);
    n = sscanf("42", "%zu", &zu);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(zu, 42u);

    n = sscanf("1 2", "%*u %u", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 2u);
    n = sscanf("12345", "%*3u %u", &v);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(v, 45u);
}
