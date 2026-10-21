#include <stdio.h>
#include <utest.h>

UTEST_CASE(p)
{
    char buf[256];
    int var;
    char cvar;
    void *ptr = &var;
    int n;

    n = snprintf(buf, sizeof(buf), "%p", (void *)&var);
    EXPECT_GT_INT(n, 0);
    EXPECT_EQ_CHAR(buf[n], '\0');

    n = snprintf(buf, sizeof(buf), "%p", (void *)&cvar);
    EXPECT_GT_INT(n, 0);
    EXPECT_EQ_CHAR(buf[n], '\0');

    n = snprintf(buf, sizeof(buf), "%p", ptr);
    EXPECT_GT_INT(n, 0);
    EXPECT_EQ_CHAR(buf[n], '\0');

    n = snprintf(buf, sizeof(buf), "x%py", (void *)&var);
    EXPECT_GE_INT(n, 3);
    EXPECT_EQ_CHAR(buf[0], 'x');
    EXPECT_EQ_CHAR(buf[n - 1], 'y');
    EXPECT_EQ_CHAR(buf[n], '\0');

    n = snprintf(buf, sizeof(buf), "%p---", (void *)&var);
    EXPECT_GE_INT(n, 4);
    EXPECT_EQ_CHAR(buf[n - 3], '-');
    EXPECT_EQ_CHAR(buf[n - 2], '-');
    EXPECT_EQ_CHAR(buf[n - 1], '-');

    n = snprintf(buf, sizeof(buf), "addr=%p", (void *)&var);
    EXPECT_GE_INT(n, 5);
    EXPECT_EQ_CHAR(buf[0], 'a');
    EXPECT_EQ_CHAR(buf[4], '=');

    n = snprintf(buf, 0, "%p", (void *)&var);
    EXPECT_GT_INT(n, 0);

    n = snprintf(buf, 1, "%p", (void *)&var);
    EXPECT_GT_INT(n, 0);
    EXPECT_EQ_STR(buf, "");

    n = snprintf(buf, sizeof(buf), "%20p", (void *)&var);
    EXPECT_GE_INT(n, 20);

    n = snprintf(buf, sizeof(buf), "%-20p", (void *)&var);
    EXPECT_GE_INT(n, 20);

    n = snprintf(buf, sizeof(buf), "%*p", 20, (void *)&var);
    EXPECT_GE_INT(n, 20);

    n = snprintf(buf, sizeof(buf), "%-*p", 20, (void *)&var);
    EXPECT_GE_INT(n, 20);

    n = snprintf(buf, sizeof(buf), "%*p", 0, (void *)&var);
    EXPECT_GT_INT(n, 0);

    n = snprintf(buf, sizeof(buf), "%*p", -20, (void *)&var);
    EXPECT_GE_INT(n, 20);

    n = snprintf(buf, sizeof(buf), "%5p", (void *)&var);
    EXPECT_GE_INT(n, 5);

    n = snprintf(buf, sizeof(buf), "%-5p", (void *)&var);
    EXPECT_GE_INT(n, 5);
}
