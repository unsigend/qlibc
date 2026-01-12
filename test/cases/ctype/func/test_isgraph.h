#include <utest.h>
#include <ctype.h>
#include <limits.h>

UTEST_TEST_CASE(isgraph){
    int i;
    
    for (i = '0'; i <= '9'; i++) {
        EXPECT_TRUE(isgraph(i));
    }
    
    for (i = 'A'; i <= 'Z'; i++) {
        EXPECT_TRUE(isgraph(i));
    }
    
    for (i = 'a'; i <= 'z'; i++) {
        EXPECT_TRUE(isgraph(i));
    }
    
    EXPECT_FALSE(isgraph(' '));
    
    EXPECT_TRUE(isgraph('!'));
    EXPECT_TRUE(isgraph('@'));
    EXPECT_TRUE(isgraph('#'));
    EXPECT_TRUE(isgraph('$'));
    EXPECT_TRUE(isgraph('%'));
    EXPECT_TRUE(isgraph('^'));
    EXPECT_TRUE(isgraph('&'));
    EXPECT_TRUE(isgraph('*'));
    EXPECT_TRUE(isgraph('('));
    EXPECT_TRUE(isgraph(')'));
    EXPECT_TRUE(isgraph('-'));
    EXPECT_TRUE(isgraph('_'));
    EXPECT_TRUE(isgraph('='));
    EXPECT_TRUE(isgraph('+'));
    EXPECT_TRUE(isgraph('['));
    EXPECT_TRUE(isgraph(']'));
    EXPECT_TRUE(isgraph('{'));
    EXPECT_TRUE(isgraph('}'));
    EXPECT_TRUE(isgraph('\\'));
    EXPECT_TRUE(isgraph('|'));
    EXPECT_TRUE(isgraph(';'));
    EXPECT_TRUE(isgraph(':'));
    EXPECT_TRUE(isgraph('\''));
    EXPECT_TRUE(isgraph('"'));
    EXPECT_TRUE(isgraph(','));
    EXPECT_TRUE(isgraph('.'));
    EXPECT_TRUE(isgraph('<'));
    EXPECT_TRUE(isgraph('>'));
    EXPECT_TRUE(isgraph('/'));
    EXPECT_TRUE(isgraph('?'));
    EXPECT_TRUE(isgraph('~'));
    EXPECT_TRUE(isgraph('`'));
    
    EXPECT_FALSE(isgraph('\t'));
    EXPECT_FALSE(isgraph('\n'));
    EXPECT_FALSE(isgraph('\r'));
    EXPECT_FALSE(isgraph('\v'));
    EXPECT_FALSE(isgraph('\f'));
    EXPECT_FALSE(isgraph('\0'));
    
    for (i = 0; i < ' '; i++) {
        EXPECT_FALSE(isgraph(i));
    }
    
    for (i = 0x7F; i <= UCHAR_MAX; i++) {
        EXPECT_FALSE(isgraph(i));
    }
    
    EXPECT_FALSE(isgraph(-1));
}
