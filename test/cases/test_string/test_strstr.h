#include <string.h>
#include <utest.h>

UTEST_TEST_CASE(strstr) {
    const char *str1 = "Hello, World!";
    const char *sub1 = "World";
    EXPECT_TRUE(strstr(str1, sub1) == str1 + 7);
    EXPECT_TRUE(strcmp(strstr(str1, sub1), "World!") == 0);

    const char *str2 = "";
    const char *sub2 = "";
    EXPECT_TRUE(strstr(str2, sub2) == str2);
    EXPECT_EQUAL_STRING(strstr("Hello", ""), "Hello");
    EXPECT_NULL(strstr("", "Hello"));

    const char *str3 = "ABCDEFGHIJKLMNOP";
    EXPECT_TRUE(strstr(str3, "ABC") == str3);
    EXPECT_TRUE(strstr(str3, "DEF") == str3 + 3);
    EXPECT_TRUE(strstr(str3, "NOP") == str3 + 13);

    EXPECT_NULL(strstr(str3, "XYZ"));
    EXPECT_NULL(strstr(str3, "ABCDEFGHIJKLMNOPQ"));

    const char *str5 = "HelloHelloHello";
    EXPECT_TRUE(strstr(str5, "Hello") == str5);
    EXPECT_TRUE(strstr(str5 + 1, "Hello") == str5 + 5);

    const char *str6 = "Hello WORLD";
    EXPECT_TRUE(strstr(str6, "WORLD") == str6 + 6);
    EXPECT_NULL(strstr(str6, "world"));

    const char *str7 = "Hello\n\t\r!@#$%^&*()";
    EXPECT_TRUE(strstr(str7, "\n\t\r") == str7 + 5);
    EXPECT_TRUE(strstr(str7, "!@#$") == str7 + 8);

    const char *str8 = "Hello";
    EXPECT_TRUE(strstr(str8, "H") == str8);
    EXPECT_TRUE(strstr(str8, "o") == str8 + 4);

    const char *str9 = "aaaaa";
    EXPECT_TRUE(strstr(str9, "aa") == str9);
    EXPECT_TRUE(strstr(str9, "aaa") == str9);

    const char *str11 = "Hello World";
    EXPECT_NULL(strstr(str11, "World!"));
    EXPECT_NULL(strstr(str11, "Hello World!"));

    const char *str13 = "This is a very long string that contains multiple words and should be tested for proper handling of long strings in the strstr function implementation";
    EXPECT_TRUE(strstr(str13, "very long string") == str13 + 10);
    EXPECT_TRUE(strstr(str13, "multiple words") == str13 + 41);
    EXPECT_NULL(strstr(str13, "nonexistent very long substring that should not be found in the original string"));

    const char *str14 = "ababababab";
    EXPECT_TRUE(strstr(str14, "abab") == str14);
    EXPECT_TRUE(strstr(str14 + 1, "abab") == str14 + 2);
    EXPECT_TRUE(strstr(str14 + 2, "abab") == str14 + 2);
    EXPECT_TRUE(strstr(str14, "") == str14);

    const char binary[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x01, 0x02, 0x00};
    const char pattern[] = {0x00, 0x01, 0x02};
    EXPECT_TRUE(strstr(binary, pattern) == binary);
    EXPECT_TRUE(strstr(binary, pattern + 1) == NULL);
    EXPECT_TRUE(strstr(binary + 1, pattern) == binary + 1);
    EXPECT_TRUE(strstr(binary + 1, pattern + 1) == binary + 1);

    const char *str16 = "   \t\n\r  Hello   \t\n\r  World   \t\n\r  ";
    EXPECT_TRUE(strstr(str16, "Hello") == str16 + 8);
    EXPECT_TRUE(strstr(str16, "World") == str16 + 21);
    EXPECT_TRUE(strstr(str16, "   \t\n\r  ") == str16);

    const char *str17 = "Hello123!@#World456";
    EXPECT_TRUE(strstr(str17, "123!@#") == str17 + 5);
    EXPECT_TRUE(strstr(str17, "World456") == str17 + 11);
    EXPECT_NULL(strstr(str17, "123!@#World4567"));

    const char *str18 = "A";
    EXPECT_TRUE(strstr(str18, "A") == str18);
    EXPECT_NULL(strstr(str18, "AA"));
    EXPECT_TRUE(strstr(str18, "") == str18);

    const char *str19 = "abcabcabcabc";
    EXPECT_TRUE(strstr(str19, "abc") == str19);
    EXPECT_TRUE(strstr(str19, "abcabc") == str19);
    EXPECT_TRUE(strstr(str19, "abcabcabc") == str19);
    EXPECT_NULL(strstr(str19, "abcabcabcabcabc"));

    const char str20[] = {'H', 'e', 'l', 'l', 'o', '\0', 'W', 'o', 'r', 'l', 'd'};
    EXPECT_TRUE(strstr(str20, "Hello") == str20);
    EXPECT_NULL(strstr(str20, "World"));

    const char *str21 = "HeLLo WoRlD";
    EXPECT_TRUE(strstr(str21, "HeLLo") == str21);
    EXPECT_TRUE(strstr(str21, "WoRlD") == str21 + 6);
    EXPECT_NULL(strstr(str21, "hello"));
    EXPECT_NULL(strstr(str21, "WORLD"));

    const char str22[] = {'H', 'e', 'l', 'l', 'o', '\0', 'W', 'o', 'r', 'l', 'd', '\0', '!'};
    EXPECT_TRUE(strstr(str22, "Hello") == str22);
    EXPECT_NULL(strstr(str22, "World"));
    EXPECT_NULL(strstr(str22, "!"));
}

