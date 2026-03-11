#include "common.h"
#include <limits.h>

/* Test sscanf with %o: basic, width, %*, length (h,hh,l,ll). */
UTEST_TEST_CASE(in_o)
{
  int n;
  unsigned u;

  n = sscanf("0", "%o", &u);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT(u, 0);

  n = sscanf("1", "%o", &u);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT(u, 1);

  n = sscanf("7", "%o", &u);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT(u, 7);

  n = sscanf("10", "%o", &u);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT(u, 8);

  n = sscanf("12", "%o", &u);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT(u, 10);

  n = sscanf("77", "%o", &u);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT(u, 63);

  n = sscanf("100", "%o", &u);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT(u, 64);

  n = sscanf("777", "%o", &u);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT(u, 511);

  n = sscanf("0777", "%o", &u);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT(u, 511);

  n = sscanf("  77", "%o", &u);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT(u, 63);

  n = sscanf("037777777777", "%o", &u);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT(u, UINT_MAX);

  n = sscanf("8", "%o", &u);
  EXPECT_EQUAL_INT(n, 0);

  n = sscanf("08", "%o", &u);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT(u, 0);

  n = sscanf("x77", "%o", &u);
  EXPECT_EQUAL_INT(n, 0);

  n = sscanf("", "%o", &u);
  EXPECT_EQUAL_INT(n, -1);

  n = sscanf("   ", "%o", &u);
  EXPECT_EQUAL_INT(n, -1);

  n = sscanf("77abc", "%o", &u);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT(u, 63);

  n = sscanf("n=77", "n=%o", &u);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT(u, 63);

  {
    unsigned u2;
    n = sscanf("10 20", "%o %o", &u, &u2);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_INT(u, 8);
    EXPECT_EQUAL_INT(u2, 16);
  }

  n = sscanf("12345", "%3o", &u);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT(u, 83);

  {
    unsigned long lu;
    n = sscanf("77", "%lo", &lu);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(lu, 63);
  }
  {
    unsigned long long llu;
    n = sscanf("77", "%llo", &llu);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(llu, 63);
  }
  {
    unsigned short hu;
    n = sscanf("177", "%ho", &hu);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(hu, 127);
  }
  {
    unsigned char hhu;
    n = sscanf("377", "%hho", &hhu);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(hhu, 0xff);
  }
  {
    unsigned u2;
    n = sscanf("10 20", "%*o %o", &u2);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u2, 16);
  }
  {
    unsigned u2;
    n = sscanf("123 77", "%*3o %o", &u2);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u2, 63);
  }
}
