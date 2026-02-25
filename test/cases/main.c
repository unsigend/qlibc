/* Main test program for qlibc. Dispatch the test suites based on the command
  line arguments. If no arguments are provided, run all the test suites by
  default.
  Usage: ./test [suite_name] */

#include "cases.h"
#include <stdio.h>

typedef struct {
  const char *name;
  utest_func_ptr func;
} suite_t;

static const suite_t suites[] = {
    {"assert", UTEST_CONCATENATE(UTEST_SUITENAME_PREFIX, assert)},
    {"ctype", UTEST_CONCATENATE(UTEST_SUITENAME_PREFIX, ctype)},
    {"limits", UTEST_CONCATENATE(UTEST_SUITENAME_PREFIX, limits)},
    {"stdalign", UTEST_CONCATENATE(UTEST_SUITENAME_PREFIX, stdalign)},
    {"stdbool", UTEST_CONCATENATE(UTEST_SUITENAME_PREFIX, stdbool)},
    {"stdarg", UTEST_CONCATENATE(UTEST_SUITENAME_PREFIX, stdarg)},
    {"stddef", UTEST_CONCATENATE(UTEST_SUITENAME_PREFIX, stddef)},
    {"stdint", UTEST_CONCATENATE(UTEST_SUITENAME_PREFIX, stdint)},
    {"string", UTEST_CONCATENATE(UTEST_SUITENAME_PREFIX, string)},
    {"stdlib", UTEST_CONCATENATE(UTEST_SUITENAME_PREFIX, stdlib)},
    {"elf", UTEST_CONCATENATE(UTEST_SUITENAME_PREFIX, elf)},
    {"sys", UTEST_CONCATENATE(UTEST_SUITENAME_PREFIX, sys)},
    {"unistd", UTEST_CONCATENATE(UTEST_SUITENAME_PREFIX, unistd)},
    {"fcntl", UTEST_CONCATENATE(UTEST_SUITENAME_PREFIX, fcntl)},
    {"time", UTEST_CONCATENATE(UTEST_SUITENAME_PREFIX, time)},
    {"termios", UTEST_CONCATENATE(UTEST_SUITENAME_PREFIX, termios)},
    {"printf", UTEST_CONCATENATE(UTEST_SUITENAME_PREFIX, printf)},
    {"signal", UTEST_CONCATENATE(UTEST_SUITENAME_PREFIX, signal)},
#if defined(_QLIBC) || defined(__QLIBC__) || defined(_QLIBC_SOURCE)
    {"ext", UTEST_CONCATENATE(UTEST_SUITENAME_PREFIX, ext)},
#endif
};
static const size_t nsuites = sizeof(suites) / sizeof(suite_t);

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  UTEST_BEGIN();
  UTEST_CLEAR_FLAG(UTEST_FLAG_STYLE_FULL);

  if (argc <= 1) {
    UTEST_CLEAR_FLAG(UTEST_FLAG_SHOW_CASE);
    for (size_t i = 0; i < nsuites; i++) {
      UtestRunTestSuite(suites[i].func, suites[i].name);
    }
  } else {
    bool found = false;
    for (size_t i = 0; i < nsuites; i++) {
      if (strcmp(argv[1], suites[i].name) == 0) {
        UtestRunTestSuite(suites[i].func, suites[i].name);
        found = true;
        break;
      }
    }
    if (!found) {
      int bound = 0;
      fprintf(stdout, "Unknown test suites: %s\n", argv[1]);
      fprintf(stdout, "Available test suites: \n\t");
      for (size_t i = 0; i < nsuites; i++) {
        if (bound == 8) {
          bound = 0;
          fprintf(stdout, "\n\t");
        }
        fprintf(stdout, "%s ", suites[i].name);
        bound++;
      }
      fprintf(stdout, "\n\n");
      return 1;
    }
  }
  UTEST_END();

  return 0;
}