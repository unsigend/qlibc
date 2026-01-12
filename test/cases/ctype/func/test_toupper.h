#include <utest.h>
#include <ctype.h>
#include <limits.h>

UTEST_TEST_CASE(toupper){
    int i;
    
    for (i = 'a'; i <= 'z'; i++) {
        EXPECT_EQUAL_INT(toupper(i), i - 'a' + 'A');
    }
    
    for (i = 'A'; i <= 'Z'; i++) {
        EXPECT_EQUAL_INT(toupper(i), i);
    }
    
    for (i = '0'; i <= '9'; i++) {
        EXPECT_EQUAL_INT(toupper(i), i);
    }
    
    EXPECT_EQUAL_INT(toupper(' '), ' ');
    EXPECT_EQUAL_INT(toupper('\t'), '\t');
    EXPECT_EQUAL_INT(toupper('\n'), '\n');
    EXPECT_EQUAL_INT(toupper('\r'), '\r');
    EXPECT_EQUAL_INT(toupper('\0'), '\0');
    
    EXPECT_EQUAL_INT(toupper('!'), '!');
    EXPECT_EQUAL_INT(toupper('@'), '@');
    EXPECT_EQUAL_INT(toupper('#'), '#');
    EXPECT_EQUAL_INT(toupper('$'), '$');
    EXPECT_EQUAL_INT(toupper('%'), '%');
    EXPECT_EQUAL_INT(toupper('^'), '^');
    EXPECT_EQUAL_INT(toupper('&'), '&');
    EXPECT_EQUAL_INT(toupper('*'), '*');
    EXPECT_EQUAL_INT(toupper('('), '(');
    EXPECT_EQUAL_INT(toupper(')'), ')');
    EXPECT_EQUAL_INT(toupper('-'), '-');
    EXPECT_EQUAL_INT(toupper('_'), '_');
    EXPECT_EQUAL_INT(toupper('='), '=');
    EXPECT_EQUAL_INT(toupper('+'), '+');
    EXPECT_EQUAL_INT(toupper('['), '[');
    EXPECT_EQUAL_INT(toupper(']'), ']');
    EXPECT_EQUAL_INT(toupper('{'), '{');
    EXPECT_EQUAL_INT(toupper('}'), '}');
    EXPECT_EQUAL_INT(toupper('\\'), '\\');
    EXPECT_EQUAL_INT(toupper('|'), '|');
    EXPECT_EQUAL_INT(toupper(';'), ';');
    EXPECT_EQUAL_INT(toupper(':'), ':');
    EXPECT_EQUAL_INT(toupper('\''), '\'');
    EXPECT_EQUAL_INT(toupper('"'), '"');
    EXPECT_EQUAL_INT(toupper(','), ',');
    EXPECT_EQUAL_INT(toupper('.'), '.');
    EXPECT_EQUAL_INT(toupper('<'), '<');
    EXPECT_EQUAL_INT(toupper('>'), '>');
    EXPECT_EQUAL_INT(toupper('/'), '/');
    EXPECT_EQUAL_INT(toupper('?'), '?');
    EXPECT_EQUAL_INT(toupper('~'), '~');
    EXPECT_EQUAL_INT(toupper('`'), '`');
    
    for (i = 0; i < 'a'; i++) {
        EXPECT_EQUAL_INT(toupper(i), i);
    }
    
    for (i = 'z' + 1; i <= UCHAR_MAX; i++) {
        EXPECT_EQUAL_INT(toupper(i), i);
    }
    
    EXPECT_EQUAL_INT(toupper(-1), -1);
}
