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

#include <stddef.h>

void *bsearch(const void *key, const void *ptr, size_t count, size_t size,
              int (*comp)(const void *, const void *))
{
  size_t maxidx = (size_t)count - 1;
  const char *l = (const char *)ptr;
  const char *r = (const char *)ptr + maxidx * size;
  size_t off;
  const char *m = NULL;

  while (l <= r) {
    off = ((size_t)r - (size_t)l) / size;
    m = l + (off / 2) * size;
    if (!comp(key, m))
      return (void *)m;
    else if (comp(key, m) < 0)
      r = m - size;
    else
      l = m + size;
  }

  return NULL;
}