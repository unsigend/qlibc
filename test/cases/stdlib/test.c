#include <utest.h>

extern UTEST_CASE(abs);
extern UTEST_CASE(bsearch);
extern UTEST_CASE(div);
extern UTEST_CASE(labs);
extern UTEST_CASE(ldiv);
extern UTEST_CASE(llabs);
extern UTEST_CASE(lldiv);
extern UTEST_CASE(qsort);

UTEST_SUITE(stdlib)
{
    UTEST_RUNCASE(abs);
    UTEST_RUNCASE(bsearch);
    UTEST_RUNCASE(div);
    UTEST_RUNCASE(labs);
    UTEST_RUNCASE(ldiv);
    UTEST_RUNCASE(llabs);
    UTEST_RUNCASE(lldiv);
    UTEST_RUNCASE(qsort);
}
