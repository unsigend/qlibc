#include "common.h"

/* Test sscanf with %s: basic, width, %*. */
UTEST_TEST_CASE(in_s)
{
  char buf[BUFSZ];
  char s[BUFSZ];
  int n;

  n = sscanf("hello", "%s", s);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING(s, "hello");

  n = sscanf("a", "%s", s);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING(s, "a");

  n = sscanf("", "%s", s);
  EXPECT_EQUAL_INT(n, -1);

  n = sscanf("  world", "%s", s);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING(s, "world");

  n = sscanf("\t\n foo", "%s", s);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING(s, "foo");

  n = sscanf("hello world", "%s", s);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING(s, "hello");

  {
    char s2[BUFSZ], s3[BUFSZ];
    n = sscanf("a b c", "%s%s%s", s, s2, s3);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING(s, "a");
    EXPECT_EQUAL_STRING(s2, "b");
    EXPECT_EQUAL_STRING(s3, "c");
  }
  {
    char s2[BUFSZ];
    n = sscanf("foo bar baz", "%s%s%s", s, s2, buf);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING(s, "foo");
    EXPECT_EQUAL_STRING(s2, "bar");
    EXPECT_EQUAL_STRING(buf, "baz");
  }

  n = sscanf("   ", "%s", s);
  EXPECT_EQUAL_INT(n, -1);

  n = sscanf("x", "x%s", s);
  EXPECT_EQUAL_INT(n, -1);

  n = sscanf("x y", "x %s", s);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING(s, "y");

  n = sscanf("hello", "%3s", s);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING(s, "hel");

  n = sscanf("ab", "%5s", s);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING(s, "ab");

  n = sscanf("abcdef", "%3s", s);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING(s, "abc");

  n = sscanf("a b", "%1s%1s", s, buf);
  s[1] = buf[1] = '\0';
  EXPECT_EQUAL_INT(n, 2);
  EXPECT_EQUAL_STRING(s, "a");
  EXPECT_EQUAL_STRING(buf, "b");

  n = sscanf("hello\nworld", "%s", s);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING(s, "hello");

  n = sscanf("n=test", "n=%s", s);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING(s, "test");

  n = sscanf("id:foo", "id:%s", s);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING(s, "foo");

  n = sscanf("x42", "x%s", s);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING(s, "42");

  n = sscanf("word\trest", "%s", s);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING(s, "word");

  n = sscanf("one two", "%s", s);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING(s, "one");

  {
    char s2[BUFSZ];
    n = sscanf("a b", "%s %s", s, s2);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING(s, "a");
    EXPECT_EQUAL_STRING(s2, "b");
  }

  n = sscanf("single", "%10s", s);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING(s, "single");

  n = sscanf("toolong", "%3s", s);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING(s, "too");

  n = sscanf("x", "%s", s);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING(s, "x");

  n = sscanf("  x  ", "%s", s);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING(s, "x");

  n = sscanf("skip me", "%*s %s", s);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING(s, "me");

  n = sscanf("a b c", "%*s %*s %s", s);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING(s, "c");

  n = sscanf("hello world", "%*5s %s", s);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING(s, "world");
}
