#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(strncmp) {
    const char str1[] = "Hello World";
    const char str2[] = "Hello World";
    EXPECT_EQUAL_INT(strncmp(str1, str2, 11), 0);

    const char str3[] = "Hello World";
    const char str4[] = "Hello Earth";
    EXPECT_TRUE(strncmp(str3, str4, 11) > 0);
    EXPECT_TRUE(strncmp(str4, str3, 11) < 0);

    const char str5[] = "";
    const char str6[] = "";
    EXPECT_EQUAL_INT(strncmp(str5, str6, 0), 0);
    EXPECT_EQUAL_INT(strncmp(str5, str6, 1), 0);

    const char str7[] = "";
    const char str8[] = "Hello";
    EXPECT_TRUE(strncmp(str7, str8, 1) < 0);
    EXPECT_TRUE(strncmp(str8, str7, 1) > 0);

    const char str9[] = "Hello";
    const char str10[] = "Hello World";
    EXPECT_EQUAL_INT(strncmp(str9, str10, 5), 0);
    EXPECT_TRUE(strncmp(str9, str10, 6) < 0);

    const char str11[] = "Hello";
    const char str12[] = "hello";
    EXPECT_TRUE(strncmp(str11, str12, 5) < 0);
    EXPECT_TRUE(strncmp(str12, str11, 5) > 0);

    const char str13[] = "Hello\n\t";
    const char str14[] = "Hello\n\t";
    EXPECT_EQUAL_INT(strncmp(str13, str14, 7), 0);

    const char str15[] = "Hello\0World";
    const char str16[] = "Hello\0Earth";
    EXPECT_EQUAL_INT(strncmp(str15, str16, 11), 0);

    const char str17[] = "Hello";
    const char str18[] = "Hello";
    EXPECT_EQUAL_INT(strncmp(str17, str18, 5), 0);
    EXPECT_EQUAL_INT(strncmp(str17, str18, 6), 0);

    const char str19[] = "Hello";
    const char str20[] = "World";
    EXPECT_EQUAL_INT(strncmp(str19, str20, 0), 0);

    const char str21[] = "Hello World";
    const char str22[] = "Hello Earth";
    EXPECT_EQUAL_INT(strncmp(str21, str22, 5), 0);
    EXPECT_TRUE(strncmp(str21, str22, 6) == 0);

    const char str23[] = "Hello";
    const char str24[] = "Jello";
    EXPECT_TRUE(strncmp(str23, str24, 1) < 0);
    EXPECT_TRUE(strncmp(str24, str23, 1) > 0);

    const char str25[] = "Hello";
    const char str26[] = "Hellp";
    EXPECT_TRUE(strncmp(str25, str26, 5) < 0);
    EXPECT_TRUE(strncmp(str26, str25, 5) > 0);

    const char str27[] = "Hello\x80";
    const char str28[] = "Hello\x81";
    EXPECT_TRUE(strncmp(str27, str28, 6) < 0);
    EXPECT_TRUE(strncmp(str28, str27, 6) > 0);

    const char str29[] = "Hello\xFF";
    const char str30[] = "Hello\xFE";
    EXPECT_TRUE(strncmp(str29, str30, 6) > 0);
    EXPECT_TRUE(strncmp(str30, str29, 6) < 0);

    const char str31[] = "Hello\x00";
    const char str32[] = "Hello\x01";
    EXPECT_TRUE(strncmp(str31, str32, 6) < 0);
    EXPECT_TRUE(strncmp(str32, str31, 6) > 0);

    const char str33[] = "Hello\xAA\x55";
    const char str34[] = "Hello\x55\xAA";
    EXPECT_TRUE(strncmp(str33, str34, 7) > 0);
    EXPECT_TRUE(strncmp(str34, str33, 7) < 0);

    const char str35[] = "Hello\x07";
    const char str36[] = "Hello\x08";
    EXPECT_TRUE(strncmp(str35, str36, 6) < 0);
    EXPECT_TRUE(strncmp(str36, str35, 6) > 0);

    const char str37[] = "Hello\t";
    const char str38[] = "Hello\0";
    EXPECT_TRUE(strncmp(str37, str38, 6) > 0);
    EXPECT_TRUE(strncmp(str38, str37, 6) < 0);

    const char str39[] = "Hello\n\t";
    const char str40[] = "hello\n\t";
    EXPECT_TRUE(strncmp(str39, str40, 7) < 0);
    EXPECT_TRUE(strncmp(str40, str39, 7) > 0);

    const char str41[] = "This is a very long string that differs at the end";
    const char str42[] = "This is a very long string that differs at the end!";
    EXPECT_EQUAL_INT(strncmp(str41, str42, 45), 0);
    EXPECT_TRUE(strncmp(str41, str42, 46) == 0);

    const char str43[] = "Hello";
    const char str44[] = "Hello World";
    EXPECT_EQUAL_INT(strncmp(str43, str44, 5), 0);
    EXPECT_TRUE(strncmp(str43, str44, 6) < 0);

    const char str45[] = "Hello\0World";
    const char str46[] = "Hello\0Earth";
    EXPECT_EQUAL_INT(strncmp(str45, str46, 5), 0);
    EXPECT_EQUAL_INT(strncmp(str45, str46, 6), 0);

    char str47[1024] = "a";
    char str48[1024] = "a";
    memset((void*)str47, 'a', 1023);
    memset((void*)str48, 'a', 1023);
    str47[1023] = '\0';
    str48[1023] = '\0';
    EXPECT_EQUAL_INT(strncmp(str47, str48, 1023), 0);

    char str49[1024] = "a";
    char str50[1024] = "a";
    memset((void*)str49, 'a', 1023);
    memset((void*)str50, 'a', 1023);
    str49[1022] = 'b';
    str49[1023] = '\0';
    str50[1023] = '\0';
    EXPECT_EQUAL_INT(strncmp(str49, str50, 1022), 0);
    EXPECT_TRUE(strncmp(str49, str50, 1023) > 0);
}