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

#ifndef _FIT_H_
#define _FIT_H_ 1

#include "mm.h"

/* First-fit algorithm: finds the first free block that is large enough to
   allocate the requested size. Remove it from the free buckets, slice it if
   necessary, and return the pointer to the allocated block. This function is
   for reserved usage only.*/

static inline void *firstfit(size_t sz, size_t buckidx)
{
  free_block_t *freeblk = __heap.buckets[buckidx];
  while (freeblk) {
    if (freeblk->header.sz >= sz) {
      removeblk(freeblk, buckidx);
      void *p = sliceblk(freeblk, sz);
      return p;
    }
    freeblk = freeblk->next;
  }
  return NULL;
}

/* Best-fit algorithm: finds the smallest free block that is large enough to
   allocate the requested size. Remove it from the free buckets, slice it if
   necessary, and return the pointer to the allocated block. */

static inline void *bestfit(size_t sz, size_t buckidx)
{
  free_block_t *freeblk = __heap.buckets[buckidx];
  free_block_t *bestfreeblk = NULL;
  while (freeblk) {
    if (freeblk->header.sz >= sz) {
      if (!bestfreeblk || freeblk->header.sz < bestfreeblk->header.sz) {
        bestfreeblk = freeblk;
      }
    }
    freeblk = freeblk->next;
  }
  if (bestfreeblk) {
    removeblk(bestfreeblk, buckidx);
    void *p = sliceblk(bestfreeblk, sz);
    return p;
  }
  return NULL;
}

#endif