#include "funcs/in.h"
#include "funcs/in_c.h"
#include "funcs/in_d.h"
#include "funcs/in_i.h"
#include "funcs/in_integration.h"
#include "funcs/in_o.h"
#include "funcs/in_p.h"
#include "funcs/in_s.h"
#include "funcs/in_u.h"
#include "funcs/in_x.h"

/* Test the core of scanf function: vsscanf, each cases is for one specifier,
   this test suite as a freestanding test suites, which will has no buffer
   related manipulation, and only test the pure function */
UTEST_TEST_SUITE(scanf)
{
  UTEST_RUN_TEST_CASE(in);
  UTEST_RUN_TEST_CASE(in_c);
  UTEST_RUN_TEST_CASE(in_d);
  UTEST_RUN_TEST_CASE(in_i);
  UTEST_RUN_TEST_CASE(in_o);
  UTEST_RUN_TEST_CASE(in_p);
  UTEST_RUN_TEST_CASE(in_s);
  UTEST_RUN_TEST_CASE(in_u);
  UTEST_RUN_TEST_CASE(in_x);
  UTEST_RUN_TEST_CASE(in_integration);
}