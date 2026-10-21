#include <utest.h>

extern UTEST_CASE(atoi);
extern UTEST_CASE(atol);
extern UTEST_CASE(atoll);

UTEST_SUITE(atoi)
{
    UTEST_RUNCASE(atoi);
    UTEST_RUNCASE(atol);
    UTEST_RUNCASE(atoll);
}
