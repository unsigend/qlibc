#include "common.h"
#include <stdint.h>

/* Test sscanf with %p: basic, %* (no width/length for pointers). */
UTEST_TEST_CASE(in_p)
{
  char buf[BUFSZ];
  int n;
  void *p;

  {
    int var;
    n = snprintf(buf, BUFSZ, "%p", (void *)&var);
  EXPECT_GREATER_INT(n, 2);
    void *q;
    n = sscanf(buf, "%p", &q);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_UINT64((uintptr_t)&var, (uintptr_t)q);
  }
  {
    char cvar;
    n = snprintf(buf, BUFSZ, "%p", (void *)&cvar);
  EXPECT_GREATER_INT(n, 2);
    void *q;
    n = sscanf(buf, "%p", &q);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_UINT64((uintptr_t)&cvar, (uintptr_t)q);
  }

  n = sscanf("0x0", "%p", &p);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_NULL(p);

  n = sscanf("0x1", "%p", &p);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_UINT64((uintptr_t)p, 1);

  n = sscanf("0x10", "%p", &p);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_UINT64((uintptr_t)p, 16);

  n = sscanf("0xdeadbeef", "%p", &p);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_UINT64((uintptr_t)p, 0xdeadbeef);

  n = sscanf("  0x20", "%p", &p);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_UINT64((uintptr_t)p, 32);

  n = sscanf("(nil)", "%p", &p);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_NULL(p);

  n = sscanf("", "%p", &p);
  EXPECT_EQUAL_INT(n, -1);

  n = sscanf("   ", "%p", &p);
  EXPECT_EQUAL_INT(n, -1);

  n = sscanf("x0x10", "%p", &p);
  EXPECT_EQUAL_INT(n, 0);

  n = sscanf("addr=0x10", "addr=%p", &p);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_UINT64((uintptr_t)p, 16);

  {
    int var;
    char cvar;
    n = snprintf(buf, BUFSZ, "%p %p", (void *)&var, (void *)&cvar);
  EXPECT_GREATER_INT(n, 5);
    void *p1, *p2;
    n = sscanf(buf, "%p %p", &p1, &p2);
  EXPECT_EQUAL_INT(n, 2);
  EXPECT_EQUAL_UINT64((uintptr_t)&var, (uintptr_t)p1);
  EXPECT_EQUAL_UINT64((uintptr_t)&cvar, (uintptr_t)p2);
  }
  {
    void *p2;
    n = sscanf("0x10 0x20", "%p %p", &p, &p2);
  EXPECT_EQUAL_INT(n, 2);
  EXPECT_EQUAL_UINT64((uintptr_t)p, 16);
  EXPECT_EQUAL_UINT64((uintptr_t)p2, 32);
  }

  n = sscanf("0x10xxx", "%p", &p);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_UINT64((uintptr_t)p, 16);

  {
    int arr[4];
    n = snprintf(buf, BUFSZ, "%p", (void *)&arr[0]);
    void *q;
    n = sscanf(buf, "%p", &q);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_UINT64((uintptr_t)&arr[0], (uintptr_t)q);
  }
  {
    void *q;
    n = sscanf("0x10 0x20", "%*p %p", &q);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_UINT64((uintptr_t)q, 32);
  }
}
