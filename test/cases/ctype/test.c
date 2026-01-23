#include <utest.h>

#include "funcs/test_isalnum.h"
#include "funcs/test_isalpha.h"
#include "funcs/test_isblank.h"
#include "funcs/test_iscntrl.h"
#include "funcs/test_isdigit.h"
#include "funcs/test_isgraph.h"
#include "funcs/test_islower.h"
#include "funcs/test_isprint.h"
#include "funcs/test_ispunct.h"
#include "funcs/test_isspace.h"
#include "funcs/test_isupper.h"
#include "funcs/test_isxdigit.h"
#include "funcs/test_tolower.h"
#include "funcs/test_toupper.h"

UTEST_TEST_SUITE(ctype) {
  UTEST_RUN_TEST_CASE(isalnum);
  UTEST_RUN_TEST_CASE(isalpha);
  UTEST_RUN_TEST_CASE(isblank);
  UTEST_RUN_TEST_CASE(iscntrl);
  UTEST_RUN_TEST_CASE(isdigit);
  UTEST_RUN_TEST_CASE(isgraph);
  UTEST_RUN_TEST_CASE(islower);
  UTEST_RUN_TEST_CASE(isprint);
  UTEST_RUN_TEST_CASE(ispunct);
  UTEST_RUN_TEST_CASE(isspace);
  UTEST_RUN_TEST_CASE(isupper);
  UTEST_RUN_TEST_CASE(isxdigit);
  UTEST_RUN_TEST_CASE(tolower);
  UTEST_RUN_TEST_CASE(toupper);
}