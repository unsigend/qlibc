#include <stdio.h>
#include <utest.h>

UTEST_CASE(s)
{
    char buf[256];
    int n;
    const char *longstr =
        "01234567890123456789012345678901234567890123456789"
        "01234567890123456789012345678901234567890123456789";

    n = snprintf(buf, sizeof(buf), "%s", "hello");
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "hello");

    n = snprintf(buf, sizeof(buf), "%s", "");
    EXPECT_EQ_INT(n, 0);
    EXPECT_EQ_STR(buf, "");

    n = snprintf(buf, sizeof(buf), "%s", "a");
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "a");

    n = snprintf(buf, sizeof(buf), "x%s y", "ab");
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "xab y");

    n = snprintf(buf, sizeof(buf), "%sxy", "ab");
    EXPECT_EQ_INT(n, 4);
    EXPECT_EQ_STR(buf, "abxy");

    n = snprintf(buf, sizeof(buf), "xy%s", "ab");
    EXPECT_EQ_INT(n, 4);
    EXPECT_EQ_STR(buf, "xyab");

    n = snprintf(buf, sizeof(buf), "%s%s", "a", "b");
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_STR(buf, "ab");

    n = snprintf(buf, sizeof(buf), "%.3s", "hello");
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "hel");

    n = snprintf(buf, sizeof(buf), "%.0s", "hello");
    EXPECT_EQ_INT(n, 0);
    EXPECT_EQ_STR(buf, "");

    n = snprintf(buf, sizeof(buf), "%.10s", "hi");
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_STR(buf, "hi");

    n = snprintf(buf, sizeof(buf), "%.5s", "hello");
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "hello");

    n = snprintf(buf, sizeof(buf), "%.1s", "hello");
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "h");

    n = snprintf(buf, sizeof(buf), "x%.2sy", "abcd");
    EXPECT_EQ_INT(n, 4);
    EXPECT_EQ_STR(buf, "xaby");

    n = snprintf(buf, sizeof(buf), "%s", "hello\nworld");
    EXPECT_EQ_INT(n, 11);
    EXPECT_EQ_STR(buf, "hello\nworld");

    n = snprintf(buf, 1, "%s", "hello");
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "");

    n = snprintf(buf, 3, "%s", "hello");
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "he");

    n = snprintf(buf, 6, "%s", "hello");
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "hello");

    n = snprintf(buf, 0, "%s", "hello");
    EXPECT_EQ_INT(n, 5);

    n = snprintf(buf, sizeof(buf), "%.3s", "ab");
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_STR(buf, "ab");

    n = snprintf(buf, 2, "%.5s", "hello");
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "h");

    n = snprintf(buf, 4, "%.3s", "hello");
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "hel");

    n = snprintf(buf, sizeof(buf), "%s", longstr);
    EXPECT_EQ_INT(n, 100);
    EXPECT_EQ_STR(buf, longstr);

    n = snprintf(buf, sizeof(buf), "%.50s", longstr);
    EXPECT_EQ_INT(n, 50);
    EXPECT_EQ_STR(buf, "01234567890123456789012345678901234567890123456789");

    n = snprintf(buf, 60, "%s", longstr);
    EXPECT_EQ_INT(n, 100);
    EXPECT_EQ_STR(buf,
                  "01234567890123456789012345678901234567890123456789012345678");

    n = snprintf(buf, sizeof(buf), "%8s", "hi");
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "      hi");

    n = snprintf(buf, sizeof(buf), "%-8s", "hi");
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "hi      ");

    n = snprintf(buf, sizeof(buf), "%5s", "hello");
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "hello");

    n = snprintf(buf, sizeof(buf), "%-5s", "ab");
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "ab   ");

    n = snprintf(buf, sizeof(buf), "%5s", "");
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "     ");

    n = snprintf(buf, sizeof(buf), "%-5s", "");
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "     ");

    n = snprintf(buf, sizeof(buf), "%8.3s", "hello");
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "     hel");

    n = snprintf(buf, sizeof(buf), "%-8.3s", "hello");
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "hel     ");

    n = snprintf(buf, sizeof(buf), "%*s", 5, "hi");
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "   hi");

    n = snprintf(buf, sizeof(buf), "%.*s", 3, "hello");
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "hel");

    n = snprintf(buf, sizeof(buf), "%*.*s", 8, 3, "hello");
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "     hel");

    n = snprintf(buf, sizeof(buf), "%-*.*s", 8, 3, "hello");
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "hel     ");

    n = snprintf(buf, sizeof(buf), "%.*s", 0, "hello");
    EXPECT_EQ_INT(n, 0);
    EXPECT_EQ_STR(buf, "");

    n = snprintf(buf, sizeof(buf), "%.*s", 5, "hi");
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_STR(buf, "hi");

    n = snprintf(buf, sizeof(buf), "%*s", -5, "hi");
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "hi   ");

    n = snprintf(buf, sizeof(buf), "%*s", 0, "x");
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "x");

    n = snprintf(buf, sizeof(buf), "%*.*s", -8, 3, "hello");
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "hel     ");

    n = snprintf(buf, sizeof(buf), "%8.0s", "");
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "        ");

    n = snprintf(buf, sizeof(buf), "%-8.0s", "");
    EXPECT_EQ_INT(n, 8);
    EXPECT_EQ_STR(buf, "        ");

    n = snprintf(buf, sizeof(buf), "%.0s", "");
    EXPECT_EQ_INT(n, 0);
    EXPECT_EQ_STR(buf, "");

    n = snprintf(buf, sizeof(buf), "%1s", "ab");
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_STR(buf, "ab");

    n = snprintf(buf, sizeof(buf), "%-1s", "ab");
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_STR(buf, "ab");

    n = snprintf(buf, sizeof(buf), "%10.2s", "abcdef");
    EXPECT_EQ_INT(n, 10);
    EXPECT_EQ_STR(buf, "        ab");

    n = snprintf(buf, sizeof(buf), "%-10.2s", "abcdef");
    EXPECT_EQ_INT(n, 10);
    EXPECT_EQ_STR(buf, "ab        ");

    n = snprintf(buf, sizeof(buf), "%.*s", 1, "x");
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "x");

    n = snprintf(buf, sizeof(buf), "%*.*s", 4, 2, "abcd");
    EXPECT_EQ_INT(n, 4);
    EXPECT_EQ_STR(buf, "  ab");

    n = snprintf(buf, sizeof(buf), "%-*.*s", 4, 2, "abcd");
    EXPECT_EQ_INT(n, 4);
    EXPECT_EQ_STR(buf, "ab  ");

    n = snprintf(buf, sizeof(buf), "%s", "\0");
    EXPECT_EQ_INT(n, 0);
    EXPECT_EQ_STR(buf, "");

    n = snprintf(buf, sizeof(buf), "%.3s", "a\0b");
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "a");

    n = snprintf(buf, sizeof(buf), "%5.s", "xyz");
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "     ");
}
