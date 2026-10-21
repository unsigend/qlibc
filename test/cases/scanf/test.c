#include <utest.h>

extern UTEST_CASE(in);
extern UTEST_CASE(in_c);
extern UTEST_CASE(in_s);
extern UTEST_CASE(in_d);
extern UTEST_CASE(in_i);
extern UTEST_CASE(in_o);
extern UTEST_CASE(in_u);
extern UTEST_CASE(in_x);
extern UTEST_CASE(in_p);
extern UTEST_CASE(in_mix);

UTEST_SUITE(scanf)
{
    UTEST_RUNCASE(in);
    UTEST_RUNCASE(in_c);
    UTEST_RUNCASE(in_s);
    UTEST_RUNCASE(in_d);
    UTEST_RUNCASE(in_i);
    UTEST_RUNCASE(in_o);
    UTEST_RUNCASE(in_u);
    UTEST_RUNCASE(in_x);
    UTEST_RUNCASE(in_p);
    UTEST_RUNCASE(in_mix);
}
