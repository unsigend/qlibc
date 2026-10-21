#include <string.h>
#include <utest.h>

UTEST_CASE(strcat)
{
    char one[32];
    char two[16];

    strcpy(one, "ijk");
    EXPECT_EQ_PTR(strcat(one, "lmn"), one);
    EXPECT_EQ_STR(one, "ijklmn");
    strcpy(one, "x");
    strcat(one, "yz");
    EXPECT_EQ_STR(one, "xyz");
    EXPECT_EQ_STR(one + 4, "mn");
    strcpy(one, "gh");
    strcpy(two, "ef");
    strcat(one, two);
    EXPECT_EQ_STR(one, "ghef");
    EXPECT_EQ_STR(two, "ef");
    strcpy(one, "");
    strcat(one, "");
    EXPECT_EQ_STR(one, "");
    strcpy(one, "ab");
    strcat(one, "");
    EXPECT_EQ_STR(one, "ab");
    strcpy(one, "");
    strcat(one, "cd");
    EXPECT_EQ_STR(one, "cd");
}
