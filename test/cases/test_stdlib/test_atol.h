#include <stdlib.h>
#include <limits.h>
#include <utest.h>

UTEST_TEST_CASE(atol){
    EXPECT_EQUAL_INT(atol("123"), 123);
    EXPECT_EQUAL_INT(atol("-123"), -123);
    EXPECT_EQUAL_INT(atol("0"), 0);
    EXPECT_EQUAL_INT(atol("123a"), 123);

    EXPECT_EQUAL_INT(atol("   123"), 123);
    EXPECT_EQUAL_INT(atol("   -123"), -123);
    EXPECT_EQUAL_INT(atol("\t\n\r 456"), 456);
    EXPECT_EQUAL_INT(atol(" \t\n\v\f\r 789"), 789);
    
    EXPECT_EQUAL_INT(atol("+123"), 123);
    EXPECT_EQUAL_INT(atol("+0"), 0);
    EXPECT_EQUAL_INT(atol("-0"), 0);
    
    EXPECT_EQUAL_INT(atol(""), 0);
    EXPECT_EQUAL_INT(atol("   "), 0);
    EXPECT_EQUAL_INT(atol("\t\n\r"), 0);
    
    EXPECT_EQUAL_INT(atol("abc"), 0);
    EXPECT_EQUAL_INT(atol("xyz123"), 0);
    EXPECT_EQUAL_INT(atol("!@#"), 0);
    
    EXPECT_EQUAL_INT(atol("123abc456"), 123);
    EXPECT_EQUAL_INT(atol("-456def"), -456);
    EXPECT_EQUAL_INT(atol("789.123"), 789);
    EXPECT_EQUAL_INT(atol("42e10"), 42);
    
    EXPECT_EQUAL_INT(atol("000123"), 123);
    EXPECT_EQUAL_INT(atol("-000456"), -456);
    EXPECT_EQUAL_INT(atol("0000"), 0);
    
// overflow on 32-bit platforms will lead to undefined behavior, so we don't test it

#if defined(__x86_64__) || defined(__aarch64__)
    EXPECT_EQUAL_INT(atol("9223372036854775807"), LONG_MAX);
    EXPECT_EQUAL_INT(atol("-9223372036854775808"), LONG_MIN);
#endif
    
    EXPECT_EQUAL_INT(atol("  +42"), 42);
    EXPECT_EQUAL_INT(atol("  -42"), -42);
    EXPECT_EQUAL_INT(atol(" + 42"), 0);
    EXPECT_EQUAL_INT(atol(" - 42"), 0);
    EXPECT_EQUAL_INT(atol("++42"), 0);
    EXPECT_EQUAL_INT(atol("--42"), 0);
    EXPECT_EQUAL_INT(atol("+-42"), 0);
    EXPECT_EQUAL_INT(atol("-+42"), 0);
    
    EXPECT_EQUAL_INT(atol("1"), 1);
    EXPECT_EQUAL_INT(atol("9"), 9);
    EXPECT_EQUAL_INT(atol("-1"), -1);
    EXPECT_EQUAL_INT(atol("-9"), -9);
    
    EXPECT_EQUAL_INT(atol("42\0hidden"), 42);
}