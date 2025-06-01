#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(memcmp) {
    const char str1[] = "Hello World";
    const char str2[] = "Hello World";
    EXPECT_TRUE(memcmp(str1, str2, sizeof(str1)) == 0);

    const char str3[] = "Hello World";
    const char str4[] = "Hello World!";
    EXPECT_TRUE(memcmp(str3, str4, sizeof(str3)) < 0);

    const char str5[] = "Hello World!";
    const char str6[] = "Hello World";
    EXPECT_TRUE(memcmp(str5, str6, sizeof(str6)) > 0);

    const char str7[] = "Hello World";
    const char str8[] = "Hello Xorld";
    EXPECT_TRUE(memcmp(str7, str8, sizeof(str7)) < 0);

    const char str9[] = "Hello World";
    const char str10[] = "Hello WorlD";
    EXPECT_TRUE(memcmp(str9, str10, sizeof(str9)) > 0);

    const char str11[] = "";
    const char str12[] = "";
    EXPECT_TRUE(memcmp(str11, str12, 0) == 0);

    const char str13[] = "Hello\0World";
    const char str14[] = "Hello\0Xorld";
    EXPECT_TRUE(memcmp(str13, str14, sizeof(str13)) < 0);

    const char str15[] = "Hello World";
    const char str16[] = "Hello Xorld";
    EXPECT_TRUE(memcmp(str15, str16, 5) == 0);

    const unsigned char binary1[] = {0x00, 0xFF, 0x42, 0x7F, 0x80};
    const unsigned char binary2[] = {0x00, 0xFF, 0x42, 0x7F, 0x81};
    EXPECT_TRUE(memcmp(binary1, binary2, sizeof(binary1) - 1) == 0);
    EXPECT_TRUE(memcmp(binary1, binary2, sizeof(binary1)) < 0);

    const char str17[] = "Hello";
    const char str18[] = "Hello World";
    EXPECT_TRUE(memcmp(str17, str18, sizeof(str17)) < 0);

    const char str19[] = "Hallo";
    const char str20[] = "Hello World";
    EXPECT_TRUE(memcmp(str19, str20, sizeof(str19)) < 0);

    char str21[] = "Hello World\"";
    char str22[] = "Hello World\"";
    EXPECT_TRUE(memcmp(str21, str22, sizeof(str21)) == 0);

    const char str23[] = "hello world";
    const char str24[] = "HELLO WORLD";
    EXPECT_TRUE(memcmp(str23, str24, sizeof(str23)) > 0);

    const char str25[] = "Hello\n\t\r World";
    const char str26[] = "Hello\n\t\r Xorld";
    EXPECT_TRUE(memcmp(str25, str26, sizeof(str25)) < 0);

    const unsigned char max1[] = {0xFF, 0xFF, 0xFF};
    const unsigned char max2[] = {0xFF, 0xFF, 0xFE};
    EXPECT_TRUE(memcmp(max1, max2, sizeof(max1)) > 0);

    const unsigned char min1[] = {0x00, 0x00, 0x00};
    const unsigned char min2[] = {0x00, 0x00, 0x01};
    EXPECT_TRUE(memcmp(min1, min2, sizeof(min1)) < 0);
}