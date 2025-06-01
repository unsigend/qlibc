#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(memcpy) {
    char dest1[20] = "Hello World";
    const char src1[] = "Test";
    void* result1 = memcpy(dest1, src1, 4);
    EXPECT_TRUE(result1 == dest1);
    EXPECT_TRUE(dest1[0] == 'T');
    EXPECT_TRUE(dest1[3] == 't');
    EXPECT_TRUE(dest1[4] == 'o');
    EXPECT_TRUE(dest1[5] == ' ');

    char dest2[20] = "Hello World";
    const char src2[] = "Test";
    void* result2 = memcpy(dest2, src2, 0);
    EXPECT_TRUE(result2 == dest2);
    EXPECT_TRUE(dest2[0] == 'H');
    EXPECT_TRUE(dest2[5] == ' ');

    unsigned char dest3[10] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    const unsigned char src3[] = {0x00, 0x11, 0x22, 0x33, 0x44};
    void* result3 = memcpy(dest3, src3, 5);
    EXPECT_TRUE(result3 == dest3);
    EXPECT_TRUE(dest3[0] == 0x00);
    EXPECT_TRUE(dest3[4] == 0x44);
    EXPECT_TRUE(dest3[5] == 0xFF);

    char dest4[20] = "Hello World";
    const char src4[] = "Test";
    void* result4 = memcpy(dest4 + 6, src4, 4);
    EXPECT_TRUE(result4 == dest4 + 6);
    EXPECT_TRUE(dest4[5] == ' ');
    EXPECT_TRUE(dest4[6] == 'T');
    EXPECT_TRUE(dest4[9] == 't');
    EXPECT_TRUE(dest4[10] == 'd');

    unsigned char dest5[5] = {0};
    const unsigned char src5[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    void* result5 = memcpy(dest5, src5, sizeof(dest5));
    EXPECT_TRUE(result5 == dest5);
    for (size_t i = 0; i < sizeof(dest5); i++) {
        EXPECT_TRUE(dest5[i] == 0xFF);
    }

    char dest6[10] = "Hello";
    const char src6[] = "World";
    void* result6 = memcpy(dest6, src6, sizeof(src6));
    EXPECT_TRUE(result6 == dest6);
    EXPECT_TRUE(dest6[0] == 'W');
    EXPECT_TRUE(dest6[4] == 'd');
    EXPECT_TRUE(dest6[5] == '\0');

    unsigned char dest7[16] = {0};
    const unsigned char src7[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
    void* result7 = memcpy(dest7 + 1, src7, 14);
    EXPECT_TRUE(result7 == dest7 + 1);
    EXPECT_TRUE(dest7[0] == 0x00);
    EXPECT_TRUE(dest7[1] == 0x00);
    EXPECT_TRUE(dest7[14] == src7[13]);
    EXPECT_TRUE(dest7[15] == 0x00);

    char dest8[20] = "Hello World";
    const char src8[] = "Test\0Extra";
    void* result8 = memcpy(dest8, src8, 5);
    EXPECT_TRUE(result8 == dest8);
    EXPECT_TRUE(dest8[0] == 'T');
    EXPECT_TRUE(dest8[4] == '\0');
    EXPECT_TRUE(dest8[5] == ' ');

    unsigned char dest9[10] = {0xFF};
    const unsigned char src9[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99};
    void* result9 = memcpy(dest9, src9, sizeof(dest9));
    EXPECT_TRUE(result9 == dest9);
    for (size_t i = 0; i < sizeof(dest9); i++) {
        EXPECT_TRUE(dest9[i] == src9[i]);
    }

    char dest10[5] = "Test";
    const char src10[] = "Hello World";
    void* result10 = memcpy(dest10, src10, sizeof(dest10));
    EXPECT_TRUE(result10 == dest10);
    EXPECT_TRUE(dest10[0] == 'H');
    EXPECT_TRUE(dest10[3] == 'l');
    EXPECT_TRUE(dest10[4] == 'o');

    unsigned char dest11[3] = {0xFF, 0xFF, 0xFF};
    const unsigned char src11[] = {0x7F, 0x7F, 0x7F};
    void* result11 = memcpy(dest11, src11, sizeof(dest11));
    EXPECT_TRUE(result11 == dest11);
    for (size_t i = 0; i < sizeof(dest11); i++) {
        EXPECT_TRUE(dest11[i] == 0x7F);
    }

    char dest12[20] = "Hello World";
    const char src12[] = "Test";
    void* result12 = memcpy(dest12 + sizeof(dest12) - 5, src12, 4);
    EXPECT_TRUE(sizeof(dest12) == 20);
    EXPECT_TRUE(result12 == dest12 + sizeof(dest12) - 5);
    EXPECT_EQUAL_UINT8(dest12[sizeof(dest12) - 6], 0x00);
    EXPECT_TRUE(dest12[sizeof(dest12) - 5] == 'T');
    EXPECT_TRUE(dest12[sizeof(dest12) - 4] == 'e');
    EXPECT_TRUE(dest12[sizeof(dest12) - 3] == 's');
    EXPECT_TRUE(dest12[sizeof(dest12) - 2] == 't');
    EXPECT_TRUE(dest12[sizeof(dest12) - 1] == 0x00);

    unsigned char dest13[8] = {0};
    const unsigned char src13[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    void* result13 = memcpy(dest13, src13, sizeof(dest13));
    EXPECT_TRUE(result13 == dest13);
    for (size_t i = 0; i < sizeof(dest13); i++) {
        EXPECT_TRUE(dest13[i] == i + 1);
    }

    char dest14[10] = "Hello";
    const char src14[] = "World";
    void* result14 = memcpy(dest14 + 2, src14, 3);
    EXPECT_TRUE(result14 == dest14 + 2);
    EXPECT_TRUE(dest14[0] == 'H');
    EXPECT_TRUE(dest14[1] == 'e');
    EXPECT_TRUE(dest14[2] == 'W');
    EXPECT_TRUE(dest14[4] == 'r');
    EXPECT_TRUE(dest14[5] == '\0');
}