#include <stdio.h>
#include <utest.h>

UTEST_CASE(out)
{
    char buf[256];
    int n;

    n = snprintf(buf, sizeof(buf), "");
    EXPECT_EQ_INT(n, 0);
    EXPECT_EQ_STR(buf, "");

    n = snprintf(buf, sizeof(buf), "a");
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "a");

    n = snprintf(buf, sizeof(buf), "hello");
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "hello");

    n = snprintf(buf, sizeof(buf), "hello\nworld");
    EXPECT_EQ_INT(n, 11);
    EXPECT_EQ_STR(buf, "hello\nworld");

    n = snprintf(buf, sizeof(buf), "a\tb");
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "a\tb");

    n = snprintf(buf, sizeof(buf), "a\rb");
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "a\rb");

    n = snprintf(buf, sizeof(buf), "a\\b");
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "a\\b");

    n = snprintf(buf, sizeof(buf), "a\"b");
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "a\"b");

    n = snprintf(buf, sizeof(buf), "a\vb");
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "a\vb");

    n = snprintf(buf, sizeof(buf), "a\bb");
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "a\bb");

    n = snprintf(buf, sizeof(buf), "a\fb");
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "a\fb");

    n = snprintf(buf, sizeof(buf), "a\ab");
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "a\ab");

    n = snprintf(buf, sizeof(buf), "a\?b");
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "a?b");

    n = snprintf(buf, sizeof(buf), "a\'b");
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "a'b");

    n = snprintf(buf, sizeof(buf), "a\x41" "b");
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "aAb");

    n = snprintf(buf, sizeof(buf), "a\101b");
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(buf, "aAb");

    n = snprintf(buf, sizeof(buf), "a\0b");
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "a");

    n = snprintf(buf, 1, "hello");
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "");

    n = snprintf(buf, 2, "hello");
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "h");

    n = snprintf(buf, 6, "hello");
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_STR(buf, "hello");

    n = snprintf(buf, 0, "hello");
    EXPECT_EQ_INT(n, 5);

    n = snprintf(buf, 0, "");
    EXPECT_EQ_INT(n, 0);

    n = snprintf(buf, sizeof(buf), "\n\t\r\v\b\f\a\\\"\?\'");
    EXPECT_EQ_INT(n, 11);
    EXPECT_EQ_STR(buf, "\n\t\r\v\b\f\a\\\"\?\'");

    n = snprintf(buf, sizeof(buf), "0123456789");
    EXPECT_EQ_INT(n, 10);
    EXPECT_EQ_STR(buf, "0123456789");

    n = snprintf(buf, sizeof(buf), " \t\n ");
    EXPECT_EQ_INT(n, 4);
    EXPECT_EQ_STR(buf, " \t\n ");
}
