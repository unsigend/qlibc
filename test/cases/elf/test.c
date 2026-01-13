#include <utest.h>

#if defined (__linux__) || defined (__x86_64__) || defined (__i386__)
#include "arch/x86_64.h"
#else
UTEST_TEST_CASE(elf_test) { }
#endif

UTEST_TEST_SUITE(elf){
    UTEST_RUN_TEST_CASE(elf_test);
}
