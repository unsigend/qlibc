#include <utest.h>
#include <ctype.h>
#include <limits.h>

UTEST_TEST_CASE(isxdigit){
    int i;
    
    for (i = '0'; i <= '9'; i++) {
        EXPECT_TRUE(isxdigit(i));
    }
    
    for (i = 'A'; i <= 'F'; i++) {
        EXPECT_TRUE(isxdigit(i));
    }
    
    for (i = 'a'; i <= 'f'; i++) {
        EXPECT_TRUE(isxdigit(i));
    }
    
    for (i = 'G'; i <= 'Z'; i++) {
        EXPECT_FALSE(isxdigit(i));
    }
    
    for (i = 'g'; i <= 'z'; i++) {
        EXPECT_FALSE(isxdigit(i));
    }
    
    EXPECT_FALSE(isxdigit(' '));
    EXPECT_FALSE(isxdigit('\t'));
    EXPECT_FALSE(isxdigit('\n'));
    EXPECT_FALSE(isxdigit('\r'));
    EXPECT_FALSE(isxdigit('\0'));
    
    EXPECT_FALSE(isxdigit('!'));
    EXPECT_FALSE(isxdigit('@'));
    EXPECT_FALSE(isxdigit('#'));
    EXPECT_FALSE(isxdigit('$'));
    EXPECT_FALSE(isxdigit('%'));
    EXPECT_FALSE(isxdigit('^'));
    EXPECT_FALSE(isxdigit('&'));
    EXPECT_FALSE(isxdigit('*'));
    EXPECT_FALSE(isxdigit('('));
    EXPECT_FALSE(isxdigit(')'));
    EXPECT_FALSE(isxdigit('-'));
    EXPECT_FALSE(isxdigit('_'));
    EXPECT_FALSE(isxdigit('='));
    EXPECT_FALSE(isxdigit('+'));
    EXPECT_FALSE(isxdigit('['));
    EXPECT_FALSE(isxdigit(']'));
    EXPECT_FALSE(isxdigit('{'));
    EXPECT_FALSE(isxdigit('}'));
    EXPECT_FALSE(isxdigit('\\'));
    EXPECT_FALSE(isxdigit('|'));
    EXPECT_FALSE(isxdigit(';'));
    EXPECT_FALSE(isxdigit(':'));
    EXPECT_FALSE(isxdigit('\''));
    EXPECT_FALSE(isxdigit('"'));
    EXPECT_FALSE(isxdigit(','));
    EXPECT_FALSE(isxdigit('.'));
    EXPECT_FALSE(isxdigit('<'));
    EXPECT_FALSE(isxdigit('>'));
    EXPECT_FALSE(isxdigit('/'));
    EXPECT_FALSE(isxdigit('?'));
    EXPECT_FALSE(isxdigit('~'));
    EXPECT_FALSE(isxdigit('`'));
    
    for (i = 0; i < '0'; i++) {
        EXPECT_FALSE(isxdigit(i));
    }
    
    for (i = 'f' + 1; i <= UCHAR_MAX; i++) {
        EXPECT_FALSE(isxdigit(i));
    }
    
    EXPECT_FALSE(isxdigit(-1));
}
