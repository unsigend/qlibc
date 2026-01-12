#include <utest.h>
#include <ctype.h>
#include <limits.h>

UTEST_TEST_CASE(isdigit){
    int i;
    
    for (i = '0'; i <= '9'; i++) {
        EXPECT_TRUE(isdigit(i));
    }
    
    for (i = 'A'; i <= 'Z'; i++) {
        EXPECT_FALSE(isdigit(i));
    }
    
    for (i = 'a'; i <= 'z'; i++) {
        EXPECT_FALSE(isdigit(i));
    }
    
    EXPECT_FALSE(isdigit(' '));
    EXPECT_FALSE(isdigit('\t'));
    EXPECT_FALSE(isdigit('\n'));
    EXPECT_FALSE(isdigit('\r'));
    EXPECT_FALSE(isdigit('\0'));
    
    EXPECT_FALSE(isdigit('!'));
    EXPECT_FALSE(isdigit('@'));
    EXPECT_FALSE(isdigit('#'));
    EXPECT_FALSE(isdigit('$'));
    EXPECT_FALSE(isdigit('%'));
    EXPECT_FALSE(isdigit('^'));
    EXPECT_FALSE(isdigit('&'));
    EXPECT_FALSE(isdigit('*'));
    EXPECT_FALSE(isdigit('('));
    EXPECT_FALSE(isdigit(')'));
    EXPECT_FALSE(isdigit('-'));
    EXPECT_FALSE(isdigit('_'));
    EXPECT_FALSE(isdigit('='));
    EXPECT_FALSE(isdigit('+'));
    EXPECT_FALSE(isdigit('['));
    EXPECT_FALSE(isdigit(']'));
    EXPECT_FALSE(isdigit('{'));
    EXPECT_FALSE(isdigit('}'));
    EXPECT_FALSE(isdigit('\\'));
    EXPECT_FALSE(isdigit('|'));
    EXPECT_FALSE(isdigit(';'));
    EXPECT_FALSE(isdigit(':'));
    EXPECT_FALSE(isdigit('\''));
    EXPECT_FALSE(isdigit('"'));
    EXPECT_FALSE(isdigit(','));
    EXPECT_FALSE(isdigit('.'));
    EXPECT_FALSE(isdigit('<'));
    EXPECT_FALSE(isdigit('>'));
    EXPECT_FALSE(isdigit('/'));
    EXPECT_FALSE(isdigit('?'));
    EXPECT_FALSE(isdigit('~'));
    EXPECT_FALSE(isdigit('`'));
    
    for (i = 0; i < '0'; i++) {
        EXPECT_FALSE(isdigit(i));
    }
    
    for (i = '9' + 1; i <= UCHAR_MAX; i++) {
        EXPECT_FALSE(isdigit(i));
    }
    
    EXPECT_FALSE(isdigit(-1));
}
