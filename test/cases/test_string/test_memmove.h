#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(memmove) {
    char dest1[20] = "Hello World";
    const char src1[] = "Test";
    void* result1 = memmove(dest1, src1, 4);
    EXPECT_TRUE(result1 == dest1);
    EXPECT_TRUE(dest1[0] == 'T');
    EXPECT_TRUE(dest1[3] == 't');
    EXPECT_TRUE(dest1[4] == 'o');
    EXPECT_TRUE(dest1[5] == ' ');

    char dest2[20] = "Hello World";
    const char src2[] = "Test";
    void* result2 = memmove(dest2, src2, 0);
    EXPECT_TRUE(result2 == dest2);
    EXPECT_TRUE(dest2[0] == 'H');
    EXPECT_TRUE(dest2[5] == ' ');

    char str3[] = "Hello World";
    void* result3 = memmove(str3 + 6, str3, 5);
    EXPECT_TRUE(result3 == str3 + 6);
    EXPECT_TRUE(str3[0] == 'H');
    EXPECT_TRUE(str3[5] == ' ');
    EXPECT_TRUE(str3[6] == 'H');
    EXPECT_TRUE(str3[10] == 'o');
    EXPECT_TRUE(str3[11] == '\0');

    char str4[] = "Hello World";
    void* result4 = memmove(str4, str4 + 6, 5);
    EXPECT_TRUE(result4 == str4);
    EXPECT_TRUE(str4[0] == 'W');
    EXPECT_TRUE(str4[4] == 'd');
    EXPECT_TRUE(str4[5] == ' ');
    EXPECT_TRUE(str4[6] == 'W');
    EXPECT_TRUE(str4[11] == '\0');

    char str5[] = "Hello World";
    void* result5 = memmove(str5, str5, 11);
    EXPECT_TRUE(result5 == str5);
    EXPECT_TRUE(str5[0] == 'H');
    EXPECT_TRUE(str5[10] == 'd');
    EXPECT_TRUE(str5[11] == '\0');

    unsigned char data6[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};
    void* result6 = memmove(data6 + 2, data6, 4);
    EXPECT_TRUE(result6 == data6 + 2);
    EXPECT_TRUE(data6[0] == 0x00);
    EXPECT_TRUE(data6[1] == 0x11);
    EXPECT_TRUE(data6[2] == 0x00);
    EXPECT_TRUE(data6[3] == 0x11);
    EXPECT_TRUE(data6[4] == 0x22);
    EXPECT_TRUE(data6[5] == 0x33);
    EXPECT_TRUE(data6[6] == 0x66);
    EXPECT_TRUE(data6[7] == 0x77);

    char str7[] = "Hello\0World";
    void* result7 = memmove(str7 + 2, str7, 7);
    EXPECT_TRUE(result7 == str7 + 2);
    EXPECT_TRUE(str7[0] == 'H');
    EXPECT_TRUE(str7[1] == 'e');
    EXPECT_TRUE(str7[2] == 'H');
    EXPECT_TRUE(str7[6] == 'o');
    EXPECT_TRUE(str7[7] == '\0');

    char str8[] = "Hello World";
    void* result8 = memmove(str8 + 8, str8 + 6, 3);
    EXPECT_TRUE(result8 == str8 + 8);
    EXPECT_TRUE(str8[0] == 'H');
    EXPECT_TRUE(str8[6] == 'W');
    EXPECT_TRUE(str8[8] == 'W');
    EXPECT_TRUE(str8[10] == 'r');
    EXPECT_TRUE(str8[11] == '\0');

    char str9[] = "Hello World";
    void* result9 = memmove(str9 + 2, str9 + 1, 8);
    EXPECT_TRUE(result9 == str9 + 2);
    EXPECT_TRUE(str9[0] == 'H');
    EXPECT_TRUE(str9[1] == 'e');
    EXPECT_TRUE(str9[2] == 'e');
    EXPECT_TRUE(str9[9] == 'r');
    EXPECT_TRUE(str9[10] == 'd');
    EXPECT_TRUE(str9[11] == '\0');

    unsigned char data10[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    void* result10 = memmove(data10 + 2, data10, 4);
    EXPECT_TRUE(result10 == data10 + 2);
    EXPECT_TRUE(data10[0] == 0xFF);
    EXPECT_TRUE(data10[1] == 0xFF);
    EXPECT_TRUE(data10[2] == 0xFF);
    EXPECT_TRUE(data10[5] == 0xFF);
    EXPECT_TRUE(data10[6] == 0xFF);
    EXPECT_TRUE(data10[7] == 0xFF);

    unsigned char data11[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    void* result11 = memmove(data11 + 2, data11, 4);
    EXPECT_TRUE(result11 == data11 + 2);
    EXPECT_TRUE(data11[0] == 0x00);
    EXPECT_TRUE(data11[1] == 0x00);
    EXPECT_TRUE(data11[2] == 0x00);
    EXPECT_TRUE(data11[5] == 0x00);
    EXPECT_TRUE(data11[6] == 0x00);
    EXPECT_TRUE(data11[7] == 0x00);

    unsigned char data12[] = {0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55};
    void* result12 = memmove(data12 + 1, data12, 6);
    EXPECT_TRUE(result12 == data12 + 1);
    EXPECT_TRUE(data12[0] == 0xAA);
    EXPECT_TRUE(data12[1] == 0xAA);
    EXPECT_TRUE(data12[2] == 0x55);
    EXPECT_TRUE(data12[3] == 0xAA);
    EXPECT_TRUE(data12[4] == 0x55);
    EXPECT_TRUE(data12[5] == 0xAA);
    EXPECT_TRUE(data12[6] == 0x55);
    EXPECT_TRUE(data12[7] == 0x55);

    char str13[] = "Hello World";
    void* result13 = memmove(str13, str13, sizeof(str13) - 1);
    EXPECT_TRUE(result13 == str13);
    EXPECT_TRUE(str13[0] == 'H');
    EXPECT_TRUE(str13[10] == 'd');
    EXPECT_TRUE(str13[11] == '\0');

    char str14[] = "Hello World";
    void* result14 = memmove(str14 + 1, str14, sizeof(str14) - 2);
    EXPECT_TRUE(result14 == str14 + 1);
    EXPECT_TRUE(str14[0] == 'H');
    EXPECT_TRUE(str14[1] == 'H');
    EXPECT_TRUE(str14[9] == 'r');
    EXPECT_TRUE(str14[10] == 'l');
    EXPECT_TRUE(str14[11] == '\0');
}