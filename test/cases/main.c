/**
 * @brief: Main test entry for qlibc
 * Dispatch the test cases based on the command line arguments
 */

#include <utest.h>
#define MATCH(ARG, CASE) (strcmp(ARG, CASE) == 0)

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

// POSIX Unix
extern UTEST_TEST_SUITE(elf);
extern UTEST_TEST_SUITE(sys);
extern UTEST_TEST_SUITE(unistd);
extern UTEST_TEST_SUITE(fcntl);
extern UTEST_TEST_SUITE(stat);

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  UTEST_BEGIN();
  UTEST_CLEAR_FLAG(UTEST_FLAG_STYLE_FULL);

  // Run test suites here
  if (argc <= 1) {
    UTEST_CLEAR_FLAG(UTEST_FLAG_SHOW_CASE);
    UTEST_RUN_TEST_SUITE(assert);
    UTEST_RUN_TEST_SUITE(ctype);
    UTEST_RUN_TEST_SUITE(limits);
    UTEST_RUN_TEST_SUITE(stdalign);
    UTEST_RUN_TEST_SUITE(stdbool);
    UTEST_RUN_TEST_SUITE(stdarg);
    UTEST_RUN_TEST_SUITE(stddef);
    UTEST_RUN_TEST_SUITE(stdint);
    UTEST_RUN_TEST_SUITE(string);
    UTEST_RUN_TEST_SUITE(stdlib);
    UTEST_RUN_TEST_SUITE(elf);
    UTEST_RUN_TEST_SUITE(sys);
    UTEST_RUN_TEST_SUITE(unistd);
    UTEST_RUN_TEST_SUITE(fcntl);
    UTEST_RUN_TEST_SUITE(stat);
    UTEST_RUN_TEST_SUITE(time);
  } else {
    if (MATCH(argv[1], "assert")) {
      UTEST_RUN_TEST_SUITE(assert);
    } else if (MATCH(argv[1], "ctype")) {
      UTEST_RUN_TEST_SUITE(ctype);
    } else if (MATCH(argv[1], "limits")) {
      UTEST_RUN_TEST_SUITE(limits);
    } else if (MATCH(argv[1], "stdalign")) {
      UTEST_RUN_TEST_SUITE(stdalign);
    } else if (MATCH(argv[1], "stdbool")) {
      UTEST_RUN_TEST_SUITE(stdbool);
    } else if (MATCH(argv[1], "stddef")) {
      UTEST_RUN_TEST_SUITE(stddef);
    } else if (MATCH(argv[1], "stdarg")) {
      UTEST_RUN_TEST_SUITE(stdarg);
    } else if (MATCH(argv[1], "stdint")) {
      UTEST_RUN_TEST_SUITE(stdint);
    } else if (MATCH(argv[1], "string")) {
      UTEST_RUN_TEST_SUITE(string);
    } else if (MATCH(argv[1], "stdlib")) {
      UTEST_RUN_TEST_SUITE(stdlib);
    } else if (MATCH(argv[1], "elf")) {
      UTEST_RUN_TEST_SUITE(elf);
    } else if (MATCH(argv[1], "sys")) {
      UTEST_RUN_TEST_SUITE(sys);
    } else if (MATCH(argv[1], "unistd")) {
      UTEST_RUN_TEST_SUITE(unistd);
    } else if (MATCH(argv[1], "fcntl")) {
      UTEST_RUN_TEST_SUITE(fcntl);
    } else if (MATCH(argv[1], "stat")) {
      UTEST_RUN_TEST_SUITE(stat);
    } else if (MATCH(argv[1], "time")) {
      UTEST_RUN_TEST_SUITE(time);
    }
  }

  UTEST_END();

  return 0;
}