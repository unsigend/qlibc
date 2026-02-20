#include "funcs/out.h"
#include "funcs/out_c.h"
#include "funcs/out_di.h"
#include "funcs/out_integration.h"
#include "funcs/out_o.h"
#include "funcs/out_p.h"
#include "funcs/out_s.h"
#include "funcs/out_u.h"
#include "funcs/out_x.h"

/* Test the core of printf function: snprintf, each cases is for one
   specifier, this test suite as a freestanding test suites, which will has no
   buffer related manipulation, and only test the pure function */

UTEST_TEST_SUITE(printf) {
  UTEST_RUN_TEST_CASE(out);
  UTEST_RUN_TEST_CASE(out_c);
  UTEST_RUN_TEST_CASE(out_s);
  UTEST_RUN_TEST_CASE(out_di);
  UTEST_RUN_TEST_CASE(out_o);
  UTEST_RUN_TEST_CASE(out_x);
  UTEST_RUN_TEST_CASE(out_u);
  UTEST_RUN_TEST_CASE(out_p);
  UTEST_RUN_TEST_CASE(out_integration);
}