#include <utest.h>

extern UTEST_CASE(out);
extern UTEST_CASE(c);
extern UTEST_CASE(s);
extern UTEST_CASE(di);
extern UTEST_CASE(o);
extern UTEST_CASE(u);
extern UTEST_CASE(x);
extern UTEST_CASE(p);
extern UTEST_CASE(mix);

UTEST_SUITE(printf)
{
    UTEST_RUNCASE(out);
    UTEST_RUNCASE(c);
    UTEST_RUNCASE(s);
    UTEST_RUNCASE(di);
    UTEST_RUNCASE(o);
    UTEST_RUNCASE(u);
    UTEST_RUNCASE(x);
    UTEST_RUNCASE(p);
    UTEST_RUNCASE(mix);
}
