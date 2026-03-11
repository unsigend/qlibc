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
#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <sys/mman.h>

extern void *malloc(size_t size);
extern void free(void *ptr);

void *realloc(void *ptr, size_t new_size)
{
  /* realloc(NULL, size) is equivalent to malloc(size) */
  if (!ptr)
    return malloc(new_size);

  /* realloc(ptr, 0) is equivalent to free(ptr) */
  if (!new_size) {
    free(ptr);
    return NULL;
  }

  block_t *blk = (block_t *)((unsigned char *)ptr - sizeof(header_t));
  size_t oldpayloadsz;

  /* If the block is allocated by mmap, use mremap to resize the block */
  if (IS_MMAP(blk))
    oldpayloadsz = blk->header.sz - sizeof(header_t);
  else
    oldpayloadsz = blk->header.sz - sizeof(header_t) - sizeof(footer_t);

  /* If the payload size is large enough, return the pointer to the old block,
     and no action is needed. */
  if (oldpayloadsz >= new_size)
    return ptr;

  /* If the block is allocated by mmap, use mremap to resize the block */
  if (IS_MMAP(blk)) {
    size_t newsz = ALIGN_PAGE(new_size + sizeof(header_t));
    void *newptr =
        mremap((unsigned char *)blk, blk->header.sz, newsz, MREMAP_MAYMOVE);
    if (newptr == MAP_FAILED) {
      errno = ENOMEM;
      return NULL;
    }
    writemeta((block_t *)newptr, newsz, true, true);
    return (void *)((unsigned char *)newptr + sizeof(header_t));
  }

  /* Optimize with in-place expansion */
  size_t reqsz = calcblksz(new_size);
  block_t *nextblk = (block_t *)((unsigned char *)blk + blk->header.sz);
  bool islastblk = ((unsigned char *)nextblk >= __heap.end);

  if (!islastblk && !nextblk->header.alloc) {
    size_t newsz = blk->header.sz + nextblk->header.sz;
    if (newsz >= reqsz) {
      removeblk((free_block_t *)nextblk, getbucketidx(nextblk->header.sz));
      size_t leftsz = newsz - reqsz;

      /* If the left size is less than the minimum block size, return the
             whole block */
      if (leftsz < MINIMUM_BLOCKSZ) {
        writemeta((block_t *)blk, newsz, true, false);
      } else {
        free_block_t *remainblk =
            (free_block_t *)((unsigned char *)blk + reqsz);
        writemeta((block_t *)blk, reqsz, true, false);
        writemeta((block_t *)remainblk, leftsz, false, false);
        insertblk(remainblk, getbucketidx(leftsz));
      }

      return ptr;
    }
  }

  /* Fallback to malloc, copy and free case, CPU intensive case. */
  void *newptr = malloc(new_size);
  if (!newptr)
    return NULL;

  /* Copy the data from the old block to the new block */
  memcpy(newptr, ptr, MIN(oldpayloadsz, new_size));
  free(ptr);
  return newptr;
}
