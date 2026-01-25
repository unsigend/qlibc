/* qlibc - A light-weight and portable C standard library
 * Copyright (C) 2025 Qiu Yixiang
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "stddef.h"
#include <ctype.h>
#include <errno.h>
#include <limits.h>

#define ASSIGN_END_PTR()                                                       \
  if (str_end) {                                                               \
    *str_end = p;                                                              \
  }

static int __check_overflow(long long r, int base, int d, long long s,
                            long long *result) {
  unsigned long long ur = (unsigned long long)r;
  unsigned long long utmp;
  unsigned long long max_abs =
      (unsigned long long)LLONG_MAX + (s == -1 ? 1 : 0);

  if (__builtin_mul_overflow(ur, (unsigned long long)base, &utmp) ||
      utmp > max_abs ||
      __builtin_add_overflow(utmp, (unsigned long long)d, &utmp) ||
      utmp > max_abs) {
    errno = ERANGE;
    *result = (long long)max_abs;
    return 1;
  }
  *result = (long long)utmp;
  return 0;
}

/**
 * Just a clone of strtol, but for long long.
 */
long long strtoll(const char *restrict str, char **restrict str_end, int base) {
  long long r = 0;
  long long s = 1;
  char *p = (char *)str;
  char *dstart = NULL;
  int overflow = 0;

  ASSIGN_END_PTR();

  if ((base < 2 && base != 0) || base > 36) {
    errno = EINVAL;
    return r;
  }

  if (!p || !*p)
    return r;

  while (isspace(*p))
    ++p;

  if (*p == '-') {
    s = -1;
    ++p;
  } else if (*p == '+')
    ++p;

  // auto detect base
  if (!base) {
    if (*p == '0') {
      if ((p[1] == 'x' || p[1] == 'X') && isxdigit(p[2])) {
        base = 16;
        p += 2;
      } else
        base = 8;
    } else
      base = 10;
  }
  // explicitly set base
  else {
    if (base == 16 && *p == '0' && (p[1] == 'x' || p[1] == 'X') &&
        isxdigit(p[2]))
      p += 2;
  }

  dstart = p;
  while (isalpha(*p) || isdigit(*p)) {
    int d = tolower(*p);
    if ((isalpha(d) && d - 'a' + 10 >= base) || (isdigit(d) && d - '0' >= base))
      break;
    if (d >= 'a')
      d = d - 'a' + 10;
    else
      d = d - '0';
    if (!overflow) {
      long long tmp;
      if (__check_overflow(r, base, d, s, &tmp)) {
        overflow = 1;
      }
      r = tmp;
    }
    ++p;
  }
  if (p > dstart)
    ASSIGN_END_PTR();
  return s * r;
}