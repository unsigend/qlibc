#include "common.h"
#include <stdint.h>
#include <stdlib.h>

/* Test snprintf standard output, with %p specifier with 0x prefix. */
UTEST_TEST_CASE(out_p) {
  unsigned char buf[BUFSZ];
  int var;
  char cvar;
  void *p = &var;

  {
    int n = snprintf((char *)buf, BUFSZ, "%p", (void *)&var);
    EXPECT_GREATER_INT(n, 2);
    EXPECT_EQUAL_INT(buf[0], '0');
    EXPECT_EQUAL_INT(buf[1], 'x');
    {
      unsigned long long parsed = strtoull((char *)buf, NULL, 0);
      EXPECT_EQUAL_UINT64((uintptr_t)&var, (uintptr_t)parsed);
    }
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%p", (void *)&cvar);
    EXPECT_GREATER_INT(n, 2);
    EXPECT_EQUAL_INT(buf[0], '0');
    EXPECT_EQUAL_INT(buf[1], 'x');
    {
      unsigned long long parsed = strtoull((char *)buf, NULL, 0);
      EXPECT_EQUAL_UINT64((uintptr_t)&cvar, (uintptr_t)parsed);
    }
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%p", p);
    EXPECT_GREATER_INT(n, 2);
    EXPECT_EQUAL_INT(buf[0], '0');
    EXPECT_EQUAL_INT(buf[1], 'x');
    {
      unsigned long long parsed = strtoull((char *)buf, NULL, 0);
      EXPECT_EQUAL_UINT64((uintptr_t)p, (uintptr_t)parsed);
    }
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%p", NULL);
    EXPECT_GREATER_INT(n, 0);
    EXPECT_EQUAL_INT(buf[n], '\0');
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "x%p y", (void *)&var);
    EXPECT_GREATER_INT(n, 4);
    EXPECT_EQUAL_INT(buf[0], 'x');
    EXPECT_EQUAL_INT(buf[1], '0');
    EXPECT_EQUAL_INT(buf[2], 'x');
    {
      unsigned long long parsed = strtoull((char *)buf + 1, NULL, 0);
      EXPECT_EQUAL_UINT64((uintptr_t)&var, (uintptr_t)parsed);
    }
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%p %p", (void *)&var, (void *)&cvar);
    EXPECT_GREATER_INT(n, 5);
    {
      char *end;
      unsigned long long p1 = strtoull((char *)buf, &end, 0);
      EXPECT_EQUAL_UINT64((uintptr_t)&var, (uintptr_t)p1);
      unsigned long long p2 = strtoull(end, NULL, 0);
      EXPECT_EQUAL_UINT64((uintptr_t)&cvar, (uintptr_t)p2);
    }
  }
  {
    int n = snprintf((char *)buf, 5, "%p", (void *)&var);
    EXPECT_GREATER_INT(n, 2);
    EXPECT_EQUAL_INT(buf[0], '0');
    EXPECT_EQUAL_INT(buf[1], 'x');
  }
  {
    int n = snprintf((char *)buf, 0, "%p", (void *)&var);
    EXPECT_GREATER_INT(n, 2);
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%p---", (void *)&var);
    EXPECT_GREATER_INT(n, 5);
    {
      char *end;
      unsigned long long parsed = strtoull((char *)buf, &end, 0);
      EXPECT_EQUAL_UINT64((uintptr_t)&var, (uintptr_t)parsed);
      EXPECT_EQUAL_INT(end[0], '-');
    }
    EXPECT_EQUAL_INT(buf[n - 3], '-');
    EXPECT_EQUAL_INT(buf[n - 2], '-');
    EXPECT_EQUAL_INT(buf[n - 1], '-');
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "addr=%p", (void *)&var);
    EXPECT_GREATER_INT(n, 6);
    {
      unsigned long long parsed = strtoull((char *)buf + 5, NULL, 0);
      EXPECT_EQUAL_UINT64((uintptr_t)&var, (uintptr_t)parsed);
    }
  }
  {
    int arr[4];
    int n = snprintf((char *)buf, BUFSZ, "%p", (void *)&arr[0]);
    EXPECT_GREATER_INT(n, 2);
    EXPECT_EQUAL_INT(buf[0], '0');
    EXPECT_EQUAL_INT(buf[1], 'x');
    {
      unsigned long long parsed = strtoull((char *)buf, NULL, 0);
      EXPECT_EQUAL_UINT64((uintptr_t)&arr[0], (uintptr_t)parsed);
    }
  }
  {
    int arr[4];
    int n =
        snprintf((char *)buf, BUFSZ, "%p %p", (void *)&arr[0], (void *)&arr[3]);
    EXPECT_GREATER_INT(n, 5);
    {
      char *end;
      unsigned long long p1 = strtoull((char *)buf, &end, 0);
      EXPECT_EQUAL_UINT64((uintptr_t)&arr[0], (uintptr_t)p1);
      unsigned long long p2 = strtoull(end, NULL, 0);
      EXPECT_EQUAL_UINT64((uintptr_t)&arr[3], (uintptr_t)p2);
    }
  }
  {
    long lvar;
    int n = snprintf((char *)buf, BUFSZ, "%p", (void *)&lvar);
    EXPECT_GREATER_INT(n, 2);
    {
      unsigned long long parsed = strtoull((char *)buf, NULL, 0);
      EXPECT_EQUAL_UINT64((uintptr_t)&lvar, (uintptr_t)parsed);
    }
  }
  {
    static int svar;
    int n = snprintf((char *)buf, BUFSZ, "%p", (void *)&svar);
    EXPECT_GREATER_INT(n, 2);
    {
      unsigned long long parsed = strtoull((char *)buf, NULL, 0);
      EXPECT_EQUAL_UINT64((uintptr_t)&svar, (uintptr_t)parsed);
    }
  }
  {
    int n = snprintf((char *)buf, 3, "%p", (void *)&var);
    EXPECT_GREATER_INT(n, 2);
    EXPECT_EQUAL_INT(buf[0], '0');
  }
  {
    int n = snprintf((char *)buf, 4, "%p", (void *)&var);
    EXPECT_GREATER_INT(n, 2);
    EXPECT_EQUAL_INT(buf[0], '0');
    EXPECT_EQUAL_INT(buf[1], 'x');
  }
  {
    char *str = (char *)&var;
    int n = snprintf((char *)buf, BUFSZ, "%p", (void *)str);
    EXPECT_GREATER_INT(n, 2);
    {
      unsigned long long parsed = strtoull((char *)buf, NULL, 0);
      EXPECT_EQUAL_UINT64((uintptr_t)str, (uintptr_t)parsed);
    }
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%20p", (void *)&var);
    EXPECT_GREATER_EQUAL_INT(n, 10);
    {
      char *p = (char *)buf;
      while (*p == ' ')
        p++;
      unsigned long long parsed = strtoull(p, NULL, 0);
      EXPECT_EQUAL_UINT64((uintptr_t)&var, (uintptr_t)parsed);
    }
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-20p", (void *)&var);
    EXPECT_GREATER_EQUAL_INT(n, 10);
    {
      unsigned long long parsed = strtoull((char *)buf, NULL, 0);
      EXPECT_EQUAL_UINT64((uintptr_t)&var, (uintptr_t)parsed);
    }
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%020p", (void *)&var);
    EXPECT_GREATER_EQUAL_INT(n, 10);
    EXPECT_EQUAL_INT(buf[0], '0');
    EXPECT_EQUAL_INT(buf[1], 'x');
    {
      unsigned long long parsed = strtoull((char *)buf, NULL, 0);
      EXPECT_EQUAL_UINT64((uintptr_t)&var, (uintptr_t)parsed);
    }
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*p", 20, (void *)&var);
    EXPECT_GREATER_EQUAL_INT(n, 10);
    {
      char *p = (char *)buf;
      while (*p == ' ')
        p++;
      unsigned long long parsed = strtoull(p, NULL, 0);
      EXPECT_EQUAL_UINT64((uintptr_t)&var, (uintptr_t)parsed);
    }
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-*p", 20, (void *)&var);
    EXPECT_GREATER_EQUAL_INT(n, 10);
    {
      unsigned long long parsed = strtoull((char *)buf, NULL, 0);
      EXPECT_EQUAL_UINT64((uintptr_t)&var, (uintptr_t)parsed);
    }
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%*p", 0, (void *)&var);
    EXPECT_GREATER_EQUAL_INT(n, 2);
    {
      unsigned long long parsed = strtoull((char *)buf, NULL, 0);
      EXPECT_EQUAL_UINT64((uintptr_t)&var, (uintptr_t)parsed);
    }
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-*p", -20, (void *)&var);
    EXPECT_GREATER_EQUAL_INT(n, 10);
    {
      unsigned long long parsed = strtoull((char *)buf, NULL, 0);
      EXPECT_EQUAL_UINT64((uintptr_t)&var, (uintptr_t)parsed);
    }
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%5p", (void *)&var);
    EXPECT_GREATER_EQUAL_INT(n, 5);
    {
      char *p = (char *)buf;
      while (*p == ' ')
        p++;
      unsigned long long parsed = strtoull(p, NULL, 0);
      EXPECT_EQUAL_UINT64((uintptr_t)&var, (uintptr_t)parsed);
    }
  }
  {
    int n = snprintf((char *)buf, BUFSZ, "%-5p", (void *)&var);
    EXPECT_GREATER_EQUAL_INT(n, 5);
    {
      unsigned long long parsed = strtoull((char *)buf, NULL, 0);
      EXPECT_EQUAL_UINT64((uintptr_t)&var, (uintptr_t)parsed);
    }
  }
}