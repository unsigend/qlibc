#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(strcat) {
    char dest[100] = "Hello, ";
    const char *src1 = "World!";
    EXPECT_TRUE(strcat(dest, src1) == dest);
    EXPECT_TRUE(strcmp(dest, "Hello, World!") == 0);
    
    char dest2[100] = "";
    const char *src2 = "Hello";
    EXPECT_TRUE(strcat(dest2, src2) == dest2);
    EXPECT_TRUE(strcmp(dest2, "Hello") == 0);
    
    char dest3[100] = "Hello";
    const char *src3 = "";
    EXPECT_TRUE(strcat(dest3, src3) == dest3);
    EXPECT_TRUE(strcmp(dest3, "Hello") == 0);
    
    char dest4[10] = "test";
    const char *src4 = "123";
    EXPECT_TRUE(strcat(dest4, src4) == dest4);
    EXPECT_TRUE(strcmp(dest4, "test123") == 0);
    
    char dest5[20] = "Hello";
    const char *src5 = " World!";
    EXPECT_TRUE(strcat(dest5, src5) == dest5);
    EXPECT_TRUE(strcmp(dest5, "Hello World!") == 0);
    
    char dest6[10] = "abc";
    const char *src6 = "def";
    EXPECT_TRUE(strcat(dest6, src6) == dest6);
    EXPECT_TRUE(strcmp(dest6, "abcdef") == 0);
    
    char dest7[5] = "a";
    const char *src7 = "b";
    EXPECT_TRUE(strcat(dest7, src7) == dest7);
    EXPECT_TRUE(strcmp(dest7, "ab") == 0);
    
    char dest8[10] = {0};
    const char *src8 = "test";
    EXPECT_TRUE(strcat(dest8, src8) == dest8);
    EXPECT_TRUE(strcmp(dest8, "test") == 0);
    
    char dest9[20] = "original";
    const char *src9 = " content";
    EXPECT_TRUE(strcat(dest9, src9) == dest9);
    EXPECT_TRUE(strcmp(dest9, "original content") == 0);
    
    char dest10[10] = "test";
    const char *src10 = "test";
    EXPECT_TRUE(strcat(dest10, src10) == dest10);
    EXPECT_TRUE(strcmp(dest10, "testtest") == 0);
    
    char dest11[10] = "123";
    const char *src11 = "456";
    EXPECT_TRUE(strcat(dest11, src11) == dest11);
    EXPECT_TRUE(strcmp(dest11, "123456") == 0);
    
    char dest12[10] = "a\0b";
    const char *src12 = "c";
    EXPECT_TRUE(strcat(dest12, src12) == dest12);
    EXPECT_TRUE(strcmp(dest12, "ac") == 0);
    
    char dest13[10] = "!@#";
    const char *src13 = "$%^";
    EXPECT_TRUE(strcat(dest13, src13) == dest13);
    EXPECT_TRUE(strcmp(dest13, "!@#$%^") == 0);
    
    char dest14[5] = "a";
    const char *src14 = "b";
    char *result14 = strcat(dest14, src14);
    EXPECT_TRUE(result14 == dest14);
    EXPECT_TRUE(strcmp(result14, "ab") == 0);
    
    char dest15[10] = "123";
    const char *src15 = "456";
    char *result15 = strcat(dest15, src15);
    EXPECT_TRUE(result15 == dest15);
    EXPECT_TRUE(strcmp(result15, "123456") == 0);
    
    char dest16[5] = {0};
    const char *src16 = "test";
    char *result16 = strcat(dest16, src16);
    EXPECT_TRUE(result16 == dest16);
    EXPECT_TRUE(strcmp(result16, "test") == 0);
    
    char dest17[10] = "new";
    const char *src17 = "\0old";
    char *result17 = strcat(dest17, src17);
    EXPECT_TRUE(result17 == dest17);
    EXPECT_TRUE(strcmp(result17, "new") == 0);
    
    char dest18[5] = "";
    const char *src18 = "test";
    char *result18 = strcat(dest18, src18);
    EXPECT_TRUE(result18 == dest18);
    EXPECT_TRUE(strcmp(result18, "test") == 0);
    
    char dest19[10] = "a";
    const char *src19 = "\0b\0c";
    char *result19 = strcat(dest19, src19);
    EXPECT_TRUE(result19 == dest19);
    EXPECT_TRUE(strcmp(result19, "a") == 0);
    
    char dest20[5] = "a";
    const char *src20 = "b";
    char *result20 = strcat(dest20, src20);
    EXPECT_TRUE(result20 == dest20);
    EXPECT_TRUE(strcmp(result20, "ab") == 0);
    EXPECT_TRUE(result20[2] == '\0');
    
    char dest21[10] = "123";
    const char *src21 = "456789";
    char *result21 = strcat(dest21, src21);
    EXPECT_TRUE(result21 == dest21);
    EXPECT_TRUE(strcmp(result21, "123456789") == 0);
    
    char dest22[5] = "a";
    const char *src22 = "bcde";
    char *result22 = strcat(dest22, src22);
    EXPECT_TRUE(result22 == dest22);
    EXPECT_TRUE(strcmp(result22, "abcde") == 0);
    
    char dest23[10] = {0};
    const char *src23 = "12345";
    char *result23 = strcat(dest23, src23);
    EXPECT_TRUE(result23 == dest23);
    EXPECT_TRUE(strcmp(result23, "12345") == 0);
    
    char dest24[20];
    memset(dest24, 0x55, 20);
    dest24[0] = '\0';
    const char *src24 = "Hello, World!";
    char *result24 = strcat(dest24, src24);
    EXPECT_TRUE(result24 == dest24);
    EXPECT_TRUE(strcmp(result24, "Hello, World!") == 0);
    EXPECT_TRUE(result24[13] == '\0');
    for (size_t i = 14; i < 20; ++i) {
        EXPECT_TRUE(result24[i] == 0x55);
    }
    
    char dest25[64] = "abc";
    const char *src25 = "defghijklmnop";
    char *result25 = strcat(dest25, src25);
    EXPECT_TRUE(result25 == dest25);
    EXPECT_TRUE(strcmp(result25, "abcdefghijklmnop") == 0);
    EXPECT_TRUE(result25[10] == 'k');
}
