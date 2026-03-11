#include "common.h"

/* Test sscanf with %c: basic, width, %*. */
UTEST_TEST_CASE(in_c)
{
  char buf[BUFSZ];
  int n;
  char c;

  n = sscanf("a", "%c", &c);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT((unsigned char)c, 'a');

  n = sscanf("A", "%c", &c);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT((unsigned char)c, 'A');

  n = sscanf("0", "%c", &c);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT((unsigned char)c, '0');

  n = sscanf(" ", "%c", &c);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT((unsigned char)c, ' ');

  n = sscanf("\n", "%c", &c);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT((unsigned char)c, '\n');

  n = sscanf("\t", "%c", &c);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT((unsigned char)c, '\t');

  n = sscanf("", "%c", &c);
  EXPECT_EQUAL_INT(n, -1);

  n = sscanf("ab", "%c%c", &c, buf);
  EXPECT_EQUAL_INT(n, 2);
  EXPECT_EQUAL_INT((unsigned char)c, 'a');
  EXPECT_EQUAL_INT((unsigned char)buf[0], 'b');

  n = sscanf("abc", "%c%c%c", &c, buf, buf + 1);
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_INT((unsigned char)c, 'a');
  EXPECT_EQUAL_INT((unsigned char)buf[0], 'b');
  EXPECT_EQUAL_INT((unsigned char)buf[1], 'c');

  n = sscanf("xay", "x%cy", &c);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT((unsigned char)c, 'a');

  n = sscanf("a\n", "%c%c", &c, buf);
  EXPECT_EQUAL_INT(n, 2);
  EXPECT_EQUAL_INT((unsigned char)c, 'a');
  EXPECT_EQUAL_INT((unsigned char)buf[0], '\n');

  n = sscanf("  x", "%c", &c);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT((unsigned char)c, ' ');

  n = sscanf("xy", "%1c", &c);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT((unsigned char)c, 'x');

  n = sscanf("xyz", "%2c", buf);
  buf[2] = '\0';
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING(buf, "xy");

  n = sscanf("hello", "%3c", buf);
  buf[3] = '\0';
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING(buf, "hel");

  n = sscanf("ab", "%5c", buf);
  buf[2] = '\0';
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING(buf, "ab");

  n = sscanf("x", "%c", &c);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT((unsigned char)c, 'x');

  n = sscanf("\x7f", "%c", &c);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT((unsigned char)c, 0x7f);

  n = sscanf("\r", "%c", &c);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT((unsigned char)c, '\r');

  n = sscanf("a b", "%c %c", &c, buf);
  EXPECT_EQUAL_INT(n, 2);
  EXPECT_EQUAL_INT((unsigned char)c, 'a');
  EXPECT_EQUAL_INT((unsigned char)buf[0], 'b');

  n = sscanf("a\tb", "%c%c", &c, buf);
  EXPECT_EQUAL_INT(n, 2);
  EXPECT_EQUAL_INT((unsigned char)c, 'a');
  EXPECT_EQUAL_INT((unsigned char)buf[0], '\t');

  n = sscanf("xy", "%c%c", &c, buf);
  EXPECT_EQUAL_INT(n, 2);
  EXPECT_EQUAL_INT((unsigned char)c, 'x');
  EXPECT_EQUAL_INT((unsigned char)buf[0], 'y');

  n = sscanf("x", "x%c", &c);
  EXPECT_EQUAL_INT(n, -1);

  n = sscanf("ay", "%cy", &c);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT((unsigned char)c, 'a');

  {
    int d;
    n = sscanf("1 42 x", "%c %d %c", &c, &d, buf);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_INT((unsigned char)c, '1');
    EXPECT_EQUAL_INT(d, 42);
    EXPECT_EQUAL_INT((unsigned char)buf[0], 'x');
  }
  {
    int d;
    n = sscanf("1 42", "%c %d", &c, &d);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_INT((unsigned char)c, '1');
    EXPECT_EQUAL_INT(d, 42);
  }

  n = sscanf("1234", "%2c%2c", buf, buf + 2);
  buf[4] = '\0';
  EXPECT_EQUAL_INT(n, 2);
  EXPECT_EQUAL_STRING(buf, "1234");

  n = sscanf("ab", "%*c%c", &c);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT((unsigned char)c, 'b');

  n = sscanf("xyz", "%*c%*c%c", &c);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT((unsigned char)c, 'z');

  n = sscanf("abcd", "%*2c%c", &c);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_INT((unsigned char)c, 'c');
}
