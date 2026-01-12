#include <utest.h>
#include <string.h>

/**
 * Based on qlibc
 * The implementation is just a copy of the strcmp function.
 */
UTEST_TEST_CASE(strcoll){
    EXPECT_EQUAL_INT(strcoll("", ""), 0);
    EXPECT_EQUAL_INT(strcoll("a", "a"), 0);
    EXPECT_EQUAL_INT(strcoll("ab", "ab"), 0);
    EXPECT_EQUAL_INT(strcoll("hello", "hello"), 0);
    EXPECT_EQUAL_INT(strcoll("Hello World", "Hello World"), 0);
}