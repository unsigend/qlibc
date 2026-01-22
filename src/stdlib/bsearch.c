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
#include <stdint.h>

void *
bsearch (const void *key, const void *ptr, size_t count, size_t size,
         int (*comp) (const void *, const void *))
{
  uint64_t _index_max = (uint64_t)count - 1;
  const char *_left = (const char *)ptr;
  const char *_right = (const char *)ptr + _index_max * size;

  while (_left <= _right)
    {
      uint64_t _ele_offset = ((uintptr_t)_right - (uintptr_t)_left) / size;
      const char *_middle = _left + (_ele_offset / 2) * size;
      if (!comp (key, _middle))
        return (void *)_middle;
      else if (comp (key, _middle) < 0)
        _right = _middle - size;
      else
        _left = _middle + size;
    }

  return NULL;
}