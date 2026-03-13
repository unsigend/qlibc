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
#include <feature.h>

static void coalescing_mid(free_block_t *prevblk, free_block_t *blk,
                           free_block_t *nextblk)
{
  /* No coalescing is needed. */
  if (prevblk->header.alloc && nextblk->header.alloc) {
    __writemeta((block_t *)blk, blk->header.sz, false, false);
    __insertblk(blk, __getbucketidx(blk->header.sz));
    return;
  }

  /* Coalescing the next block with the current block. */
  if (prevblk->header.alloc && !nextblk->header.alloc) {
    size_t newsz = blk->header.sz + nextblk->header.sz;
    __removeblk(nextblk, __getbucketidx(nextblk->header.sz));
    __writemeta((block_t *)blk, newsz, false, false);
    __insertblk(blk, __getbucketidx(newsz));
    return;
  }

  /* Coalescing the previous block with the current block. */
  if (!prevblk->header.alloc && nextblk->header.alloc) {
    size_t newsz = blk->header.sz + prevblk->header.sz;
    __removeblk(prevblk, __getbucketidx(prevblk->header.sz));
    __writemeta((block_t *)prevblk, newsz, false, false);
    __insertblk(prevblk, __getbucketidx(newsz));
    return;
  }

  /* Coalescing the previous and next blocks with the current block. */
  else {
    size_t newsz = prevblk->header.sz + blk->header.sz + nextblk->header.sz;
    __removeblk(nextblk, __getbucketidx(nextblk->header.sz));
    __removeblk(prevblk, __getbucketidx(prevblk->header.sz));
    __writemeta((block_t *)prevblk, newsz, false, false);
    __insertblk(prevblk, __getbucketidx(newsz));
    return;
  }
}

__hidden void __coalescing(free_block_t *blk)
{
  /* coalescing is based on the adjacent heap memory blocks. */
  bool isfirstblk = ((unsigned char *)blk == __heap.start);
  bool islastblk =
      ((unsigned char *)((unsigned char *)blk + blk->header.sz) == __heap.end);
  block_t *nextblk, *prevblk;
  footer_t *prevblkfooter;

  /* If the current block is the first block in the heap, coalescing the next
  block is needed.*/
  if (isfirstblk) {
    nextblk = (block_t *)((unsigned char *)blk + blk->header.sz);
    if (!islastblk && !nextblk->header.alloc) {
      size_t newsz = blk->header.sz + nextblk->header.sz;
      __removeblk((free_block_t *)nextblk, __getbucketidx(nextblk->header.sz));
      __writemeta((block_t *)blk, newsz, false, false);
      __insertblk(blk, __getbucketidx(newsz));
    } else {
      __writemeta((block_t *)blk, blk->header.sz, false, false);
      __insertblk(blk, __getbucketidx(blk->header.sz));
    }
    return;
  }

  prevblkfooter = (footer_t *)((unsigned char *)blk - sizeof(footer_t));
  prevblk = (block_t *)((unsigned char *)blk - prevblkfooter->sz);

  /* If the current block is the last block in the heap, coalescing the
  previous block is needed.*/
  if (islastblk) {
    if (!prevblk->header.alloc) {
      size_t newsz = blk->header.sz + prevblk->header.sz;
      __removeblk((free_block_t *)prevblk, __getbucketidx(prevblk->header.sz));
      __writemeta((block_t *)prevblk, newsz, false, false);
      __insertblk((free_block_t *)prevblk, __getbucketidx(newsz));
    } else {
      __writemeta((block_t *)blk, blk->header.sz, false, false);
      __insertblk(blk, __getbucketidx(blk->header.sz));
    }
    return;
  }

  nextblk = (block_t *)((unsigned char *)blk + blk->header.sz);
  coalescing_mid((free_block_t *)prevblk, blk, (free_block_t *)nextblk);
}