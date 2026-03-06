#include "common.h"
#include <limits.h>
#include <stddef.h>

/* Test sscanf with %u: basic, width, %*, length (h,hh,l,ll,z). */
UTEST_TEST_CASE(in_u) {
  int n;
  unsigned u;

  {
    n = sscanf("0", "%u", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 0);
  }
  {
    n = sscanf("1", "%u", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 1);
  }
  {
    n = sscanf("42", "%u", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 42);
  }
  {
    n = sscanf("  123", "%u", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 123);
  }
  {
    n = sscanf("\t\n  99", "%u", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 99);
  }
  {
    n = sscanf("4294967295", "%u", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, UINT_MAX);
  }
  {
    n = sscanf("1234567890", "%u", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 1234567890);
  }
  {
    n = sscanf("x42", "%u", &u);
    EXPECT_EQUAL_INT(n, 0);
  }
  {
    n = sscanf("", "%u", &u);
    EXPECT_EQUAL_INT(n, -1);
  }
  {
    n = sscanf("   ", "%u", &u);
    EXPECT_EQUAL_INT(n, -1);
  }
  {
    n = sscanf("abc", "%u", &u);
    EXPECT_EQUAL_INT(n, 0);
  }
  {
    n = sscanf("42abc", "%u", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 42);
  }
  {
    n = sscanf("x42", "x%u", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 42);
  }
  {
    unsigned u2;
    n = sscanf("12 34", "%u %u", &u, &u2);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_INT(u, 12);
    EXPECT_EQUAL_INT(u2, 34);
  }
  {
    n = sscanf("42", "%3u", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 42);
  }
  {
    n = sscanf("12345", "%3u", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 123);
  }
  {
    unsigned long lu;
    n = sscanf("42", "%lu", &lu);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(lu, 42);
  }
  {
    unsigned long long llu;
    n = sscanf("42", "%llu", &llu);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(llu, 42);
  }
  {
    unsigned short hu;
    n = sscanf("42", "%hu", &hu);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(hu, 42);
  }
  {
    unsigned char hhu;
    n = sscanf("42", "%hhu", &hhu);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(hhu, 42);
  }
  {
    size_t zu;
    n = sscanf("42", "%zu", &zu);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(zu, 42);
  }
  {
    unsigned u2;
    n = sscanf("1 2", "%*u %u", &u2);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u2, 2);
  }
  {
    unsigned u2;
    n = sscanf("12345", "%*3u %u", &u2);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u2, 45);
  }
}
