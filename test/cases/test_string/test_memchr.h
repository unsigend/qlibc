#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(memchr) {
    const char str1[] = "Hello World";
    const void* result1 = memchr(str1, 'W', sizeof(str1));
    EXPECT_NOT_NULL(result1);
    EXPECT_TRUE(*(const char*)result1 == 'W');
    EXPECT_TRUE((const char*)result1 == str1 + 6);

    const char str2[] = "Hello Hello";
    const void* result2 = memchr(str2, 'H', sizeof(str2));
    EXPECT_NOT_NULL(result2);
    EXPECT_TRUE(*(const char*)result2 == 'H');
    EXPECT_TRUE((const char*)result2 == str2);

    const char str3[] = "Hello World";
    const void* result3 = memchr(str3, 'z', sizeof(str3));
    EXPECT_NULL(result3);

    const char str4[] = "";
    const void* result4 = memchr(str4, 'a', 0);
    EXPECT_NULL(result4);

    const char str5[] = "Hello\0World";
    const void* result5 = memchr(str5, '\0', sizeof(str5));
    EXPECT_NOT_NULL(result5);
    EXPECT_TRUE(*(const char*)result5 == '\0');
    EXPECT_TRUE((const char*)result5 == str5 + 5);

    const char str6[] = "Hello World";
    const void* result6 = memchr(str6, 'W', 5);
    EXPECT_NULL(result6);

    const char str7[] = "Hello World";
    const void* result7 = memchr(str7, 'd', sizeof(str7));
    EXPECT_NOT_NULL(result7);
    EXPECT_TRUE(*(const char*)result7 == 'd');
    EXPECT_TRUE((const char*)result7 == str7 + 10);

    const unsigned char binary[] = {0x00, 0xFF, 0x42, 0x7F, 0x80};
    const void* result8 = memchr(binary, 0x42, sizeof(binary));
    EXPECT_NOT_NULL(result8);
    EXPECT_TRUE(*(const unsigned char*)result8 == 0x42);
    EXPECT_TRUE((const unsigned char*)result8 == binary + 2);
}