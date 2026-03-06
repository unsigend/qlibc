#include "common.h"
#include <limits.h>
#include <stddef.h>

/* Test sscanf with %x/%X: basic, width, %*, length (h,hh,l,ll,z). */
UTEST_TEST_CASE(in_x) {
  int n;
  unsigned u;

  {
    n = sscanf("0", "%x", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 0);
  }
  {
    n = sscanf("1", "%x", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 1);
  }
  {
    n = sscanf("a", "%x", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 10);
  }
  {
    n = sscanf("A", "%x", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 10);
  }
  {
    n = sscanf("f", "%x", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 15);
  }
  {
    n = sscanf("F", "%X", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 15);
  }
  {
    n = sscanf("10", "%x", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 16);
  }
  {
    n = sscanf("ff", "%x", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 255);
  }
  {
    n = sscanf("FF", "%X", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 255);
  }
  {
    n = sscanf("0x10", "%x", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 16);
  }
  {
    n = sscanf("0X1a", "%x", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 26);
  }
  {
    n = sscanf("0XABC", "%X", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 0xabc);
  }
  {
    n = sscanf("abcdef", "%x", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 0xabcdef);
  }
  {
    n = sscanf("ABCDEF", "%x", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 0xabcdef);
  }
  {
    n = sscanf("aBcDeF", "%x", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 0xabcdef);
  }
  {
    n = sscanf("DEADBEEF", "%x", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 0xdeadbeef);
  }
  {
    n = sscanf("  0x20", "%x", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 32);
  }
  {
    n = sscanf("  0X20", "%X", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 32);
  }
  {
    n = sscanf("7fffffff", "%x", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, INT_MAX);
  }
  {
    n = sscanf("7FFFFFFF", "%X", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, INT_MAX);
  }
  {
    n = sscanf("ffffffff", "%x", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, UINT_MAX);
  }
  {
    n = sscanf("FFFFFFFF", "%X", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, UINT_MAX);
  }
  {
    n = sscanf("x42", "%x", &u);
    EXPECT_EQUAL_INT(n, 0);
  }
  {
    n = sscanf("", "%x", &u);
    EXPECT_EQUAL_INT(n, -1);
  }
  {
    n = sscanf("   ", "%x", &u);
    EXPECT_EQUAL_INT(n, -1);
  }
  {
    n = sscanf("0x", "%x", &u);
    EXPECT_EQUAL_INT(n, 1);
  }
  {
    n = sscanf("42g", "%x", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 0x42);
  }
  {
    n = sscanf("42G", "%X", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 0x42);
  }
  {
    n = sscanf("n=0x1a", "n=%x", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 26);
  }
  {
    n = sscanf("n=0X1A", "n=%X", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 26);
  }
  {
    unsigned u2;
    n = sscanf("10 ff", "%x %x", &u, &u2);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_INT(u, 16);
    EXPECT_EQUAL_INT(u2, 255);
  }
  {
    unsigned u2;
    n = sscanf("10 FF", "%X %X", &u, &u2);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_INT(u, 16);
    EXPECT_EQUAL_INT(u2, 255);
  }
  {
    n = sscanf("0x123", "%5x", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 0x123);
  }
  {
    unsigned long lu;
    n = sscanf("ff", "%lx", &lu);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(lu, 255);
  }
  {
    unsigned long lu;
    n = sscanf("FF", "%lX", &lu);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(lu, 255);
  }
  {
    unsigned short hu;
    n = sscanf("ff", "%hx", &hu);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(hu, 255);
  }
  {
    unsigned char hhu;
    n = sscanf("ff", "%hhx", &hhu);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(hhu, 255);
  }
  {
    unsigned long long llu;
    n = sscanf("deadbeef", "%llx", &llu);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(llu, 0xdeadbeef);
  }
  {
    size_t zu;
    n = sscanf("ff", "%zx", &zu);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(zu, 255);
  }
  {
    unsigned u2;
    n = sscanf("10 ff", "%*x %x", &u2);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u2, 255);
  }
  {
    unsigned u2;
    n = sscanf("0x123 ab", "%*5x %x", &u2);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u2, 0xab);
  }
}
