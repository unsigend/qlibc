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
#include "strtox.h"
#include <errno.h>
#include <limits.h>

long long
strtoll(const char *restrict str, char **restrict str_end, int base)
{
  int neg = 0;
  errno = 0;
  unsigned long long r = strtox(str, str_end, base, (ULL)LLONG_MAX + 1, &neg);
  if (errno == ERANGE)
    {
      if (neg)
        return LLONG_MIN;
      else
        return LLONG_MAX;
    }
  return neg ? (LL)(-r) : (LL)r;
}