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

long long
atoll (const char *str)
{
  long long r = 0;
  long long sign = 1;
  int i = 0;

  while (isspace (str[i]))
    {
      ++i;
    }
  if (str[i] == '-')
    {
      sign = -1;
      ++i;
    }
  else if (str[i] == '+')
    {
      ++i;
    }

  while (isdigit (str[i]))
    {
      r = r * 10 + (str[i] - '0');
      ++i;
    }
  return sign * r;
}