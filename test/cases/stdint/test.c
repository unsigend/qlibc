#include <utest.h>
#include <stdint.h>
#include <stddef.h>
#include <limits.h>

UTEST_TEST_CASE(fixed_width_types){
    EXPECT_TRUE(sizeof(int8_t) == 1);
    EXPECT_TRUE(sizeof(int16_t) == 2);
    EXPECT_TRUE(sizeof(int32_t) == 4);
    EXPECT_TRUE(sizeof(int64_t) == 8);

    EXPECT_TRUE(sizeof(uint8_t) == 1);
    EXPECT_TRUE(sizeof(uint16_t) == 2);
    EXPECT_TRUE(sizeof(uint32_t) == 4);
    EXPECT_TRUE(sizeof(uint64_t) == 8);

    EXPECT_EQUAL_INT(INT8_MIN, -128);
    EXPECT_EQUAL_INT(INT8_MAX, 127);
    EXPECT_EQUAL_INT(INT16_MIN, -32768);
    EXPECT_EQUAL_INT(INT16_MAX, 32767);
    EXPECT_EQUAL_INT(INT32_MIN, -2147483648);
    EXPECT_EQUAL_INT(INT32_MAX, 2147483647);
    EXPECT_EQUAL_INT(INT64_MIN, -9223372036854775808LL);
    EXPECT_EQUAL_INT(INT64_MAX, 9223372036854775807LL);

    EXPECT_EQUAL_INT(UINT8_MAX, 255);
    EXPECT_EQUAL_INT(UINT16_MAX, 65535);
    EXPECT_EQUAL_INT(UINT32_MAX, 4294967295U);
    EXPECT_EQUAL_INT(UINT64_MAX, 18446744073709551615ULL);

    EXPECT_TRUE(INT8_MIN == -1 - INT8_MAX);
    EXPECT_TRUE(INT16_MIN == -1 - INT16_MAX);
    EXPECT_TRUE(INT32_MIN == -1 - INT32_MAX);
    EXPECT_TRUE(INT64_MIN == -1 - INT64_MAX);

    EXPECT_TRUE(UINT8_MAX == (uint8_t)-1);
    EXPECT_TRUE(UINT16_MAX == (uint16_t)-1);
    EXPECT_TRUE(UINT32_MAX == (uint32_t)-1);
    EXPECT_TRUE(UINT64_MAX == (uint64_t)-1);
}

UTEST_TEST_CASE(least_types){
    EXPECT_TRUE(sizeof(int_least8_t) * CHAR_BIT >= 8);
    EXPECT_TRUE(sizeof(int_least16_t) * CHAR_BIT >= 16);
    EXPECT_TRUE(sizeof(int_least32_t) * CHAR_BIT >= 32);
    EXPECT_TRUE(sizeof(int_least64_t) * CHAR_BIT >= 64);

    EXPECT_TRUE(sizeof(uint_least8_t) * CHAR_BIT >= 8);
    EXPECT_TRUE(sizeof(uint_least16_t) * CHAR_BIT >= 16);
    EXPECT_TRUE(sizeof(uint_least32_t) * CHAR_BIT >= 32);
    EXPECT_TRUE(sizeof(uint_least64_t) * CHAR_BIT >= 64);

    EXPECT_TRUE(INT_LEAST8_MIN < 0);
    EXPECT_TRUE(INT_LEAST8_MAX > 0);
    EXPECT_TRUE(INT_LEAST16_MIN < 0);
    EXPECT_TRUE(INT_LEAST16_MAX > 0);
    EXPECT_TRUE(INT_LEAST32_MIN < 0);
    EXPECT_TRUE(INT_LEAST32_MAX > 0);
    EXPECT_TRUE(INT_LEAST64_MIN < 0);
    EXPECT_TRUE(INT_LEAST64_MAX > 0);

    EXPECT_TRUE(UINT_LEAST8_MAX > 0);
    EXPECT_TRUE(UINT_LEAST16_MAX > 0);
    EXPECT_TRUE(UINT_LEAST32_MAX > 0);
    EXPECT_TRUE(UINT_LEAST64_MAX > 0);

    EXPECT_TRUE(INT_LEAST8_MIN == -1 - INT_LEAST8_MAX);
    EXPECT_TRUE(INT_LEAST16_MIN == -1 - INT_LEAST16_MAX);
    EXPECT_TRUE(INT_LEAST32_MIN == -1 - INT_LEAST32_MAX);
    EXPECT_TRUE(INT_LEAST64_MIN == -1 - INT_LEAST64_MAX);

    EXPECT_TRUE(UINT_LEAST8_MAX == (uint_least8_t)-1);
    EXPECT_TRUE(UINT_LEAST16_MAX == (uint_least16_t)-1);
    EXPECT_TRUE(UINT_LEAST32_MAX == (uint_least32_t)-1);
    EXPECT_TRUE(UINT_LEAST64_MAX == (uint_least64_t)-1);
}

