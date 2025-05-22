#include <limits.h>
#include <utest.h>

UTEST_TEST_CASE(limits){
    // CHAR_BIT
    EXPECT_EQUAL_INT(CHAR_BIT, 8);

    // CHAR_MIN
    EXPECT_EQUAL_INT8(CHAR_MIN, -128);
    EXPECT_EQUAL_INT8(CHAR_MIN, 0x80);
    
    // CHAR_MAX
    EXPECT_EQUAL_INT8(CHAR_MAX, 127);
    EXPECT_EQUAL_INT8(CHAR_MAX, 0x7f);

    // Signed number Min
    EXPECT_EQUAL_INT8(SCHAR_MIN, -128);
    EXPECT_EQUAL_INT8(SCHAR_MIN, 0x80);
    EXPECT_EQUAL_INT16(SHRT_MIN, 0x8000);
    EXPECT_EQUAL_INT32(INT_MIN, 0x80000000);
#ifdef __i386__
    EXPECT_EQUAL_INT32(LONG_MIN, 0x80000000);
#endif
#ifdef __x86_64__
    EXPECT_EQUAL_INT64(LONG_MIN, 0x8000000000000000);
#endif
#ifdef __aarch64__
    EXPECT_EQUAL_INT64(LONG_MIN, 0x8000000000000000);
#endif
    EXPECT_EQUAL_INT64(LLONG_MIN, 0x8000000000000000);

    // Signed number Max
    EXPECT_EQUAL_INT8(SCHAR_MAX, 127);
    EXPECT_EQUAL_INT8(SCHAR_MAX, 0x7f);
    EXPECT_EQUAL_INT16(SHRT_MAX, 0x7fff);
    EXPECT_EQUAL_INT32(INT_MAX, 0x7fffffff);
#ifdef __i386__
    EXPECT_EQUAL_INT32(LONG_MAX, 0x7fffffff);
#endif
#ifdef __x86_64__
    EXPECT_EQUAL_INT64(LONG_MAX, 0x7fffffffffffffff);
#endif
#ifdef __aarch64__
    EXPECT_EQUAL_INT64(LONG_MAX, 0x7fffffffffffffff);
#endif
    EXPECT_EQUAL_INT64(LLONG_MAX, 0x7fffffffffffffff);

    // Unsigned number Max
    EXPECT_EQUAL_UINT8(UCHAR_MAX, 255);
    EXPECT_EQUAL_UINT8(UCHAR_MAX, 0xff);

    EXPECT_EQUAL_UINT16(USHRT_MAX, 0xffff);
    EXPECT_EQUAL_UINT32(UINT_MAX, 0xffffffff);
#ifdef __i386__
    EXPECT_EQUAL_UINT32(ULONG_MAX, 0xffffffff);
#endif
#ifdef __x86_64__
    EXPECT_EQUAL_UINT64(ULONG_MAX, 0xffffffffffffffff);
#endif
#ifdef __aarch64__
    EXPECT_EQUAL_UINT64(ULONG_MAX, 0xffffffffffffffff);
#endif
    EXPECT_EQUAL_UINT64(ULLONG_MAX, 0xffffffffffffffff);
}

UTEST_TEST_SUITE(limits){
    UTEST_RUN_TEST_CASE(limits);
}