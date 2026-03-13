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

#include "mm.h"
#include "feature.h"

__hidden void __writemeta(block_t *blk, size_t sz, bool alloc, bool ismmap)
{
  blk->header.sz = sz;
  blk->header.alloc = alloc;
  blk->header.ismmap = ismmap;
  footer_t *footer = GET_FOOTER(blk);
  *footer = blk->header;
}

__hidden size_t __getbucketidx(size_t sz)
{
  for (size_t i = 0; i < BUCKET_COUNT; ++i) {
    if (sz <= __slots[i])
      return i;
  }
  return BUCKET_COUNT - 1;
}

__hidden void __insertblk(free_block_t *blk, size_t buckidx)
{
  /* Based on LIFO strategy, the new block is inserted at the head of the
     bucket. */
  free_block_t *freehead = __heap.buckets[buckidx];
  blk->next = freehead;
  blk->prev = NULL;
  if (freehead) {
    freehead->prev = blk;
  }
  __heap.buckets[buckidx] = blk;
}

__hidden free_block_t *__removeblk(free_block_t *blk, size_t buckidx)
{
  free_block_t *prevblk = blk->prev;
  free_block_t *nextblk = blk->next;
  if (prevblk) {
    prevblk->next = nextblk;
  } else {
    __heap.buckets[buckidx] = nextblk;
  }
  if (nextblk) {
    nextblk->prev = prevblk;
  }
  blk->next = NULL;
  blk->prev = NULL;
  return blk;
}

__hidden void *__sliceblk(free_block_t *blk, size_t sz)
{
  size_t blocksz = blk->header.sz;
  size_t leftsz = blocksz - sz;

  /* If the left size is less than the minimum block size, return the whole
     block, since it is not worth splitting and acceptable internal
     fragmentation. */

  if (leftsz < MINIMUM_BLOCKSZ) {
    __writemeta((block_t *)blk, blocksz, true, false);
    return (void *)((unsigned char *)blk + sizeof(header_t));
  }

  /* Otherwise, split the block into two parts: the first part is the requested
     size, the second part is the remaining block. */

  free_block_t *remainblk = (free_block_t *)((unsigned char *)blk + sz);
  __writemeta((block_t *)blk, sz, true, false);
  __writemeta((block_t *)remainblk, leftsz, false, false);
  __insertblk(remainblk, __getbucketidx(leftsz));

  return (void *)((unsigned char *)blk + sizeof(header_t));
}