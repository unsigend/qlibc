#include <ctype.h>
#include <errno.h>

#define AUTO_BASE(base) (!(base))
#define BASE_HEX(str)                                                          \
  (((str)[1] == 'x' || (str)[1] == 'X') && isxdigit((str)[2]))
#define CHARTODIGIT(c) (isalpha((c)) ? (c) - 'a' + 10 : (c) - '0')
#define VALID_DIGIT(c, base) (CHARTODIGIT(c) < base)

/* Core parser function for convert a string to a number. */
unsigned long long strtox(const char *restrict str, char **restrict str_end,
                          int base, unsigned long long lim, int *sign) {
  unsigned long long n = 0;
  char *p = (char *)str;
  /* A sentinel pointer to the start of the first digit number. */
  char *dstart = (char *)str;
  int overflow = 0;

  if (base == 1 || base < 0 || base > 36) {
    errno = EINVAL;
    if (str_end)
      *str_end = p;
    return n;
  }

  while (isspace(*p))
    ++p;

  switch (*p) {
  case '-':
    *sign = 1;
  case '+':
    ++p;
  }

  if (AUTO_BASE(base)) {
    if (*p == '0') {
      /* Only when next character is valid hex digit after prefix, then move
         forward two characters. */
      if (BASE_HEX(p)) {
        base = 16;
        p += 2;
      } else
        base = 8;
    } else
      base = 10;
  } else {
    if (base == 16 && BASE_HEX(p))
      p += 2;
  }

  dstart = p;
  while (*p) {
    unsigned char ch = tolower(*p);
    if (!isalnum(ch) || !VALID_DIGIT(ch, base))
      break;
    /* Based on ANSI/ISO C standard, even the overflow it should still consuming
       digits. */
    if (n > (lim - CHARTODIGIT(ch)) / base) {
      errno = ERANGE;
      overflow = 1;
    }
    if (!overflow)
      n = n * base + CHARTODIGIT(ch);
    ++p;
  }

  if (overflow)
    n = lim;

  if (str_end)
    *str_end = p > dstart ? p : (char *)str;

  return n;
}