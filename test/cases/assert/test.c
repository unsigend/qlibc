#include <assert.h>
#include <utest.h>

UTEST_TEST_CASE(assert_defined) {
  int x = 5;
  assert(x == 5);
  assert(x > 0);
  assert(x != 0);
  assert(1);
  assert(1 == 1);
  assert(2 + 2 == 4);
}

UTEST_TEST_CASE(assert_expressions) {
  {
    int a = 10;
    int b = 20;
    assert(a < b);
    assert(a != b);
    assert(a + b == 30);
  }

  {
    char c = 'A';
    assert(c != '\0');
    assert(c == 'A');
  }

  {
    int arr[5] = {1, 2, 3, 4, 5};
    assert(arr[0] == 1);
    assert(arr[4] == 5);
    assert(sizeof(arr) == 5 * sizeof(int));
  }

  {
    int *ptr = (int *)0x1000;
    assert(ptr != NULL);
    ptr = NULL;
    assert(ptr == NULL);
  }

  {
    int x = 0;
    assert(x == 0);
    x = 1;
    assert(x != 0);
    assert(x);
  }
}

UTEST_TEST_CASE(assert_void_result) {
  {
    int result = 0;
    assert(1);
    result = 1;
    EXPECT_EQUAL_INT(result, 1);
  }

  {
    int x = 5;
    assert(x == 5);
    assert(x > 0);
    assert(x < 100);
  }
}

UTEST_TEST_CASE(assert_ndebug) {
#undef assert
#define NDEBUG
#include <assert.h>

  assert(1);
  assert(0);
  assert(1 == 0);
  assert(NULL != NULL);

  {
    assert(1 == 1);
    assert(2 != 1);
    assert(100 > 50);
  }

#undef NDEBUG
#undef assert
}

UTEST_TEST_SUITE(assert) {
  UTEST_RUN_TEST_CASE(assert_defined);
  UTEST_RUN_TEST_CASE(assert_expressions);
  UTEST_RUN_TEST_CASE(assert_void_result);
  UTEST_RUN_TEST_CASE(assert_ndebug);
}