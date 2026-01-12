#include <utest.h>
#include <ctype.h>
#include <limits.h>

UTEST_TEST_CASE(isalnum){
    int i;
    
    for (i = '0'; i <= '9'; i++) {
        EXPECT_TRUE(isalnum(i));
    }
    
    for (i = 'A'; i <= 'Z'; i++) {
        EXPECT_TRUE(isalnum(i));
    }
    
    for (i = 'a'; i <= 'z'; i++) {
        EXPECT_TRUE(isalnum(i));
    }
    
    EXPECT_FALSE(isalnum(' '));
    EXPECT_FALSE(isalnum('\t'));
    EXPECT_FALSE(isalnum('\n'));
    EXPECT_FALSE(isalnum('\r'));
    EXPECT_FALSE(isalnum('\0'));
    
    EXPECT_FALSE(isalnum('!'));
    EXPECT_FALSE(isalnum('@'));
    EXPECT_FALSE(isalnum('#'));
    EXPECT_FALSE(isalnum('$'));
    EXPECT_FALSE(isalnum('%'));
    EXPECT_FALSE(isalnum('^'));
    EXPECT_FALSE(isalnum('&'));
    EXPECT_FALSE(isalnum('*'));
    EXPECT_FALSE(isalnum('('));
    EXPECT_FALSE(isalnum(')'));
    EXPECT_FALSE(isalnum('-'));
    EXPECT_FALSE(isalnum('_'));
    EXPECT_FALSE(isalnum('='));
    EXPECT_FALSE(isalnum('+'));
    EXPECT_FALSE(isalnum('['));
    EXPECT_FALSE(isalnum(']'));
    EXPECT_FALSE(isalnum('{'));
    EXPECT_FALSE(isalnum('}'));
    EXPECT_FALSE(isalnum('\\'));
    EXPECT_FALSE(isalnum('|'));
    EXPECT_FALSE(isalnum(';'));
    EXPECT_FALSE(isalnum(':'));
    EXPECT_FALSE(isalnum('\''));
    EXPECT_FALSE(isalnum('"'));
    EXPECT_FALSE(isalnum(','));
    EXPECT_FALSE(isalnum('.'));
    EXPECT_FALSE(isalnum('<'));
    EXPECT_FALSE(isalnum('>'));
    EXPECT_FALSE(isalnum('/'));
    EXPECT_FALSE(isalnum('?'));
    EXPECT_FALSE(isalnum('~'));
    EXPECT_FALSE(isalnum('`'));
    
    for (i = 0; i < '0'; i++) {
        EXPECT_FALSE(isalnum(i));
    }
    
    for (i = '9' + 1; i < 'A'; i++) {
        EXPECT_FALSE(isalnum(i));
    }
    
    for (i = 'Z' + 1; i < 'a'; i++) {
        EXPECT_FALSE(isalnum(i));
    }
    
    for (i = 'z' + 1; i <= UCHAR_MAX; i++) {
        EXPECT_FALSE(isalnum(i));
    }
    
    EXPECT_FALSE(isalnum(-1));
}