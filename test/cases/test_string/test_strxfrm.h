#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(strxfrm) {
    const char *str1 = "Hello, World!";
    char buffer[100];
    EXPECT_EQUAL_UINT(strxfrm(buffer, str1, sizeof(buffer)), strlen(str1));
    EXPECT_EQUAL_STRING(buffer, str1);
}