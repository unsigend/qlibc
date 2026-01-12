#include <utest.h>
#include <ctype.h>
#include <limits.h>

UTEST_TEST_CASE(isupper){
    int i;
    
    for (i = 'A'; i <= 'Z'; i++) {
        EXPECT_TRUE(isupper(i));
    }
    
    for (i = 'a'; i <= 'z'; i++) {
        EXPECT_FALSE(isupper(i));
    }
    
    for (i = '0'; i <= '9'; i++) {
        EXPECT_FALSE(isupper(i));
    }
    
    EXPECT_FALSE(isupper(' '));
    EXPECT_FALSE(isupper('\t'));
    EXPECT_FALSE(isupper('\n'));
    EXPECT_FALSE(isupper('\r'));
    EXPECT_FALSE(isupper('\0'));
    
    EXPECT_FALSE(isupper('!'));
    EXPECT_FALSE(isupper('@'));
    EXPECT_FALSE(isupper('#'));
    EXPECT_FALSE(isupper('$'));
    EXPECT_FALSE(isupper('%'));
    EXPECT_FALSE(isupper('^'));
    EXPECT_FALSE(isupper('&'));
    EXPECT_FALSE(isupper('*'));
    EXPECT_FALSE(isupper('('));
    EXPECT_FALSE(isupper(')'));
    EXPECT_FALSE(isupper('-'));
    EXPECT_FALSE(isupper('_'));
    EXPECT_FALSE(isupper('='));
    EXPECT_FALSE(isupper('+'));
    EXPECT_FALSE(isupper('['));
    EXPECT_FALSE(isupper(']'));
    EXPECT_FALSE(isupper('{'));
    EXPECT_FALSE(isupper('}'));
    EXPECT_FALSE(isupper('\\'));
    EXPECT_FALSE(isupper('|'));
    EXPECT_FALSE(isupper(';'));
    EXPECT_FALSE(isupper(':'));
    EXPECT_FALSE(isupper('\''));
    EXPECT_FALSE(isupper('"'));
    EXPECT_FALSE(isupper(','));
    EXPECT_FALSE(isupper('.'));
    EXPECT_FALSE(isupper('<'));
    EXPECT_FALSE(isupper('>'));
    EXPECT_FALSE(isupper('/'));
    EXPECT_FALSE(isupper('?'));
    EXPECT_FALSE(isupper('~'));
    EXPECT_FALSE(isupper('`'));
    
    for (i = 0; i < 'A'; i++) {
        EXPECT_FALSE(isupper(i));
    }
    
    for (i = 'Z' + 1; i <= UCHAR_MAX; i++) {
        EXPECT_FALSE(isupper(i));
    }
    
    EXPECT_FALSE(isupper(-1));
}
