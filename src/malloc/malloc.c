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

#include "mm/fit.h"
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

/* Global heap instance */
heap_t __heap = {.init = false};

/* Bucket size lookup table. Base thresholds: MINIMUM_BLOCKSZ 24 on 32-bit, 48
   on 64-bit */
const size_t __slots[BUCKET_COUNT] = {
    /* Tiny: 8-byte increments */
    MINIMUM_BLOCKSZ, 32, 40, 48, 56, 64, 72, 80,
    /* Small: 16-byte increments */
    96, 112, 128, 144, 160, 192, 224, 256,
    /* Medium: Fibonacci-like */
    288, 320, 384, 448, 512, 576, 640, 768, 896, 1024, 1280, 1536,
    /* Large: 512-1024 byte steps */
    2048, 2560, 3072, 4096, 5120, 6144, 8192, 10240, 12288, 16384, 20480, 24576,
    /* Very Large: exponential */
    32768, 40960, 49152, 65536, 81920, 98304, 131072, 163840, 196608, 262144,
    327680, 393216, 524288, 655360, 786432, 1048576, 1310720, 1572864, 2097152,
    2621440, 3145728, 4194304, 5242880};

/* Initialize the malloc package. */
static int __init(void) {
  /* Initialize the free buckets */
  memset(__heap.free_buckets, 0, sizeof(__heap.free_buckets));
  __heap.heap_start = (unsigned char *)__brk(0);
  __heap.heap_end = __heap.heap_start;
  __heap.init = true;
  return 0;
}

/* Refills the free buckets with the new memory. The sz is the size of the
   memory request form system, put the new block into proper bucket. Return 0
   if successful, -1 if failed. */

static inline int refill(size_t sz) {
  void *p = sbrk((intptr_t)sz);
  if (p == (void *)-1)
    return -1;
  free_block_t *free_block = (free_block_t *)p;
  write_meta((block_t *)free_block, sz, false, false);
  insert_block(free_block, get_bucket_idx(sz));
  __heap.heap_end = (unsigned char *)p + sz;
  return 0;
}

/* Allocate memory, the malloc implementation based on fast path and slow path,
   if the request size reach the mmap threshold, then directly use mmap to
   allocate memory, otherwise use the segregated best fit algorithm to allocate
   memory. */

void *malloc(size_t size) {
  if (size >= MMAP_THRESHOLD) {
    /* Align the size + header with page size */
    size_t mmap_sz = ALIGN_PAGE(size + sizeof(header_t));
    void *p = mmap(NULL, mmap_sz, PROT_READ | PROT_WRITE,
                   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (p == MAP_FAILED) {
      errno = ENOMEM;
      return NULL;
    }
    write_meta((block_t *)p, mmap_sz, true, true);
    return (void *)((unsigned char *)p + sizeof(header_t));
  }
  if (!__heap.init) {
    if (__init() == -1) {
      errno = ENOMEM;
      return NULL;
    }
  }
  if (!size)
    return NULL;
  size_t block_sz = calc_block_sz(size);
  size_t bucket_idx = get_bucket_idx(block_sz);
  while (bucket_idx < BUCKET_COUNT) {
    void *p = best_fit(block_sz, bucket_idx);
    if (p)
      return p;
    ++bucket_idx;
  }

  /* No free block is found, request more memory */
  size_t refillsz = MAX(block_sz, PAGE_SIZE);
  if (refill(refillsz) == -1) {
    errno = ENOMEM;
    return NULL;
  }
  return best_fit(block_sz, get_bucket_idx(refillsz));
}
