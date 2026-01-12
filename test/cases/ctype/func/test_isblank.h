#include <utest.h>
#include <ctype.h>
#include <limits.h>

UTEST_TEST_CASE(isblank){
    int i;
    
    EXPECT_TRUE(isblank(' '));
    EXPECT_TRUE(isblank('\t'));
    
    EXPECT_FALSE(isblank('\n'));
    EXPECT_FALSE(isblank('\r'));
    EXPECT_FALSE(isblank('\v'));
    EXPECT_FALSE(isblank('\f'));
    EXPECT_FALSE(isblank('\0'));
    
    for (i = '0'; i <= '9'; i++) {
        EXPECT_FALSE(isblank(i));
    }
    
    for (i = 'A'; i <= 'Z'; i++) {
        EXPECT_FALSE(isblank(i));
    }
    
    for (i = 'a'; i <= 'z'; i++) {
        EXPECT_FALSE(isblank(i));
    }
    
    EXPECT_FALSE(isblank('!'));
    EXPECT_FALSE(isblank('@'));
    EXPECT_FALSE(isblank('#'));
    EXPECT_FALSE(isblank('$'));
    EXPECT_FALSE(isblank('%'));
    EXPECT_FALSE(isblank('^'));
    EXPECT_FALSE(isblank('&'));
    EXPECT_FALSE(isblank('*'));
    EXPECT_FALSE(isblank('('));
    EXPECT_FALSE(isblank(')'));
    EXPECT_FALSE(isblank('-'));
    EXPECT_FALSE(isblank('_'));
    EXPECT_FALSE(isblank('='));
    EXPECT_FALSE(isblank('+'));
    EXPECT_FALSE(isblank('['));
    EXPECT_FALSE(isblank(']'));
    EXPECT_FALSE(isblank('{'));
    EXPECT_FALSE(isblank('}'));
    EXPECT_FALSE(isblank('\\'));
    EXPECT_FALSE(isblank('|'));
    EXPECT_FALSE(isblank(';'));
    EXPECT_FALSE(isblank(':'));
    EXPECT_FALSE(isblank('\''));
    EXPECT_FALSE(isblank('"'));
    EXPECT_FALSE(isblank(','));
    EXPECT_FALSE(isblank('.'));
    EXPECT_FALSE(isblank('<'));
    EXPECT_FALSE(isblank('>'));
    EXPECT_FALSE(isblank('/'));
    EXPECT_FALSE(isblank('?'));
    EXPECT_FALSE(isblank('~'));
    EXPECT_FALSE(isblank('`'));
    
    for (i = 0; i < ' '; i++) {
        if (i != '\t') {
            EXPECT_FALSE(isblank(i));
        }
    }
    
    for (i = ' ' + 1; i < '0'; i++) {
        EXPECT_FALSE(isblank(i));
    }
    
    for (i = 'z' + 1; i <= UCHAR_MAX; i++) {
        EXPECT_FALSE(isblank(i));
    }
    
    EXPECT_FALSE(isblank(-1));
}
