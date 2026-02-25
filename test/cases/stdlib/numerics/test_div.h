#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <utest.h>
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#include <inttypes.h>
#endif

UTEST_TEST_CASE(div) {
  div_t r;
  r = div(7, 3);
  EXPECT_EQUAL_INT(r.quot, 2);
  EXPECT_EQUAL_INT(r.rem, 1);
  EXPECT_EQUAL_INT(r.quot * 3 + r.rem, 7);
  r = div(-7, 3);
  EXPECT_EQUAL_INT(r.quot, -2);
  EXPECT_EQUAL_INT(r.rem, -1);
  EXPECT_EQUAL_INT(r.quot * 3 + r.rem, -7);
  r = div(7, -3);
  EXPECT_EQUAL_INT(r.quot, -2);
  EXPECT_EQUAL_INT(r.rem, 1);
  EXPECT_EQUAL_INT(r.quot * (-3) + r.rem, 7);
  r = div(-7, -3);
  EXPECT_EQUAL_INT(r.quot, 2);
  EXPECT_EQUAL_INT(r.rem, -1);
  EXPECT_EQUAL_INT(r.quot * (-3) + r.rem, -7);
  r = div(6, 3);
  EXPECT_EQUAL_INT(r.quot, 2);
  EXPECT_EQUAL_INT(r.rem, 0);
  r = div(0, 5);
  EXPECT_EQUAL_INT(r.quot, 0);
  EXPECT_EQUAL_INT(r.rem, 0);
  r = div(INT_MAX, 1);
  EXPECT_EQUAL_INT(r.quot, INT_MAX);
  EXPECT_EQUAL_INT(r.rem, 0);
  r = div(INT_MAX, INT_MAX);
  EXPECT_EQUAL_INT(r.quot, 1);
  EXPECT_EQUAL_INT(r.rem, 0);
  r = div(-INT_MAX, INT_MAX);
  EXPECT_EQUAL_INT(r.quot, -1);
  EXPECT_EQUAL_INT(r.rem, 0);

  ldiv_t lr;
  lr = ldiv(7L, 3L);
  EXPECT_EQUAL_INT(lr.quot, 2L);
  EXPECT_EQUAL_INT(lr.rem, 1L);
  EXPECT_EQUAL_INT(lr.quot * 3L + lr.rem, 7L);
  lr = ldiv(-7L, 3L);
  EXPECT_EQUAL_INT(lr.quot, -2L);
  EXPECT_EQUAL_INT(lr.rem, -1L);
  lr = ldiv(0L, 5L);
  EXPECT_EQUAL_INT(lr.quot, 0L);
  EXPECT_EQUAL_INT(lr.rem, 0L);
  lr = ldiv(LONG_MAX, 1L);
  EXPECT_EQUAL_INT(lr.quot, LONG_MAX);
  EXPECT_EQUAL_INT(lr.rem, 0L);
  lr = ldiv(LONG_MAX, LONG_MAX);
  EXPECT_EQUAL_INT(lr.quot, 1L);
  EXPECT_EQUAL_INT(lr.rem, 0L);

  lldiv_t llr;
  llr = lldiv(7LL, 3LL);
  EXPECT_EQUAL_INT(llr.quot, 2LL);
  EXPECT_EQUAL_INT(llr.rem, 1LL);
  EXPECT_EQUAL_INT(llr.quot * 3LL + llr.rem, 7LL);
  llr = lldiv(-7LL, 3LL);
  EXPECT_EQUAL_INT(llr.quot, -2LL);
  EXPECT_EQUAL_INT(llr.rem, -1LL);
  llr = lldiv(0LL, 5LL);
  EXPECT_EQUAL_INT(llr.quot, 0LL);
  EXPECT_EQUAL_INT(llr.rem, 0LL);
  llr = lldiv(LLONG_MAX, 1LL);
  EXPECT_EQUAL_INT(llr.quot, LLONG_MAX);
  EXPECT_EQUAL_INT(llr.rem, 0LL);
  llr = lldiv(LLONG_MAX, LLONG_MAX);
  EXPECT_EQUAL_INT(llr.quot, 1LL);
  EXPECT_EQUAL_INT(llr.rem, 0LL);
  llr = lldiv(9223372036854775807LL, 1000000000LL);
  EXPECT_EQUAL_INT(llr.quot, 9223372036854775807LL / 1000000000LL);
  EXPECT_EQUAL_INT(llr.rem, 9223372036854775807LL % 1000000000LL);
  EXPECT_EQUAL_INT(llr.quot * 1000000000LL + llr.rem, 9223372036854775807LL);

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
  imaxdiv_t ir;
  ir = imaxdiv(7, 3);
  EXPECT_EQUAL_INT(ir.quot, 2);
  EXPECT_EQUAL_INT(ir.rem, 1);
  EXPECT_EQUAL_INT(ir.quot * 3 + ir.rem, 7);
  ir = imaxdiv(-7, 3);
  EXPECT_EQUAL_INT(ir.quot, -2);
  EXPECT_EQUAL_INT(ir.rem, -1);
  ir = imaxdiv(0, 5);
  EXPECT_EQUAL_INT(ir.quot, 0);
  EXPECT_EQUAL_INT(ir.rem, 0);
  ir = imaxdiv(INTMAX_MAX, 1);
  EXPECT_EQUAL_INT(ir.quot, INTMAX_MAX);
  EXPECT_EQUAL_INT(ir.rem, 0);
  ir = imaxdiv(INTMAX_MAX, INTMAX_MAX);
  EXPECT_EQUAL_INT(ir.quot, 1);
  EXPECT_EQUAL_INT(ir.rem, 0);
#endif
}
