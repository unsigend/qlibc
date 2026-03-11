#include "common.h"

/* Test sscanf literal matching only (no conversion specifiers). */
UTEST_TEST_CASE(in)
{
  int n;

  n = sscanf("", "");
  EXPECT_EQUAL_INT(n, 0);

  n = sscanf("x", "x");
  EXPECT_EQUAL_INT(n, 0);

  n = sscanf("xy", "xy");
  EXPECT_EQUAL_INT(n, 0);

  n = sscanf("hello", "hello");
  EXPECT_EQUAL_INT(n, 0);

  n = sscanf("a b", "a b");
  EXPECT_EQUAL_INT(n, 0);

  n = sscanf("x", "y");
  EXPECT_EQUAL_INT(n, 0);

  n = sscanf("", "x");
  EXPECT_EQUAL_INT(n, -1);

  n = sscanf("x", "");
  EXPECT_EQUAL_INT(n, 0);

  n = sscanf("x y", "x y");
  EXPECT_EQUAL_INT(n, 0);

  n = sscanf("%", "%%");
  EXPECT_EQUAL_INT(n, 0);

  n = sscanf("%%", "%%%%");
  EXPECT_EQUAL_INT(n, 0);

  n = sscanf("50%", "50%%");
  EXPECT_EQUAL_INT(n, 0);

  n = sscanf("x%y", "x%%y");
  EXPECT_EQUAL_INT(n, 0);

  n = sscanf("", "%%");
  EXPECT_EQUAL_INT(n, -1);

  n = sscanf("x", "%%");
  EXPECT_EQUAL_INT(n, 0);
}
