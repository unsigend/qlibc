#include <stddef.h>
#include <stdio.h>
#include <utest.h>

UTEST_CASE(mix)
{
    char buf[256];
    int n;

    n = snprintf(buf, sizeof(buf), "%-*c", 5, 'x');
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "x    ");

    n = snprintf(buf, sizeof(buf), "%-*.*s", 8, 3, "hello");
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "hel     ");

    n = snprintf(buf, sizeof(buf), "%-*.*ld", 8, 4, 42L);
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "0042    ");

    n = snprintf(buf, sizeof(buf), "%-*.*li", 8, 4, 42L);
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "0042    ");

    n = snprintf(buf, sizeof(buf), "%#-*.*lo", 8, 4, 64UL);
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "0100    ");

    n = snprintf(buf, sizeof(buf), "%#-*.*lx", 8, 4, 0xffUL);
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "0x00ff  ");

    n = snprintf(buf, sizeof(buf), "%#-*.*lX", 8, 4, 0xffUL);
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "0X00FF  ");

    n = snprintf(buf, sizeof(buf), "%-*.*lu", 8, 4, 42UL);
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "0042    ");

    n = snprintf(buf, sizeof(buf), "%-*p", 20, (void *)&n);
    EXPECT_GE_INT(n, 20);

    n = snprintf(buf, sizeof(buf), "%*.*lld", 10, 5, 42LL);
    EXPECT_EQ_INT(n, 10);
    EXPECT_EQ_STR(buf, "     00042");

    n = snprintf(buf, sizeof(buf), "%-*.*lld", 10, 5, 42LL);
    EXPECT_EQ_INT(n, 10);
    EXPECT_EQ_STR(buf, "00042     ");

    n = snprintf(buf, sizeof(buf), "%*.*hd", 8, 4, (short)42);
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "    0042");

    n = snprintf(buf, sizeof(buf), "%*.*zu", 8, 4, (size_t)42);
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "    0042");

    n = snprintf(buf, sizeof(buf), "%#*.*llo", 10, 4, 64ULL);
    EXPECT_EQ_INT(n, 10);
    EXPECT_EQ_STR(buf, "      0100");

    n = snprintf(buf, sizeof(buf), "%#*.*llx", 10, 4, 0xffULL);
    EXPECT_EQ_INT(n, 10);
    EXPECT_EQ_STR(buf, "    0x00ff");

    n = snprintf(buf, sizeof(buf), "%*.*hu", 8, 4, (unsigned short)42);
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "    0042");

    n = snprintf(buf, sizeof(buf), "%08ld", 42L);
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "00000042");

    n = snprintf(buf, sizeof(buf), "%#08o", 8u);
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "00000010");

    n = snprintf(buf, sizeof(buf), "%#08x", 0xffu);
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "0x0000ff");

    n = snprintf(buf, sizeof(buf), "%hhd %hhu %hho %hhx", (signed char)-1,
                 (unsigned char)255, (unsigned char)8, (unsigned char)0xff);
    EXPECT_EQ_STR(buf, "-1 255 10 ff");
}
