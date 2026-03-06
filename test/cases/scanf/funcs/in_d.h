#include "common.h"
#include <limits.h>

/* Test sscanf with %d: basic, width, %*, length (h,hh,l,ll). */
UTEST_TEST_CASE(in_d) {
  int n, d;

  {
    n = sscanf("0", "%d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 0);
  }
  {
    n = sscanf("1", "%d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 1);
  }
  {
    n = sscanf("42", "%d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 42);
  }
  {
    n = sscanf("-1", "%d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, -1);
  }
  {
    n = sscanf("-42", "%d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, -42);
  }
  {
    n = sscanf("+99", "%d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 99);
  }
  {
    n = sscanf("  123", "%d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 123);
  }
  {
    n = sscanf("\t\n  -7", "%d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, -7);
  }
  {
    n = sscanf("2147483647", "%d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, INT_MAX);
  }
  {
    n = sscanf("-2147483648", "%d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, INT_MIN);
  }
  {
    n = sscanf("9", "%d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 9);
  }
  {
    n = sscanf("99", "%d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 99);
  }
  {
    n = sscanf("100", "%d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 100);
  }
  {
    n = sscanf("-9", "%d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, -9);
  }
  {
    n = sscanf("-100", "%d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, -100);
  }
  {
    n = sscanf("1234567890", "%d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 1234567890);
  }
  {
    n = sscanf("-1234567890", "%d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, -1234567890);
  }

  {
    n = sscanf("x42", "%d", &d);
    EXPECT_EQUAL_INT(n, 0);
  }
  {
    n = sscanf("", "%d", &d);
    EXPECT_EQUAL_INT(n, -1);
  }
  {
    n = sscanf("   ", "%d", &d);
    EXPECT_EQUAL_INT(n, -1);
  }
  {
    n = sscanf("abc", "%d", &d);
    EXPECT_EQUAL_INT(n, 0);
  }
  {
    n = sscanf("42abc", "%d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 42);
  }
  {
    n = sscanf("0x10", "%d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 0);
  }

  {
    n = sscanf("x42", "x%d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 42);
  }
  {
    n = sscanf("x42y", "x%dy", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 42);
  }
  {
    n = sscanf("n=42", "n=%d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 42);
  }
  {
    int d2;
    n = sscanf("12 34", "%d %d", &d, &d2);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_INT(d, 12);
    EXPECT_EQUAL_INT(d2, 34);
  }
  {
    int d2, d3;
    n = sscanf("1 2 3", "%d%d%d", &d, &d2, &d3);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_INT(d, 1);
    EXPECT_EQUAL_INT(d2, 2);
    EXPECT_EQUAL_INT(d3, 3);
  }
  {
    int d2;
    n = sscanf("1", "%d %d", &d, &d2);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 1);
  }

  {
    n = sscanf("42", "%3d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 42);
  }
  {
    n = sscanf("12345", "%3d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 123);
  }
  {
    n = sscanf("12345", "%5d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 12345);
  }
  {
    n = sscanf("-99", "%5d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, -99);
  }
  {
    n = sscanf("-123", "%4d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, -123);
  }
  {
    n = sscanf("12", "%10d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 12);
  }
  {
    n = sscanf("  42", "%5d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 42);
  }

  {
    long ld;
    n = sscanf("42", "%ld", &ld);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(ld, 42);
  }
  {
    long ld;
    n = sscanf("-123", "%ld", &ld);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(ld, -123);
  }
  {
    long long lld;
    n = sscanf("42", "%lld", &lld);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(lld, 42);
  }
  {
    long long lld;
    n = sscanf("-123", "%lld", &lld);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(lld, -123);
  }
  {
    short hd;
    n = sscanf("42", "%hd", &hd);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(hd, 42);
  }
  {
    short hd;
    n = sscanf("-123", "%hd", &hd);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(hd, -123);
  }
  {
    signed char hhd;
    n = sscanf("42", "%hhd", &hhd);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(hhd, 42);
  }
  {
    int d2;
    n = sscanf("1 2", "%*d %d", &d2);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d2, 2);
  }
  {
    int d2;
    n = sscanf("99 42", "%*d %d", &d2);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d2, 42);
  }
  {
    int d2;
    n = sscanf("12345", "%*3d %d", &d2);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d2, 45);
  }
}
