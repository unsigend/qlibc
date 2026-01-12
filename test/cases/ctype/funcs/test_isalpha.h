#include <utest.h>
#include <ctype.h>
#include <limits.h>

UTEST_TEST_CASE(isalpha){
    int i;
    
    for (i = 'A'; i <= 'Z'; i++) {
        EXPECT_TRUE(isalpha(i));
    }
    
    for (i = 'a'; i <= 'z'; i++) {
        EXPECT_TRUE(isalpha(i));
    }
    
    for (i = '0'; i <= '9'; i++) {
        EXPECT_FALSE(isalpha(i));
    }
    
    EXPECT_FALSE(isalpha(' '));
    EXPECT_FALSE(isalpha('\t'));
    EXPECT_FALSE(isalpha('\n'));
    EXPECT_FALSE(isalpha('\r'));
    EXPECT_FALSE(isalpha('\0'));
    
    EXPECT_FALSE(isalpha('!'));
    EXPECT_FALSE(isalpha('@'));
    EXPECT_FALSE(isalpha('#'));
    EXPECT_FALSE(isalpha('$'));
    EXPECT_FALSE(isalpha('%'));
    EXPECT_FALSE(isalpha('^'));
    EXPECT_FALSE(isalpha('&'));
    EXPECT_FALSE(isalpha('*'));
    EXPECT_FALSE(isalpha('('));
    EXPECT_FALSE(isalpha(')'));
    EXPECT_FALSE(isalpha('-'));
    EXPECT_FALSE(isalpha('_'));
    EXPECT_FALSE(isalpha('='));
    EXPECT_FALSE(isalpha('+'));
    EXPECT_FALSE(isalpha('['));
    EXPECT_FALSE(isalpha(']'));
    EXPECT_FALSE(isalpha('{'));
    EXPECT_FALSE(isalpha('}'));
    EXPECT_FALSE(isalpha('\\'));
    EXPECT_FALSE(isalpha('|'));
    EXPECT_FALSE(isalpha(';'));
    EXPECT_FALSE(isalpha(':'));
    EXPECT_FALSE(isalpha('\''));
    EXPECT_FALSE(isalpha('"'));
    EXPECT_FALSE(isalpha(','));
    EXPECT_FALSE(isalpha('.'));
    EXPECT_FALSE(isalpha('<'));
    EXPECT_FALSE(isalpha('>'));
    EXPECT_FALSE(isalpha('/'));
    EXPECT_FALSE(isalpha('?'));
    EXPECT_FALSE(isalpha('~'));
    EXPECT_FALSE(isalpha('`'));
    
    for (i = 0; i < 'A'; i++) {
        EXPECT_FALSE(isalpha(i));
    }
    
    for (i = 'Z' + 1; i < 'a'; i++) {
        EXPECT_FALSE(isalpha(i));
    }
    
    for (i = 'z' + 1; i <= UCHAR_MAX; i++) {
        EXPECT_FALSE(isalpha(i));
    }
    
    EXPECT_FALSE(isalpha(-1));
}
