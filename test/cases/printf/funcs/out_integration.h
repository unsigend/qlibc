#include "common.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

/* Integration tests for snprintf: %[flags][width][precision][length][specifier]
   All specifiers are tested in separate test cases, this test case is for
   testing the integration of the parser and formatter. */
UTEST_TEST_CASE(out_integration) {
  unsigned char buf[BUFSZ];
  int var;

  {
    int n = snprintf((char *)buf, BUFSZ, "%-*c", 5, 'x');
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "x    ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-*.*s", 8, 3, "hello");
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "hel     ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-*.*ld", 8, 4, (long)42);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "0042    ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-*.*li", 8, 4, (long)42);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "0042    ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%#-*.*lo", 8, 4, (unsigned long)64);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "0100    ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%#-*.*lx", 8, 4, (unsigned long)0xff);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "0x00ff  ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%#-*.*lX", 8, 4, (unsigned long)0xff);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "0X00FF  ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-*.*lu", 8, 4, (unsigned long)42);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "0042    ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-*p", 20, (void *)&var);
    EXPECT_GREATER_EQUAL_INT(n, 10);
    {
      unsigned long long parsed = strtoull((char *)buf, NULL, 0);
      EXPECT_EQUAL_UINT64((uintptr_t)&var, (uintptr_t)parsed);
    }
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*.*lld", 10, 5, (long long)42);
    EXPECT_EQUAL_INT(n, 10);
    EXPECT_EQUAL_STRING((char *)buf, "     00042");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-*.*lld", 10, 5, (long long)42);
    EXPECT_EQUAL_INT(n, 10);
    EXPECT_EQUAL_STRING((char *)buf, "00042     ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*.*hd", 8, 4, (short)42);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "    0042");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*.*zu", 8, 4, (size_t)42);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "    0042");
  }
  {
    int n =
        snprintf((char *)buf, BUFSZ, "%#*.*llo", 10, 4, (unsigned long long)64);
    EXPECT_EQUAL_INT(n, 10);
    EXPECT_EQUAL_STRING((char *)buf, "      0100");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%#*.*llx", 10, 4,
                     (unsigned long long)0xff);
    EXPECT_EQUAL_INT(n, 10);
    EXPECT_EQUAL_STRING((char *)buf, "    0x00ff");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*.*hu", 8, 4, (unsigned short)42);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "    0042");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%08ld", (long)42);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "00000042");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%#08o", (unsigned)8);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "00000010");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%#08x", (unsigned)0xff);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "0x0000ff");
  }
}
