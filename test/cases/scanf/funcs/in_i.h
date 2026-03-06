#include "common.h"
#include <limits.h>

/* Test sscanf with %i: basic, width, %*, length (h,hh,l,ll). */
UTEST_TEST_CASE(in_i) {
  int n, d;

  {
    n = sscanf("42", "%i", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 42);
  }
  {
    n = sscanf("0", "%i", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 0);
  }
  {
    n = sscanf("-42", "%i", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, -42);
  }
  {
    n = sscanf("+99", "%i", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 99);
  }

  {
    n = sscanf("0x10", "%i", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 16);
  }
  {
    n = sscanf("0X10", "%i", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 16);
  }
  {
    n = sscanf("0x1a", "%i", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 26);
  }
  {
    n = sscanf("0xff", "%i", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 255);
  }
  {
    n = sscanf("0xFF", "%i", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 255);
  }
  {
    n = sscanf("-0x10", "%i", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, -16);
  }
  {
    n = sscanf("+0x20", "%i", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 32);
  }
  {
    n = sscanf("  0x1a", "%i", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 26);
  }
  {
    n = sscanf("0x7fffffff", "%i", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, INT_MAX);
  }

  {
    n = sscanf("010", "%i", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 8);
  }
  {
    n = sscanf("012", "%i", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 10);
  }
  {
    n = sscanf("07", "%i", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 7);
  }
  {
    n = sscanf("08", "%i", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 0);
  }
  {
    n = sscanf("0177", "%i", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 127);
  }
  {
    n = sscanf("-010", "%i", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, -8);
  }
  {
    n = sscanf("  077", "%i", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 63);
  }

  {
    n = sscanf("x42", "%i", &d);
    EXPECT_EQUAL_INT(n, 0);
  }
  {
    n = sscanf("", "%i", &d);
    EXPECT_EQUAL_INT(n, -1);
  }
  {
    n = sscanf("   ", "%i", &d);
    EXPECT_EQUAL_INT(n, -1);
  }
  {
    n = sscanf("0x", "%i", &d);
    EXPECT_EQUAL_INT(n, 1);
  }
  {
    n = sscanf("0xg", "%i", &d);
    EXPECT_EQUAL_INT(n, 1);
  }
  {
    n = sscanf("42abc", "%i", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 42);
  }
  {
    n = sscanf("0x10g", "%i", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 16);
  }

  {
    n = sscanf("n=0x1a", "n=%i", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 26);
  }
  {
    int d2, d3;
    n = sscanf("0x10 010 10", "%i %i %i", &d, &d2, &d3);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_INT(d, 16);
    EXPECT_EQUAL_INT(d2, 8);
    EXPECT_EQUAL_INT(d3, 10);
  }

  {
    n = sscanf("0x10", "%5i", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 16);
  }
  {
    n = sscanf("0x123", "%3i", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 1);
  }
  {
    n = sscanf("010", "%4i", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 8);
  }

  {
    long ld;
    n = sscanf("0x10", "%li", &ld);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(ld, 16);
  }
  {
    long ld;
    n = sscanf("010", "%li", &ld);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(ld, 8);
  }
  {
    long long lld;
    n = sscanf("0x10", "%lli", &lld);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(lld, 16);
  }
  {
    short hd;
    n = sscanf("0x10", "%hi", &hd);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(hd, 16);
  }
  {
    signed char hhd;
    n = sscanf("0x1a", "%hhi", &hhd);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(hhd, 26);
  }
  {
    int d2;
    n = sscanf("1 2", "%*i %i", &d2);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d2, 2);
  }
  {
    int d2;
    n = sscanf("0x10 20", "%*i %i", &d2);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d2, 20);
  }
  {
    int d2;
    n = sscanf("12345", "%*3i %i", &d2);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d2, 45);
  }
}