UTEST_TEST_CASE(fast_types){
    EXPECT_TRUE(sizeof(int_fast8_t) * CHAR_BIT >= 8);
    EXPECT_TRUE(sizeof(int_fast16_t) * CHAR_BIT >= 16);
    EXPECT_TRUE(sizeof(int_fast32_t) * CHAR_BIT >= 32);
    EXPECT_TRUE(sizeof(int_fast64_t) * CHAR_BIT >= 64);

    EXPECT_TRUE(sizeof(uint_fast8_t) * CHAR_BIT >= 8);
    EXPECT_TRUE(sizeof(uint_fast16_t) * CHAR_BIT >= 16);
    EXPECT_TRUE(sizeof(uint_fast32_t) * CHAR_BIT >= 32);
    EXPECT_TRUE(sizeof(uint_fast64_t) * CHAR_BIT >= 64);

    EXPECT_TRUE(INT_FAST8_MIN < 0);
    EXPECT_TRUE(INT_FAST8_MAX > 0);
    EXPECT_TRUE(INT_FAST16_MIN < 0);
    EXPECT_TRUE(INT_FAST16_MAX > 0);
    EXPECT_TRUE(INT_FAST32_MIN < 0);
    EXPECT_TRUE(INT_FAST32_MAX > 0);
    EXPECT_TRUE(INT_FAST64_MIN < 0);
    EXPECT_TRUE(INT_FAST64_MAX > 0);

    EXPECT_TRUE(UINT_FAST8_MAX > 0);
    EXPECT_TRUE(UINT_FAST16_MAX > 0);
    EXPECT_TRUE(UINT_FAST32_MAX > 0);
    EXPECT_TRUE(UINT_FAST64_MAX > 0);

    EXPECT_TRUE(INT_FAST8_MIN == -1 - INT_FAST8_MAX);
    EXPECT_TRUE(INT_FAST16_MIN == -1 - INT_FAST16_MAX);
    EXPECT_TRUE(INT_FAST32_MIN == -1 - INT_FAST32_MAX);
    EXPECT_TRUE(INT_FAST64_MIN == -1 - INT_FAST64_MAX);

    EXPECT_TRUE(UINT_FAST8_MAX == (uint_fast8_t)-1);
    EXPECT_TRUE(UINT_FAST16_MAX == (uint_fast16_t)-1);
    EXPECT_TRUE(UINT_FAST32_MAX == (uint_fast32_t)-1);
    EXPECT_TRUE(UINT_FAST64_MAX == (uint_fast64_t)-1);
}

UTEST_TEST_CASE(max_types){
    EXPECT_TRUE(sizeof(intmax_t) >= sizeof(long));
    EXPECT_TRUE(sizeof(intmax_t) >= sizeof(long long));
    EXPECT_TRUE(sizeof(uintmax_t) >= sizeof(unsigned long));
    EXPECT_TRUE(sizeof(uintmax_t) >= sizeof(unsigned long long));

    EXPECT_TRUE(INTMAX_MIN < 0);
    EXPECT_TRUE(INTMAX_MAX > 0);
    EXPECT_TRUE(UINTMAX_MAX > 0);

    EXPECT_TRUE(INTMAX_MIN == -1 - INTMAX_MAX);
    EXPECT_TRUE(UINTMAX_MAX == (uintmax_t)-1);

    EXPECT_TRUE(sizeof(intmax_t) >= sizeof(intptr_t));
    EXPECT_TRUE(sizeof(uintmax_t) >= sizeof(uintptr_t));

    EXPECT_TRUE(INTMAX_MAX >= LLONG_MAX);
    EXPECT_TRUE(INTMAX_MAX >= LONG_MAX);
    EXPECT_TRUE(UINTMAX_MAX >= ULLONG_MAX);
    EXPECT_TRUE(UINTMAX_MAX >= ULONG_MAX);

    {
        intmax_t imax = LLONG_MAX;
        EXPECT_TRUE(imax <= INTMAX_MAX);
        imax = LONG_MAX;
        EXPECT_TRUE(imax <= INTMAX_MAX);
    }

    {
        uintmax_t umax = ULLONG_MAX;
        EXPECT_TRUE(umax <= UINTMAX_MAX);
        umax = ULONG_MAX;
        EXPECT_TRUE(umax <= UINTMAX_MAX);
    }
}

