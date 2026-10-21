#include <string.h>
#include <utest.h>

UTEST_CASE(strtok)
{
    char one[32];
    char two[16];
    char *tok;

    strcpy(one, "first, second, third");
    tok = strtok(one, ", ");
    EXPECT_EQ_STR(tok, "first");
    EXPECT_EQ_STR(one, "first");
    tok = strtok(NULL, ", ");
    EXPECT_EQ_STR(tok, "second");
    tok = strtok(NULL, ", ");
    EXPECT_EQ_STR(tok, "third");
    EXPECT_NULL(strtok(NULL, ", "));
    strcpy(one, ", first, ");
    tok = strtok(one, ", ");
    EXPECT_EQ_STR(tok, "first");
    EXPECT_NULL(strtok(NULL, ", "));
    strcpy(one, "1a, 1b; 2a, 2b");
    tok = strtok(one, ", ");
    EXPECT_EQ_STR(tok, "1a");
    tok = strtok(NULL, "; ");
    EXPECT_EQ_STR(tok, "1b");
    tok = strtok(NULL, ", ");
    EXPECT_EQ_STR(tok, "2a");
    strcpy(two, "x-y");
    tok = strtok(two, "-");
    EXPECT_EQ_STR(tok, "x");
    tok = strtok(NULL, "-");
    EXPECT_EQ_STR(tok, "y");
    EXPECT_NULL(strtok(NULL, "-"));
    strcpy(one, "a,b, c,, ,d");
    tok = strtok(one, ", ");
    EXPECT_EQ_STR(tok, "a");
    tok = strtok(NULL, ", ");
    EXPECT_EQ_STR(tok, "b");
    tok = strtok(NULL, " ,");
    EXPECT_EQ_STR(tok, "c");
    tok = strtok(NULL, " ,");
    EXPECT_EQ_STR(tok, "d");
    EXPECT_NULL(strtok(NULL, ", "));
    EXPECT_NULL(strtok(NULL, ", "));
    strcpy(one, ", ");
    EXPECT_NULL(strtok(one, ", "));
    strcpy(one, "");
    EXPECT_NULL(strtok(one, ", "));
    strcpy(one, "abc");
    tok = strtok(one, ", ");
    EXPECT_EQ_STR(tok, "abc");
    EXPECT_NULL(strtok(NULL, ", "));
    strcpy(one, "abc");
    tok = strtok(one, "");
    EXPECT_EQ_STR(tok, "abc");
    EXPECT_NULL(strtok(NULL, ""));
    strcpy(one, "abcdefgh");
    strcpy(one, "a,b,c");
    tok = strtok(one, ",");
    EXPECT_EQ_STR(tok, "a");
    tok = strtok(NULL, ",");
    EXPECT_EQ_STR(tok, "b");
    tok = strtok(NULL, ",");
    EXPECT_EQ_STR(tok, "c");
    EXPECT_NULL(strtok(NULL, ","));
    EXPECT_EQ_STR(one + 6, "gh");
    EXPECT_EQ_STR(one, "a");
    EXPECT_EQ_STR(one + 2, "b");
    EXPECT_EQ_STR(one + 4, "c");
}
