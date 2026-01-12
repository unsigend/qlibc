#include <utest.h>
#include <ctype.h>
#include <limits.h>

UTEST_TEST_CASE(isprint){
    int i;
    
    EXPECT_TRUE(isprint(' '));
    
    for (i = '0'; i <= '9'; i++) {
        EXPECT_TRUE(isprint(i));
    }
    
    for (i = 'A'; i <= 'Z'; i++) {
        EXPECT_TRUE(isprint(i));
    }
    
    for (i = 'a'; i <= 'z'; i++) {
        EXPECT_TRUE(isprint(i));
    }
    
    EXPECT_TRUE(isprint('!'));
    EXPECT_TRUE(isprint('@'));
    EXPECT_TRUE(isprint('#'));
    EXPECT_TRUE(isprint('$'));
    EXPECT_TRUE(isprint('%'));
    EXPECT_TRUE(isprint('^'));
    EXPECT_TRUE(isprint('&'));
    EXPECT_TRUE(isprint('*'));
    EXPECT_TRUE(isprint('('));
    EXPECT_TRUE(isprint(')'));
    EXPECT_TRUE(isprint('-'));
    EXPECT_TRUE(isprint('_'));
    EXPECT_TRUE(isprint('='));
    EXPECT_TRUE(isprint('+'));
    EXPECT_TRUE(isprint('['));
    EXPECT_TRUE(isprint(']'));
    EXPECT_TRUE(isprint('{'));
    EXPECT_TRUE(isprint('}'));
    EXPECT_TRUE(isprint('\\'));
    EXPECT_TRUE(isprint('|'));
    EXPECT_TRUE(isprint(';'));
    EXPECT_TRUE(isprint(':'));
    EXPECT_TRUE(isprint('\''));
    EXPECT_TRUE(isprint('"'));
    EXPECT_TRUE(isprint(','));
    EXPECT_TRUE(isprint('.'));
    EXPECT_TRUE(isprint('<'));
    EXPECT_TRUE(isprint('>'));
    EXPECT_TRUE(isprint('/'));
    EXPECT_TRUE(isprint('?'));
    EXPECT_TRUE(isprint('~'));
    EXPECT_TRUE(isprint('`'));
    
    EXPECT_FALSE(isprint('\t'));
    EXPECT_FALSE(isprint('\n'));
    EXPECT_FALSE(isprint('\r'));
    EXPECT_FALSE(isprint('\v'));
    EXPECT_FALSE(isprint('\f'));
    EXPECT_FALSE(isprint('\0'));
    
    for (i = 0; i < ' '; i++) {
        EXPECT_FALSE(isprint(i));
    }
    
    for (i = 0x7F; i <= UCHAR_MAX; i++) {
        EXPECT_FALSE(isprint(i));
    }
    
    EXPECT_FALSE(isprint(-1));
}
