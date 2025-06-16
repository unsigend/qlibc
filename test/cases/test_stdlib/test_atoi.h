#include <stdlib.h>
#include <limits.h>
#include <utest.h>

UTEST_TEST_CASE(atoi){
    EXPECT_EQUAL_INT(atoi("123"), 123);
    EXPECT_EQUAL_INT(atoi("-123"), -123);
    EXPECT_EQUAL_INT(atoi("0"), 0);
    EXPECT_EQUAL_INT(atoi("123a"), 123);
    
    EXPECT_EQUAL_INT(atoi("   123"), 123);
    EXPECT_EQUAL_INT(atoi("   -123"), -123);
    EXPECT_EQUAL_INT(atoi("\t\n\r 456"), 456);
    EXPECT_EQUAL_INT(atoi(" \t\n\v\f\r 789"), 789);
    
    EXPECT_EQUAL_INT(atoi("+123"), 123);
    EXPECT_EQUAL_INT(atoi("+0"), 0);
    EXPECT_EQUAL_INT(atoi("-0"), 0);
    
    EXPECT_EQUAL_INT(atoi(""), 0);
    EXPECT_EQUAL_INT(atoi("   "), 0);
    EXPECT_EQUAL_INT(atoi("\t\n\r"), 0);
    
    EXPECT_EQUAL_INT(atoi("abc"), 0);
    EXPECT_EQUAL_INT(atoi("xyz123"), 0);
    EXPECT_EQUAL_INT(atoi("!@#"), 0);
    
    EXPECT_EQUAL_INT(atoi("123abc456"), 123);
    EXPECT_EQUAL_INT(atoi("-456def"), -456);
    EXPECT_EQUAL_INT(atoi("789.123"), 789);
    EXPECT_EQUAL_INT(atoi("42e10"), 42);
    
    EXPECT_EQUAL_INT(atoi("000123"), 123);
    EXPECT_EQUAL_INT(atoi("-000456"), -456);
    EXPECT_EQUAL_INT(atoi("0000"), 0);
    
    EXPECT_EQUAL_INT(atoi("2147483647"), 2147483647);
    EXPECT_EQUAL_INT(atoi("-2147483648"), -2147483648);
    
    EXPECT_EQUAL_INT(atoi("  +42"), 42);
    EXPECT_EQUAL_INT(atoi("  -42"), -42);
    EXPECT_EQUAL_INT(atoi(" + 42"), 0);
    EXPECT_EQUAL_INT(atoi(" - 42"), 0);
    EXPECT_EQUAL_INT(atoi("++42"), 0);
    EXPECT_EQUAL_INT(atoi("--42"), 0);
    EXPECT_EQUAL_INT(atoi("+-42"), 0);
    EXPECT_EQUAL_INT(atoi("-+42"), 0);
    
    EXPECT_EQUAL_INT(atoi("1"), 1);
    EXPECT_EQUAL_INT(atoi("9"), 9);
    EXPECT_EQUAL_INT(atoi("-1"), -1);
    EXPECT_EQUAL_INT(atoi("-9"), -9);
    
    EXPECT_EQUAL_INT(atoi("42\0hidden"), 42);
}