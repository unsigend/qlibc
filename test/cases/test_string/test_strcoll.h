#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(strcoll) {
    // no locale support
    const char str1[] = "Hello";
    const char str2[] = "Hello";
    EXPECT_EQUAL_INT(strcoll(str1, str2), 0);

    const char str3[] = "Hello";
    const char str4[] = "Hello World";
    EXPECT_TRUE(strcoll(str3, str4) < 0);
    EXPECT_TRUE(strcoll(str4, str3) > 0);
}