UTEST_TEST_CASE(ptr_types){
    EXPECT_TRUE(sizeof(intptr_t) >= sizeof(void *));
    EXPECT_TRUE(sizeof(uintptr_t) >= sizeof(void *));
    EXPECT_TRUE(sizeof(intptr_t) == sizeof(uintptr_t));

    EXPECT_TRUE(INTPTR_MIN < 0);
    EXPECT_TRUE(INTPTR_MAX > 0);
    EXPECT_TRUE(UINTPTR_MAX > 0);

    EXPECT_TRUE(INTPTR_MIN == -1 - INTPTR_MAX);
    EXPECT_TRUE(UINTPTR_MAX == (uintptr_t)-1);

    {
        void *ptr = (void *)0x1000;
        intptr_t iptr = (intptr_t)ptr;
        uintptr_t uptr = (uintptr_t)ptr;
        EXPECT_TRUE(iptr >= INTPTR_MIN);
        EXPECT_TRUE(iptr <= INTPTR_MAX);
        EXPECT_TRUE(uptr <= UINTPTR_MAX);
    }
}

UTEST_TEST_CASE(size_types){
    EXPECT_TRUE(sizeof(ptrdiff_t) == sizeof(intptr_t));
    EXPECT_TRUE(sizeof(size_t) == sizeof(uintptr_t));

    EXPECT_TRUE(PTRDIFF_MIN < 0);
    EXPECT_TRUE(PTRDIFF_MAX > 0);
    EXPECT_TRUE(SIZE_MAX > 0);

    EXPECT_TRUE(PTRDIFF_MIN == -1 - PTRDIFF_MAX);
    EXPECT_TRUE(SIZE_MAX == (size_t)-1);

    {
        void *p1 = (void *)0x1000;
        void *p2 = (void *)0x2000;
        ptrdiff_t diff = (char *)p2 - (char *)p1;
        EXPECT_TRUE(diff >= PTRDIFF_MIN);
        EXPECT_TRUE(diff <= PTRDIFF_MAX);
    }
}

UTEST_TEST_CASE(constants){
    {
        int8_t val = INT8_C(42);
        EXPECT_EQUAL_INT(val, 42);
    }

    {
        int16_t val = INT16_C(1000);
        EXPECT_EQUAL_INT(val, 1000);
    }

    {
        int32_t val = INT32_C(100000);
        EXPECT_EQUAL_INT(val, 100000);
    }

    {
        uint8_t val = UINT8_C(42);
        EXPECT_EQUAL_INT(val, 42);
    }

    {
        uint16_t val = UINT16_C(1000);
        EXPECT_EQUAL_INT(val, 1000);
    }

    {
        uint32_t val = UINT32_C(100000);
        EXPECT_EQUAL_INT(val, 100000U);
    }

    {
        intmax_t val = INTMAX_C(1000000);
        EXPECT_TRUE(val == 1000000L || val == 1000000LL);
    }

    {
        uintmax_t val = UINTMAX_C(1000000);
        EXPECT_TRUE(val == 1000000UL || val == 1000000ULL);
    }
}

