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

#ifndef _COALESCING_H_
#define _COALESCING_H_ 1

#include "mm.h"

/* Coalescing the middle block with the adjacent memory-allocated free blocks.
   This function has no heap boundary check. And will assume both prev, next
   and current block are not NULL.*/

static inline void
coalescing_mid(free_block_t *prevblk, free_block_t *blk, free_block_t *nextblk)
{
  /* No coalescing is needed. */
  if (prevblk->header.alloc && nextblk->header.alloc)
    {
      writemeta((block_t *)blk, blk->header.sz, false, false);
      insertblk(blk, getbucketidx(blk->header.sz));
      return;
    }

  /* Coalescing the next block with the current block. */
  if (prevblk->header.alloc && !nextblk->header.alloc)
    {
      size_t newsz = blk->header.sz + nextblk->header.sz;
      removeblk(nextblk, getbucketidx(nextblk->header.sz));
      writemeta((block_t *)blk, newsz, false, false);
      insertblk(blk, getbucketidx(newsz));
      return;
    }

  /* Coalescing the previous block with the current block. */
  if (!prevblk->header.alloc && nextblk->header.alloc)
    {
      size_t newsz = blk->header.sz + prevblk->header.sz;
      removeblk(prevblk, getbucketidx(prevblk->header.sz));
      writemeta((block_t *)prevblk, newsz, false, false);
      insertblk(prevblk, getbucketidx(newsz));
      return;
    }

  /* Coalescing the previous and next blocks with the current block. */
  else
    {
      size_t newsz = prevblk->header.sz + blk->header.sz + nextblk->header.sz;
      removeblk(nextblk, getbucketidx(nextblk->header.sz));
      removeblk(prevblk, getbucketidx(prevblk->header.sz));
      writemeta((block_t *)prevblk, newsz, false, false);
      insertblk(prevblk, getbucketidx(newsz));
      return;
    }
}

/* Coalescing the block with the adjacent memory-allocated free blocks. */
static inline void
coalescing(free_block_t *blk)
{
  /* The coalescing is based on the adjacent heap memory blocks. */
  bool isfirstblk = ((unsigned char *)blk == __heap.start);
  bool islastblk = ((unsigned char *)((unsigned char *)blk + blk->header.sz)
                    == __heap.end);
  block_t *nextblk, *prevblk;
  footer_t *prevblkfooter;

  /* If the current block is the first block in the heap, coalescing the next
     block is needed.*/
  if (isfirstblk)
    {
      nextblk = (block_t *)((unsigned char *)blk + blk->header.sz);
      if (!islastblk && !nextblk->header.alloc)
        {
          size_t newsz = blk->header.sz + nextblk->header.sz;
          removeblk((free_block_t *)nextblk, getbucketidx(nextblk->header.sz));
          writemeta((block_t *)blk, newsz, false, false);
          insertblk(blk, getbucketidx(newsz));
        }
      else
        {
          writemeta((block_t *)blk, blk->header.sz, false, false);
          insertblk(blk, getbucketidx(blk->header.sz));
        }
      return;
    }

  prevblkfooter = (footer_t *)((unsigned char *)blk - sizeof(footer_t));
  prevblk = (block_t *)((unsigned char *)blk - prevblkfooter->sz);

  /* If the current block is the last block in the heap, coalescing the
     previous block is needed.*/
  if (islastblk)
    {
      if (!prevblk->header.alloc)
        {
          size_t newsz = blk->header.sz + prevblk->header.sz;
          removeblk((free_block_t *)prevblk, getbucketidx(prevblk->header.sz));
          writemeta((block_t *)prevblk, newsz, false, false);
          insertblk((free_block_t *)prevblk, getbucketidx(newsz));
        }
      else
        {
          writemeta((block_t *)blk, blk->header.sz, false, false);
          insertblk(blk, getbucketidx(blk->header.sz));
        }
      return;
    }

  nextblk = (block_t *)((unsigned char *)blk + blk->header.sz);
  coalescing_mid((free_block_t *)prevblk, blk, (free_block_t *)nextblk);
}

#endif
