#include <stdint.h>
#include <utest.h>

UTEST_TEST_CASE(fixed_width_types){
    EXPECT_EQUAL_UINT64(sizeof(int8_t), 1);
    EXPECT_EQUAL_UINT64(sizeof(int16_t), 2);
    EXPECT_EQUAL_UINT64(sizeof(int32_t), 4);
    EXPECT_EQUAL_UINT64(sizeof(int64_t), 8);

    EXPECT_EQUAL_UINT64(sizeof(uint8_t), 1);
    EXPECT_EQUAL_UINT64(sizeof(uint16_t), 2);
    EXPECT_EQUAL_UINT64(sizeof(uint32_t), 4);
    EXPECT_EQUAL_UINT64(sizeof(uint64_t), 8);
}

UTEST_TEST_CASE(integer_types){
#if defined(__i386__) || defined(__arm__)
    EXPECT_EQUAL_UINT64(sizeof(intptr_t), 4);
    EXPECT_EQUAL_UINT64(sizeof(uintptr_t), 4);
#elif defined(__x86_64__) || defined(__amd64__)
    EXPECT_EQUAL_UINT64(sizeof(intptr_t), 8);
    EXPECT_EQUAL_UINT64(sizeof(uintptr_t), 8);
#elif defined(__aarch64__)
    EXPECT_EQUAL_UINT64(sizeof(intptr_t), 8);
    EXPECT_EQUAL_UINT64(sizeof(uintptr_t), 8);
#endif
    EXPECT_EQUAL_UINT64(sizeof(intmax_t), 8);
    EXPECT_EQUAL_UINT64(sizeof(uintmax_t), 8);
}

UTEST_TEST_CASE(fast_least_types){
    EXPECT_EQUAL_UINT64(sizeof(int_least8_t), 1);
    EXPECT_EQUAL_UINT64(sizeof(int_least16_t), 2);
    EXPECT_EQUAL_UINT64(sizeof(int_least32_t), 4);
    EXPECT_EQUAL_UINT64(sizeof(int_least64_t), 8);

    EXPECT_EQUAL_UINT64(sizeof(uint_least8_t), 1);
    EXPECT_EQUAL_UINT64(sizeof(uint_least16_t), 2);
    EXPECT_EQUAL_UINT64(sizeof(uint_least32_t), 4);
    EXPECT_EQUAL_UINT64(sizeof(uint_least64_t), 8);

#if defined(__i386__) || defined(__arm__)
    EXPECT_EQUAL_UINT64(sizeof(int_fast8_t), 1);
    EXPECT_EQUAL_UINT64(sizeof(int_fast16_t), 4);
    EXPECT_EQUAL_UINT64(sizeof(int_fast32_t), 4);
    EXPECT_EQUAL_UINT64(sizeof(int_fast64_t), 8);

    EXPECT_EQUAL_UINT64(sizeof(uint_fast8_t), 1);
    EXPECT_EQUAL_UINT64(sizeof(uint_fast16_t), 4);
    EXPECT_EQUAL_UINT64(sizeof(uint_fast32_t), 4);
    EXPECT_EQUAL_UINT64(sizeof(uint_fast64_t), 8);
#elif defined(__x86_64__) || defined(__amd64__)
    EXPECT_EQUAL_UINT64(sizeof(int_fast8_t), 1);
    EXPECT_EQUAL_UINT64(sizeof(int_fast16_t), 8);
    EXPECT_EQUAL_UINT64(sizeof(int_fast32_t), 8);
    EXPECT_EQUAL_UINT64(sizeof(int_fast64_t), 8);

    EXPECT_EQUAL_UINT64(sizeof(uint_fast8_t), 1);
    EXPECT_EQUAL_UINT64(sizeof(uint_fast16_t), 8);
    EXPECT_EQUAL_UINT64(sizeof(uint_fast32_t), 8);
    EXPECT_EQUAL_UINT64(sizeof(uint_fast64_t), 8);
#elif defined(__aarch64__)
    EXPECT_EQUAL_UINT64(sizeof(int_fast8_t), 1);
    EXPECT_EQUAL_UINT64(sizeof(int_fast16_t), 2);
    EXPECT_EQUAL_UINT64(sizeof(int_fast32_t), 4);
    EXPECT_EQUAL_UINT64(sizeof(int_fast64_t), 8);

    EXPECT_EQUAL_UINT64(sizeof(uint_fast8_t), 1);
    EXPECT_EQUAL_UINT64(sizeof(uint_fast16_t), 2);
    EXPECT_EQUAL_UINT64(sizeof(uint_fast32_t), 4);
    EXPECT_EQUAL_UINT64(sizeof(uint_fast64_t), 8);
#endif
}
UTEST_TEST_SUITE(stdint){
    UTEST_RUN_TEST_CASE(fixed_width_types);
    UTEST_RUN_TEST_CASE(integer_types);
    UTEST_RUN_TEST_CASE(fast_least_types);
}