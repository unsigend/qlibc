#include <stddef.h>
#include <stdio.h>
#include <utest.h>

UTEST_CASE(in_mix)
{
    char a[64], b[64], ch;
    int n, d, d1, d2;
    short hd;
    signed char hhd;
    long ld;
    long long lld;
    unsigned u;
    unsigned char hhu;
    unsigned short hu;
    unsigned long lu;
    unsigned long long llu;
    size_t z;
    void *p;

    n = sscanf("1 2", "%*d %d", &d);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(d, 2);

    n = sscanf("12345", "%*3d %d", &d);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(d, 45);

    n = sscanf("1 2 3", "%hd %ld %lld", &hd, &ld, &lld);
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_INT(hd, 1);
    EXPECT_EQ_INT(ld, 2L);
    EXPECT_EQ_INT(lld, 3LL);

    n = sscanf("0x10 42", "%*i %d", &d);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(d, 42);

    n = sscanf("1 2 3", "%hu %lu %llu", &hu, &lu, &llu);
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_UINT(hu, 1u);
    EXPECT_EQ_UINT(lu, 2UL);
    EXPECT_EQ_UINT(llu, 3ULL);

    n = sscanf("12345", "%*3u %u", &u);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(u, 45u);

    n = sscanf("10 77", "%*o %o", &u);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(u, 63u);

    n = sscanf("0x10 ff", "%*x %x", &u);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(u, 255u);

    n = sscanf("skip me", "%*s %s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "me");

    n = sscanf("foo bar baz", "%*s %*s %s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "baz");

    n = sscanf("hello world", "%*5s %s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "world");

    n = sscanf("ab", "%*c%c", &ch);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT((unsigned char)ch, 'b');

    n = sscanf("xyz", "%*2c%c", &ch);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT((unsigned char)ch, 'z');

    {
        char fmt[64];
        int x, y;

        n = snprintf(fmt, sizeof(fmt), "%p %p", (void *)&x, (void *)&y);
        n = sscanf(fmt, "%*p %p", &p);
        EXPECT_EQ_INT(n, 1);
        EXPECT_EQ_PTR(p, (void *)&y);
    }

    n = sscanf("42", "%zu", &z);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_UINT(z, 42u);

    n = sscanf("42 foo 0xff", "%d %3s %x", &d, a, &u);
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_INT(d, 42);
    EXPECT_EQ_STR(a, "foo");
    EXPECT_EQ_UINT(u, 255u);

    n = sscanf("id:123 name:test", "id:%d name:%s", &d, a);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_INT(d, 123);
    EXPECT_EQ_STR(a, "test");

    n = sscanf("skip 1 2", "%*s %d %d", &d1, &d2);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_INT(d1, 1);
    EXPECT_EQ_INT(d2, 2);

    n = sscanf("1 x hello", "%*d %c %s", &ch, a);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_INT((unsigned char)ch, 'x');
    EXPECT_EQ_STR(a, "hello");

    n = sscanf("0x10 010", "%x %lo", &u, &lu);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_UINT(u, 16u);
    EXPECT_EQ_UINT(lu, 8UL);

    n = sscanf("     42 12345", "%d %ld", &d, &ld);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_INT(d, 42);
    EXPECT_EQ_INT(ld, 12345L);

    n = sscanf("  hello   world  ", "%s %s", a, b);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_STR(a, "hello");
    EXPECT_EQ_STR(b, "world");

    n = sscanf("50% done", "50%% %s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "done");

    n = sscanf("100%", "%d%%", &d);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(d, 100);

    n = sscanf("42 abcdef", "%d %3s", &d, a);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_INT(d, 42);
    EXPECT_EQ_STR(a, "abc");

    n = sscanf("1 2 3 4", "%hhd %hd %d %ld", &hhd, &hd, &d, &ld);
    EXPECT_EQ_INT(n, 4);
    EXPECT_EQ_INT(hhd, 1);
    EXPECT_EQ_INT(hd, 2);
    EXPECT_EQ_INT(d, 3);
    EXPECT_EQ_INT(ld, 4L);

    n = sscanf("1 2 3 4", "%hhu %hu %u %lu", &hhu, &hu, &u, &lu);
    EXPECT_EQ_INT(n, 4);
    EXPECT_EQ_UINT(hhu, 1u);
    EXPECT_EQ_UINT(hu, 2u);
    EXPECT_EQ_UINT(u, 3u);
    EXPECT_EQ_UINT(lu, 4UL);

    n = sscanf("12345", "%3d", &d);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(d, 123);

    n = sscanf("hello", "%5s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "hello");

    n = sscanf("hello", "%3c", a);
    a[3] = '\0';
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "hel");
}
