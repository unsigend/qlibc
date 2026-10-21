#include <string.h>
#include <utest.h>

UTEST_CASE(memset)
{
    char one[16];
    int i;

    strcpy(one, "abcdefgh");
    EXPECT_EQ_PTR(memset(one + 1, 'x', 3), one + 1);
    EXPECT_EQ_STR(one, "axxxefgh");
    memset(one + 2, 'y', (0));
    EXPECT_EQ_STR(one, "axxxefgh");
    memset(one + 5, 0, 1);
    EXPECT_EQ_STR(one, "axxxe");
    EXPECT_EQ_STR(one + 6, "gh");
    memset(one + 2, 010045, 1);
    EXPECT_EQ_STR(one, "ax\045xe");
    memset(one, 0x101, sizeof(one));
    for (i = 0; i < (int)sizeof(one); i++)
        EXPECT_EQ_CHAR(one[i], '\01');
}
