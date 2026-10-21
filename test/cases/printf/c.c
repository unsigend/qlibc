#include <stdio.h>
#include <utest.h>

UTEST_CASE(c)
{
    char buf[256];
    int n;

    n = snprintf(buf, sizeof(buf), "%c", 'a');
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "a");

    n = snprintf(buf, sizeof(buf), "%c", 'A');
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "A");

    n = snprintf(buf, sizeof(buf), "%c", '0');
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "0");

    n = snprintf(buf, sizeof(buf), "%c", ' ');
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, " ");

    n = snprintf(buf, sizeof(buf), "%c", '\n');
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "\n");

    n = snprintf(buf, sizeof(buf), "%c", '\t');
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "\t");

    n = snprintf(buf, sizeof(buf), "%c", 65);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "A");

    n = snprintf(buf, sizeof(buf), "%c", 0);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT(buf[0], 0);
    EXPECT_EQ_INT(buf[1], 0);

    n = snprintf(buf, sizeof(buf), "%c%c%c", 'a', 'b', 'c');
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "abc");

    n = snprintf(buf, sizeof(buf), "x%cy", 'a');
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "xay");

    n = snprintf(buf, sizeof(buf), "%cxy", 'a');
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "axy");

    n = snprintf(buf, sizeof(buf), "%c%c", 'a', '\n');
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_STR(buf, "a\n");

    n = snprintf(buf, sizeof(buf), "%c", (unsigned char)127);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "\x7f");

    n = snprintf(buf, 1, "%c", 'a');
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "");

    n = snprintf(buf, 2, "%c", 'a');
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "a");

    n = snprintf(buf, 0, "%c", 'a');
    EXPECT_EQ_INT(n, 1);

    n = snprintf(buf, sizeof(buf), "%5c", 'a');
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "    a");

    n = snprintf(buf, sizeof(buf), "%-5c", 'a');
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "a    ");

    n = snprintf(buf, sizeof(buf), "%3c", 'x');
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "  x");

    n = snprintf(buf, sizeof(buf), "%-3c", 'x');
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "x  ");

    n = snprintf(buf, sizeof(buf), "%*c", 5, 'a');
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "    a");

    n = snprintf(buf, sizeof(buf), "%*c", 3, 'x');
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "  x");

    n = snprintf(buf, sizeof(buf), "%-*c", 5, 'a');
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "a    ");

    n = snprintf(buf, sizeof(buf), "%*c", 0, 'x');
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "x");

    n = snprintf(buf, sizeof(buf), "%*c", 1, 'x');
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "x");

    n = snprintf(buf, sizeof(buf), "%*c", -3, 'x');
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "x  ");

    n = snprintf(buf, sizeof(buf), "%-*c", 1, 'a');
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "a");

    n = snprintf(buf, sizeof(buf), "%10c", '\0');
    EXPECT_EQ_INT(n, 10);
    EXPECT_EQ_INT(buf[9], 0);

    n = snprintf(buf, sizeof(buf), "%-10c", '\0');
    EXPECT_EQ_INT(n, 10);
    EXPECT_EQ_INT(buf[0], 0);

    n = snprintf(buf, sizeof(buf), "%*c", 10, '\0');
    EXPECT_EQ_INT(n, 10);
    EXPECT_EQ_INT(buf[9], 0);

    n = snprintf(buf, sizeof(buf), "%-*c", 10, '\0');
    EXPECT_EQ_INT(n, 10);
    EXPECT_EQ_INT(buf[0], 0);

    n = snprintf(buf, sizeof(buf), "%c%c%c%c", '1', '2', '3', '4');
    EXPECT_EQ_INT(n, 4);
    EXPECT_EQ_STR(buf, "1234");

    n = snprintf(buf, sizeof(buf), "%2c", '\n');
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_STR(buf, " \n");

    n = snprintf(buf, sizeof(buf), "%-2c", '\n');
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_STR(buf, "\n ");
}
