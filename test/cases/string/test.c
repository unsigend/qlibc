#include <utest.h>

// character array examination
#include "memory/test_memchr.h"
#include "memory/test_memcmp.h"
#include "memory/test_memcpy.h"
#include "memory/test_memmove.h"
#include "memory/test_memset.h"

// string manipulation
#include "mani/test_strcat.h"
#include "mani/test_strcpy.h"
#include "mani/test_strncat.h"
#include "mani/test_strncpy.h"
#include "mani/test_strxfrm.h"

// string examination
#include "exam/test_strchr.h"
#include "exam/test_strcmp.h"
#include "exam/test_strcoll.h"
#include "exam/test_strcspn.h"
#include "exam/test_strlen.h"
#include "exam/test_strncmp.h"
#include "exam/test_strpbrk.h"
#include "exam/test_strrchr.h"
#include "exam/test_strspn.h"
#include "exam/test_strstr.h"
#include "exam/test_strtok.h"

UTEST_TEST_SUITE(string) {
  UTEST_RUN_TEST_CASE(memchr);
  UTEST_RUN_TEST_CASE(memcmp);
  UTEST_RUN_TEST_CASE(memcpy);
  UTEST_RUN_TEST_CASE(memmove);
  UTEST_RUN_TEST_CASE(memset);
  UTEST_RUN_TEST_CASE(strcpy);
  UTEST_RUN_TEST_CASE(strncpy);
  UTEST_RUN_TEST_CASE(strcat);
  UTEST_RUN_TEST_CASE(strncat);
  UTEST_RUN_TEST_CASE(strxfrm);
  UTEST_RUN_TEST_CASE(strlen);
  UTEST_RUN_TEST_CASE(strcmp);
  UTEST_RUN_TEST_CASE(strncmp);
  UTEST_RUN_TEST_CASE(strcoll);
  UTEST_RUN_TEST_CASE(strchr);
  UTEST_RUN_TEST_CASE(strrchr);
  UTEST_RUN_TEST_CASE(strspn);
  UTEST_RUN_TEST_CASE(strcspn);
  UTEST_RUN_TEST_CASE(strpbrk);
  UTEST_RUN_TEST_CASE(strstr);
  UTEST_RUN_TEST_CASE(strtok);
}