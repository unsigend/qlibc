#include <string.h>
#include <utest.h>

UTEST_CASE(strncat)
{
    char one[32];
    char two[16];

    strcpy(one, "ijk");
    EXPECT_EQ_PTR(strncat(one, "lmn", 3), one);
    EXPECT_EQ_STR(one, "ijklmn");
    strcpy(one, "x");
    strncat(one, "yz", 3);
    EXPECT_EQ_STR(one, "xyz");
    EXPECT_EQ_STR(one + 4, "mn");
    strcpy(one, "gh");
    strcpy(two, "ef");
    strncat(one, two, 2);
    EXPECT_EQ_STR(one, "ghef");
    EXPECT_EQ_STR(two, "ef");
    strcpy(one, "");
    strncat(one, "", 1);
    EXPECT_EQ_STR(one, "");
    strcpy(one, "ab");
    strncat(one, "", 1);
    EXPECT_EQ_STR(one, "ab");
    strcpy(one, "");
    strncat(one, "cd", 2);
    EXPECT_EQ_STR(one, "cd");
    strcpy(one, "ab");
    strncat(one, "cdef", 2);
    EXPECT_EQ_STR(one, "abcd");
    strncat(one, "gh", 0);
    EXPECT_EQ_STR(one, "abcd");
    strncat(one, "gh", 2);
    EXPECT_EQ_STR(one, "abcdgh");
}
