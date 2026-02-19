#include "common.h"

/* Test snprintf standard output, with %c specifier. */
UTEST_TEST_CASE(out_c) {
  unsigned char buf[BUFSZ];

  {
    int n = snprintf((char *)buf, BUFSZ, "%c", 'a');
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "a");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%c", 'A');
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "A");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%c", '0');
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "0");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%c", ' ');
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, " ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%c", '\n');
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "\n");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%c", '\t');
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "\t");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%c", 65);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "A");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%c", 0);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(buf[0], 0);
    EXPECT_EQUAL_INT(buf[1], 0);
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%c%c%c", 'a', 'b', 'c');
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "abc");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "x%cy", 'a');
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "xay");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%cxy", 'a');
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "axy");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "xy%c", 'a');
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "xya");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%c%c", 'a', '\n');
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "a\n");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%c", (unsigned char)127);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "\x7f");
  }
  {
    int n = snprintf((char *)buf, 1, "%c", 'a');
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "");
  }
  {
    int n = snprintf((char *)buf, 2, "%c", 'a');
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "a");
  }
  {
    int n = snprintf((char *)buf, 0, "%c", 'a');
    EXPECT_EQUAL_INT(n, 1);
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%c%c", 'x', 'y');
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "xy");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%5c", 'a');
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "    a");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-5c", 'a');
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "a    ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%3c", 'x');
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "  x");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-3c", 'x');
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "x  ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*c", 5, 'a');
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "    a");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*c", 3, 'x');
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "  x");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-*c", 5, 'a');
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "a    ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*c", 0, 'x');
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "x");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*c", 1, 'x');
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "x");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*c", -3, 'x');
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "x  ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-*c", 1, 'a');
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "a");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%10c", '\0');
    EXPECT_EQUAL_INT(n, 10);
    EXPECT_EQUAL_INT(buf[9], 0);
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-10c", '\0');
    EXPECT_EQUAL_INT(n, 10);
    EXPECT_EQUAL_INT(buf[0], 0);
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*c", 10, '\0');
    EXPECT_EQUAL_INT(n, 10);
    EXPECT_EQUAL_INT(buf[9], 0);
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-*c", 10, '\0');
    EXPECT_EQUAL_INT(n, 10);
    EXPECT_EQUAL_INT(buf[0], 0);
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%c%c%c%c", '1', '2', '3', '4');
    EXPECT_EQUAL_INT(n, 4);
    EXPECT_EQUAL_STRING((char *)buf, "1234");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%2c", '\n');
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, " \n");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-2c", '\n');
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "\n ");
  }
}