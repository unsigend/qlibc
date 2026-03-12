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

#include <stdio.h>
#include <stdlib.h>

/* TODO: optimize this function with a chunked buffer if malloc fails. */
int vfprintf(FILE *restrict stream, const char *restrict format, va_list vlist)
{
  va_list ap_copy;

  va_copy(ap_copy, vlist);
  int n = vsnprintf(NULL, 0, format, ap_copy);
  va_end(ap_copy);

  if (n < 0)
    return -1;

  char *buff = malloc(n + 1);
  if (!buff)
    return -1;

  va_copy(ap_copy, vlist);
  vsnprintf(buff, n + 1, format, ap_copy);
  va_end(ap_copy);

  int wn = fwrite(buff, 1, n, stream);
  free(buff);
  return wn;
}