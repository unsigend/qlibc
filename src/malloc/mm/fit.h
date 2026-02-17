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

#ifndef _QLIBC_MALLOC_MM_FIT_H_
#define _QLIBC_MALLOC_MM_FIT_H_

#include "mm.h"

/* First-fit algorithm: finds the first free block that is large enough to
   allocate the requested size. Remove it from the free buckets, slice it if
   necessary, and return the pointer to the allocated block. This function is
   for reserved usage only.*/

static inline void *first_fit(size_t sz, size_t bucket_idx) {
  free_block_t *free_block = __heap.free_buckets[bucket_idx];
  while (free_block) {
    if (free_block->header.sz >= sz) {
      remove_block(free_block, bucket_idx);
      void *p = slice_block(free_block, sz);
      return p;
    }
    free_block = free_block->next;
  }
  return NULL;
}

/* Best-fit algorithm: finds the smallest free block that is large enough to
   allocate the requested size. Remove it from the free buckets, slice it if
   necessary, and return the pointer to the allocated block. */

static inline void *best_fit(size_t sz, size_t bucket_idx) {
  free_block_t *free_block = __heap.free_buckets[bucket_idx];
  free_block_t *best_free_block = NULL;
  while (free_block) {
    if (free_block->header.sz >= sz) {
      if (!best_free_block ||
          free_block->header.sz < best_free_block->header.sz) {
        best_free_block = free_block;
      }
    }
    free_block = free_block->next;
  }
  if (best_free_block) {
    remove_block(best_free_block, bucket_idx);
    void *p = slice_block(best_free_block, sz);
    return p;
  }
  return NULL;
}

#endif