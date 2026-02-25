#include <utest.h>
#include <utest/core.h>

// ANSI/ISO C standard library
extern UTEST_TEST_SUITE(assert);
extern UTEST_TEST_SUITE(string);
extern UTEST_TEST_SUITE(ctype);
extern UTEST_TEST_SUITE(limits);
extern UTEST_TEST_SUITE(stdalign);
extern UTEST_TEST_SUITE(stdbool);
extern UTEST_TEST_SUITE(stdarg);
extern UTEST_TEST_SUITE(stddef);
extern UTEST_TEST_SUITE(stdint);
extern UTEST_TEST_SUITE(stdlib);
extern UTEST_TEST_SUITE(time);
extern UTEST_TEST_SUITE(printf);
extern UTEST_TEST_SUITE(signal);

// POSIX Unix
extern UTEST_TEST_SUITE(elf);
extern UTEST_TEST_SUITE(sys);
extern UTEST_TEST_SUITE(unistd);
extern UTEST_TEST_SUITE(fcntl);
extern UTEST_TEST_SUITE(termios);

// qlibc extensions
// #if defined(_QLIBC) || defined(__QLIBC__) || defined(_QLIBC_SOURCE)
// extern UTEST_TEST_SUITE(ext);
// #endif