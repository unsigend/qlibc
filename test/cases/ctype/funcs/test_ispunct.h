#include <utest.h>
#include <ctype.h>
#include <limits.h>

UTEST_TEST_CASE(ispunct){
    int i;
    
    for (i = '0'; i <= '9'; i++) {
        EXPECT_FALSE(ispunct(i));
    }
    
    for (i = 'A'; i <= 'Z'; i++) {
        EXPECT_FALSE(ispunct(i));
    }
    
    for (i = 'a'; i <= 'z'; i++) {
        EXPECT_FALSE(ispunct(i));
    }
    
    EXPECT_FALSE(ispunct(' '));
    EXPECT_FALSE(ispunct('\t'));
    EXPECT_FALSE(ispunct('\n'));
    EXPECT_FALSE(ispunct('\r'));
    EXPECT_FALSE(ispunct('\0'));
    
    EXPECT_TRUE(ispunct('!'));
    EXPECT_TRUE(ispunct('@'));
    EXPECT_TRUE(ispunct('#'));
    EXPECT_TRUE(ispunct('$'));
    EXPECT_TRUE(ispunct('%'));
    EXPECT_TRUE(ispunct('^'));
    EXPECT_TRUE(ispunct('&'));
    EXPECT_TRUE(ispunct('*'));
    EXPECT_TRUE(ispunct('('));
    EXPECT_TRUE(ispunct(')'));
    EXPECT_TRUE(ispunct('-'));
    EXPECT_TRUE(ispunct('_'));
    EXPECT_TRUE(ispunct('='));
    EXPECT_TRUE(ispunct('+'));
    EXPECT_TRUE(ispunct('['));
    EXPECT_TRUE(ispunct(']'));
    EXPECT_TRUE(ispunct('{'));
    EXPECT_TRUE(ispunct('}'));
    EXPECT_TRUE(ispunct('\\'));
    EXPECT_TRUE(ispunct('|'));
    EXPECT_TRUE(ispunct(';'));
    EXPECT_TRUE(ispunct(':'));
    EXPECT_TRUE(ispunct('\''));
    EXPECT_TRUE(ispunct('"'));
    EXPECT_TRUE(ispunct(','));
    EXPECT_TRUE(ispunct('.'));
    EXPECT_TRUE(ispunct('<'));
    EXPECT_TRUE(ispunct('>'));
    EXPECT_TRUE(ispunct('/'));
    EXPECT_TRUE(ispunct('?'));
    EXPECT_TRUE(ispunct('~'));
    EXPECT_TRUE(ispunct('`'));
    
    for (i = 0; i < '!'; i++) {
        EXPECT_FALSE(ispunct(i));
    }
    
    for (i = '~' + 1; i <= UCHAR_MAX; i++) {
        EXPECT_FALSE(ispunct(i));
    }
    
    EXPECT_FALSE(ispunct(-1));
}
