#include "common.h"

/* Test snprintf standard output, with %s specifier. */
UTEST_TEST_CASE(out_s)
{
  unsigned char buf[BUFSZ];
  int n;

  n = snprintf((char *)buf, BUFSZ, "%s", "hello");
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "hello");

  n = snprintf((char *)buf, BUFSZ, "%s", "");
  EXPECT_EQUAL_INT(n, 0);
  EXPECT_EQUAL_STRING((char *)buf, "");

  n = snprintf((char *)buf, BUFSZ, "%s", "a");
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING((char *)buf, "a");

  n = snprintf((char *)buf, BUFSZ, "x%s y", "ab");
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "xab y");

  n = snprintf((char *)buf, BUFSZ, "%sxy", "ab");
  EXPECT_EQUAL_INT(n, 4);
  EXPECT_EQUAL_STRING((char *)buf, "abxy");

  n = snprintf((char *)buf, BUFSZ, "xy%s", "ab");
  EXPECT_EQUAL_INT(n, 4);
  EXPECT_EQUAL_STRING((char *)buf, "xyab");

  n = snprintf((char *)buf, BUFSZ, "%s%s", "a", "b");
  EXPECT_EQUAL_INT(n, 2);
  EXPECT_EQUAL_STRING((char *)buf, "ab");

  n = snprintf((char *)buf, BUFSZ, "%.3s", "hello");
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "hel");

  n = snprintf((char *)buf, BUFSZ, "%.0s", "hello");
  EXPECT_EQUAL_INT(n, 0);
  EXPECT_EQUAL_STRING((char *)buf, "");

  n = snprintf((char *)buf, BUFSZ, "%.10s", "hi");
  EXPECT_EQUAL_INT(n, 2);
  EXPECT_EQUAL_STRING((char *)buf, "hi");

  n = snprintf((char *)buf, BUFSZ, "%.5s", "hello");
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "hello");

  n = snprintf((char *)buf, BUFSZ, "%.1s", "hello");
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING((char *)buf, "h");

  n = snprintf((char *)buf, BUFSZ, "x%.2sy", "abcd");
  EXPECT_EQUAL_INT(n, 4);
  EXPECT_EQUAL_STRING((char *)buf, "xaby");

  n = snprintf((char *)buf, BUFSZ, "%s", "hello\nworld");
  EXPECT_EQUAL_INT(n, 11);
  EXPECT_EQUAL_STRING((char *)buf, "hello\nworld");

  n = snprintf((char *)buf, 1, "%s", "hello");
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "");

  n = snprintf((char *)buf, 3, "%s", "hello");
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "he");

  n = snprintf((char *)buf, 6, "%s", "hello");
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "hello");

  n = snprintf((char *)buf, 0, "%s", "hello");
  EXPECT_EQUAL_INT(n, 5);

  n = snprintf((char *)buf, BUFSZ, "%.3s", "ab");
  EXPECT_EQUAL_INT(n, 2);
  EXPECT_EQUAL_STRING((char *)buf, "ab");

  n = snprintf((char *)buf, 2, "%.5s", "hello");
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "h");

  n = snprintf((char *)buf, 4, "%.3s", "hello");
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "hel");

  {
    const char *longstr = "01234567890123456789012345678901234567890123456789"
                          "01234567890123456789012345678901234567890123456789";
    n = snprintf((char *)buf, BUFSZ, "%s", longstr);
    EXPECT_EQUAL_INT(n, 100);
    EXPECT_EQUAL_STRING((char *)buf, longstr);
  }
  {
    const char *longstr = "01234567890123456789012345678901234567890123456789"
                          "01234567890123456789012345678901234567890123456789";
    n = snprintf((char *)buf, BUFSZ, "%.50s", longstr);
    EXPECT_EQUAL_INT(n, 50);
    EXPECT_EQUAL_STRING((char *)buf,
                        "01234567890123456789012345678901234567890123456789");
  }
  {
    const char *longstr = "01234567890123456789012345678901234567890123456789"
                          "01234567890123456789012345678901234567890123456789";
    n = snprintf((char *)buf, 60, "%s", longstr);
    EXPECT_EQUAL_INT(n, 100);
    EXPECT_EQUAL_STRING(
        (char *)buf,
        "01234567890123456789012345678901234567890123456789012345678");
  }

  n = snprintf((char *)buf, BUFSZ, "%8s", "hi");
  EXPECT_EQUAL_INT(n, 8);
  EXPECT_EQUAL_STRING((char *)buf, "      hi");

  n = snprintf((char *)buf, BUFSZ, "%-8s", "hi");
  EXPECT_EQUAL_INT(n, 8);
  EXPECT_EQUAL_STRING((char *)buf, "hi      ");

  n = snprintf((char *)buf, BUFSZ, "%5s", "hello");
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "hello");

  n = snprintf((char *)buf, BUFSZ, "%-5s", "ab");
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "ab   ");

  n = snprintf((char *)buf, BUFSZ, "%5s", "");
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "     ");

  n = snprintf((char *)buf, BUFSZ, "%-5s", "");
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "     ");

  n = snprintf((char *)buf, BUFSZ, "%8.3s", "hello");
  EXPECT_EQUAL_INT(n, 8);
  EXPECT_EQUAL_STRING((char *)buf, "     hel");

  n = snprintf((char *)buf, BUFSZ, "%-8.3s", "hello");
  EXPECT_EQUAL_INT(n, 8);
  EXPECT_EQUAL_STRING((char *)buf, "hel     ");

  n = snprintf((char *)buf, BUFSZ, "%*s", 5, "hi");
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "   hi");

  n = snprintf((char *)buf, BUFSZ, "%.*s", 3, "hello");
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "hel");

  n = snprintf((char *)buf, BUFSZ, "%*.*s", 8, 3, "hello");
  EXPECT_EQUAL_INT(n, 8);
  EXPECT_EQUAL_STRING((char *)buf, "     hel");

  n = snprintf((char *)buf, BUFSZ, "%-*.*s", 8, 3, "hello");
  EXPECT_EQUAL_INT(n, 8);
  EXPECT_EQUAL_STRING((char *)buf, "hel     ");

  n = snprintf((char *)buf, BUFSZ, "%.*s", 0, "hello");
  EXPECT_EQUAL_INT(n, 0);
  EXPECT_EQUAL_STRING((char *)buf, "");

  n = snprintf((char *)buf, BUFSZ, "%.*s", 5, "hi");
  EXPECT_EQUAL_INT(n, 2);
  EXPECT_EQUAL_STRING((char *)buf, "hi");

  n = snprintf((char *)buf, BUFSZ, "%*s", -5, "hi");
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "hi   ");

  n = snprintf((char *)buf, BUFSZ, "%*s", 0, "x");
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING((char *)buf, "x");

  n = snprintf((char *)buf, BUFSZ, "%*.*s", -8, 3, "hello");
  EXPECT_EQUAL_INT(n, 8);
  EXPECT_EQUAL_STRING((char *)buf, "hel     ");

  n = snprintf((char *)buf, BUFSZ, "%8.0s", "");
  EXPECT_EQUAL_INT(n, 8);
  EXPECT_EQUAL_STRING((char *)buf, "        ");

  n = snprintf((char *)buf, BUFSZ, "%-8.0s", "");
  EXPECT_EQUAL_INT(n, 8);
  EXPECT_EQUAL_STRING((char *)buf, "        ");

  n = snprintf((char *)buf, BUFSZ, "%.0s", "");
  EXPECT_EQUAL_INT(n, 0);
  EXPECT_EQUAL_STRING((char *)buf, "");

  n = snprintf((char *)buf, BUFSZ, "%1s", "ab");
  EXPECT_EQUAL_INT(n, 2);
  EXPECT_EQUAL_STRING((char *)buf, "ab");

  n = snprintf((char *)buf, BUFSZ, "%-1s", "ab");
  EXPECT_EQUAL_INT(n, 2);
  EXPECT_EQUAL_STRING((char *)buf, "ab");

  n = snprintf((char *)buf, BUFSZ, "%10.2s", "abcdef");
  EXPECT_EQUAL_INT(n, 10);
  EXPECT_EQUAL_STRING((char *)buf, "        ab");

  n = snprintf((char *)buf, BUFSZ, "%-10.2s", "abcdef");
  EXPECT_EQUAL_INT(n, 10);
  EXPECT_EQUAL_STRING((char *)buf, "ab        ");

  n = snprintf((char *)buf, BUFSZ, "%.*s", 1, "x");
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING((char *)buf, "x");

  n = snprintf((char *)buf, BUFSZ, "%*.*s", 4, 2, "abcd");
  EXPECT_EQUAL_INT(n, 4);
  EXPECT_EQUAL_STRING((char *)buf, "  ab");

  n = snprintf((char *)buf, BUFSZ, "%-*.*s", 4, 2, "abcd");
  EXPECT_EQUAL_INT(n, 4);
  EXPECT_EQUAL_STRING((char *)buf, "ab  ");

  n = snprintf((char *)buf, BUFSZ, "%s", "\0");
  EXPECT_EQUAL_INT(n, 0);
  EXPECT_EQUAL_STRING((char *)buf, "");

  n = snprintf((char *)buf, BUFSZ, "%.3s", "a\0b");
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING((char *)buf, "a");

  n = snprintf((char *)buf, BUFSZ, "%s", NULL);
  EXPECT_EQUAL_INT(n, 6);
  EXPECT_EQUAL_STRING((char *)buf, "(null)");
}