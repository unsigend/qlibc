#include <stdalign.h>
#include <stdint.h>
#include <stdlib.h>
#include <utest.h>

#define IS_ALIGNED(PTR, ALIGNMENT) (((uintptr_t)(PTR) & ((ALIGNMENT) - 1)) == 0)
#define IS_MAX_ALIGNED(PTR) IS_ALIGNED((PTR), (alignof(max_align_t)))

#define PTRS_COUNT 128

UTEST_TEST_CASE(malloc) {
  void *ptrs[PTRS_COUNT];
  for (size_t i = 1; i < PTRS_COUNT; i++) {
    ptrs[i] = malloc(i);
    EXPECT_TRUE(ptrs[i]);
    EXPECT_TRUE(IS_MAX_ALIGNED(ptrs[i]));
  }

  for (size_t i = 1; i < PTRS_COUNT; i++) {
    free(ptrs[i]);
  }

  {
    size_t sz = 200 * 1024;
    unsigned char *p = (unsigned char *)malloc(sz);
    EXPECT_NOT_NULL(p);
    EXPECT_TRUE(IS_MAX_ALIGNED(p));
    p[0] = 0xAB;
    p[sz / 2] = 0xCD;
    p[sz - 1] = 0xEF;
    EXPECT_TRUE(p[0] == 0xAB);
    EXPECT_TRUE(p[sz / 2] == 0xCD);
    EXPECT_TRUE(p[sz - 1] == 0xEF);
    free(p);
  }
}

UTEST_TEST_CASE(calloc) {
  {
    int *p = (int *)calloc(16, sizeof(int));
    EXPECT_NOT_NULL(p);
    EXPECT_TRUE(IS_MAX_ALIGNED(p));
    for (int i = 0; i < 16; i++)
      EXPECT_TRUE(p[i] == 0);
    free(p);
  }

  {
    void *p = calloc(0, sizeof(int));
#ifdef _QLIBC_SOURCE
    EXPECT_NULL(p);
#endif
  }

  {
    void *p = calloc(16, 0);
#ifdef _QLIBC_SOURCE
    EXPECT_NULL(p);
#endif
  }

  {
    size_t n = 256 * 1024;
    unsigned char *p = (unsigned char *)calloc(n, 1);
    EXPECT_NOT_NULL(p);
    EXPECT_TRUE(IS_MAX_ALIGNED(p));
    EXPECT_TRUE(p[0] == 0);
    EXPECT_TRUE(p[n / 2] == 0);
    EXPECT_TRUE(p[n - 1] == 0);
    free(p);
  }
}

UTEST_TEST_CASE(realloc) {
  {
    void *p = realloc(NULL, 64);
    EXPECT_NOT_NULL(p);
    EXPECT_TRUE(IS_MAX_ALIGNED(p));
    free(p);
  }

  {
    void *p = malloc(64);
    EXPECT_NOT_NULL(p);
    void *q = realloc(p, 0);
    EXPECT_NULL(q);
  }

  {
    int *p = (int *)malloc(8 * sizeof(int));
    EXPECT_NOT_NULL(p);
    for (int i = 0; i < 8; i++)
      p[i] = i;
    int *q = (int *)realloc(p, 16 * sizeof(int));
    EXPECT_NOT_NULL(q);
    EXPECT_TRUE(IS_MAX_ALIGNED(q));
    for (int i = 0; i < 8; i++)
      EXPECT_TRUE(q[i] == i);
    free(q);
  }

  {
    int *p = (int *)malloc(16 * sizeof(int));
    EXPECT_NOT_NULL(p);
    for (int i = 0; i < 16; i++)
      p[i] = i * 2;
    int *q = (int *)realloc(p, 8 * sizeof(int));
    EXPECT_NOT_NULL(q);
    for (int i = 0; i < 8; i++)
      EXPECT_TRUE(q[i] == i * 2);
    free(q);
  }

  {
    size_t small = 200 * 1024;
    size_t large = 400 * 1024;
    unsigned char *p = (unsigned char *)malloc(small);
    EXPECT_NOT_NULL(p);
    p[0] = 0x11;
    p[small / 2] = 0x22;
    p[small - 1] = 0x33;
    unsigned char *q = (unsigned char *)realloc(p, large);
    EXPECT_NOT_NULL(q);
    EXPECT_TRUE(IS_MAX_ALIGNED(q));
    EXPECT_TRUE(q[0] == 0x11);
    EXPECT_TRUE(q[small / 2] == 0x22);
    EXPECT_TRUE(q[small - 1] == 0x33);
    free(q);
  }
}