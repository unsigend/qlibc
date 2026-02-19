#include "common.h"
#include <limits.h>
#include <stddef.h>

/* Test snprintf standard output, with %d|%i specifier. */
UTEST_TEST_CASE(out_di) {
  unsigned char buf[BUFSZ];

  {
    int n = snprintf((char *)buf, BUFSZ, "%d", 0);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "0");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%d", 1);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "1");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%d", -1);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "-1");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%d", 42);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "42");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%d", -42);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "-42");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%i", 42);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "42");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%i", -42);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "-42");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.3d", 1);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "001");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.5d", 42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "00042");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.1d", 0);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "0");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.0d", 0);
    EXPECT_EQUAL_INT(n, 0);
    EXPECT_EQUAL_STRING((char *)buf, "");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.3d", -1);
    EXPECT_EQUAL_INT(n, 4);
    EXPECT_EQUAL_STRING((char *)buf, "-001");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.2d", 7);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "07");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "x%d y", 42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "x42 y");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%d%d", 1, 2);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "12");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%d", 12345);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "12345");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%d", -12345);
    EXPECT_EQUAL_INT(n, 6);
    EXPECT_EQUAL_STRING((char *)buf, "-12345");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.6d", 123);
    EXPECT_EQUAL_INT(n, 6);
    EXPECT_EQUAL_STRING((char *)buf, "000123");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.4d", -99);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "-0099");
  }
  {
    int n = snprintf((char *)buf, 1, "%d", 42);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "");
  }
  {
    int n = snprintf((char *)buf, 3, "%d", 42);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "42");
  }
  {
    int n = snprintf((char *)buf, 0, "%d", 42);
    EXPECT_EQUAL_INT(n, 2);
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.0d", 1);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "1");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.0i", 0);
    EXPECT_EQUAL_INT(n, 0);
    EXPECT_EQUAL_STRING((char *)buf, "");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%d", 9);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "9");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%d", 10);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "10");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%d", 99);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "99");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%d", 100);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "100");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%d", -9);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "-9");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%d", -100);
    EXPECT_EQUAL_INT(n, 4);
    EXPECT_EQUAL_STRING((char *)buf, "-100");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.2d", 123);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "123");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.10d", 1);
    EXPECT_EQUAL_INT(n, 10);
    EXPECT_EQUAL_STRING((char *)buf, "0000000001");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.4d", 99999);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "99999");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%d %d", 0, -1);
    EXPECT_EQUAL_INT(n, 4);
    EXPECT_EQUAL_STRING((char *)buf, "0 -1");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%d %i", 42, 42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "42 42");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%dxy", 12);
    EXPECT_EQUAL_INT(n, 4);
    EXPECT_EQUAL_STRING((char *)buf, "12xy");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "xy%d", 12);
    EXPECT_EQUAL_INT(n, 4);
    EXPECT_EQUAL_STRING((char *)buf, "xy12");
  }
  {
    int n = snprintf((char *)buf, 2, "%d", 9);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "9");
  }
  {
    int n = snprintf((char *)buf, 4, "%d", -1);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "-1");
  }
  {
    int n = snprintf((char *)buf, 2, "%.3d", 1);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "0");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%d", 999999);
    EXPECT_EQUAL_INT(n, 6);
    EXPECT_EQUAL_STRING((char *)buf, "999999");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%d", -999999);
    EXPECT_EQUAL_INT(n, 7);
    EXPECT_EQUAL_STRING((char *)buf, "-999999");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.1d", 5);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "5");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.0d", 7);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "7");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%d", INT_MAX);
    EXPECT_EQUAL_INT(n, 10);
    EXPECT_EQUAL_STRING((char *)buf, "2147483647");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%d", INT_MIN);
    EXPECT_EQUAL_INT(n, 11);
    EXPECT_EQUAL_STRING((char *)buf, "-2147483648");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%i", INT_MAX);
    EXPECT_EQUAL_INT(n, 10);
    EXPECT_EQUAL_STRING((char *)buf, "2147483647");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%i", INT_MIN);
    EXPECT_EQUAL_INT(n, 11);
    EXPECT_EQUAL_STRING((char *)buf, "-2147483648");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.12d", INT_MAX);
    EXPECT_EQUAL_INT(n, 12);
    EXPECT_EQUAL_STRING((char *)buf, "002147483647");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.12d", INT_MIN);
    EXPECT_EQUAL_INT(n, 13);
    EXPECT_EQUAL_STRING((char *)buf, "-002147483648");
  }
  {
    int n = snprintf((char *)buf, 12, "%d", INT_MAX);
    EXPECT_EQUAL_INT(n, 10);
    EXPECT_EQUAL_STRING((char *)buf, "2147483647");
  }
  {
    int n = snprintf((char *)buf, 12, "%d", INT_MIN);
    EXPECT_EQUAL_INT(n, 11);
    EXPECT_EQUAL_STRING((char *)buf, "-2147483648");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%5d", 42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "   42");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-5d", 42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "42   ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%5d", -42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "  -42");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-5d", -42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "-42  ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%3d", 1234);
    EXPECT_EQUAL_INT(n, 4);
    EXPECT_EQUAL_STRING((char *)buf, "1234");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%5i", 1);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "    1");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-5i", 1);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "1    ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%05d", 42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "00042");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%05d", -42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "-0042");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%05i", 1);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "00001");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%08d", 123);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "00000123");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%5.3d", 1);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "  001");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%8.4d", 42);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "    0042");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-5.3d", 1);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "001  ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*d", 5, 42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "   42");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*d", -5, 42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "42   ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-05d", 42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "42   ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.*d", 3, 1);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "001");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*.*d", 8, 4, 42);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "    0042");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*.*i", 6, 2, 7);
    EXPECT_EQUAL_INT(n, 6);
    EXPECT_EQUAL_STRING((char *)buf, "    07");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-*.*d", 8, 4, 42);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "0042    ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%ld", (long)42);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "42");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%ld", (long)-123);
    EXPECT_EQUAL_INT(n, 4);
    EXPECT_EQUAL_STRING((char *)buf, "-123");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%lld", (long long)42);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "42");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%lld", (long long)-123);
    EXPECT_EQUAL_INT(n, 4);
    EXPECT_EQUAL_STRING((char *)buf, "-123");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%lld", LLONG_MAX);
    EXPECT_EQUAL_INT(n, 19);
    EXPECT_EQUAL_STRING((char *)buf, "9223372036854775807");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%lld", LLONG_MIN);
    EXPECT_EQUAL_INT(n, 20);
    EXPECT_EQUAL_STRING((char *)buf, "-9223372036854775808");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%zd", (size_t)42);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "42");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%zd", (ptrdiff_t)-123);
    EXPECT_EQUAL_INT(n, 4);
    EXPECT_EQUAL_STRING((char *)buf, "-123");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%li", (long)99);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "99");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%5ld", (long)42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "   42");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-5ld", (long)42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "42   ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.3ld", (long)1);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "001");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%08ld", (long)123);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "00000123");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.3lld", (long long)1);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "001");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%08zd", (size_t)123);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "00000123");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%hd", (short)42);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "42");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%hd", (short)-123);
    EXPECT_EQUAL_INT(n, 4);
    EXPECT_EQUAL_STRING((char *)buf, "-123");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%hi", (short)99);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "99");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%5hd", (short)42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "   42");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-5hd", (short)42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "42   ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.3hd", (short)1);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "001");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%08hd", (short)123);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "00000123");
  }
}