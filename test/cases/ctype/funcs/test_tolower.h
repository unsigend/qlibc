#include <utest.h>
#include <ctype.h>
#include <limits.h>

UTEST_TEST_CASE(tolower){
    int i;
    
    for (i = 'A'; i <= 'Z'; i++) {
        EXPECT_EQUAL_INT(tolower(i), i - 'A' + 'a');
    }
    
    for (i = 'a'; i <= 'z'; i++) {
        EXPECT_EQUAL_INT(tolower(i), i);
    }
    
    for (i = '0'; i <= '9'; i++) {
        EXPECT_EQUAL_INT(tolower(i), i);
    }
    
    EXPECT_EQUAL_INT(tolower(' '), ' ');
    EXPECT_EQUAL_INT(tolower('\t'), '\t');
    EXPECT_EQUAL_INT(tolower('\n'), '\n');
    EXPECT_EQUAL_INT(tolower('\r'), '\r');
    EXPECT_EQUAL_INT(tolower('\0'), '\0');
    
    EXPECT_EQUAL_INT(tolower('!'), '!');
    EXPECT_EQUAL_INT(tolower('@'), '@');
    EXPECT_EQUAL_INT(tolower('#'), '#');
    EXPECT_EQUAL_INT(tolower('$'), '$');
    EXPECT_EQUAL_INT(tolower('%'), '%');
    EXPECT_EQUAL_INT(tolower('^'), '^');
    EXPECT_EQUAL_INT(tolower('&'), '&');
    EXPECT_EQUAL_INT(tolower('*'), '*');
    EXPECT_EQUAL_INT(tolower('('), '(');
    EXPECT_EQUAL_INT(tolower(')'), ')');
    EXPECT_EQUAL_INT(tolower('-'), '-');
    EXPECT_EQUAL_INT(tolower('_'), '_');
    EXPECT_EQUAL_INT(tolower('='), '=');
    EXPECT_EQUAL_INT(tolower('+'), '+');
    EXPECT_EQUAL_INT(tolower('['), '[');
    EXPECT_EQUAL_INT(tolower(']'), ']');
    EXPECT_EQUAL_INT(tolower('{'), '{');
    EXPECT_EQUAL_INT(tolower('}'), '}');
    EXPECT_EQUAL_INT(tolower('\\'), '\\');
    EXPECT_EQUAL_INT(tolower('|'), '|');
    EXPECT_EQUAL_INT(tolower(';'), ';');
    EXPECT_EQUAL_INT(tolower(':'), ':');
    EXPECT_EQUAL_INT(tolower('\''), '\'');
    EXPECT_EQUAL_INT(tolower('"'), '"');
    EXPECT_EQUAL_INT(tolower(','), ',');
    EXPECT_EQUAL_INT(tolower('.'), '.');
    EXPECT_EQUAL_INT(tolower('<'), '<');
    EXPECT_EQUAL_INT(tolower('>'), '>');
    EXPECT_EQUAL_INT(tolower('/'), '/');
    EXPECT_EQUAL_INT(tolower('?'), '?');
    EXPECT_EQUAL_INT(tolower('~'), '~');
    EXPECT_EQUAL_INT(tolower('`'), '`');
    
    for (i = 0; i < 'A'; i++) {
        EXPECT_EQUAL_INT(tolower(i), i);
    }
    
    for (i = 'z' + 1; i <= UCHAR_MAX; i++) {
        EXPECT_EQUAL_INT(tolower(i), i);
    }
    
    EXPECT_EQUAL_INT(tolower(-1), -1);
}
