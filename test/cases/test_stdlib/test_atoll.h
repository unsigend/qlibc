#include <stdlib.h>
#include <limits.h>
#include <utest.h>

UTEST_TEST_CASE(atoll){
    EXPECT_EQUAL_INT(atoll("123"), 123);
    EXPECT_EQUAL_INT(atoll("-123"), -123);
    EXPECT_EQUAL_INT(atoll("0"), 0);
    EXPECT_EQUAL_INT(atoll("123a"), 123);
    
    EXPECT_EQUAL_INT(atoll("   123"), 123);
    EXPECT_EQUAL_INT(atoll("   -123"), -123);
    EXPECT_EQUAL_INT(atoll("\t\n\r 456"), 456);
    EXPECT_EQUAL_INT(atoll(" \t\n\v\f\r 789"), 789);
    
    EXPECT_EQUAL_INT(atoll("+123"), 123);
    EXPECT_EQUAL_INT(atoll("+0"), 0);
    EXPECT_EQUAL_INT(atoll("-0"), 0);
    
    EXPECT_EQUAL_INT(atoll(""), 0);
    EXPECT_EQUAL_INT(atoll("   "), 0);
    EXPECT_EQUAL_INT(atoll("\t\n\r"), 0);
    
    EXPECT_EQUAL_INT(atoll("abc"), 0);
    EXPECT_EQUAL_INT(atoll("xyz123"), 0);
    EXPECT_EQUAL_INT(atoll("!@#"), 0);
    
    EXPECT_EQUAL_INT(atoll("123abc456"), 123);
    EXPECT_EQUAL_INT(atoll("-456def"), -456);
    EXPECT_EQUAL_INT(atoll("789.123"), 789);
    EXPECT_EQUAL_INT(atoll("42e10"), 42);
    
    EXPECT_EQUAL_INT(atoll("000123"), 123);
    EXPECT_EQUAL_INT(atoll("-000456"), -456);
    EXPECT_EQUAL_INT(atoll("0000"), 0);
    
    EXPECT_EQUAL_INT(atoll("9223372036854775807"), LLONG_MAX);
    EXPECT_EQUAL_INT(atoll("-9223372036854775808"), LLONG_MIN);
    
    EXPECT_EQUAL_INT(atoll("  +42"), 42);
    EXPECT_EQUAL_INT(atoll("  -42"), -42);
    EXPECT_EQUAL_INT(atoll(" + 42"), 0);
    EXPECT_EQUAL_INT(atoll(" - 42"), 0);
    EXPECT_EQUAL_INT(atoll("++42"), 0);
    EXPECT_EQUAL_INT(atoll("--42"), 0);
    EXPECT_EQUAL_INT(atoll("+-42"), 0);
    EXPECT_EQUAL_INT(atoll("-+42"), 0);
    
    EXPECT_EQUAL_INT(atoll("1"), 1);
    EXPECT_EQUAL_INT(atoll("9"), 9);
    EXPECT_EQUAL_INT(atoll("-1"), -1);
    EXPECT_EQUAL_INT(atoll("-9"), -9);
    
    EXPECT_EQUAL_INT(atoll("42\0hidden"), 42);
} 