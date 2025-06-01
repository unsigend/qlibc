#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(strchr) {
    const char *str1 = "Hello, World!";
    EXPECT_TRUE(strchr(str1, 'o') == str1 + 4);
    EXPECT_TRUE(strchr(str1, 'W') == str1 + 7);
    
    EXPECT_TRUE(strchr(str1, 'z') == NULL);
    
    EXPECT_TRUE(strchr(str1, 'H') == str1);
    
    EXPECT_TRUE(strchr(str1, '!') == str1 + 12);
    
    EXPECT_TRUE(strchr(str1, '\0') == str1 + 13);
    
    const char *empty = "";
    EXPECT_TRUE(strchr(empty, 'a') == NULL);
    EXPECT_TRUE(strchr(empty, '\0') == empty);
    
    const char *special = "Hello\n\t\r";
    EXPECT_TRUE(strchr(special, '\n') == special + 5);
    EXPECT_TRUE(strchr(special, '\t') == special + 6);
    EXPECT_TRUE(strchr(special, '\r') == special + 7);
    
    const char *repeated = "aaa";
    EXPECT_TRUE(strchr(repeated, 'a') == repeated);
    
    const char *mixed = "HeLLo";
    EXPECT_TRUE(strchr(mixed, 'L') == mixed + 2);
    EXPECT_TRUE(strchr(mixed, 'l') == NULL);
}