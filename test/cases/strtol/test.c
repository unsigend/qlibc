#include <utest.h>

extern UTEST_CASE(strtol);
extern UTEST_CASE(strtoll);
extern UTEST_CASE(strtoul);
extern UTEST_CASE(strtoull);

UTEST_SUITE(strtol)
{
    UTEST_RUNCASE(strtol);
    UTEST_RUNCASE(strtoll);
    UTEST_RUNCASE(strtoul);
    UTEST_RUNCASE(strtoull);
}
