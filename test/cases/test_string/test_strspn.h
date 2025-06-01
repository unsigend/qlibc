#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(strspn) {
    const char *str1 = "12345abc";
    EXPECT_TRUE(strspn(str1, "1234567890") == 5);
    EXPECT_TRUE(strspn(str1, "abc") == 0);
    EXPECT_TRUE(strspn(str1, "12345abc") == 8);
    
    const char *empty = "";
    EXPECT_TRUE(strspn(empty, "123") == 0);
    EXPECT_TRUE(strspn(empty, "") == 0);
    
    const char *str2 = "hello";
    EXPECT_TRUE(strspn(str2, "") == 0);
    
    const char *str3 = "   \t\nhello";
    EXPECT_TRUE(strspn(str3, " \t\n") == 5);
    
    const char *str4 = "!@#$%^&*()hello";
    EXPECT_TRUE(strspn(str4, "!@#$%^&*()") == 10);
    
    const char *str5 = "abc123def";
    EXPECT_TRUE(strspn(str5, "abcdef") == 3);
    EXPECT_TRUE(strspn(str5, "abc123") == 6);
    
    const char *str6 = "aaaabbbbcccc";
    EXPECT_TRUE(strspn(str6, "ab") == 8);
    
    const char *str7 = "12345";
    EXPECT_TRUE(strspn(str7, "12345") == 5);
    
    const char *str8 = "hello";
    EXPECT_TRUE(strspn(str8, "12345") == 0);
    
    const char *str9 = "hello\0world";
    EXPECT_TRUE(strspn(str9, "helo\0") == 5);
    
    const char *str10 = "hello\0world";
    EXPECT_TRUE(strspn(str10, "helo") == 5);
    
    const char *str11 = "Hello";
    EXPECT_TRUE(strspn(str11, "helo") == 0);
    EXPECT_TRUE(strspn(str11, "Helo") == 5);

    const char *str12 = "!@#$%^&*()_+{}|:<>?~`-=[]\\;',./";
    EXPECT_EQUAL_UINT(strspn(str12, "!@#$%^&*()_+{}|:<>?~`-=[]\\;',./"), strlen(str12));
    
    const char *str13 = "aaaaaaaa";
    EXPECT_TRUE(strspn(str13, "a") == 8);

    const char *str14 = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char *charset14 = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    EXPECT_EQUAL_UINT(strspn(str14, charset14), strlen(str14));

    const char * str15 = "jsdhiwepkaiwge836401kajsy327amchgdifhaleu328ehdoq8jsydkaidgakw92738103jkaus8qhskd7aka2iahsdio";
    EXPECT_EQUAL_UINT(strspn(str15, charset14), strlen(str15));
}