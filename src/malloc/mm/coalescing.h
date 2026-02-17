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

#ifndef _QLIBC_MALLOC_MM_COALESCING_H_
#define _QLIBC_MALLOC_MM_COALESCING_H_

#include "mm.h"

/* Coalescing the middle block with the adjacent memory-allocated free blocks.
   This function has no heap boundary check. And will assume both prev, next
   and current block are not NULL.*/

static inline void coalescing_mid(free_block_t *prev_block, free_block_t *block,
                                  free_block_t *next_block) {
  /* No coalescing is needed. */
  if (prev_block->header.alloc && next_block->header.alloc) {
    write_meta((block_t *)block, block->header.sz, false, false);
    insert_block(block, get_bucket_idx(block->header.sz));
    return;
  }

  /* Coalescing the next block with the current block. */
  if (prev_block->header.alloc && !next_block->header.alloc) {
    size_t newsz = block->header.sz + next_block->header.sz;
    remove_block(next_block, get_bucket_idx(next_block->header.sz));
    write_meta((block_t *)block, newsz, false, false);
    insert_block(block, get_bucket_idx(newsz));
    return;
  }

  /* Coalescing the previous block with the current block. */
  if (!prev_block->header.alloc && next_block->header.alloc) {
    size_t newsz = block->header.sz + prev_block->header.sz;
    remove_block(prev_block, get_bucket_idx(prev_block->header.sz));
    write_meta((block_t *)prev_block, newsz, false, false);
    insert_block(prev_block, get_bucket_idx(newsz));
    return;
  }

  /* Coalescing the previous and next blocks with the current block. */
  else {
    size_t newsz =
        prev_block->header.sz + block->header.sz + next_block->header.sz;
    remove_block(next_block, get_bucket_idx(next_block->header.sz));
    remove_block(prev_block, get_bucket_idx(prev_block->header.sz));
    write_meta((block_t *)prev_block, newsz, false, false);
    insert_block(prev_block, get_bucket_idx(newsz));
    return;
  }
}

/* Coalescing the block with the adjacent memory-allocated free blocks. */
static inline void coalescing(free_block_t *block) {
  /* The coalescing is based on the adjacent heap memory blocks. */
  bool is_first_block = ((unsigned char *)block == __heap.heap_start);
  bool is_last_block = ((unsigned char *)((unsigned char *)block +
                                          block->header.sz) == __heap.heap_end);
  block_t *next_block, *prev_block;
  footer_t *prev_block_footer;

  /* If the current block is the first block in the heap, coalescing the next
     block is needed.*/
  if (is_first_block) {
    next_block = (block_t *)((unsigned char *)block + block->header.sz);
    if (!is_last_block && !next_block->header.alloc) {
      size_t newsz = block->header.sz + next_block->header.sz;
      remove_block((free_block_t *)next_block,
                   get_bucket_idx(next_block->header.sz));
      write_meta((block_t *)block, newsz, false, false);
      insert_block(block, get_bucket_idx(newsz));
    } else {
      write_meta((block_t *)block, block->header.sz, false, false);
      insert_block(block, get_bucket_idx(block->header.sz));
    }
    return;
  }

  prev_block_footer = (footer_t *)((unsigned char *)block - sizeof(footer_t));
  prev_block = (block_t *)((unsigned char *)block - prev_block_footer->sz);

  /* If the current block is the last block in the heap, coalescing the previous
     block is needed.*/
  if (is_last_block) {
    if (!prev_block->header.alloc) {
      size_t newsz = block->header.sz + prev_block->header.sz;
      remove_block((free_block_t *)prev_block,
                   get_bucket_idx(prev_block->header.sz));
      write_meta((block_t *)prev_block, newsz, false, false);
      insert_block((free_block_t *)prev_block, get_bucket_idx(newsz));
    } else {
      write_meta((block_t *)block, block->header.sz, false, false);
      insert_block(block, get_bucket_idx(block->header.sz));
    }
    return;
  }

  next_block = (block_t *)((unsigned char *)block + block->header.sz);
  coalescing_mid((free_block_t *)prev_block, block, (free_block_t *)next_block);
}

#endif
