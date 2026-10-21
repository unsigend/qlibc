#include <utest.h>

extern UTEST_CASE(malloc);
extern UTEST_CASE(calloc);
extern UTEST_CASE(realloc);
extern UTEST_CASE(free);

UTEST_SUITE(malloc)
{
    UTEST_RUNCASE(malloc);
    UTEST_RUNCASE(calloc);
    UTEST_RUNCASE(realloc);
    UTEST_RUNCASE(free);
}
