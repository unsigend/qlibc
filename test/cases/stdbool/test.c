#include <stdbool.h>
#include <utest.h>

UTEST_TEST_CASE(constants) {
  EXPECT_EQUAL_INT(__bool_true_false_are_defined, 1);
  EXPECT_EQUAL_INT(true, 1);
  EXPECT_EQUAL_INT(false, 0);
  EXPECT_TRUE(true);
  EXPECT_FALSE(false);
}

UTEST_TEST_CASE(macros) {
  bool b1 = true;
  bool b2 = false;

  EXPECT_TRUE(b1);
  EXPECT_FALSE(b2);
  EXPECT_EQUAL_INT(b1, 1);
  EXPECT_EQUAL_INT(b2, 0);

  {
    bool b = true;
    EXPECT_TRUE(b);
    b = false;
    EXPECT_FALSE(b);
  }

  {
    bool b = 1;
    EXPECT_TRUE(b);
    b = 0;
    EXPECT_FALSE(b);
  }

  {
    bool b = 5;
    EXPECT_TRUE(b);
    b = -1;
    EXPECT_TRUE(b);
    b = 0;
    EXPECT_FALSE(b);
  }

  {
    bool b = true;
    int i = b;
    EXPECT_EQUAL_INT(i, 1);
  }

  {
    bool b = false;
    int i = b;
    EXPECT_EQUAL_INT(i, 0);
  }

  {
    int x = 5;
    bool b = x;
    EXPECT_TRUE(b);
  }

  {
    int x = 0;
    bool b = x;
    EXPECT_FALSE(b);
  }

  {
    bool b1 = true;
    bool b2 = true;
    EXPECT_TRUE(b1 == b2);
  }

  {
    bool b1 = false;
    bool b2 = false;
    EXPECT_TRUE(b1 == b2);
  }

  {
    bool b1 = true;
    bool b2 = false;
    EXPECT_TRUE(b1 != b2);
  }

  {
    bool b = true;
    EXPECT_TRUE(b);
    b = !b;
    EXPECT_FALSE(b);
    b = !b;
    EXPECT_TRUE(b);
  }

  {
    bool b1 = true;
    bool b2 = false;
    EXPECT_TRUE(b1 && b1);
    EXPECT_FALSE(b1 && b2);
    EXPECT_FALSE(b2 && b1);
    EXPECT_FALSE(b2 && b2);
  }

  {
    bool b1 = true;
    bool b2 = false;
    EXPECT_TRUE(b1 || b1);
    EXPECT_TRUE(b1 || b2);
    EXPECT_TRUE(b2 || b1);
    EXPECT_FALSE(b2 || b2);
  }

  {
    bool b = true;
    if (b) {
      EXPECT_TRUE(1);
    } else {
      EXPECT_FALSE(1);
    }
  }

  {
    bool b = false;
    if (b) {
      EXPECT_FALSE(1);
    } else {
      EXPECT_TRUE(1);
    }
  }

  {
    bool arr[2] = {true, false};
    EXPECT_TRUE(arr[0]);
    EXPECT_FALSE(arr[1]);
  }

  {
    bool b = sizeof(bool);
    EXPECT_TRUE(b);
  }

  { EXPECT_TRUE(sizeof(bool) == sizeof(_Bool)); }

  {
    _Bool b = 1;
    EXPECT_TRUE(b);
    b = 0;
    EXPECT_FALSE(b);
  }
}

UTEST_TEST_SUITE(stdbool) {
  UTEST_RUN_TEST_CASE(constants);
  UTEST_RUN_TEST_CASE(macros);
}
