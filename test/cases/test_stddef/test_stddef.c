#include <stddef.h>
#include <utest.h>
#include <stdint.h>

UTEST_TEST_CASE(stddef_types){
#if defined(__i386__) || defined(__arm__)
    EXPECT_EQUAL_UINT(sizeof(ptrdiff_t), 4);
    EXPECT_EQUAL_UINT(sizeof(size_t), 4);
#elif defined(__x86_64__) || defined(__amd64__)
    EXPECT_EQUAL_UINT(sizeof(ptrdiff_t), 8);
    EXPECT_EQUAL_UINT(sizeof(size_t), 8);
#elif defined(__aarch64__)
    EXPECT_EQUAL_UINT(sizeof(ptrdiff_t), 8);
    EXPECT_EQUAL_UINT(sizeof(size_t), 8);
#endif

#if defined(QLIBC_ISO_C_VERSION) && (QLIBC_ISO_C_VERSION >= ISO_C_STANDARD_C11)
#if defined(__arm__) || defined(__i386__)
    EXPECT_EQUAL_UINT(sizeof(max_align_t), 8);
#else
    EXPECT_EQUAL_UINT(sizeof(max_align_t), 16);
#endif
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
#if defined(__arm__) || defined(__i386__)
    EXPECT_EQUAL_UINT(sizeof(max_align_t), 8);
#else
    EXPECT_EQUAL_UINT(sizeof(max_align_t), 16);
#endif
#endif
}
struct test_struct{
    uint32_t a;
    uint32_t b;
    uint64_t c;
    uint8_t d;
    uint32_t e;
};
struct __attribute__((packed)) test_struct_packed{
    uint32_t a;
    uint32_t b;
    uint64_t c;
    uint8_t d;
    uint32_t e;
};
UTEST_TEST_CASE(stddef_macro){
    EXPECT_EQUAL_UINT((unsigned long)NULL, 0);
    
    EXPECT_EQUAL_UINT(offsetof(struct {int a; int b;}, b), 4);
    EXPECT_EQUAL_UINT(offsetof(struct {int a; int b;}, a), 0);
    EXPECT_EQUAL_UINT(offsetof(struct {int a; int b; int c;}, c), 8);
    EXPECT_EQUAL_UINT(offsetof(struct {int a; int b; int c; int d;}, d), 12);

    EXPECT_EQUAL_UINT(offsetof(struct test_struct, a), 0);
    EXPECT_EQUAL_UINT(offsetof(struct test_struct, b), 4);
    EXPECT_EQUAL_UINT(offsetof(struct test_struct, c), 8);
    EXPECT_EQUAL_UINT(offsetof(struct test_struct, d), 16);
    EXPECT_EQUAL_UINT(offsetof(struct test_struct, e), 20);
    EXPECT_EQUAL_UINT(sizeof(struct test_struct), 24);

    EXPECT_EQUAL_UINT(offsetof(struct test_struct_packed, a), 0);
    EXPECT_EQUAL_UINT(offsetof(struct test_struct_packed, b), 4);
    EXPECT_EQUAL_UINT(offsetof(struct test_struct_packed, c), 8);
    EXPECT_EQUAL_UINT(offsetof(struct test_struct_packed, d), 16);
    EXPECT_EQUAL_UINT(offsetof(struct test_struct_packed, e), 17);
    EXPECT_EQUAL_UINT(sizeof(struct test_struct_packed), 21);
}
UTEST_TEST_SUITE(stddef){
    UTEST_RUN_TEST_CASE(stddef_types);
    UTEST_RUN_TEST_CASE(stddef_macro);
}