UTEST_TEST_CASE(relationships){
    EXPECT_TRUE(sizeof(int8_t) <= sizeof(int_least8_t));
    EXPECT_TRUE(sizeof(int_least8_t) <= sizeof(int_fast8_t));
    EXPECT_TRUE(sizeof(int16_t) <= sizeof(int_least16_t));
    EXPECT_TRUE(sizeof(int_least16_t) <= sizeof(int_fast16_t));
    EXPECT_TRUE(sizeof(int32_t) <= sizeof(int_least32_t));
    EXPECT_TRUE(sizeof(int_least32_t) <= sizeof(int_fast32_t));
    EXPECT_TRUE(sizeof(int64_t) <= sizeof(int_least64_t));
    EXPECT_TRUE(sizeof(int_least64_t) <= sizeof(int_fast64_t));

    EXPECT_TRUE(sizeof(uint8_t) <= sizeof(uint_least8_t));
    EXPECT_TRUE(sizeof(uint_least8_t) <= sizeof(uint_fast8_t));
    EXPECT_TRUE(sizeof(uint16_t) <= sizeof(uint_least16_t));
    EXPECT_TRUE(sizeof(uint_least16_t) <= sizeof(uint_fast16_t));
    EXPECT_TRUE(sizeof(uint32_t) <= sizeof(uint_least32_t));
    EXPECT_TRUE(sizeof(uint_least32_t) <= sizeof(uint_fast32_t));
    EXPECT_TRUE(sizeof(uint64_t) <= sizeof(uint_least64_t));
    EXPECT_TRUE(sizeof(uint_least64_t) <= sizeof(uint_fast64_t));

    EXPECT_TRUE(INT8_MAX <= INT_LEAST8_MAX);
    EXPECT_TRUE(INT16_MAX <= INT_LEAST16_MAX);
    EXPECT_TRUE(INT32_MAX <= INT_LEAST32_MAX);
    EXPECT_TRUE(INT64_MAX <= INT_LEAST64_MAX);

    EXPECT_TRUE(UINT8_MAX <= UINT_LEAST8_MAX);
    EXPECT_TRUE(UINT16_MAX <= UINT_LEAST16_MAX);
    EXPECT_TRUE(UINT32_MAX <= UINT_LEAST32_MAX);
    EXPECT_TRUE(UINT64_MAX <= UINT_LEAST64_MAX);

    EXPECT_TRUE(INT_LEAST8_MAX <= INT_FAST8_MAX);
    EXPECT_TRUE(INT_LEAST16_MAX <= INT_FAST16_MAX);
    EXPECT_TRUE(INT_LEAST32_MAX <= INT_FAST32_MAX);
    EXPECT_TRUE(INT_LEAST64_MAX <= INT_FAST64_MAX);

    EXPECT_TRUE(UINT_LEAST8_MAX <= UINT_FAST8_MAX);
    EXPECT_TRUE(UINT_LEAST16_MAX <= UINT_FAST16_MAX);
    EXPECT_TRUE(UINT_LEAST32_MAX <= UINT_FAST32_MAX);
    EXPECT_TRUE(UINT_LEAST64_MAX <= UINT_FAST64_MAX);

    EXPECT_TRUE(INT8_MAX <= INTMAX_MAX);
    EXPECT_TRUE(INT16_MAX <= INTMAX_MAX);
    EXPECT_TRUE(INT32_MAX <= INTMAX_MAX);
    EXPECT_TRUE(INT64_MAX <= INTMAX_MAX);
    EXPECT_TRUE(INTMAX_MAX >= LLONG_MAX);
    EXPECT_TRUE(INTMAX_MAX >= LONG_MAX);

    EXPECT_TRUE(UINT8_MAX <= UINTMAX_MAX);
    EXPECT_TRUE(UINT16_MAX <= UINTMAX_MAX);
    EXPECT_TRUE(UINT32_MAX <= UINTMAX_MAX);
    EXPECT_TRUE(UINT64_MAX <= UINTMAX_MAX);
    EXPECT_TRUE(UINTMAX_MAX >= ULLONG_MAX);
    EXPECT_TRUE(UINTMAX_MAX >= ULONG_MAX);
}

UTEST_TEST_SUITE(stdint){
    UTEST_RUN_TEST_CASE(fixed_width_types);
    UTEST_RUN_TEST_CASE(least_types);
    UTEST_RUN_TEST_CASE(fast_types);
    UTEST_RUN_TEST_CASE(max_types);
    UTEST_RUN_TEST_CASE(ptr_types);
    UTEST_RUN_TEST_CASE(size_types);
    UTEST_RUN_TEST_CASE(constants);
    UTEST_RUN_TEST_CASE(relationships);
}
