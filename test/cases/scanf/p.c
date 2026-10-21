#include <stdio.h>
#include <utest.h>

UTEST_CASE(in_p)
{
    char fmt[64];
    int n;
    int var;
    char cvar;
    int arr[4];
    void *q, *p1, *p2;

    n = snprintf(fmt, sizeof(fmt), "%p", (void *)&var);
    EXPECT_GT_INT(n, 0);
    n = sscanf(fmt, "%p", &q);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_PTR(q, (void *)&var);

    n = snprintf(fmt, sizeof(fmt), "%p", (void *)&cvar);
    EXPECT_GT_INT(n, 0);
    n = sscanf(fmt, "%p", &q);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_PTR(q, (void *)&cvar);

    n = snprintf(fmt, sizeof(fmt), "%p", (void *)&arr[0]);
    n = sscanf(fmt, "%p", &q);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_PTR(q, (void *)&arr[0]);

    n = sscanf("", "%p", &q);
    EXPECT_EQ_INT(n, -1);

    n = sscanf("   ", "%p", &q);
    EXPECT_EQ_INT(n, -1);

    n = sscanf("xyz", "%p", &q);
    EXPECT_EQ_INT(n, 0);

    n = snprintf(fmt, sizeof(fmt), "addr=%p", (void *)&var);
    n = sscanf(fmt, "addr=%p", &q);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_PTR(q, (void *)&var);

    n = snprintf(fmt, sizeof(fmt), "%p %p", (void *)&var, (void *)&cvar);
    n = sscanf(fmt, "%p %p", &p1, &p2);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_PTR(p1, (void *)&var);
    EXPECT_EQ_PTR(p2, (void *)&cvar);

    n = snprintf(fmt, sizeof(fmt), "%pxxx", (void *)&var);
    n = sscanf(fmt, "%p", &q);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_PTR(q, (void *)&var);

    n = snprintf(fmt, sizeof(fmt), "%p %p", (void *)&var, (void *)&cvar);
    n = sscanf(fmt, "%*p %p", &q);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_PTR(q, (void *)&cvar);
}
