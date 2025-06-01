#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(memset) {
    char str1[20] = "Hello World";
    void* result1 = memset(str1, 'X', 5);
    EXPECT_TRUE(result1 == str1);
    EXPECT_TRUE(str1[0] == 'X');
    EXPECT_TRUE(str1[4] == 'X');
    EXPECT_TRUE(str1[5] == ' ');
    EXPECT_TRUE(str1[6] == 'W');

    char str2[20] = "Hello World";
    void* result2 = memset(str2, '\0', sizeof(str2));
    EXPECT_TRUE(result2 == str2);
    EXPECT_TRUE(str2[0] == '\0');
    EXPECT_TRUE(str2[sizeof(str2) - 1] == '\0');

    unsigned char binary[10] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    void* result3 = memset(binary, 0x42, 5);
    EXPECT_TRUE(result3 == binary);
    EXPECT_TRUE(binary[0] == 0x42);
    EXPECT_TRUE(binary[4] == 0x42);
    EXPECT_TRUE(binary[5] == 0xFF);

    char str3[1] = {'A'};
    void* result4 = memset(str3, 'B', 1);
    EXPECT_TRUE(result4 == str3);
    EXPECT_TRUE(str3[0] == 'B');

    char str4[10] = "Hello";
    void* result5 = memset(str4, 'Z', 0);
    EXPECT_TRUE(result5 == str4);
    EXPECT_TRUE(str4[0] == 'H');

    unsigned char max[5] = {0};
    void* result6 = memset(max, 0xFF, sizeof(max));
    EXPECT_TRUE(result6 == max);
    EXPECT_TRUE(max[0] == 0xFF);
    EXPECT_TRUE(max[sizeof(max) - 1] == 0xFF);

    unsigned char min[5] = {0xFF};
    void* result7 = memset(min, 0x00, sizeof(min));
    EXPECT_TRUE(result7 == min);
    EXPECT_TRUE(min[0] == 0x00);
    EXPECT_TRUE(min[sizeof(min) - 1] == 0x00);

    char str5[20] = "Hello World";
    void* result8 = memset(str5 + 6, 'Y', 5);
    EXPECT_TRUE(result8 == str5 + 6);
    EXPECT_TRUE(str5[5] == ' ');
    EXPECT_TRUE(str5[6] == 'Y');
    EXPECT_TRUE(str5[10] == 'Y');
    EXPECT_EQUAL_UINT8(str5[11], '\0');

    unsigned char pattern[10] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99};
    void* result9 = memset(pattern, 0xAA, sizeof(pattern));
    EXPECT_TRUE(result9 == pattern);
    for (size_t i = 0; i < sizeof(pattern); i++) {
        EXPECT_TRUE(pattern[i] == 0xAA);
    }

    char str6[5] = "Test";
    void* result10 = memset(str6, 'A', sizeof(str6));
    EXPECT_TRUE(result10 == str6);
    for (size_t i = 0; i < sizeof(str6); i++) {
        EXPECT_TRUE(str6[i] == 'A');
    }

    unsigned char align[16] = {0};
    void* result11 = memset(align + 1, 0x55, 14);
    EXPECT_TRUE(result11 == align + 1);
    EXPECT_TRUE(align[0] == 0x00);
    EXPECT_TRUE(align[1] == 0x55);
    EXPECT_TRUE(align[14] == 0x55);
    EXPECT_TRUE(align[15] == 0x00);

    char str7[10] = "Hello";
    void* result12 = memset(str7, 'X', sizeof(str7) - 1);
    EXPECT_TRUE(result12 == str7);
    EXPECT_TRUE(str7[sizeof(str7) - 2] == 'X');
    EXPECT_TRUE(str7[sizeof(str7) - 1] == '\0');

    unsigned char edge[3] = {0xFF, 0xFF, 0xFF};
    void* result13 = memset(edge, 0x7F, 2);
    EXPECT_TRUE(result13 == edge);
    EXPECT_TRUE(edge[0] == 0x7F);
    EXPECT_TRUE(edge[1] == 0x7F);
    EXPECT_TRUE(edge[2] == 0xFF);
}