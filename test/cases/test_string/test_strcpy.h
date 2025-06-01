#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(strcpy) {
    char dest[100];
    const char *src1 = "Hello, World!";
    EXPECT_TRUE(strcpy(dest, src1) == dest);
    EXPECT_TRUE(strcmp(dest, "Hello, World!") == 0);
    
    const char *src2 = "";
    EXPECT_TRUE(strcpy(dest, src2) == dest);
    EXPECT_TRUE(strcmp(dest, "") == 0);
    
    const char *src3 = "test\0hidden";
    EXPECT_TRUE(strcpy(dest, src3) == dest);
    EXPECT_TRUE(strcmp(dest, "test") == 0);
    EXPECT_TRUE(dest[4] == '\0');
    EXPECT_TRUE(dest[5] == ',');
    EXPECT_TRUE(strlen(dest) == 4);
    
    char dest4[5];
    const char *src4 = "test";
    EXPECT_TRUE(strcpy(dest4, src4) == dest4);
    EXPECT_TRUE(strcmp(dest4, "test") == 0);
    
    char dest5[10] = "original";
    const char *src5 = "new";
    EXPECT_TRUE(strcpy(dest5, src5) == dest5);
    EXPECT_TRUE(strcmp(dest5, "new") == 0);
    EXPECT_TRUE(dest5[3] == '\0');
    
    char dest6[10] = "longer";
    const char *src6 = "short";
    EXPECT_TRUE(strcpy(dest6, src6) == dest6);
    EXPECT_TRUE(strcmp(dest6, "short") == 0);
    EXPECT_TRUE(dest6[5] == '\0');
    
    char dest7[5] = "test";
    const char *src7 = "a";
    EXPECT_TRUE(strcpy(dest7, src7) == dest7);
    EXPECT_TRUE(strcmp(dest7, "a") == 0);
    EXPECT_TRUE(dest7[1] == '\0');
    
    char dest8[10] = {0};
    const char *src8 = "12345";
    EXPECT_TRUE(strcpy(dest8, src8) == dest8);
    EXPECT_TRUE(strcmp(dest8, "12345") == 0);
    EXPECT_TRUE(dest8[5] == '\0');
    
    char dest9[20] = "original content";
    const char *src9 = "new content";
    EXPECT_TRUE(strcpy(dest9, src9) == dest9);
    EXPECT_TRUE(strcmp(dest9, "new content") == 0);
    EXPECT_TRUE(dest9[11] == '\0');
    
    char dest10[5] = "test";
    const char *src10 = "test";
    EXPECT_TRUE(strcpy(dest10, src10) == dest10);
    EXPECT_TRUE(strcmp(dest10, "test") == 0);
    EXPECT_TRUE(dest10[4] == '\0');
    
    char dest11[10] = "123456789";
    const char *src11 = "abc";
    EXPECT_TRUE(strcpy(dest11, src11) == dest11);
    EXPECT_TRUE(strcmp(dest11, "abc") == 0);
    EXPECT_TRUE(dest11[3] == '\0');
    
    char dest12[5] = "test";
    const char *src12 = "a\0b";
    EXPECT_TRUE(strcpy(dest12, src12) == dest12);
    EXPECT_TRUE(strcmp(dest12, "a") == 0);
    EXPECT_TRUE(dest12[1] == '\0');
    
    char dest13[10] = "123456789";
    const char *src13 = "!@#$%";
    EXPECT_TRUE(strcpy(dest13, src13) == dest13);
    EXPECT_TRUE(strcmp(dest13, "!@#$%") == 0);
    EXPECT_TRUE(dest13[5] == '\0');
    
    char dest14[5] = "test";
    const char *src14 = "a";
    char *result14 = strcpy(dest14, src14);
    EXPECT_TRUE(result14 == dest14);
    EXPECT_TRUE(strcmp(result14, "a") == 0);
    EXPECT_TRUE(result14[1] == '\0');
    
    char dest15[10] = "123456789";
    const char *src15 = "abcdef";
    char *result15 = strcpy(dest15, src15);
    EXPECT_TRUE(result15 == dest15);
    EXPECT_TRUE(strcmp(result15, "abcdef") == 0);
    EXPECT_TRUE(result15[6] == '\0');
    
    char dest16[5] = {0};
    const char *src16 = "test";
    char *result16 = strcpy(dest16, src16);
    EXPECT_TRUE(result16 == dest16);
    EXPECT_TRUE(strcmp(result16, "test") == 0);
    EXPECT_TRUE(result16[4] == '\0');
    
    char dest17[10] = "original";
    const char *src17 = "new\0old";
    char *result17 = strcpy(dest17, src17);
    EXPECT_TRUE(result17 == dest17);
    EXPECT_TRUE(strcmp(result17, "new") == 0);
    EXPECT_TRUE(result17[3] == '\0');
    
    char dest18[5] = "test";
    const char *src18 = "";
    char *result18 = strcpy(dest18, src18);
    EXPECT_TRUE(result18 == dest18);
    EXPECT_TRUE(strcmp(result18, "") == 0);
    EXPECT_TRUE(result18[0] == '\0');
    
    char dest19[10] = "123456789";
    const char *src19 = "a\0b\0c";
    char *result19 = strcpy(dest19, src19);
    EXPECT_TRUE(result19 == dest19);
    EXPECT_TRUE(strcmp(result19, "a") == 0);
    EXPECT_TRUE(result19[1] == '\0');
    
    char dest20[5] = "test";
    const char *src20 = "a";
    char *result20 = strcpy(dest20, src20);
    EXPECT_TRUE(result20 == dest20);
    EXPECT_TRUE(strcmp(result20, "a") == 0);
    EXPECT_TRUE(result20[1] == '\0');
    EXPECT_TRUE(result20[2] == 's');
}
