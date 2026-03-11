#include "common.h"

/* Test snprintf standard output, with no specifier. */
UTEST_TEST_CASE(out)
{
  unsigned char buf[BUFSZ];
  int n;

  n = snprintf((char *)buf, BUFSZ, "");
  EXPECT_EQUAL_INT(n, 0);
  EXPECT_EQUAL_STRING((char *)buf, "");

  n = snprintf((char *)buf, BUFSZ, "a");
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING((char *)buf, "a");

  n = snprintf((char *)buf, BUFSZ, "hello");
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "hello");

  n = snprintf((char *)buf, BUFSZ, "hello\nworld");
  EXPECT_EQUAL_INT(n, 11);
  EXPECT_EQUAL_STRING((char *)buf, "hello\nworld");

  n = snprintf((char *)buf, BUFSZ, "a\tb");
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "a\tb");

  n = snprintf((char *)buf, BUFSZ, "a\rb");
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "a\rb");

  n = snprintf((char *)buf, BUFSZ, "a\\b");
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "a\\b");

  n = snprintf((char *)buf, BUFSZ, "a\"b");
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "a\"b");

  n = snprintf((char *)buf, BUFSZ, "a\vb");
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "a\vb");

  n = snprintf((char *)buf, BUFSZ, "a\bb");
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "a\bb");

  n = snprintf((char *)buf, BUFSZ, "a\fb");
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "a\fb");

  n = snprintf((char *)buf, BUFSZ, "a\ab");
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "a\ab");

  n = snprintf((char *)buf, BUFSZ, "a\?b");
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "a?b");

  n = snprintf((char *)buf, BUFSZ, "a\'b");
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "a'b");

  n = snprintf((char *)buf, BUFSZ,
               "a\x41"
               "b");
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "aAb");

  n = snprintf((char *)buf, BUFSZ, "a\101b");
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "aAb");

  n = snprintf((char *)buf, BUFSZ, "a\0b");
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING((char *)buf, "a");

  n = snprintf((char *)buf, 1, "hello");
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "");

  n = snprintf((char *)buf, 2, "hello");
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "h");

  n = snprintf((char *)buf, 6, "hello");
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "hello");

  n = snprintf((char *)buf, 0, "hello");
  EXPECT_EQUAL_INT(n, 5);

  n = snprintf((char *)buf, 0, "");
  EXPECT_EQUAL_INT(n, 0);

  n = snprintf((char *)buf, BUFSZ, "\n\t\r\v\b\f\a\\\"\?\'");
  EXPECT_EQUAL_INT(n, 11);
  EXPECT_EQUAL_STRING((char *)buf, "\n\t\r\v\b\f\a\\\"\?\'");

  n = snprintf((char *)buf, BUFSZ, "0123456789");
  EXPECT_EQUAL_INT(n, 10);
  EXPECT_EQUAL_STRING((char *)buf, "0123456789");

  n = snprintf((char *)buf, BUFSZ, " \t\n ");
  EXPECT_EQUAL_INT(n, 4);
  EXPECT_EQUAL_STRING((char *)buf, " \t\n ");
}