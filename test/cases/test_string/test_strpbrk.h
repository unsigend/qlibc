#include <string.h>
#include <utest.h>
#include <stdio.h>

UTEST_TEST_CASE(strpbrk) {
    const char *str1 = "Hello World";
    const char *accept1 = "oW";
    EXPECT_TRUE(strpbrk(str1, accept1) == str1 + 4);
    
    const char *str2 = "Programming";
    const char *accept2 = "ing";
    EXPECT_TRUE(strpbrk(str2, accept2) == str2 + 3);
    
    const char *str3 = "Hello";
    const char *accept3 = "xyz";
    EXPECT_TRUE(strpbrk(str3, accept3) == NULL);
    
    const char *str4 = "";
    const char *accept4 = "abc";
    EXPECT_TRUE(strpbrk(str4, accept4) == NULL);
    
    const char *str5 = "Hello";
    const char *accept5 = "";
    EXPECT_TRUE(strpbrk(str5, accept5) == NULL);
    
    const char *str6 = "Hello\n\tWorld!";
    const char *accept6 = "\n\t";
    EXPECT_TRUE(strpbrk(str6, accept6) == str6 + 5);

    const char *str7 = "Hello123World";
    const char *accept7 = "123";
    EXPECT_TRUE(strpbrk(str7, accept7) == str7 + 5);

    const char *str8 = "Hello";
    const char *accept8 = "L";
    EXPECT_TRUE(strpbrk(str8, accept8) == NULL);

    const char *str9 = "Hello World";
    const char *accept9 = "l";
    EXPECT_TRUE(strpbrk(str9, accept9) == str9 + 2);

    const char *str10 = "Hello World";
    const char *accept10 = " ";
    EXPECT_TRUE(strpbrk(str10, accept10) == str10 + 5);

    const char *accept11 = "abc";
    EXPECT_TRUE(strpbrk(NULL, accept11) == NULL);

    const char *str12 = "Hello";
    EXPECT_TRUE(strpbrk(str12, NULL) == NULL);

    EXPECT_TRUE(strpbrk(NULL, NULL) == NULL);

    const char *str14 = "This is a very long string that contains multiple occurrences of characters "
                        "that we are looking for in a complex pattern that should test the function's "
                        "ability to handle long input strings properly";
    const char *accept14 = "xyz";
    EXPECT_TRUE(strpbrk(str14, accept14) == NULL);

    const char *str16 = "Hello";
    const char *accept16 = "lll";
    EXPECT_TRUE(strpbrk(str16, accept16) == str16 + 2);
    
    const char *str17 = "abc";
    const char *accept17 = "abc";
    EXPECT_TRUE(strpbrk(str17, accept17) == str17);
    
    const char *str18 = "a";
    const char *accept18 = "abc";
    EXPECT_TRUE(strpbrk(str18, accept18) == str18);

    const char *str19 = "Hello";
    const char *accept19 = "Helo Wrd";
    EXPECT_TRUE(strpbrk(str19, accept19) == str19);

    const char str20[] = "Hello\0World";
    const char *accept20 = "W";
    EXPECT_TRUE(strpbrk(str20, accept20) == NULL);
    
    const char *str21 = "Hello";
    const char accept21[] = "abc\0def";
    EXPECT_TRUE(strpbrk(str21, accept21) == NULL);
    
    const char *str22 = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    const char *accept22 = "XYZ";
    EXPECT_TRUE(strpbrk(str22, accept22) == str22 + 58);
}