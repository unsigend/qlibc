#include <stdarg.h>
#include <utest.h>

static void sum_ints(int *result, int count, ...) {
  va_list args;
  va_start(args, count);
  *result = 0;
  for (int i = 0; i < count; i++) {
    *result += va_arg(args, int);
  }
  va_end(args);
}

static void modify_ints(int *a, int *b, int *c, ...) {
  va_list args;
  va_start(args, c);
  *a = va_arg(args, int);
  *b = va_arg(args, int);
  *c = va_arg(args, int);
  va_end(args);
}

static void sum_doubles(double *result, int count, ...) {
  va_list args;
  va_start(args, count);
  *result = 0.0;
  for (int i = 0; i < count; i++) {
    *result += va_arg(args, double);
  }
  va_end(args);
}

static void modify_chars(char *a, char *b, ...) {
  va_list args;
  va_start(args, b);
  *a = va_arg(args, int);
  *b = va_arg(args, int);
  va_end(args);
}

static void modify_pointers(int **a, int **b, ...) {
  va_list args;
  va_start(args, b);
  *a = va_arg(args, int *);
  *b = va_arg(args, int *);
  va_end(args);
}

static void va_copy_test(int *result, int count, ...) {
  va_list args1, args2;
  va_start(args1, count);
  va_copy(args2, args1);
  *result = 0;
  for (int i = 0; i < count; i++) {
    *result += va_arg(args1, int);
  }
  int sum2 = 0;
  for (int i = 0; i < count; i++) {
    sum2 += va_arg(args2, int);
  }
  va_end(args1);
  va_end(args2);
  *result = (*result == sum2) ? *result : -1;
}

UTEST_TEST_CASE(va_start_va_arg_va_end) {
  {
    int result = 0;
    sum_ints(&result, 3, 1, 2, 3);
    EXPECT_EQUAL_INT(result, 6);
  }

  {
    int result = 0;
    sum_ints(&result, 5, 10, 20, 30, 40, 50);
    EXPECT_EQUAL_INT(result, 150);
  }

  {
    int result = 0;
    sum_ints(&result, 1, 42);
    EXPECT_EQUAL_INT(result, 42);
  }

  {
    int result = 0;
    sum_ints(&result, 0);
    EXPECT_EQUAL_INT(result, 0);
  }
}

UTEST_TEST_CASE(va_modify_pointers) {
  {
    int a = 0, b = 0, c = 0;
    modify_ints(&a, &b, &c, 10, 20, 30);
    EXPECT_EQUAL_INT(a, 10);
    EXPECT_EQUAL_INT(b, 20);
    EXPECT_EQUAL_INT(c, 30);
  }

  {
    int x = 0, y = 0, z = 0;
    modify_ints(&x, &y, &z, 100, 200, 300);
    EXPECT_EQUAL_INT(x, 100);
    EXPECT_EQUAL_INT(y, 200);
    EXPECT_EQUAL_INT(z, 300);
  }
}

UTEST_TEST_CASE(va_different_types) {
  {
    double result = 0.0;
    sum_doubles(&result, 3, 1.5, 2.5, 3.5);
    EXPECT_TRUE(result >= 7.4 && result <= 7.6);
  }

  {
    char a = 0, b = 0;
    modify_chars(&a, &b, 'A', 'B');
    EXPECT_EQUAL_INT(a, 'A');
    EXPECT_EQUAL_INT(b, 'B');
  }

  {
    int val1 = 100, val2 = 200;
    int *ptr1 = NULL, *ptr2 = NULL;
    modify_pointers(&ptr1, &ptr2, &val1, &val2);
    EXPECT_NOT_NULL(ptr1);
    EXPECT_NOT_NULL(ptr2);
    EXPECT_EQUAL_INT(*ptr1, 100);
    EXPECT_EQUAL_INT(*ptr2, 200);
  }
}

UTEST_TEST_CASE(va_copy) {
  {
    int result = 0;
    va_copy_test(&result, 3, 1, 2, 3);
    EXPECT_EQUAL_INT(result, 6);
  }

  {
    int result = 0;
    va_copy_test(&result, 4, 5, 10, 15, 20);
    EXPECT_EQUAL_INT(result, 50);
  }

  {
    int result = 0;
    va_copy_test(&result, 1, 42);
    EXPECT_EQUAL_INT(result, 42);
  }
}

UTEST_TEST_CASE(va_multiple_calls) {
  {
    int result1 = 0, result2 = 0, result3 = 0;
    sum_ints(&result1, 2, 1, 2);
    sum_ints(&result2, 2, 3, 4);
    sum_ints(&result3, 2, 5, 6);
    EXPECT_EQUAL_INT(result1, 3);
    EXPECT_EQUAL_INT(result2, 7);
    EXPECT_EQUAL_INT(result3, 11);
  }

  {
    int a1 = 0, b1 = 0, c1 = 0;
    int a2 = 0, b2 = 0, c2 = 0;
    modify_ints(&a1, &b1, &c1, 1, 2, 3);
    modify_ints(&a2, &b2, &c2, 4, 5, 6);
    EXPECT_EQUAL_INT(a1, 1);
    EXPECT_EQUAL_INT(b1, 2);
    EXPECT_EQUAL_INT(c1, 3);
    EXPECT_EQUAL_INT(a2, 4);
    EXPECT_EQUAL_INT(b2, 5);
    EXPECT_EQUAL_INT(c2, 6);
  }
}

UTEST_TEST_SUITE(stdarg) {
  UTEST_RUN_TEST_CASE(va_start_va_arg_va_end);
  UTEST_RUN_TEST_CASE(va_modify_pointers);
  UTEST_RUN_TEST_CASE(va_different_types);
  UTEST_RUN_TEST_CASE(va_copy);
  UTEST_RUN_TEST_CASE(va_multiple_calls);
}
