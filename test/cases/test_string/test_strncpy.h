#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(strncpy) {
    char dest[100];
    const char *src1 = "Hello, World!";
    EXPECT_TRUE(strncpy(dest, src1, 14) == dest);
    EXPECT_TRUE(strcmp(dest, "Hello, World!") == 0);
    
    const char *src2 = "Hello, World!";
    EXPECT_TRUE(strncpy(dest, src2, 5) == dest);
    EXPECT_TRUE(strncmp(dest, "Hello", 5) == 0);
    EXPECT_TRUE(dest[5] == ',');
    
    const char *src3 = "test";
    EXPECT_TRUE(strncpy(dest, src3, 10) == dest);
    EXPECT_TRUE(strcmp(dest, "test") == 0);
    EXPECT_TRUE(dest[4] == '\0');
    EXPECT_TRUE(dest[5] == '\0');
    EXPECT_TRUE(dest[6] == '\0');
    EXPECT_TRUE(dest[7] == '\0');
    EXPECT_TRUE(dest[8] == '\0');
    EXPECT_TRUE(dest[9] == '\0');
    
    char dest4[5] = "test";
    const char *src4 = "abc";
    EXPECT_TRUE(strncpy(dest4, src4, 2) == dest4);
    EXPECT_TRUE(strncmp(dest4, "ab", 2) == 0);
    EXPECT_TRUE(dest4[2] == 's');
    
    char dest5[10] = "original";
    const char *src5 = "new";
    EXPECT_TRUE(strncpy(dest5, src5, 3) == dest5);
    EXPECT_TRUE(strncmp(dest5, "new", 3) == 0);
    EXPECT_TRUE(dest5[3] == 'g');
    
    char dest6[10] = "longer";
    const char *src6 = "short";
    EXPECT_TRUE(strncpy(dest6, src6, 5) == dest6);
    EXPECT_TRUE(strncmp(dest6, "short", 5) == 0);
    EXPECT_TRUE(dest6[5] == 'r');
    
    char dest7[5] = "test";
    const char *src7 = "a";
    EXPECT_TRUE(strncpy(dest7, src7, 1) == dest7);
    EXPECT_TRUE(strncmp(dest7, "a", 1) == 0);
    EXPECT_TRUE(dest7[1] == 'e');
    
    char dest8[10] = {0};
    const char *src8 = "12345";
    EXPECT_TRUE(strncpy(dest8, src8, 3) == dest8);
    EXPECT_TRUE(strncmp(dest8, "123", 3) == 0);
    EXPECT_TRUE(dest8[3] == '\0');
    
    char dest9[20] = "original content";
    const char *src9 = "new content";
    EXPECT_TRUE(strncpy(dest9, src9, 4) == dest9);
    EXPECT_TRUE(strncmp(dest9, "new ", 4) == 0);
    EXPECT_TRUE(dest9[4] == 'i');
    
    char dest10[5] = "test";
    const char *src10 = "test";
    EXPECT_TRUE(strncpy(dest10, src10, 4) == dest10);
    EXPECT_TRUE(strcmp(dest10, "test") == 0);
    
    char dest11[10] = "123456789";
    const char *src11 = "abc";
    EXPECT_TRUE(strncpy(dest11, src11, 2) == dest11);
    EXPECT_TRUE(strncmp(dest11, "ab", 2) == 0);
    EXPECT_TRUE(dest11[2] == '3');
    
    char dest12[5] = "test";
    const char *src12 = "a\0b";
    EXPECT_TRUE(strncpy(dest12, src12, 3) == dest12);
    EXPECT_TRUE(strncmp(dest12, "a\0b", 3) == 0);
    
    char dest13[10] = "123456789";
    const char *src13 = "!@#$%";
    EXPECT_TRUE(strncpy(dest13, src13, 3) == dest13);
    EXPECT_TRUE(strncmp(dest13, "!@#", 3) == 0);
    EXPECT_TRUE(dest13[3] == '4');
    
    char dest14[5] = "test";
    const char *src14 = "a";
    EXPECT_TRUE(strncpy(dest14, src14, 0) == dest14);
    EXPECT_TRUE(strcmp(dest14, "test") == 0);
    
    char dest15[10] = "123456789";
    const char *src15 = "abcdef";
    EXPECT_TRUE(strncpy(dest15, src15, 10) == dest15);
    EXPECT_TRUE(strcmp(dest15, "abcdef") == 0);
    EXPECT_TRUE(dest15[6] == '\0');
    EXPECT_TRUE(dest15[7] == '\0');
    EXPECT_TRUE(dest15[8] == '\0');
    EXPECT_TRUE(dest15[9] == '\0');
    
    char dest16[5] = {0};
    const char *src16 = "test";
    EXPECT_TRUE(strncpy(dest16, src16, 5) == dest16);
    EXPECT_TRUE(strcmp(dest16, "test") == 0);
    EXPECT_TRUE(dest16[4] == '\0');
    
    char dest17[10] = "original";
    const char *src17 = "new\0old";
    EXPECT_TRUE(strncpy(dest17, src17, 7) == dest17);
    EXPECT_TRUE(strncmp(dest17, "new", 7) == 0);
    EXPECT_EQUAL_UINT8(dest17[7], 'l');
    
    char dest18[5] = "test";
    const char *src18 = "";
    EXPECT_TRUE(strncpy(dest18, src18, 3) == dest18);
    EXPECT_TRUE(dest18[0] == '\0');
    EXPECT_TRUE(dest18[1] == '\0');
    EXPECT_TRUE(dest18[2] == '\0');
    EXPECT_TRUE(dest18[3] == 't');
    
    char dest19[10] = "123456789";
    const char *src19 = "a\0b\0c";
    EXPECT_TRUE(strncpy(dest19, src19, 5) == dest19);
    EXPECT_TRUE(strncmp(dest19, "a\0b\0c", 5) == 0);
    EXPECT_TRUE(dest19[5] == '6');
    
    char dest20[5] = "test";
    const char *src20 = "a";
    EXPECT_TRUE(strncpy(dest20, src20, 1) == dest20);
    EXPECT_TRUE(strncmp(dest20, "a", 1) == 0);
    EXPECT_TRUE(dest20[1] == 'e');
    EXPECT_TRUE(dest20[2] == 's');
    EXPECT_TRUE(dest20[3] == 't');
    EXPECT_TRUE(dest20[4] == '\0');
    
    char dest21[10] = "123456789";
    const char *src21 = "abcdefghijklmnop";
    EXPECT_TRUE(strncpy(dest21, src21, 10) == dest21);
    EXPECT_TRUE(strncmp(dest21, "abcdefghij", 10) == 0);
    
    char dest22[5] = "test";
    const char *src22 = "abcde";
    EXPECT_TRUE(strncpy(dest22, src22, 5) == dest22);
    EXPECT_TRUE(strncmp(dest22, "abcd", 4) == 0);
    EXPECT_TRUE(dest22[4] == 'e');
    
    char dest23[10] = {0};
    const char *src23 = "12345";
    EXPECT_TRUE(strncpy(dest23, src23, 3) == dest23);
    EXPECT_TRUE(strncmp(dest23, "123", 3) == 0);
    EXPECT_TRUE(dest23[3] == '\0');
    EXPECT_TRUE(dest23[4] == '\0');
    EXPECT_TRUE(dest23[5] == '\0');
    EXPECT_TRUE(dest23[6] == '\0');
    EXPECT_TRUE(dest23[7] == '\0');
    EXPECT_TRUE(dest23[8] == '\0');
    EXPECT_TRUE(dest23[9] == '\0');

    char buffer[24];
    memset(buffer, 0x55, 24);
    const char *src24 = "12345678";
    EXPECT_TRUE(strncpy(buffer, src24, 10) == buffer);
    EXPECT_TRUE(strcmp(buffer, "12345678") == 0);
    EXPECT_TRUE(buffer[8] == '\0');
    EXPECT_TRUE(buffer[9] == '\0');
    for (size_t i = 10; i < 24; ++i){
        EXPECT_TRUE(buffer[i] == 0x55);
    }
}
