#include <stdlib.h>
#include <utest.h>

/* supress warnings */
extern int setenv(const char *name, const char *value, int overwrite);
extern int unsetenv(const char *name);
extern int putenv(char *string);
extern void clearenv(void);

UTEST_TEST_CASE(getenv)
{
  EXPECT_NULL(getenv("QLIBC_T_NONEXISTENT"));
  EXPECT_NULL(getenv(""));
  setenv("QLIBC_T_A", "v", 1);
  EXPECT_NOT_NULL(getenv("QLIBC_T_A"));
  EXPECT_EQUAL_STRING(getenv("QLIBC_T_A"), "v");
  EXPECT_EQUAL_STRING(getenv("QLIBC_T_A"), "v");
  unsetenv("QLIBC_T_A");
  EXPECT_NULL(getenv("QLIBC_T_A"));
}

UTEST_TEST_CASE(putenv)
{
  char s[] = "QLIBC_T_B=val";
  EXPECT_EQUAL_INT(putenv(s), 0);
  EXPECT_EQUAL_STRING(getenv("QLIBC_T_B"), "val");
  unsetenv("QLIBC_T_B");
  setenv("QLIBC_T_B", "first", 1);
  char s2[] = "QLIBC_T_B=second";
  EXPECT_EQUAL_INT(putenv(s2), 0);
  EXPECT_EQUAL_STRING(getenv("QLIBC_T_B"), "second");
  unsetenv("QLIBC_T_B");
  {
    char s3[] = "QLIBC_T_B=";
    EXPECT_EQUAL_INT(putenv(s3), 0);
  }
  EXPECT_EQUAL_STRING(getenv("QLIBC_T_B"), "");
  unsetenv("QLIBC_T_B");
}

UTEST_TEST_CASE(setenv)
{
  EXPECT_EQUAL_INT(setenv("QLIBC_T_C", "v1", 1), 0);
  EXPECT_EQUAL_STRING(getenv("QLIBC_T_C"), "v1");
  setenv("QLIBC_T_C", "v2", 0);
  EXPECT_EQUAL_STRING(getenv("QLIBC_T_C"), "v1");
  setenv("QLIBC_T_C", "v2", 1);
  EXPECT_EQUAL_STRING(getenv("QLIBC_T_C"), "v2");
  unsetenv("QLIBC_T_C");
  EXPECT_EQUAL_INT(setenv("QLIBC_T_C", "x", 1), 0);
  unsetenv("QLIBC_T_C");
  EXPECT_EQUAL_INT(setenv("QLIBC_T_C", "", 1), 0);
  EXPECT_EQUAL_STRING(getenv("QLIBC_T_C"), "");
  unsetenv("QLIBC_T_C");
}

UTEST_TEST_CASE(unsetenv)
{
  setenv("QLIBC_T_D", "x", 1);
  EXPECT_EQUAL_INT(unsetenv("QLIBC_T_D"), 0);
  EXPECT_NULL(getenv("QLIBC_T_D"));
  EXPECT_EQUAL_INT(unsetenv("QLIBC_T_NONEXISTENT"), 0);
  EXPECT_NULL(getenv("QLIBC_T_NONEXISTENT"));
  setenv("QLIBC_T_D", "y", 1);
  EXPECT_EQUAL_INT(unsetenv("QLIBC_T_D"), 0);
  EXPECT_EQUAL_INT(unsetenv("QLIBC_T_D"), 0);
  unsetenv("QLIBC_T_D");
}

UTEST_TEST_CASE(clearenv)
{
  setenv("QLIBC_T_E", "x", 1);
  clearenv();
  EXPECT_NULL(getenv("QLIBC_T_E"));
  EXPECT_EQUAL_INT(putenv("QLIBC_T_E=after"), 0);
  EXPECT_EQUAL_STRING(getenv("QLIBC_T_E"), "after");
  unsetenv("QLIBC_T_E");
  clearenv();
  EXPECT_EQUAL_INT(setenv("QLIBC_T_E", "set", 1), 0);
  EXPECT_EQUAL_STRING(getenv("QLIBC_T_E"), "set");
  unsetenv("QLIBC_T_E");
}
