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

#ifndef _QLIBC_MALLOC_MM_H_
#define _QLIBC_MALLOC_MM_H_

#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* This file is the internal memory management header file, it contains the
   definitions of the memory management functions and macros. For now this is
   just a simple segregated best fit implementation, no thread-safety support,
   in later version, it will add race condition protection, and multi-thread
   support.*/

#define ALIGNMENT alignof(max_align_t) /* alignment size */
#define ALIGN(size)                                                            \
  (((size) + (ALIGNMENT - 1)) &                                                \
   ~(ALIGNMENT - 1))    /* rounds up to the nearest multiple of ALIGNMENT */
#define BUCKET_COUNT 64 /* bucket count */
#define PAGE_SIZE 4096  /* page size */
#define ALIGN_PAGE(size)                                                       \
  (((size) + (PAGE_SIZE - 1)) &                                                \
   ~(PAGE_SIZE - 1)) /* rounds up to the nearest multiple of PAGE_SIZE */
#define MMAP_THRESHOLD (4096 * 128) /* threshold size to use mmap: 128 KiB */

/* Meta data type: used for both header and footer, here 32 bits is chosen to
   store the meta data for both 32 bits and 64 bits machine, the actual bits is
   29 bits since the last 3 bits are used to store the allocation status. The
   maximum block size is 512 MiB. */

typedef uint32_t nmeta_t;

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* Design of the meta data: The first 29 bits are used to store the size of the
   block: payload + meta data (header + footer ). The LSB is used to store the
   allocation status. 0 means free, 1 means allocated.

   After alignment, the current implementation has some extra metadata overhead,
   since needs add padding to the meta data to confirms the ANSI/ISO C
   standard.*/

typedef struct meta {
  nmeta_t alloc : 1;   /* allocation status */
  nmeta_t is_mmap : 1; /* whether the block is allocated by mmap */
  nmeta_t unused : 1;  /* unused bits */
  nmeta_t sz : 29;     /* size of the whole block */
} __attribute__((aligned(ALIGNMENT))) meta_t;

typedef meta_t header_t;
typedef meta_t footer_t;

typedef struct block {
  header_t header;         /* header of the block */
  unsigned char payload[]; /* payload of the block */
} block_t;

typedef struct free_block {
  header_t header;         /* header of the free block */
  struct free_block *next; /* next free block */
  struct free_block *prev; /* previous free block */
  unsigned char payload[]; /* payload of the block */
} free_block_t;

typedef struct heap {
  free_block_t *free_buckets[BUCKET_COUNT]; /* free buckets */
  unsigned char *heap_start;                /* start of the heap */
  unsigned char *heap_end;                  /* end of the heap */
  bool init; /* whether the heap is initialized */
} heap_t;

/* Global heap instance */
extern heap_t __heap;
/* Bucket size lookup table */
extern const size_t __slots[BUCKET_COUNT];

/* Minimum threshold of the block size */
#define MINIMUM_BLOCKSZ                                                        \
  (sizeof(header_t) + sizeof(footer_t) + 2 * sizeof(uintptr_t))

/* Returns the header of the block */
#define GET_HEADER(block) (header_t *)((char *)block)

/* Returns the footer of the block */
#define GET_FOOTER(block)                                                      \
  (footer_t *)((char *)block + (block)->header.sz - sizeof(footer_t))

/* Returns whether the block is allocated by mmap */
#define IS_MMAP(block) ((block)->header.is_mmap)

/* Returns whether the block is allocated */
#define IS_ALLOC(block) ((block)->header.alloc)

/* Writes the meta data to the block */
static inline void write_meta(block_t *block, size_t sz, bool alloc,
                              bool is_mmap) {
  block->header.sz = sz;
  block->header.alloc = alloc;
  block->header.is_mmap = is_mmap;
  footer_t *footer = GET_FOOTER(block);
  *footer = block->header;
}

/* Returns the required size of the block with meta data after alignment */
static inline size_t calc_block_sz(size_t reqsz) {
  return MAX(ALIGN(reqsz + sizeof(header_t) + sizeof(footer_t)),
             ALIGN(MINIMUM_BLOCKSZ));
}

/* Returns the index of the bucket that the sz belongs to. The sz here is the
   size of the whole block (header + footer + payload) after alignment.The
   progressing order is based on the Fibonacci method. */

static inline size_t get_bucket_idx(size_t sz) {
  for (size_t i = 0; i < BUCKET_COUNT; ++i) {
    if (sz <= __slots[i])
      return i;
  }
  return BUCKET_COUNT - 1;
}

/* Inserts the block into the free buckets. The block is inserted based on
   LIFO strategy, so the new block is inserted at the head of the bucket. */

static inline void insert_block(free_block_t *block, size_t bucket_idx) {
  /* Based on LIFO strategy, the new block is inserted at the head of the
     bucket. */

  free_block_t *free_head = __heap.free_buckets[bucket_idx];
  block->next = free_head;
  block->prev = NULL;
  if (free_head) {
    free_head->prev = block;
  }
  __heap.free_buckets[bucket_idx] = block;
}

/* Removes the block from the free buckets. The caller must ensure that the
   block is not NULL. The bucket_idx is the index of the bucket that the block
   belongs to. */

static inline free_block_t *remove_block(free_block_t *block,
                                         size_t bucket_idx) {
  free_block_t *prev_block = block->prev;
  free_block_t *next_block = block->next;
  if (prev_block) {
    prev_block->next = next_block;
  } else {
    __heap.free_buckets[bucket_idx] = next_block;
  }
  if (next_block) {
    next_block->prev = prev_block;
  }
  block->next = NULL;
  block->prev = NULL;
  return block;
}

/* Slices the block into two parts: the first part is the requested size, the
   second part is the remaining block. It will put the second part back to the
   free buckets. */

static inline void *slice_block(free_block_t *block, size_t sz) {
  size_t blocksz = block->header.sz;
  size_t leftsz = blocksz - sz;

  /* If the left size is less than the minimum block size, return the whole
     block, since it is not worth splitting and acceptable internal
     fragmentation. */
  if (leftsz < MINIMUM_BLOCKSZ) {
    write_meta((block_t *)block, blocksz, true, false);
    return (void *)((unsigned char *)block + sizeof(header_t));
  }

  /* Otherwise, split the block into two parts: the first part is the requested
     size, the second part is the remaining block. */
  free_block_t *remaining_block = (free_block_t *)((unsigned char *)block + sz);
  write_meta((block_t *)block, sz, true, false);
  write_meta((block_t *)remaining_block, leftsz, false, false);
  insert_block(remaining_block, get_bucket_idx(leftsz));
  return (void *)((unsigned char *)block + sizeof(header_t));
}

#endif