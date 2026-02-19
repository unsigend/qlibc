#include "common.h"
#include <limits.h>
#include <stddef.h>

/* Test snprintf standard output, with %u specifier. */
UTEST_TEST_CASE(out_u) {
  unsigned char buf[BUFSZ];

  {
    int n = snprintf((char *)buf, BUFSZ, "%u", 0);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "0");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%u", 1);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "1");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%u", 9);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "9");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%u", 10);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "10");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%u", 99);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "99");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%u", 100);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "100");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%u", 999999);
    EXPECT_EQUAL_INT(n, 6);
    EXPECT_EQUAL_STRING((char *)buf, "999999");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%u", UINT_MAX);
    EXPECT_EQUAL_INT(n, 10);
    EXPECT_EQUAL_STRING((char *)buf, "4294967295");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%u", UINT_MAX - 1);
    EXPECT_EQUAL_INT(n, 10);
    EXPECT_EQUAL_STRING((char *)buf, "4294967294");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.0u", 0);
    EXPECT_EQUAL_INT(n, 0);
    EXPECT_EQUAL_STRING((char *)buf, "");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.0u", 1);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "1");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.3u", 1);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "001");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.5u", 42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "00042");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.1u", 0);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "0");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.2u", 123);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "123");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.12u", UINT_MAX);
    EXPECT_EQUAL_INT(n, 12);
    EXPECT_EQUAL_STRING((char *)buf, "004294967295");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "x%u y", 42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "x42 y");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%u%u", 1, 2);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "12");
  }
  {
    int n = snprintf((char *)buf, 1, "%u", 42);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "");
  }
  {
    int n = snprintf((char *)buf, 12, "%u", UINT_MAX);
    EXPECT_EQUAL_INT(n, 10);
    EXPECT_EQUAL_STRING((char *)buf, "4294967295");
  }
  {
    int n = snprintf((char *)buf, 0, "%u", 42);
    EXPECT_EQUAL_INT(n, 2);
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.10u", 1);
    EXPECT_EQUAL_INT(n, 10);
    EXPECT_EQUAL_STRING((char *)buf, "0000000001");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%u", (unsigned)-1);
    EXPECT_EQUAL_INT(n, 10);
    EXPECT_EQUAL_STRING((char *)buf, "4294967295");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%u", USHRT_MAX);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "65535");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%u", UCHAR_MAX);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "255");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%5u", 42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "   42");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-5u", 42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "42   ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%5u", 0);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "    0");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-5u", 0);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "0    ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%05u", 42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "00042");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%05u", 0);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "00000");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%08u", 123);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "00000123");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%5.3u", 1);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "  001");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%8.4u", 42);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "    0042");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*u", 5, 42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "   42");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.*u", 3, 1);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "001");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*.*u", 8, 4, 42);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "    0042");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-5.3u", 1);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "001  ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-*.*u", 8, 4, 42);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "0042    ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%lu", (unsigned long)42);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "42");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%lu", ULONG_MAX);
#if ULONG_MAX == 0xffffffffffffffffULL
    EXPECT_EQUAL_INT(n, 20);
    EXPECT_EQUAL_STRING((char *)buf, "18446744073709551615");
#else
    EXPECT_EQUAL_INT(n, 10);
    EXPECT_EQUAL_STRING((char *)buf, "4294967295");
#endif
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%llu", (unsigned long long)42);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "42");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%llu", ULLONG_MAX);
    EXPECT_EQUAL_INT(n, 20);
    EXPECT_EQUAL_STRING((char *)buf, "18446744073709551615");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%zu", (size_t)42);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "42");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%5lu", (unsigned long)42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "   42");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-5zu", (size_t)42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "42   ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.3lu", (unsigned long)1);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "001");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%08lu", (unsigned long)123);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "00000123");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.3llu", (unsigned long long)1);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "001");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%08zu", (size_t)123);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "00000123");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%hu", (unsigned short)42);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "42");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%5hu", (unsigned short)42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "   42");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-5hu", (unsigned short)42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "42   ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.3hu", (unsigned short)1);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "001");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%08hu", (unsigned short)123);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "00000123");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*u", 0, 42);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "42");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*u", -5, 42);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "42   ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.*u", 0, 0);
    EXPECT_EQUAL_INT(n, 0);
    EXPECT_EQUAL_STRING((char *)buf, "");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.*u", 0, 5);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "5");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*.*u", 10, 0, 0);
    EXPECT_EQUAL_INT(n, 10);
    EXPECT_EQUAL_STRING((char *)buf, "          ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-*.*u", 10, 0, 0);
    EXPECT_EQUAL_INT(n, 10);
    EXPECT_EQUAL_STRING((char *)buf, "          ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*.*u", 6, -1, 42);
    EXPECT_EQUAL_INT(n, 6);
    EXPECT_EQUAL_STRING((char *)buf, "    42");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%010u", 42);
    EXPECT_EQUAL_INT(n, 10);
    EXPECT_EQUAL_STRING((char *)buf, "0000000042");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%010u", 0);
    EXPECT_EQUAL_INT(n, 10);
    EXPECT_EQUAL_STRING((char *)buf, "0000000000");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%0.5u", 1);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "00001");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%0.5u", 0);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "00000");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%hu", (unsigned short)USHRT_MAX);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "65535");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%1u", 12345);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "12345");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-1u", 12345);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "12345");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%zu", (size_t)0);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "0");
  }
}