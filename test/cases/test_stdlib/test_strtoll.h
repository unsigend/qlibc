#include <utest.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>

#define NAMESPACE_BEGIN {
#define NAMESPACE_END }
#define AUTO 0

UTEST_TEST_CASE(strtoll){
NAMESPACE_BEGIN
    EXPECT_EQUAL_INT(strtoll("123", NULL, 10), 123);
    EXPECT_EQUAL_INT(strtoll("0", NULL, 10), AUTO);
    EXPECT_EQUAL_INT(strtoll("456789", NULL, 10), 456789);
NAMESPACE_END

NAMESPACE_BEGIN
    EXPECT_EQUAL_INT(strtoll("123", NULL, 16), 0x123);
    EXPECT_EQUAL_INT(strtoll("abc", NULL, 16), 0xabc);
    EXPECT_EQUAL_INT(strtoll("ABC", NULL, 16), 0xABC);
    EXPECT_EQUAL_INT(strtoll("1a2b3c", NULL, 16), 0x1a2b3c);
    EXPECT_EQUAL_INT(strtoll("ff", NULL, 16), 0xff);
    EXPECT_EQUAL_INT(strtoll("0x123", NULL, 16), 0x123);
    EXPECT_EQUAL_INT(strtoll("0X456", NULL, 16), 0x456);
NAMESPACE_END

NAMESPACE_BEGIN
    EXPECT_EQUAL_INT(strtoll("123", NULL, 8), 0123);
    EXPECT_EQUAL_INT(strtoll("0", NULL, 8), AUTO);
    EXPECT_EQUAL_INT(strtoll("7", NULL, 8), 07);
    EXPECT_EQUAL_INT(strtoll("777", NULL, 8), 0777);
    EXPECT_EQUAL_INT(strtoll("0123", NULL, 8), 0123);
NAMESPACE_END

NAMESPACE_BEGIN
    EXPECT_EQUAL_INT(strtoll("123", NULL, 2), 0b1); 
    EXPECT_EQUAL_INT(strtoll("101", NULL, 2), 0b101);
    EXPECT_EQUAL_INT(strtoll("1111", NULL, 2), 0b1111);
    EXPECT_EQUAL_INT(strtoll("0", NULL, 2), AUTO);
    EXPECT_EQUAL_INT(strtoll("1", NULL, 2), 1);
NAMESPACE_END

NAMESPACE_BEGIN
    EXPECT_EQUAL_INT(strtoll("123", NULL, 0), 123);    
    EXPECT_EQUAL_INT(strtoll("0123", NULL, 0), 0123);  
    EXPECT_EQUAL_INT(strtoll("0x123", NULL, 0), 0x123);
    EXPECT_EQUAL_INT(strtoll("0X456", NULL, 0), 0x456);
NAMESPACE_END

NAMESPACE_BEGIN
    EXPECT_EQUAL_INT(strtoll("-123", NULL, 10), -123);
    EXPECT_EQUAL_INT(strtoll("-0", NULL, 10), AUTO);
    EXPECT_EQUAL_INT(strtoll("-456", NULL, 10), -456);
    EXPECT_EQUAL_INT(strtoll("-ff", NULL, 16), -0xff);
    EXPECT_EQUAL_INT(strtoll("-0x123", NULL, 16), -0x123);
    EXPECT_EQUAL_INT(strtoll("-777", NULL, 8), -0777);
    EXPECT_EQUAL_INT(strtoll("-101", NULL, 2), -0b101);
NAMESPACE_END

NAMESPACE_BEGIN
    EXPECT_EQUAL_INT(strtoll("+123", NULL, 10), 123);
    EXPECT_EQUAL_INT(strtoll("+0", NULL, 10), AUTO);
    EXPECT_EQUAL_INT(strtoll("+abc", NULL, 16), 0xabc);
    EXPECT_EQUAL_INT(strtoll("+0x123", NULL, 0), 0x123);
NAMESPACE_END

NAMESPACE_BEGIN
    EXPECT_EQUAL_INT(strtoll("    ", NULL, 10), 0);
    EXPECT_EQUAL_INT(strtoll("    ", NULL, 16), 0);
    EXPECT_EQUAL_INT(strtoll("  123", NULL, 10), 123);
    EXPECT_EQUAL_INT(strtoll("\t\n\r 456", NULL, 10), 456);
    EXPECT_EQUAL_INT(strtoll("   -789", NULL, 10), -789);
    EXPECT_EQUAL_INT(strtoll("\t+123", NULL, 10), 123);
NAMESPACE_END

NAMESPACE_BEGIN
    EXPECT_EQUAL_INT(strtoll("123abc", NULL, 10), 123);  
    EXPECT_EQUAL_INT(strtoll("456xyz", NULL, 10), 456);  
    EXPECT_EQUAL_INT(strtoll("12.34", NULL, 10), 12);    
    EXPECT_EQUAL_INT(strtoll("123,456", NULL, 10), 123); 
    EXPECT_EQUAL_INT(strtoll("abc123", NULL, 10), 0);    
NAMESPACE_END

NAMESPACE_BEGIN
    EXPECT_EQUAL_INT(strtoll("", NULL, 10), 0);
    EXPECT_EQUAL_INT(strtoll("   ", NULL, 10), 0);
    EXPECT_EQUAL_INT(strtoll("\t\n", NULL, 10), 0);
NAMESPACE_END

NAMESPACE_BEGIN
    EXPECT_EQUAL_INT(strtoll("g", NULL, 16), 0);         
    EXPECT_EQUAL_INT(strtoll("8", NULL, 8), 0);          
    EXPECT_EQUAL_INT(strtoll("2", NULL, 2), 0);          
    EXPECT_EQUAL_INT(strtoll("abcdefg", NULL, 16), 0xabcdef); 
NAMESPACE_END

NAMESPACE_BEGIN
    char *endptr;
    EXPECT_EQUAL_INT(strtoll("123abc", &endptr, 10), 123);
    
    EXPECT_EQUAL_INT(strtoll("   456   ", &endptr, 10), 456);
    EXPECT_EQUAL_INT(strtoll("0x123xyz", &endptr, 16), 0x123);
    EXPECT_EQUAL_INT(strtoll("-789def", &endptr, 10), -789);
NAMESPACE_END

NAMESPACE_BEGIN
    char *endptr;
    const char *str1 = "123abc";
    EXPECT_EQUAL_INT(strtoll(str1, &endptr, 10), 123);
    EXPECT_EQUAL_INT(*endptr, 'a');
    
    const char *str2 = "456xyz789";
    EXPECT_EQUAL_INT(strtoll(str2, &endptr, 10), 456);
    EXPECT_EQUAL_INT(*endptr, 'x');
    
    const char *str3 = "789";
    EXPECT_EQUAL_INT(strtoll(str3, &endptr, 10), 789);
    EXPECT_EQUAL_INT(*endptr, '\0');
NAMESPACE_END

NAMESPACE_BEGIN
    char *endptr;
    const char *str1 = "abc123";
    EXPECT_EQUAL_INT(strtoll(str1, &endptr, 10), 0);
    EXPECT_EQUAL_INT(endptr, str1);
    
    const char *str2 = "xyz";
    EXPECT_EQUAL_INT(strtoll(str2, &endptr, 10), 0);
    EXPECT_EQUAL_INT(endptr, str2);
    
    const char *str3 = "";
    EXPECT_EQUAL_INT(strtoll(str3, &endptr, 10), 0);
    EXPECT_EQUAL_INT(endptr, str3);
NAMESPACE_END

NAMESPACE_BEGIN
    char *endptr;
    const char *str1 = "   123abc";
    EXPECT_EQUAL_INT(strtoll(str1, &endptr, 10), 123);
    EXPECT_EQUAL_INT(*endptr, 'a');
    
    const char *str2 = "\t\n 456 xyz";
    EXPECT_EQUAL_INT(strtoll(str2, &endptr, 10), 456);
    EXPECT_EQUAL_INT(*endptr, ' ');
    
    const char *str3 = "   ";
    EXPECT_EQUAL_INT(strtoll(str3, &endptr, 10), 0);
    EXPECT_EQUAL_INT(endptr, str3);
NAMESPACE_END

NAMESPACE_BEGIN
    char *endptr;
    const char *str1 = "abc123";
    EXPECT_EQUAL_INT(strtoll(str1, &endptr, 16), 0xabc123);
    EXPECT_EQUAL_INT8(*endptr, '\0');
    
    const char *str2 = "777999";
    EXPECT_EQUAL_INT(strtoll(str2, &endptr, 8), 0777);
    EXPECT_EQUAL_INT(*endptr, '9');
    
    const char *str3 = "101abc";
    EXPECT_EQUAL_INT(strtoll(str3, &endptr, 2), 0b101);
    EXPECT_EQUAL_INT(*endptr, 'a');
NAMESPACE_END

NAMESPACE_BEGIN
    char *endptr;
    const char *str1 = "-123abc";
    EXPECT_EQUAL_INT(strtoll(str1, &endptr, 10), -123);
    EXPECT_EQUAL_INT(*endptr, 'a');
    
    const char *str2 = "+456xyz";
    EXPECT_EQUAL_INT(strtoll(str2, &endptr, 10), +456);
    EXPECT_EQUAL_INT(*endptr, 'x');
    
    const char *str3 = "0x123ghi";
    EXPECT_EQUAL_INT(strtoll(str3, &endptr, 16), 0x123);
    EXPECT_EQUAL_INT(*endptr, 'g');
    
    const char *str4 = "0x123ghi";
    EXPECT_EQUAL_INT(strtoll(str4, &endptr, 0), 0x123);
    EXPECT_EQUAL_INT(*endptr, 'g');
NAMESPACE_END

NAMESPACE_BEGIN
    char *endptr;
    const char *str1 = "0";
    EXPECT_EQUAL_INT(strtoll(str1, &endptr, 10), 0);
    EXPECT_EQUAL_INT(*endptr, '\0');
    
    const char *str2 = "0abc";
    EXPECT_EQUAL_INT(strtoll(str2, &endptr, 10), 0);
    EXPECT_EQUAL_INT(*endptr, 'a');
    
    const char *str3 = "+";
    EXPECT_EQUAL_INT(strtoll(str3, &endptr, 10), 0);
    EXPECT_EQUAL_INT(endptr, str3);
    
    const char *str4 = "-";
    EXPECT_EQUAL_INT(strtoll(str4, &endptr, 10), 0);
    EXPECT_EQUAL_INT(endptr, str4);
    
    const char *str5 = "0x";
    EXPECT_EQUAL_INT(strtoll(str5, &endptr, 16), 0);
    EXPECT_EQUAL_INT(*endptr, 'x');
NAMESPACE_END

NAMESPACE_BEGIN
    EXPECT_EQUAL_INT(strtoll("123", NULL, 36), 1*36*36 + 2*36 + 3); 
    EXPECT_EQUAL_INT(strtoll("zz", NULL, 36), 35*36 + 35);          
    EXPECT_EQUAL_INT(strtoll("10", NULL, 3), 1*3 + 0);              
    EXPECT_EQUAL_INT(strtoll("77", NULL, 9), 7*9 + 7);              
NAMESPACE_END

NAMESPACE_BEGIN
    EXPECT_EQUAL_INT(strtoll("0", NULL, 10), 0);
    EXPECT_EQUAL_INT(strtoll("00", NULL, 10), 0);
    EXPECT_EQUAL_INT(strtoll("000", NULL, 8), 0);
    EXPECT_EQUAL_INT(strtoll("0x0", NULL, 16), 0);
    EXPECT_EQUAL_INT(strtoll("-0", NULL, 10), 0);
    EXPECT_EQUAL_INT(strtoll("+0", NULL, 10), 0);
NAMESPACE_END

// under bonder, without overflow
NAMESPACE_BEGIN
    errno = 0;
    char *endptr;
    const char *llong_max = "9223372036854775807";
    const char *llong_min = "-9223372036854775808";
    EXPECT_EQUAL_INT(strtoll(llong_max, &endptr, AUTO), LLONG_MAX);
    EXPECT_EQUAL_UINT8(*endptr, '\0');
    EXPECT_EQUAL_UINT(endptr, llong_max + strlen(llong_max));

    EXPECT_EQUAL_INT(strtoll(llong_min, &endptr, AUTO), LLONG_MIN);
    EXPECT_EQUAL_UINT8(*endptr, '\0');
    EXPECT_EQUAL_UINT(endptr, llong_min + strlen(llong_min));
    
    EXPECT_EQUAL_INT(errno, 0);
NAMESPACE_END

// test for positive overflow
NAMESPACE_BEGIN
    errno = 0;
    char *endptr;
    const char *str1 = "999999999999999999999";
    EXPECT_EQUAL_INT(strtoll(str1, &endptr, AUTO), LLONG_MAX);
    EXPECT_EQUAL_INT(errno, ERANGE);
    EXPECT_EQUAL_UINT(endptr, str1 + strlen(str1));
NAMESPACE_END

// test for negative overflow
NAMESPACE_BEGIN
    errno = 0;
    char *endptr;
    const char *str1 = "-999999999999999999999";
    EXPECT_EQUAL_INT(strtoll(str1, &endptr, AUTO), LLONG_MIN);
    EXPECT_EQUAL_INT(errno, ERANGE);
    EXPECT_EQUAL_UINT(endptr, str1 + strlen(str1));
NAMESPACE_END

// invalid base check
NAMESPACE_BEGIN
    errno = 0;
    char *endptr;
    const char *str1 = "123";
    EXPECT_EQUAL_INT(strtoll(str1, &endptr, 1), 0);
    EXPECT_EQUAL_UINT(endptr, str1);
    EXPECT_EQUAL_INT(errno, EINVAL);
NAMESPACE_END

NAMESPACE_BEGIN
    errno = 0;
    char *endptr;
    const char *str1 = "123";
    EXPECT_EQUAL_INT(strtoll(str1, &endptr, 37), 0);
    EXPECT_EQUAL_UINT(endptr, str1);
    EXPECT_EQUAL_INT(errno, EINVAL);
NAMESPACE_END

NAMESPACE_BEGIN
    errno = 0;
    char *endptr;
    const char *str1 = "123";
    EXPECT_EQUAL_INT(strtoll(str1, &endptr, -3), 0);
    EXPECT_EQUAL_UINT(endptr, str1);
    EXPECT_EQUAL_INT(errno, EINVAL);
NAMESPACE_END

    // make sure the errno is cleared
    errno = 0;
}