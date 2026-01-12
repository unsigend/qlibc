#include <utest.h>
#include <ctype.h>
#include <limits.h>

UTEST_TEST_CASE(iscntrl){
    int i;
    
    for (i = 0; i <= 0x1F; i++) {
        EXPECT_TRUE(iscntrl(i));
    }
    
    EXPECT_TRUE(iscntrl(0x7F));
    
    for (i = '0'; i <= '9'; i++) {
        EXPECT_FALSE(iscntrl(i));
    }
    
    for (i = 'A'; i <= 'Z'; i++) {
        EXPECT_FALSE(iscntrl(i));
    }
    
    for (i = 'a'; i <= 'z'; i++) {
        EXPECT_FALSE(iscntrl(i));
    }
    
    EXPECT_FALSE(iscntrl(' '));
    EXPECT_FALSE(iscntrl('!'));
    EXPECT_FALSE(iscntrl('@'));
    EXPECT_FALSE(iscntrl('#'));
    EXPECT_FALSE(iscntrl('$'));
    EXPECT_FALSE(iscntrl('%'));
    EXPECT_FALSE(iscntrl('^'));
    EXPECT_FALSE(iscntrl('&'));
    EXPECT_FALSE(iscntrl('*'));
    EXPECT_FALSE(iscntrl('('));
    EXPECT_FALSE(iscntrl(')'));
    EXPECT_FALSE(iscntrl('-'));
    EXPECT_FALSE(iscntrl('_'));
    EXPECT_FALSE(iscntrl('='));
    EXPECT_FALSE(iscntrl('+'));
    EXPECT_FALSE(iscntrl('['));
    EXPECT_FALSE(iscntrl(']'));
    EXPECT_FALSE(iscntrl('{'));
    EXPECT_FALSE(iscntrl('}'));
    EXPECT_FALSE(iscntrl('\\'));
    EXPECT_FALSE(iscntrl('|'));
    EXPECT_FALSE(iscntrl(';'));
    EXPECT_FALSE(iscntrl(':'));
    EXPECT_FALSE(iscntrl('\''));
    EXPECT_FALSE(iscntrl('"'));
    EXPECT_FALSE(iscntrl(','));
    EXPECT_FALSE(iscntrl('.'));
    EXPECT_FALSE(iscntrl('<'));
    EXPECT_FALSE(iscntrl('>'));
    EXPECT_FALSE(iscntrl('/'));
    EXPECT_FALSE(iscntrl('?'));
    EXPECT_FALSE(iscntrl('~'));
    EXPECT_FALSE(iscntrl('`'));
    
    for (i = 0x20; i < 0x7F; i++) {
        EXPECT_FALSE(iscntrl(i));
    }
    
    for (i = 0x80; i <= UCHAR_MAX; i++) {
        EXPECT_FALSE(iscntrl(i));
    }
    
    EXPECT_FALSE(iscntrl(-1));
}
