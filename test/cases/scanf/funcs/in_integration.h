#include "common.h"
#include <limits.h>
#include <stddef.h>

/* Integration tests: %[*][width][length]specifier combined across all
   specifiers (d,i,u,o,x,c,s,p). Tests parser integration and modifier combos.
 */
UTEST_TEST_CASE(in_integration)
{
  char buf[BUFSZ];
  int n;

  {
    int d;
    n = sscanf("1 2", "%*d %d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 2);
  }
  {
    int d;
    n = sscanf("12345", "%*3d %d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 45);
  }
  {
    short hd;
    long ld;
    long long lld;
    n = sscanf("1 2 3", "%hd %ld %lld", &hd, &ld, &lld);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_INT(hd, 1);
    EXPECT_EQUAL_INT(ld, 2);
    EXPECT_EQUAL_INT(lld, 3);
  }
  {
    int d;
    n = sscanf("0x10 42", "%*i %d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 42);
  }
  {
    unsigned short hu;
    unsigned long lu;
    unsigned long long llu;
    n = sscanf("1 2 3", "%hu %lu %llu", &hu, &lu, &llu);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_INT(hu, 1);
    EXPECT_EQUAL_INT(lu, 2);
    EXPECT_EQUAL_INT(llu, 3);
  }
  {
    unsigned u;
    n = sscanf("12345", "%*3u %u", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 45);
  }
  {
    unsigned u;
    n = sscanf("10 77", "%*o %o", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 63);
  }
  {
    unsigned u;
    n = sscanf("0x10 ff", "%*x %x", &u);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(u, 255);
  }
  {
    char s[BUFSZ];
    n = sscanf("skip me", "%*s %s", s);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING(s, "me");
  }
  {
    char s[BUFSZ];
    n = sscanf("foo bar baz", "%*s %*s %s", s);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING(s, "baz");
  }
  {
    char s[BUFSZ];
    n = sscanf("hello world", "%*5s %s", s);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING(s, "world");
  }
  {
    char c;
    n = sscanf("ab", "%*c%c", &c);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT((unsigned char)c, 'b');
  }
  {
    char c;
    n = sscanf("xyz", "%*2c%c", &c);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT((unsigned char)c, 'z');
  }
  {
    void *p;
    n = sscanf("0x10 0x20", "%*p %p", &p);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_UINT64(p, 32);
  }
  {
    size_t z;
    n = sscanf("42", "%zu", &z);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(z, 42);
  }
  {
    int d;
    char s[BUFSZ];
    unsigned u;
    n = sscanf("42 foo 0xff", "%d %3s %x", &d, s, &u);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_INT(d, 42);
    EXPECT_EQUAL_STRING(s, "foo");
    EXPECT_EQUAL_INT(u, 255);
  }
  {
    int d;
    char s[BUFSZ];
    n = sscanf("id:123 name:test", "id:%d name:%s", &d, s);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_INT(d, 123);
    EXPECT_EQUAL_STRING(s, "test");
  }
  {
    int d1, d2;
    n = sscanf("skip 1 2", "%*s %d %d", &d1, &d2);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_INT(d1, 1);
    EXPECT_EQUAL_INT(d2, 2);
  }
  {
    char c;
    char s[BUFSZ];
    n = sscanf("1 x hello", "%*d %c %s", &c, s);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_INT((unsigned char)c, 'x');
    EXPECT_EQUAL_STRING(s, "hello");
  }
  {
    unsigned u;
    unsigned long lu;
    n = sscanf("0x10 010", "%x %lo", &u, &lu);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_INT(u, 16);
    EXPECT_EQUAL_INT(lu, 8);
  }
  {
    int d;
    long ld;
    n = sscanf("     42 12345", "%d %ld", &d, &ld);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_INT(d, 42);
    EXPECT_EQUAL_INT(ld, 12345);
  }
  {
    char s[BUFSZ];
    n = sscanf("  hello   world  ", "%s %s", s, buf);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING(s, "hello");
    EXPECT_EQUAL_STRING(buf, "world");
  }
  {
    char s2[BUFSZ];
    n = sscanf("50% done", "50%% %s", s2);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING(s2, "done");
  }
  {
    int d;
    n = sscanf("100%", "%d%%", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 100);
  }
  {
    int d;
    char s[BUFSZ];
    n = sscanf("42 abcdef", "%d %3s", &d, s);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_INT(d, 42);
    EXPECT_EQUAL_STRING(s, "abc");
  }
  {
    signed char hhd;
    short hd;
    int d;
    long ld;
    n = sscanf("1 2 3 4", "%hhd %hd %d %ld", &hhd, &hd, &d, &ld);
    EXPECT_EQUAL_INT(n, 4);
    EXPECT_EQUAL_INT(hhd, 1);
    EXPECT_EQUAL_INT(hd, 2);
    EXPECT_EQUAL_INT(d, 3);
    EXPECT_EQUAL_INT(ld, 4);
  }
  {
    unsigned char hhu;
    unsigned short hu;
    unsigned u;
    unsigned long lu;
    n = sscanf("1 2 3 4", "%hhu %hu %u %lu", &hhu, &hu, &u, &lu);
    EXPECT_EQUAL_INT(n, 4);
    EXPECT_EQUAL_INT(hhu, 1);
    EXPECT_EQUAL_INT(hu, 2);
    EXPECT_EQUAL_INT(u, 3);
    EXPECT_EQUAL_INT(lu, 4);
  }
  {
    int d;
    n = sscanf("12345", "%3d", &d);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_INT(d, 123);
  }
  {
    char buf2[BUFSZ];
    n = sscanf("hello", "%5s", buf2);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING(buf2, "hello");
  }
  {
    char buf2[16];
    n = sscanf("hello", "%3c", buf2);
    buf2[3] = '\0';
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING(buf2, "hel");
  }
}
