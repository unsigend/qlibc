#include "common.h"
#include <limits.h>
#include <stddef.h>

/* Test snprintf standard output, with %o specifier */
UTEST_TEST_CASE(out_o) {
  unsigned char buf[BUFSZ];

  {
    int n = snprintf((char *)buf, BUFSZ, "%o", 0);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "0");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%o", 1);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "1");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%o", 7);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "7");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%o", 8);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "10");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%o", 9);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "11");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%o", 10);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "12");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%o", 64);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "100");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%o", 511);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "777");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%o", 512);
    EXPECT_EQUAL_INT(n, 4);
    EXPECT_EQUAL_STRING((char *)buf, "1000");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.0o", 0);
    EXPECT_EQUAL_INT(n, 0);
    EXPECT_EQUAL_STRING((char *)buf, "");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.0o", 1);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "1");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.3o", 1);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "001");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.5o", 8);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "00010");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.1o", 0);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "0");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.2o", 8);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "10");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.4o", 777);
    EXPECT_EQUAL_INT(n, 4);
    EXPECT_EQUAL_STRING((char *)buf, "1411");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "x%o y", 8);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "x10 y");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%o%o", 1, 2);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "12");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%o", (unsigned)63);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "77");
  }
  {
    int n = snprintf((char *)buf, 1, "%o", 8);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "");
  }
  {
    int n = snprintf((char *)buf, 4, "%o", 64);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "100");
  }
  {
    int n = snprintf((char *)buf, 0, "%o", 8);
    EXPECT_EQUAL_INT(n, 2);
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.10o", 1);
    EXPECT_EQUAL_INT(n, 10);
    EXPECT_EQUAL_STRING((char *)buf, "0000000001");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.2o", 100);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "144");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%o", UINT_MAX);
    EXPECT_EQUAL_INT(n, 11);
    EXPECT_EQUAL_STRING((char *)buf, "37777777777");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%o", UINT_MAX - 1);
    EXPECT_EQUAL_INT(n, 11);
    EXPECT_EQUAL_STRING((char *)buf, "37777777776");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.12o", UINT_MAX);
    EXPECT_EQUAL_INT(n, 12);
    EXPECT_EQUAL_STRING((char *)buf, "037777777777");
  }
  {
    int n = snprintf((char *)buf, 13, "%o", UINT_MAX);
    EXPECT_EQUAL_INT(n, 11);
    EXPECT_EQUAL_STRING((char *)buf, "37777777777");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%5o", 8);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "   10");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-5o", 8);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "10   ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%5o", 0);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "    0");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-5o", 0);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "0    ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%05o", 8);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "00010");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%05o", 0);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "00000");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%08o", 64);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "00000100");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%#o", 8);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "010");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%#o", 0);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "0");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%#o", 64);
    EXPECT_EQUAL_INT(n, 4);
    EXPECT_EQUAL_STRING((char *)buf, "0100");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%#o", 1);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "01");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%5.3o", 1);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "  001");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%8.4o", 64);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "    0100");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*o", 5, 8);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "   10");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.*o", 3, 1);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "001");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*.*o", 8, 4, 64);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "    0100");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%#5o", 8);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "  010");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-#5o", 8);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "010  ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%#05o", 8);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "00010");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%#*.*o", 8, 4, 64);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "    0100");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%lo", (unsigned long)42);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "52");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%llo", (unsigned long long)42);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "52");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%zo", (size_t)42);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "52");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%5lo", (unsigned long)8);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "   10");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-5zo", (size_t)8);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "10   ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.3lo", (unsigned long)1);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "001");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%08lo", (unsigned long)64);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "00000100");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.3llo", (unsigned long long)1);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "001");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%08zo", (size_t)64);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "00000100");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%#lo", (unsigned long)8);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "010");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%#5llo", (unsigned long long)8);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "  010");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%ho", (unsigned short)42);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "52");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%5ho", (unsigned short)8);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "   10");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-5ho", (unsigned short)8);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "10   ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.3ho", (unsigned short)1);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "001");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%08ho", (unsigned short)64);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "00000100");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%#ho", (unsigned short)8);
    EXPECT_EQUAL_INT(n, 3);
    EXPECT_EQUAL_STRING((char *)buf, "010");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*o", 0, 8);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "10");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*o", -5, 8);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "10   ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.*o", 0, 0);
    EXPECT_EQUAL_INT(n, 0);
    EXPECT_EQUAL_STRING((char *)buf, "");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%.*o", 0, 1);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "1");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*.*o", 8, 0, 0);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "        ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%#.0o", 0);
    EXPECT_EQUAL_INT(n, 1);
    EXPECT_EQUAL_STRING((char *)buf, "0");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%#.0o", 1);
    EXPECT_EQUAL_INT(n, 2);
    EXPECT_EQUAL_STRING((char *)buf, "01");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%#8o", 8);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "     010");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%#-8o", 8);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "010     ");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%#*o", 5, 8);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "  010");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%#*.*o", 8, 4, 64);
    EXPECT_EQUAL_INT(n, 8);
    EXPECT_EQUAL_STRING((char *)buf, "    0100");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%0.5o", 1);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "00001");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%0.5o", 0);
    EXPECT_EQUAL_INT(n, 5);
    EXPECT_EQUAL_STRING((char *)buf, "00000");
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*.*o", 6, -1, 64);
    EXPECT_EQUAL_INT(n, 6);
    EXPECT_EQUAL_STRING((char *)buf, "   100");
  }
}