#include <stdlib.h>
#include <stdint.h>
#include <stdalign.h>
#include <stddef.h>
#include <utest.h>

// make sure even the old standard has max_align_t
#if QLIBC_ISO_C_VERSION < ISO_C_STANDARD_C11
#define max_align_t long double
#endif

#define NAMESPACE_BEGIN {
#define NAMESPACE_END }

UTEST_TEST_CASE(malloc){
NAMESPACE_BEGIN
    void * ptr = NULL;
    for (size_t i = 1; i < 1024; i*=2){
        ptr = malloc(i);
        EXPECT_NOT_NULL(ptr);
        EXPECT_EQUAL_UINT64((uintptr_t)ptr % alignof(max_align_t), 0);
        free(ptr);
    }
NAMESPACE_END
}