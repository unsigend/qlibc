#include <stdio.h>
#include <utest.h>

UTEST_CASE(in)
{
    int n;

    n = sscanf("", "");
    EXPECT_EQ_INT(n, 0);

    n = sscanf("x", "x");
    EXPECT_EQ_INT(n, 0);

    n = sscanf("xy", "xy");
    EXPECT_EQ_INT(n, 0);

    n = sscanf("hello", "hello");
    EXPECT_EQ_INT(n, 0);

    n = sscanf("a b", "a b");
    EXPECT_EQ_INT(n, 0);

    n = sscanf("x", "y");
    EXPECT_EQ_INT(n, 0);

    n = sscanf("", "x");
    EXPECT_EQ_INT(n, -1);

    n = sscanf("x", "");
    EXPECT_EQ_INT(n, 0);

    n = sscanf("x y", "x y");
    EXPECT_EQ_INT(n, 0);

    n = sscanf("%", "%%");
    EXPECT_EQ_INT(n, 0);

    n = sscanf("%%", "%%%%");
    EXPECT_EQ_INT(n, 0);

    n = sscanf("50%", "50%%");
    EXPECT_EQ_INT(n, 0);

    n = sscanf("x%y", "x%%y");
    EXPECT_EQ_INT(n, 0);

    n = sscanf("", "%%");
    EXPECT_EQ_INT(n, -1);

    n = sscanf("x", "%%");
    EXPECT_EQ_INT(n, 0);
}
