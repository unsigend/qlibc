#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <utest.h>

UTEST_CASE(in_o)
{
    int n;
    unsigned u, u2;
    unsigned long lu;
    unsigned long long llu;
    unsigned short hu;
    unsigned char hhu;
    size_t zu;

    n = sscanf("0", "%o", &u);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(u, 0u);
    n = sscanf("1", "%o", &u);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(u, 1u);
    n = sscanf("7", "%o", &u);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(u, 7u);
    n = sscanf("10", "%o", &u);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(u, 8u);
    n = sscanf("12", "%o", &u);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(u, 10u);
    n = sscanf("77", "%o", &u);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(u, 63u);
    n = sscanf("100", "%o", &u);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(u, 64u);
    n = sscanf("777", "%o", &u);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(u, 511u);
    n = sscanf("0777", "%o", &u);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(u, 511u);
    n = sscanf("  77", "%o", &u);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(u, 63u);

    if (UINT_MAX == 4294967295u) {
        n = sscanf("037777777777", "%o", &u);
        EXPECT_EQ_INT(n, 1);
        EXPECT_EQ_UINT(u, UINT_MAX);
    }

    n = sscanf("8", "%o", &u);
    EXPECT_EQ_INT(n, 0);
    n = sscanf("08", "%o", &u);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(u, 0u);
    n = sscanf("x77", "%o", &u);
    EXPECT_EQ_INT(n, 0);
    n = sscanf("", "%o", &u);
    EXPECT_EQ_INT(n, -1);
    n = sscanf("   ", "%o", &u);
    EXPECT_EQ_INT(n, -1);
    n = sscanf("77abc", "%o", &u);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(u, 63u);
    n = sscanf("n=77", "n=%o", &u);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(u, 63u);

    n = sscanf("10 20", "%o %o", &u, &u2);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_UINT(u, 8u);
    EXPECT_EQ_UINT(u2, 16u);

    n = sscanf("12345", "%3o", &u);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(u, 83u);

    n = sscanf("77", "%lo", &lu);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(lu, 63UL);
    n = sscanf("77", "%llo", &llu);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(llu, 63ULL);
    n = sscanf("177", "%ho", &hu);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(hu, 127u);
    n = sscanf("377", "%hho", &hhu);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(hhu, 0xffu);
    n = sscanf("77", "%zo", &zu);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(zu, 63u);

    n = sscanf("10 20", "%*o %o", &u2);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(u2, 16u);
    n = sscanf("123 77", "%*3o %o", &u2);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(u2, 63u);
}
