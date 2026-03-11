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

#include <errno.h>

char *
xtoa(unsigned long long value, char *buff, int base)
{
  if (base < 2 || base > 36)
    {
      errno = EINVAL;
      return buff;
    }

  char *p = buff;
  const char *d = "0123456789abcdefghijklmnopqrstuvwxyz";
  do
    {
      *p++ = d[value % base];
      value /= base;
    }
  while (value);

  for (char *l = buff, *r = p - 1; l < r; l++, r--)
    {
      char tmp = *l;
      *l = *r;
      *r = tmp;
    }

  *p = '\0';
  return buff;
}