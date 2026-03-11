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

#include <ctype.h>

long long atoll(const char *str)
{
  long long n = 0;
  int neg = 0;

  while (isspace(*str))
    ++str;

  switch (*str) {
  case '-':
    neg = 1;
  case '+':
    ++str;
  }

  while (isdigit(*str))
    n = n * 10 + (*str++ - '0');

  return neg ? -n : n;
}