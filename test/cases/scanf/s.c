#include <stdio.h>
#include <utest.h>

UTEST_CASE(in_s)
{
    char a[64], b[64], c[64];
    int n;

    n = sscanf("hello", "%s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "hello");

    n = sscanf("a", "%s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "a");

    n = sscanf("", "%s", a);
    EXPECT_EQ_INT(n, -1);

    n = sscanf("  world", "%s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "world");

    n = sscanf("\t\n foo", "%s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "foo");

    n = sscanf("hello world", "%s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "hello");

    n = sscanf("a b c", "%s%s%s", a, b, c);
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(a, "a");
    EXPECT_EQ_STR(b, "b");
    EXPECT_EQ_STR(c, "c");

    n = sscanf("foo bar baz", "%s%s%s", a, b, c);
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_STR(a, "foo");
    EXPECT_EQ_STR(b, "bar");
    EXPECT_EQ_STR(c, "baz");

    n = sscanf("   ", "%s", a);
    EXPECT_EQ_INT(n, -1);

    n = sscanf("x", "x%s", a);
    EXPECT_EQ_INT(n, -1);

    n = sscanf("x y", "x %s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "y");

    n = sscanf("hello", "%3s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "hel");

    n = sscanf("ab", "%5s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "ab");

    n = sscanf("abcdef", "%3s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "abc");

    n = sscanf("a b", "%1s%1s", a, b);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_STR(a, "a");
    EXPECT_EQ_STR(b, "b");

    n = sscanf("hello\nworld", "%s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "hello");

    n = sscanf("n=test", "n=%s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "test");

    n = sscanf("id:foo", "id:%s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "foo");

    n = sscanf("x42", "x%s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "42");

    n = sscanf("word\trest", "%s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "word");

    n = sscanf("one two", "%s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "one");

    n = sscanf("a b", "%s %s", a, b);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_STR(a, "a");
    EXPECT_EQ_STR(b, "b");

    n = sscanf("single", "%10s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "single");

    n = sscanf("toolong", "%3s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "too");

    n = sscanf("x", "%s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "x");

    n = sscanf("  x  ", "%s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "x");

    n = sscanf("skip me", "%*s %s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "me");

    n = sscanf("a b c", "%*s %*s %s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "c");

    n = sscanf("hello world", "%*5s %s", a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(a, "world");
}
