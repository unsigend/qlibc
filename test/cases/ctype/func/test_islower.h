#include <utest.h>
#include <ctype.h>
#include <limits.h>

UTEST_TEST_CASE(islower){
    int i;
    
    for (i = 'a'; i <= 'z'; i++) {
        EXPECT_TRUE(islower(i));
    }
    
    for (i = 'A'; i <= 'Z'; i++) {
        EXPECT_FALSE(islower(i));
    }
    
    for (i = '0'; i <= '9'; i++) {
        EXPECT_FALSE(islower(i));
    }
    
    EXPECT_FALSE(islower(' '));
    EXPECT_FALSE(islower('\t'));
    EXPECT_FALSE(islower('\n'));
    EXPECT_FALSE(islower('\r'));
    EXPECT_FALSE(islower('\0'));
    
    EXPECT_FALSE(islower('!'));
    EXPECT_FALSE(islower('@'));
    EXPECT_FALSE(islower('#'));
    EXPECT_FALSE(islower('$'));
    EXPECT_FALSE(islower('%'));
    EXPECT_FALSE(islower('^'));
    EXPECT_FALSE(islower('&'));
    EXPECT_FALSE(islower('*'));
    EXPECT_FALSE(islower('('));
    EXPECT_FALSE(islower(')'));
    EXPECT_FALSE(islower('-'));
    EXPECT_FALSE(islower('_'));
    EXPECT_FALSE(islower('='));
    EXPECT_FALSE(islower('+'));
    EXPECT_FALSE(islower('['));
    EXPECT_FALSE(islower(']'));
    EXPECT_FALSE(islower('{'));
    EXPECT_FALSE(islower('}'));
    EXPECT_FALSE(islower('\\'));
    EXPECT_FALSE(islower('|'));
    EXPECT_FALSE(islower(';'));
    EXPECT_FALSE(islower(':'));
    EXPECT_FALSE(islower('\''));
    EXPECT_FALSE(islower('"'));
    EXPECT_FALSE(islower(','));
    EXPECT_FALSE(islower('.'));
    EXPECT_FALSE(islower('<'));
    EXPECT_FALSE(islower('>'));
    EXPECT_FALSE(islower('/'));
    EXPECT_FALSE(islower('?'));
    EXPECT_FALSE(islower('~'));
    EXPECT_FALSE(islower('`'));
    
    for (i = 0; i < 'a'; i++) {
        EXPECT_FALSE(islower(i));
    }
    
    for (i = 'z' + 1; i <= UCHAR_MAX; i++) {
        EXPECT_FALSE(islower(i));
    }
    
    EXPECT_FALSE(islower(-1));
}
