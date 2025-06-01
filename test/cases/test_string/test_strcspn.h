#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(strcspn) {
    const char *str1 = "12345abc";
    EXPECT_TRUE(strcspn(str1, "abc") == 5);
    EXPECT_TRUE(strcspn(str1, "12345") == 0);
    EXPECT_EQUAL_UINT(strcspn(str1, "xyz"), 8);
    
    const char *empty = "";
    EXPECT_TRUE(strcspn(empty, "123") == 0);
    EXPECT_TRUE(strcspn(empty, "") == 0);
    
    const char *str2 = "hello";
    EXPECT_TRUE(strcspn(str2, "") == 5);
    
    const char *str3 = "   \t\nhello";
    EXPECT_TRUE(strcspn(str3, "helo") == 5);
    EXPECT_TRUE(strcspn(str3, " \t\n") == 0);
    
    const char *str4 = "!@#$%^&*()hello";
    EXPECT_TRUE(strcspn(str4, "helo") == 10);
    EXPECT_TRUE(strcspn(str4, "!@#$%^&*()") == 0);
    
    const char *str5 = "abc123def";
    EXPECT_TRUE(strcspn(str5, "123") == 3);
    EXPECT_TRUE(strcspn(str5, "def") == 6);
    
    const char *str6 = "aaaabbbbcccc";
    EXPECT_TRUE(strcspn(str6, "b") == 4);
    EXPECT_TRUE(strcspn(str6, "c") == 8);
    
    const char *str7 = "12345";
    EXPECT_TRUE(strcspn(str7, "abc") == 5);
    EXPECT_TRUE(strcspn(str7, "12345") == 0);
    
    const char *str8 = "hello";
    EXPECT_TRUE(strcspn(str8, "12345") == 5);
    EXPECT_TRUE(strcspn(str8, "helo") == 0);
    
    const char *str9 = "hello\0world";
    EXPECT_TRUE(strcspn(str9, "helo") == 0);
    EXPECT_TRUE(strcspn(str9, "w") == 5);
    
    const char *str10 = "hello\0world";
    EXPECT_TRUE(strcspn(str10, "helo") == 0);
    EXPECT_TRUE(strcspn(str10, "w") == 5);
    
    const char *str11 = "Hello";
    EXPECT_TRUE(strcspn(str11, "helo") == 1);
    EXPECT_TRUE(strcspn(str11, "HELO") == 0);
    
    const char *str12 = "!@#$%^&*()_+{}|:<>?~`-=[]\\;',./";
    EXPECT_TRUE(strcspn(str12, "abcdefghijklmnopqrstuvwxyz") == strlen(str12));
    EXPECT_TRUE(strcspn(str12, "!") == 0);
    
    const char *str13 = "aaaaaaaa";
    EXPECT_TRUE(strcspn(str13, "b") == 8);
    EXPECT_TRUE(strcspn(str13, "a") == 0);
    
    const char *str14 = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char *charset14 = "!@#$%^&*()_+{}|:<>?~`-=[]\\;',./";
    EXPECT_EQUAL_UINT(strcspn(str14, charset14), strlen(str14));
    
    const char *str15 = "jsdhiwepkaiwge836401kajsy327amchgdifhaleu328ehdoq8jsydkaidgakw92738103jkaus8qhskd7aka2iahsdio";
    EXPECT_EQUAL_UINT(strcspn(str15, charset14), strlen(str15));
    
    const char *str16 = "test123";
    EXPECT_TRUE(strcspn(str16, "1234567890") == 4);
    EXPECT_TRUE(strcspn(str16, "test") == 0);
    EXPECT_TRUE(strcspn(str16, "xyz") == 7);
    
    const char *str17 = "a\0b\0c";
    EXPECT_TRUE(strcspn(str17, "b") == 1);
    EXPECT_TRUE(strcspn(str17, "c") == 1);
    
    const char *str18 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    EXPECT_TRUE(strcspn(str18, "abcdefghijklmnopqrstuvwxyz") == 26);
    EXPECT_TRUE(strcspn(str18, "ABCDEFGHIJKLMNOPQRSTUVWXYZ") == 0);
    
    const char *str19 = "0123456789";
    EXPECT_TRUE(strcspn(str19, "abcdefghijklmnopqrstuvwxyz") == 10);
    EXPECT_TRUE(strcspn(str19, "0123456789") == 0);
    
    const char *str20 = "!@#$%^&*()";
    EXPECT_TRUE(strcspn(str20, "abcdefghijklmnopqrstuvwxyz0123456789") == 10);
    EXPECT_TRUE(strcspn(str20, "!@#$%^&*()") == 0);
}