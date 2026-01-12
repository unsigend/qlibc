#include <utest.h>
#include <ctype.h>
#include <limits.h>

UTEST_TEST_CASE(isspace){
    int i;
    
    EXPECT_TRUE(isspace(' '));
    EXPECT_TRUE(isspace('\t'));
    EXPECT_TRUE(isspace('\n'));
    EXPECT_TRUE(isspace('\r'));
    EXPECT_TRUE(isspace('\v'));
    EXPECT_TRUE(isspace('\f'));
    
    EXPECT_FALSE(isspace('\0'));
    
    for (i = '0'; i <= '9'; i++) {
        EXPECT_FALSE(isspace(i));
    }
    
    for (i = 'A'; i <= 'Z'; i++) {
        EXPECT_FALSE(isspace(i));
    }
    
    for (i = 'a'; i <= 'z'; i++) {
        EXPECT_FALSE(isspace(i));
    }
    
    EXPECT_FALSE(isspace('!'));
    EXPECT_FALSE(isspace('@'));
    EXPECT_FALSE(isspace('#'));
    EXPECT_FALSE(isspace('$'));
    EXPECT_FALSE(isspace('%'));
    EXPECT_FALSE(isspace('^'));
    EXPECT_FALSE(isspace('&'));
    EXPECT_FALSE(isspace('*'));
    EXPECT_FALSE(isspace('('));
    EXPECT_FALSE(isspace(')'));
    EXPECT_FALSE(isspace('-'));
    EXPECT_FALSE(isspace('_'));
    EXPECT_FALSE(isspace('='));
    EXPECT_FALSE(isspace('+'));
    EXPECT_FALSE(isspace('['));
    EXPECT_FALSE(isspace(']'));
    EXPECT_FALSE(isspace('{'));
    EXPECT_FALSE(isspace('}'));
    EXPECT_FALSE(isspace('\\'));
    EXPECT_FALSE(isspace('|'));
    EXPECT_FALSE(isspace(';'));
    EXPECT_FALSE(isspace(':'));
    EXPECT_FALSE(isspace('\''));
    EXPECT_FALSE(isspace('"'));
    EXPECT_FALSE(isspace(','));
    EXPECT_FALSE(isspace('.'));
    EXPECT_FALSE(isspace('<'));
    EXPECT_FALSE(isspace('>'));
    EXPECT_FALSE(isspace('/'));
    EXPECT_FALSE(isspace('?'));
    EXPECT_FALSE(isspace('~'));
    EXPECT_FALSE(isspace('`'));
    
    for (i = 0; i < ' '; i++) {
        if (i != '\t' && i != '\n' && i != '\r' && i != '\v' && i != '\f') {
            EXPECT_FALSE(isspace(i));
        }
    }
    
    for (i = 0x20 + 1; i <= UCHAR_MAX; i++) {
        EXPECT_FALSE(isspace(i));
    }
    
    EXPECT_FALSE(isspace(-1));
}
