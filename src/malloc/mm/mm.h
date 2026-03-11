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

#ifndef _MM_H_
#define _MM_H_ 1

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

   After alignment, the current implementation has some extra metadata
   overhead, since needs add padding to the meta data to confirms the ANSI/ISO
   C standard.*/

typedef struct meta {
  nmeta_t alloc : 1;  /* allocation status */
  nmeta_t ismmap : 1; /* whether the block is allocated by mmap */
  nmeta_t unused : 1; /* unused bits */
  nmeta_t sz : 29;    /* size of the whole block */
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
  free_block_t *buckets[BUCKET_COUNT]; /* free buckets */
  unsigned char *start;                /* start of the heap */
  unsigned char *end;                  /* end of the heap */
  bool init;                           /* whether the heap is initialized */
} heap_t;

/* Global heap instance */
extern heap_t __heap;
/* Bucket size lookup table */
extern const size_t __slots[BUCKET_COUNT];

/* Minimum threshold of the block size */
#define MINIMUM_BLOCKSZ                                                        \
  (sizeof(header_t) + sizeof(footer_t) + 2 * sizeof(uintptr_t))

/* Returns the header of the block */
#define GET_HEADER(blk) (header_t *)((char *)blk)

/* Returns the footer of the block */
#define GET_FOOTER(blk)                                                        \
  (footer_t *)((char *)blk + (blk)->header.sz - sizeof(footer_t))

/* Returns whether the block is allocated by mmap */
#define IS_MMAP(blk) ((blk)->header.ismmap)

/* Returns whether the block is allocated */
#define IS_ALLOC(blk) ((blk)->header.alloc)

/* Writes the meta data to the block */
static inline void writemeta(block_t *blk, size_t sz, bool alloc, bool ismmap)
{
  blk->header.sz = sz;
  blk->header.alloc = alloc;
  blk->header.ismmap = ismmap;
  footer_t *footer = GET_FOOTER(blk);
  *footer = blk->header;
}

/* Returns the required size of the block with meta data after alignment */
static inline size_t calcblksz(size_t reqsz)
{
  return MAX(ALIGN(reqsz + sizeof(header_t) + sizeof(footer_t)),
             ALIGN(MINIMUM_BLOCKSZ));
}

/* Returns the index of the bucket that the sz belongs to. The sz here is the
   size of the whole block (header + footer + payload) after alignment.The
   progressing order is based on the Fibonacci method. */

static inline size_t getbucketidx(size_t sz)
{
  for (size_t i = 0; i < BUCKET_COUNT; ++i) {
    if (sz <= __slots[i])
      return i;
  }
  return BUCKET_COUNT - 1;
}

/* Inserts the block into the free buckets. The block is inserted based on
   LIFO strategy, so the new block is inserted at the head of the bucket. */

static inline void insertblk(free_block_t *blk, size_t buckidx)
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

/* Removes the block from the free buckets. The caller must ensure that the
   block is not NULL. The bucket_idx is the index of the bucket that the block
   belongs to. */

static inline free_block_t *removeblk(free_block_t *blk, size_t buckidx)
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

/* Slices the block into two parts: the first part is the requested size, the
   second part is the remaining block. It will put the second part back to the
   free buckets. */

static inline void *sliceblk(free_block_t *blk, size_t sz)
{
  size_t blocksz = blk->header.sz;
  size_t leftsz = blocksz - sz;

  /* If the left size is less than the minimum block size, return the whole
     block, since it is not worth splitting and acceptable internal
     fragmentation. */
  if (leftsz < MINIMUM_BLOCKSZ) {
    writemeta((block_t *)blk, blocksz, true, false);
    return (void *)((unsigned char *)blk + sizeof(header_t));
  }

  /* Otherwise, split the block into two parts: the first part is the requested
     size, the second part is the remaining block. */
  free_block_t *remainblk = (free_block_t *)((unsigned char *)blk + sz);
  writemeta((block_t *)blk, sz, true, false);
  writemeta((block_t *)remainblk, leftsz, false, false);
  insertblk(remainblk, getbucketidx(leftsz));

  return (void *)((unsigned char *)blk + sizeof(header_t));
}

#endif