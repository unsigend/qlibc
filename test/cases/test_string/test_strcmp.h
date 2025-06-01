#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(strcmp) {
    const char str1[] = "Hello World";
    const char str2[] = "Hello World";
    EXPECT_TRUE(strcmp(str1, str2) == 0);

    const char str3[] = "Hello World";
    const char str4[] = "Hello World!";
    EXPECT_TRUE(strcmp(str3, str4) < 0);

    const char str5[] = "Hello World!";
    const char str6[] = "Hello World";
    EXPECT_TRUE(strcmp(str5, str6) > 0);

    const char str7[] = "Hello World";
    const char str8[] = "Hello Xorld";
    EXPECT_TRUE(strcmp(str7, str8) < 0);

    const char str9[] = "Hello World";
    const char str10[] = "Hello WorlD";
    EXPECT_TRUE(strcmp(str9, str10) > 0);

    const char str11[] = "";
    const char str12[] = "";
    EXPECT_TRUE(strcmp(str11, str12) == 0);

    const char str13[] = "Hello";
    const char str14[] = "Hello World";
    EXPECT_TRUE(strcmp(str13, str14) < 0);

    const char str15[] = "Hello World";
    const char str16[] = "Hello";
    EXPECT_TRUE(strcmp(str15, str16) > 0);

    const char str17[] = "hello world";
    const char str18[] = "HELLO WORLD";
    EXPECT_TRUE(strcmp(str17, str18) > 0);

    const char str19[] = "HELLO WORLD";
    const char str20[] = "hello world";
    EXPECT_TRUE(strcmp(str19, str20) < 0);

    const char str21[] = "Hello\n\t\r World";
    const char str22[] = "Hello\n\t\r Xorld";
    EXPECT_TRUE(strcmp(str21, str22) < 0);

    const char str23[] = "Hello\0World";
    const char str24[] = "Hello\0Xorld";
    EXPECT_TRUE(strcmp(str23, str24) == 0);

    const char str25[] = "Hello";
    const char str26[] = "Hallo";
    EXPECT_TRUE(strcmp(str25, str26) > 0);

    const char str27[] = "Hallo";
    const char str28[] = "Hello";
    EXPECT_TRUE(strcmp(str27, str28) < 0);

    const char str29[] = "Hello World";
    const char str30[] = "Hello World";
    EXPECT_TRUE(strcmp(str29, str30) == 0);

    const char str31[] = "Hello World!";
    const char str32[] = "Hello World";
    EXPECT_TRUE(strcmp(str31, str32) > 0);

    const char str33[] = "Hello World";
    const char str34[] = "Hello World!";
    EXPECT_TRUE(strcmp(str33, str34) < 0);

    const char str35[] = "Hello World";
    const char str36[] = "Hello Xorld";
    EXPECT_TRUE(strcmp(str35, str36) < 0);

    const char str37[] = "Hello Xorld";
    const char str38[] = "Hello World";
    EXPECT_TRUE(strcmp(str37, str38) > 0);

    const char str39[] = "Hello World";
    const char str40[] = "Hello WorlD";
    EXPECT_TRUE(strcmp(str39, str40) > 0);

    const char str41[] = "Hello WorlD";
    const char str42[] = "Hello World";
    EXPECT_TRUE(strcmp(str41, str42) < 0);

    const char str43[] = "Hello World";
    const char str44[] = "Hello World";
    EXPECT_TRUE(strcmp(str43, str44) == 0);

    const char str45[] = "Hello World!";
    const char str46[] = "Hello World";
    EXPECT_TRUE(strcmp(str45, str46) > 0);

    const char str47[] = "Hello World";
    const char str48[] = "Hello World!";
    EXPECT_TRUE(strcmp(str47, str48) < 0);

    const char str49[] = "Hello World";
    const char str50[] = "Hello Xorld";
    EXPECT_TRUE(strcmp(str49, str50) < 0);

    const char str51[] = "Hello Xorld";
    const char str52[] = "Hello World";
    EXPECT_TRUE(strcmp(str51, str52) > 0);

    const char str53[] = "Hello World";
    const char str54[] = "Hello WorlD";
    EXPECT_TRUE(strcmp(str53, str54) > 0);

    const char str55[] = "Hello WorlD";
    const char str56[] = "Hello World";
    EXPECT_TRUE(strcmp(str55, str56) < 0);

    const char str57[] = "Hello World";
    const char str58[] = "Hello World";
    EXPECT_TRUE(strcmp(str57, str58) == 0);

    const char str59[] = "Hello World!";
    const char str60[] = "Hello World";
    EXPECT_TRUE(strcmp(str59, str60) > 0);

    const char str61[] = "Hello World";
    const char str62[] = "Hello World!";
    EXPECT_TRUE(strcmp(str61, str62) < 0);

    const char str63[] = "Hello World";
    const char str64[] = "Hello Xorld";
    EXPECT_TRUE(strcmp(str63, str64) < 0);

    const char str65[] = "Hello Xorld";
    const char str66[] = "Hello World";
    EXPECT_TRUE(strcmp(str65, str66) > 0);

    const char str67[] = "Hello World";
    const char str68[] = "Hello WorlD";
    EXPECT_TRUE(strcmp(str67, str68) > 0);

    const char str69[] = "Hello WorlD";
    const char str70[] = "Hello World";
    EXPECT_TRUE(strcmp(str69, str70) < 0);
}