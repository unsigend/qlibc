#include "common.h"
#include <limits.h>
#include <stddef.h>

/* Test snprintf standard output, with %x|%X specifier. */
UTEST_TEST_CASE(out_x)
{
  unsigned char buf[BUFSZ];
  int n;

  n = snprintf((char *)buf, BUFSZ, "%x", 0);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING((char *)buf, "0");

  n = snprintf((char *)buf, BUFSZ, "%x", 1);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING((char *)buf, "1");

  n = snprintf((char *)buf, BUFSZ, "%x", 9);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING((char *)buf, "9");

  n = snprintf((char *)buf, BUFSZ, "%x", 10);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING((char *)buf, "a");

  n = snprintf((char *)buf, BUFSZ, "%x", 15);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING((char *)buf, "f");

  n = snprintf((char *)buf, BUFSZ, "%x", 16);
  EXPECT_EQUAL_INT(n, 2);
  EXPECT_EQUAL_STRING((char *)buf, "10");

  n = snprintf((char *)buf, BUFSZ, "%x", 255);
  EXPECT_EQUAL_INT(n, 2);
  EXPECT_EQUAL_STRING((char *)buf, "ff");

  n = snprintf((char *)buf, BUFSZ, "%x", 256);
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "100");

  n = snprintf((char *)buf, BUFSZ, "%X", 10);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING((char *)buf, "A");

  n = snprintf((char *)buf, BUFSZ, "%X", 15);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING((char *)buf, "F");

  n = snprintf((char *)buf, BUFSZ, "%X", 255);
  EXPECT_EQUAL_INT(n, 2);
  EXPECT_EQUAL_STRING((char *)buf, "FF");

  n = snprintf((char *)buf, BUFSZ, "%X", 0xabc);
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "ABC");

  n = snprintf((char *)buf, BUFSZ, "%x", 0xabc);
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "abc");

  n = snprintf((char *)buf, BUFSZ, "%.0x", 0);
  EXPECT_EQUAL_INT(n, 0);
  EXPECT_EQUAL_STRING((char *)buf, "");

  n = snprintf((char *)buf, BUFSZ, "%.0x", 1);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING((char *)buf, "1");

  n = snprintf((char *)buf, BUFSZ, "%.3x", 1);
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "001");

  n = snprintf((char *)buf, BUFSZ, "%.4x", 0xff);
  EXPECT_EQUAL_INT(n, 4);
  EXPECT_EQUAL_STRING((char *)buf, "00ff");

  n = snprintf((char *)buf, BUFSZ, "%.4X", 0xff);
  EXPECT_EQUAL_INT(n, 4);
  EXPECT_EQUAL_STRING((char *)buf, "00FF");

  n = snprintf((char *)buf, BUFSZ, "%.1x", 0);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING((char *)buf, "0");

  n = snprintf((char *)buf, BUFSZ, "x%x y", 16);
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "x10 y");

  n = snprintf((char *)buf, BUFSZ, "%x%x", 1, 2);
  EXPECT_EQUAL_INT(n, 2);
  EXPECT_EQUAL_STRING((char *)buf, "12");

  n = snprintf((char *)buf, BUFSZ, "%x", (unsigned)0xdead);
  EXPECT_EQUAL_INT(n, 4);
  EXPECT_EQUAL_STRING((char *)buf, "dead");

  n = snprintf((char *)buf, BUFSZ, "%X", (unsigned)0xdead);
  EXPECT_EQUAL_INT(n, 4);
  EXPECT_EQUAL_STRING((char *)buf, "DEAD");

  n = snprintf((char *)buf, 1, "%x", 16);
  EXPECT_EQUAL_INT(n, 2);
  EXPECT_EQUAL_STRING((char *)buf, "");

  n = snprintf((char *)buf, 4, "%x", 255);
  EXPECT_EQUAL_INT(n, 2);
  EXPECT_EQUAL_STRING((char *)buf, "ff");

  n = snprintf((char *)buf, 0, "%x", 16);
  EXPECT_EQUAL_INT(n, 2);

  n = snprintf((char *)buf, BUFSZ, "%.8x", 0xff);
  EXPECT_EQUAL_INT(n, 8);
  EXPECT_EQUAL_STRING((char *)buf, "000000ff");

  n = snprintf((char *)buf, BUFSZ, "%.2x", 0x123);
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "123");

  n = snprintf((char *)buf, BUFSZ, "%x", UINT_MAX);
  EXPECT_EQUAL_INT(n, 8);
  EXPECT_EQUAL_STRING((char *)buf, "ffffffff");

  n = snprintf((char *)buf, BUFSZ, "%X", UINT_MAX);
  EXPECT_EQUAL_INT(n, 8);
  EXPECT_EQUAL_STRING((char *)buf, "FFFFFFFF");

  n = snprintf((char *)buf, BUFSZ, "%.10x", UINT_MAX);
  EXPECT_EQUAL_INT(n, 10);
  EXPECT_EQUAL_STRING((char *)buf, "00ffffffff");

  n = snprintf((char *)buf, BUFSZ, "%.10X", UINT_MAX);
  EXPECT_EQUAL_INT(n, 10);
  EXPECT_EQUAL_STRING((char *)buf, "00FFFFFFFF");

  n = snprintf((char *)buf, 10, "%x", UINT_MAX);
  EXPECT_EQUAL_INT(n, 8);
  EXPECT_EQUAL_STRING((char *)buf, "ffffffff");

  n = snprintf((char *)buf, BUFSZ, "%5x", 16);
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "   10");

  n = snprintf((char *)buf, BUFSZ, "%-5x", 16);
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "10   ");

  n = snprintf((char *)buf, BUFSZ, "%5X", 255);
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "   FF");

  n = snprintf((char *)buf, BUFSZ, "%-5X", 255);
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "FF   ");

  n = snprintf((char *)buf, BUFSZ, "%05x", 16);
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "00010");

  n = snprintf((char *)buf, BUFSZ, "%05X", 255);
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "000FF");

  n = snprintf((char *)buf, BUFSZ, "%08x", 0xff);
  EXPECT_EQUAL_INT(n, 8);
  EXPECT_EQUAL_STRING((char *)buf, "000000ff");

  n = snprintf((char *)buf, BUFSZ, "%#x", 255);
  EXPECT_EQUAL_INT(n, 4);
  EXPECT_EQUAL_STRING((char *)buf, "0xff");

  n = snprintf((char *)buf, BUFSZ, "%#x", 0);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING((char *)buf, "0");

  n = snprintf((char *)buf, BUFSZ, "%#08x", 0);
  EXPECT_EQUAL_INT(n, 8);
  EXPECT_EQUAL_STRING((char *)buf, "00000000");

  n = snprintf((char *)buf, BUFSZ, "%#x", 0xabc);
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "0xabc");

  n = snprintf((char *)buf, BUFSZ, "%#X", 255);
  EXPECT_EQUAL_INT(n, 4);
  EXPECT_EQUAL_STRING((char *)buf, "0XFF");

  n = snprintf((char *)buf, BUFSZ, "%#X", 0);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING((char *)buf, "0");

  n = snprintf((char *)buf, BUFSZ, "%#X", 0xabc);
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "0XABC");

  n = snprintf((char *)buf, BUFSZ, "%5.3x", 1);
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "  001");

  n = snprintf((char *)buf, BUFSZ, "%8.4x", 0xff);
  EXPECT_EQUAL_INT(n, 8);
  EXPECT_EQUAL_STRING((char *)buf, "    00ff");

  n = snprintf((char *)buf, BUFSZ, "%*x", 5, 16);
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "   10");

  n = snprintf((char *)buf, BUFSZ, "%.*x", 3, 1);
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "001");

  n = snprintf((char *)buf, BUFSZ, "%*.*x", 8, 4, 0xff);
  EXPECT_EQUAL_INT(n, 8);
  EXPECT_EQUAL_STRING((char *)buf, "    00ff");

  n = snprintf((char *)buf, BUFSZ, "%#5x", 16);
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, " 0x10");

  n = snprintf((char *)buf, BUFSZ, "%-#5x", 16);
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "0x10 ");

  n = snprintf((char *)buf, BUFSZ, "%#05x", 16);
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "0x010");

  n = snprintf((char *)buf, BUFSZ, "%#*.*x", 8, 4, 0xff);
  EXPECT_EQUAL_INT(n, 8);
  EXPECT_EQUAL_STRING((char *)buf, "  0x00ff");

  n = snprintf((char *)buf, BUFSZ, "%lx", (unsigned long)0xff);
  EXPECT_EQUAL_INT(n, 2);
  EXPECT_EQUAL_STRING((char *)buf, "ff");

  n = snprintf((char *)buf, BUFSZ, "%llx", (unsigned long long)0xff);
  EXPECT_EQUAL_INT(n, 2);
  EXPECT_EQUAL_STRING((char *)buf, "ff");

  n = snprintf((char *)buf, BUFSZ, "%llx", ULLONG_MAX);
  EXPECT_EQUAL_INT(n, 16);
  EXPECT_EQUAL_STRING((char *)buf, "ffffffffffffffff");

  n = snprintf((char *)buf, BUFSZ, "%zx", (size_t)0xff);
  EXPECT_EQUAL_INT(n, 2);
  EXPECT_EQUAL_STRING((char *)buf, "ff");

  n = snprintf((char *)buf, BUFSZ, "%lX", (unsigned long)0xabc);
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "ABC");

  n = snprintf((char *)buf, BUFSZ, "%llX", (unsigned long long)0xabc);
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "ABC");

  n = snprintf((char *)buf, BUFSZ, "%zX", (size_t)0xabc);
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "ABC");

  n = snprintf((char *)buf, BUFSZ, "%5lx", (unsigned long)16);
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "   10");

  n = snprintf((char *)buf, BUFSZ, "%-5zx", (size_t)16);
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "10   ");

  n = snprintf((char *)buf, BUFSZ, "%.3lx", (unsigned long)1);
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "001");

  n = snprintf((char *)buf, BUFSZ, "%08lx", (unsigned long)0xff);
  EXPECT_EQUAL_INT(n, 8);
  EXPECT_EQUAL_STRING((char *)buf, "000000ff");

  n = snprintf((char *)buf, BUFSZ, "%.3llx", (unsigned long long)1);
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "001");

  n = snprintf((char *)buf, BUFSZ, "%08zx", (size_t)0xff);
  EXPECT_EQUAL_INT(n, 8);
  EXPECT_EQUAL_STRING((char *)buf, "000000ff");

  n = snprintf((char *)buf, BUFSZ, "%#lx", (unsigned long)255);
  EXPECT_EQUAL_INT(n, 4);
  EXPECT_EQUAL_STRING((char *)buf, "0xff");

  n = snprintf((char *)buf, BUFSZ, "%#5llX", (unsigned long long)16);
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, " 0X10");

  n = snprintf((char *)buf, BUFSZ, "%hx", (unsigned short)0xff);
  EXPECT_EQUAL_INT(n, 2);
  EXPECT_EQUAL_STRING((char *)buf, "ff");

  n = snprintf((char *)buf, BUFSZ, "%hX", (unsigned short)0xabc);
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "ABC");

  n = snprintf((char *)buf, BUFSZ, "%5hx", (unsigned short)16);
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "   10");

  n = snprintf((char *)buf, BUFSZ, "%-5hx", (unsigned short)16);
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "10   ");

  n = snprintf((char *)buf, BUFSZ, "%.3hx", (unsigned short)1);
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "001");

  n = snprintf((char *)buf, BUFSZ, "%08hx", (unsigned short)0xff);
  EXPECT_EQUAL_INT(n, 8);
  EXPECT_EQUAL_STRING((char *)buf, "000000ff");

  n = snprintf((char *)buf, BUFSZ, "%#hx", (unsigned short)255);
  EXPECT_EQUAL_INT(n, 4);
  EXPECT_EQUAL_STRING((char *)buf, "0xff");

  n = snprintf((char *)buf, BUFSZ, "%*x", 0, 16);
  EXPECT_EQUAL_INT(n, 2);
  EXPECT_EQUAL_STRING((char *)buf, "10");

  n = snprintf((char *)buf, BUFSZ, "%*x", -5, 16);
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "10   ");

  n = snprintf((char *)buf, BUFSZ, "%.*x", 0, 0);
  EXPECT_EQUAL_INT(n, 0);
  EXPECT_EQUAL_STRING((char *)buf, "");

  n = snprintf((char *)buf, BUFSZ, "%.*x", 0, 1);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING((char *)buf, "1");

  n = snprintf((char *)buf, BUFSZ, "%*.*x", 8, 0, 0);
  EXPECT_EQUAL_INT(n, 8);
  EXPECT_EQUAL_STRING((char *)buf, "        ");

  n = snprintf((char *)buf, BUFSZ, "%#.0x", 0);
  EXPECT_EQUAL_INT(n, 0);
  EXPECT_EQUAL_STRING((char *)buf, "");

  n = snprintf((char *)buf, BUFSZ, "%#.0x", 1);
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "0x1");

  n = snprintf((char *)buf, BUFSZ, "%#.0X", 1);
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "0X1");

  n = snprintf((char *)buf, BUFSZ, "%#8x", 16);
  EXPECT_EQUAL_INT(n, 8);
  EXPECT_EQUAL_STRING((char *)buf, "    0x10");

  n = snprintf((char *)buf, BUFSZ, "%#-8x", 16);
  EXPECT_EQUAL_INT(n, 8);
  EXPECT_EQUAL_STRING((char *)buf, "0x10    ");

  n = snprintf((char *)buf, BUFSZ, "%#8X", 255);
  EXPECT_EQUAL_INT(n, 8);
  EXPECT_EQUAL_STRING((char *)buf, "    0XFF");

  n = snprintf((char *)buf, BUFSZ, "%#*x", 5, 16);
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, " 0x10");

  n = snprintf((char *)buf, BUFSZ, "%#*.*x", 8, 4, 0xff);
  EXPECT_EQUAL_INT(n, 8);
  EXPECT_EQUAL_STRING((char *)buf, "  0x00ff");

  n = snprintf((char *)buf, BUFSZ, "%0.5x", 1);
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "00001");

  n = snprintf((char *)buf, BUFSZ, "%0.5x", 0);
  EXPECT_EQUAL_INT(n, 5);
  EXPECT_EQUAL_STRING((char *)buf, "00000");

  n = snprintf((char *)buf, BUFSZ, "%*.*x", 6, -1, 0xff);
  EXPECT_EQUAL_INT(n, 6);
  EXPECT_EQUAL_STRING((char *)buf, "    ff");

  n = snprintf((char *)buf, BUFSZ, "%1x", 0x123);
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "123");

  n = snprintf((char *)buf, BUFSZ, "%-1x", 0x123);
  EXPECT_EQUAL_INT(n, 3);
  EXPECT_EQUAL_STRING((char *)buf, "123");

  n = snprintf((char *)buf, BUFSZ, "%zx", (size_t)0);
  EXPECT_EQUAL_INT(n, 1);
  EXPECT_EQUAL_STRING((char *)buf, "0");
}