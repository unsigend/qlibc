#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(strrchr) {
    const char *str1 = "Hello, World!";
    EXPECT_TRUE(strrchr(str1, 'l') == str1 + 10);
    EXPECT_TRUE(strrchr(str1, 'o') == str1 + 8);
    
    EXPECT_TRUE(strrchr(str1, 'H') == str1);
    EXPECT_TRUE(strrchr(str1, '!') == str1 + 12);
    
    EXPECT_TRUE(strrchr(str1, 'z') == NULL);
    
    EXPECT_TRUE(strrchr(str1, '\0') == str1 + 13);
    
    const char *empty = "";
    EXPECT_TRUE(strrchr(empty, 'a') == NULL);
    EXPECT_TRUE(strrchr(empty, '\0') == empty);
    
    const char *special = "Hello\n\t\r\n";
    EXPECT_TRUE(strrchr(special, '\n') == special + 8);
    EXPECT_TRUE(strrchr(special, '\t') == special + 6);
    EXPECT_TRUE(strrchr(special, '\r') == special + 7);
    
    const char *repeated = "aaa";
    EXPECT_TRUE(strrchr(repeated, 'a') == repeated + 2);
    
    const char *mixed = "HeLLo";
    EXPECT_TRUE(strrchr(mixed, 'L') == mixed + 3); 
    EXPECT_TRUE(strrchr(mixed, 'l') == NULL);
    
    const char *all_same = "xxxxx";
    EXPECT_TRUE(strrchr(all_same, 'x') == all_same + 4);
    
    const char *end_char = "test!";
    EXPECT_TRUE(strrchr(end_char, '!') == end_char + 4);
    
    const char *start_char = "!test";
    EXPECT_TRUE(strrchr(start_char, '!') == start_char);
}