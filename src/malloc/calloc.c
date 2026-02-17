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

#include "mm/mm.h"
#include <string.h>
#if __QLIBC_CALLOC_CHECK_OVERFLOW__ == 1
#include <errno.h>
#endif

extern void *malloc(size_t size);

/* Allocate memory for an array of num elements, each of which is size bytes,
   and initialize the memory to 0. */

void *calloc(size_t num, size_t size) {
  if (!num || !size)
    return NULL;

  size_t sz;

#if __QLIBC_CALLOC_CHECK_OVERFLOW__ == 1
  /* Calculate the size of the memory requested in bytes, and detect if there is
    overflow */

  if (__builtin_mul_overflow(num, size, &sz)) {
    errno = ENOMEM;
    return NULL;
  }
#else
  sz = num * size;
#endif

  void *p = malloc(sz);

  /* If the reuqest size reach the mmap threshold, the MAP_ANONYMOUS flag will
    be set, so the memory will be initialized to 0 by the kernel */
  if (p && sz < MMAP_THRESHOLD)
    memset(p, 0, sz);
  return p;
}