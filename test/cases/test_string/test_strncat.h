#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(strncat) {
    char dest[100] = "Hello, ";
    const char *src1 = "World!";
    EXPECT_TRUE(strncat(dest, src1, 6) == dest);
    EXPECT_TRUE(strcmp(dest, "Hello, World!") == 0);
    
    char dest2[100] = "Hello, ";
    const char *src2 = "World!";
    EXPECT_TRUE(strncat(dest2, src2, 3) == dest2);
    EXPECT_TRUE(strcmp(dest2, "Hello, Wor") == 0);
    
    char dest3[100] = "";
    const char *src3 = "Hello";
    EXPECT_TRUE(strncat(dest3, src3, 5) == dest3);
    EXPECT_TRUE(strcmp(dest3, "Hello") == 0);
    
    char dest4[100] = "Hello";
    const char *src4 = "";
    EXPECT_TRUE(strncat(dest4, src4, 0) == dest4);
    EXPECT_TRUE(strcmp(dest4, "Hello") == 0);
    
    char dest5[10] = "test";
    const char *src5 = "123";
    EXPECT_TRUE(strncat(dest5, src5, 2) == dest5);
    EXPECT_TRUE(strcmp(dest5, "test12") == 0);
    
    char dest6[20] = "Hello";
    const char *src6 = " World!";
    EXPECT_TRUE(strncat(dest6, src6, 7) == dest6);
    EXPECT_TRUE(strcmp(dest6, "Hello World!") == 0);
    
    char dest7[10] = "abc";
    const char *src7 = "def";
    EXPECT_TRUE(strncat(dest7, src7, 1) == dest7);
    EXPECT_TRUE(strcmp(dest7, "abcd") == 0);
    
    char dest8[5] = "a";
    const char *src8 = "b";
    EXPECT_TRUE(strncat(dest8, src8, 1) == dest8);
    EXPECT_TRUE(strcmp(dest8, "ab") == 0);
    
    char dest9[10] = {0};
    const char *src9 = "test";
    EXPECT_TRUE(strncat(dest9, src9, 4) == dest9);
    EXPECT_TRUE(strcmp(dest9, "test") == 0);
    
    char dest10[20] = "original";
    const char *src10 = " content";
    EXPECT_TRUE(strncat(dest10, src10, 4) == dest10);
    EXPECT_TRUE(strcmp(dest10, "original con") == 0);
    
    char dest11[10] = "test";
    const char *src11 = "test";
    EXPECT_TRUE(strncat(dest11, src11, 2) == dest11);
    EXPECT_TRUE(strcmp(dest11, "testte") == 0);
    
    char dest12[10] = "123";
    const char *src12 = "456";
    EXPECT_TRUE(strncat(dest12, src12, 1) == dest12);
    EXPECT_TRUE(strcmp(dest12, "1234") == 0);
    
    char dest13[10] = "a\0b";
    const char *src13 = "c";
    EXPECT_TRUE(strncat(dest13, src13, 1) == dest13);
    EXPECT_TRUE(strcmp(dest13, "ac") == 0);
    
    char dest14[10] = "!@#";
    const char *src14 = "$%^";
    EXPECT_TRUE(strncat(dest14, src14, 2) == dest14);
    EXPECT_TRUE(strcmp(dest14, "!@#$%") == 0);
    
    char dest15[5] = "a";
    const char *src15 = "b";
    char *result15 = strncat(dest15, src15, 1);
    EXPECT_TRUE(result15 == dest15);
    EXPECT_TRUE(strcmp(result15, "ab") == 0);
    
    char dest16[10] = "123";
    const char *src16 = "456";
    char *result16 = strncat(dest16, src16, 2);
    EXPECT_TRUE(result16 == dest16);
    EXPECT_TRUE(strcmp(result16, "12345") == 0);
    
    char dest17[5] = {0};
    const char *src17 = "test";
    char *result17 = strncat(dest17, src17, 3);
    EXPECT_TRUE(result17 == dest17);
    EXPECT_TRUE(strcmp(result17, "tes") == 0);
    
    char dest18[10] = "new";
    const char *src18 = "\0old";
    char *result18 = strncat(dest18, src18, 4);
    EXPECT_TRUE(result18 == dest18);
    EXPECT_TRUE(strcmp(result18, "new") == 0);
    
    char dest19[5] = "";
    const char *src19 = "test";
    char *result19 = strncat(dest19, src19, 2);
    EXPECT_TRUE(result19 == dest19);
    EXPECT_TRUE(strcmp(result19, "te") == 0);
    
    char dest20[10] = "a";
    const char *src20 = "\0b\0c";
    char *result20 = strncat(dest20, src20, 3);
    EXPECT_TRUE(result20 == dest20);
    EXPECT_TRUE(strcmp(result20, "a") == 0);
    
    char dest21[5] = "a";
    const char *src21 = "b";
    char *result21 = strncat(dest21, src21, 1);
    EXPECT_TRUE(result21 == dest21);
    EXPECT_TRUE(strcmp(result21, "ab") == 0);
    EXPECT_TRUE(result21[2] == '\0');
    
    char dest22[10] = "123";
    const char *src22 = "456789";
    char *result22 = strncat(dest22, src22, 3);
    EXPECT_TRUE(result22 == dest22);
    EXPECT_TRUE(strcmp(result22, "123456") == 0);
    
    char dest23[5] = "a";
    const char *src23 = "bcde";
    char *result23 = strncat(dest23, src23, 2);
    EXPECT_TRUE(result23 == dest23);
    EXPECT_TRUE(strcmp(result23, "abc") == 0);
    
    char dest24[10] = {0};
    const char *src24 = "12345";
    char *result24 = strncat(dest24, src24, 3);
    EXPECT_TRUE(result24 == dest24);
    EXPECT_TRUE(strcmp(result24, "123") == 0);
    
    char dest25[20];
    memset(dest25, 0x55, 20);
    dest25[0] = '\0';
    const char *src25 = "Hello, World!";
    char *result25 = strncat(dest25, src25, 5);
    EXPECT_TRUE(result25 == dest25);
    EXPECT_TRUE(strcmp(result25, "Hello") == 0);
    EXPECT_TRUE(result25[5] == '\0');
    for (size_t i = 6; i < 20; ++i) {
        EXPECT_TRUE(result25[i] == 0x55);
    }
    
    char dest26[64] = "abc";
    const char *src26 = "defghijklmnop";
    char *result26 = strncat(dest26, src26, 4);
    EXPECT_TRUE(result26 == dest26);
    EXPECT_TRUE(strcmp(result26, "abcdefg") == 0);
    EXPECT_TRUE(result26[7] == '\0');
    EXPECT_TRUE(result26[8] == '\0');
    
    char dest27[10] = "test";
    const char *src27 = "123456789";
    char *result27 = strncat(dest27, src27, 5);
    EXPECT_TRUE(result27 == dest27);
    EXPECT_TRUE(strcmp(result27, "test12345") == 0);
    EXPECT_TRUE(result27[9] == '\0');
    
    char dest28[5] = "a";
    const char *src28 = "bcdef";
    char *result28 = strncat(dest28, src28, 10);
    EXPECT_TRUE(result28 == dest28);
    EXPECT_TRUE(strcmp(result28, "abcdef") == 0);
    EXPECT_TRUE(result28[5] == 'f');
    EXPECT_TRUE(result28[6] == '\0');
}
