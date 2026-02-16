#include <assert.h>
#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#define __INTERNAL_FUNC static inline
// alignment size
#define ALIGNMENT sizeof(max_align_t)
// rounds up to the nearest multiple of ALIGNMENT
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))
// bucket count
#define BUCKET_COUNT 64

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define PAGE_SIZE mem_pagesize()

// meta data type: used for both header and footer, here 32 bits is chosen to
// store the meta data for both 32 bits and 64 bits machine, the actual bits is
// 29 bits since the last 3 bits are used to store the allocation status. The
// maximum block size is 512 MiB.
typedef uint32_t nmeta_t;

// Design of the meta data:
//   The first 29 bits are used to store the size of the block: payload + meta
//   data (header + footer ). The LSB is used to store the allocation status. 0
//   means free, 1 means allocated.
typedef struct meta {
  nmeta_t sz : 29;    // size of the whole block
  nmeta_t unused : 2; // unused bits
  nmeta_t alloc : 1;  // allocation status
  uint32_t padding;   // padding
} meta_t;

typedef meta_t header_t;
typedef meta_t footer_t;

typedef struct block {
  header_t header;         // header of the block
  unsigned char payload[]; // payload of the block
} block_t;

typedef struct free_block {
  header_t header;         // header of the free block
  struct free_block *next; // next free block
  struct free_block *prev; // previous free block
  unsigned char payload[]; // payload of the block
} free_block_t;

typedef struct heap {
  free_block_t *free_buckets[BUCKET_COUNT]; // free buckets
  unsigned char *heap_start;                // start of the heap
  unsigned char *heap_end;                  // end of the heap
} heap_t;

// global heap instance
static heap_t heap;

// minimum threshold of the block size
#define MINIMUM_BLOCKSZ                                                        \
  (sizeof(header_t) + sizeof(footer_t) + 2 * sizeof(uintptr_t))

// bucket size lookup table
//   Base thresholds: MINIMUM_BLOCKSZ 16 on 32-bit, 24 on 64-bit
static const size_t bucket_sizes[BUCKET_COUNT] = {
    // Tiny: 8-byte increments
    MINIMUM_BLOCKSZ, 32, 40, 48, 56, 64, 72, 80,
    // Small: 16-byte increments
    96, 112, 128, 144, 160, 192, 224, 256,
    // Medium: Fibonacci-like
    288, 320, 384, 448, 512, 576, 640, 768, 896, 1024, 1280, 1536,
    // Large: 512-1024 byte steps
    2048, 2560, 3072, 4096, 5120, 6144, 8192, 10240, 12288, 16384, 20480, 24576,
    // Very Large: exponential
    32768, 40960, 49152, 65536, 81920, 98304, 131072, 163840, 196608, 262144,
    327680, 393216, 524288, 655360, 786432, 1048576, 1310720, 1572864, 2097152,
    2621440, 3145728, 4194304, 5242880};

// get_header(block_t *block)
//   returns the header of the block
__INTERNAL_FUNC header_t *get_header(block_t *block) {
  return (header_t *)block;
}

// get_footer(block_t *block)
//   returns the footer of the block
__INTERNAL_FUNC footer_t *get_footer(block_t *block) {
  return (footer_t *)((char *)block + block->header.sz - sizeof(footer_t));
}

// write_meta(block_t *block, size_t sz, bool alloc)
//   writes the meta data to the block
__INTERNAL_FUNC void write_meta(block_t *block, size_t sz, bool alloc) {
  block->header.sz = sz;
  block->header.alloc = alloc;
  footer_t *footer = get_footer(block);
  *footer = block->header;
}

// calc_block_sz(size_t reqsz)
//   returns the required size of the block with meta data after alignment
__INTERNAL_FUNC size_t calc_block_sz(size_t reqsz) {
  return MAX(ALIGN(reqsz + sizeof(header_t) + sizeof(footer_t)),
             ALIGN(MINIMUM_BLOCKSZ));
}

// get_bucket_idx(size_t sz)
//    returns the index of the bucket that the sz belongs to. The sz here is the
//    size of the whole block (header + footer + payload) after alignment.The
//    progressing order is based on the power-of-two method.
__INTERNAL_FUNC size_t get_bucket_idx(size_t sz) {
  for (size_t i = 0; i < BUCKET_COUNT; ++i) {
    if (sz <= bucket_sizes[i])
      return i;
  }
  return BUCKET_COUNT - 1;
}

// insert_block(free_block_t *block, size_t bucket_idx)
//   inserts the block into the free buckets. The block is inserted based on
//   LIFO strategy, so the new block is inserted at the head of the bucket.
__INTERNAL_FUNC void insert_block(free_block_t *block, size_t bucket_idx) {
  // based on LIFO strategy, the new block is inserted at the head of the
  // bucket.
  free_block_t *free_head = heap.free_buckets[bucket_idx];
  block->next = free_head;
  block->prev = NULL;
  if (free_head) {
    free_head->prev = block;
  }
  heap.free_buckets[bucket_idx] = block;
}

// remove_block(free_block_t *block, size_t bucket_idx)
//   removes the block from the free buckets. The caller must ensure that the
//   block is not NULL. The bucket_idx is the index of the bucket that the block
//   belongs to.
__INTERNAL_FUNC free_block_t *remove_block(free_block_t *block,
                                           size_t bucket_idx) {
  free_block_t *prev_block = block->prev;
  free_block_t *next_block = block->next;
  if (prev_block) {
    prev_block->next = next_block;
  } else {
    heap.free_buckets[bucket_idx] = next_block;
  }
  if (next_block) {
    next_block->prev = prev_block;
  }
  block->next = NULL;
  block->prev = NULL;
  return block;
}

// slice_block(free_block_t *block, size_t sz)
//   slices the block into two parts: the first part is the requested size, the
//   second part is the remaining block. It will put the second part back to the
//   free buckets.
__INTERNAL_FUNC void *slice_block(free_block_t *block, size_t sz) {
  size_t blocksz = block->header.sz;
  size_t leftsz = blocksz - sz;
  // if the left size is less than the minimum block size, return the whole
  // block, since it is not worth splitting and acceptable internal
  // fragmentation.
  if (leftsz < MINIMUM_BLOCKSZ) {
    write_meta((block_t *)block, blocksz, true);
    return (void *)((unsigned char *)block + sizeof(header_t));
  }
  // otherwise, split the block into two parts: the first part is the requested
  // size, the second part is the remaining block.
  free_block_t *remaining_block = (free_block_t *)((unsigned char *)block + sz);
  write_meta((block_t *)block, sz, true);
  write_meta((block_t *)remaining_block, leftsz, false);
  insert_block(remaining_block, get_bucket_idx(leftsz));
  return (void *)((unsigned char *)block + sizeof(header_t));
}

// first_fit(size_t sz, size_t bucket_idx)
//   finds the first free block that is large enough to allocate the requested
//   size. Remove it from the free buckets, slice it if necessary, and return
//   the pointer to the allocated block.
__INTERNAL_FUNC void *first_fit(size_t sz, size_t bucket_idx) {
  free_block_t *free_block = heap.free_buckets[bucket_idx];
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

// best_fit(size_t sz, size_t bucket_idx)
//   finds the smallest free block that is large enough to allocate the
//   requested size. Remove it from the free buckets, slice it if necessary, and
//   return the pointer to the allocated block.
__INTERNAL_FUNC void *best_fit(size_t sz, size_t bucket_idx) {
  free_block_t *free_block = heap.free_buckets[bucket_idx];
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

// refill(size_t sz)
//   refills the free buckets with the new memory. The sz is the size of the
//   memory request form system, put the new block into proper bucket.  Return 0
//   if successful, -1 if failed.
__INTERNAL_FUNC int refill(size_t sz) {
  void *p = mem_sbrk(sz);
  if (p == (void *)-1)
    return -1;
  free_block_t *free_block = (free_block_t *)p;
  write_meta((block_t *)free_block, sz, false);
  insert_block(free_block, get_bucket_idx(sz));
  heap.heap_end = (unsigned char *)p + sz;
  return 0;
}

// coalescing_mid(free_block_t *prev_block, free_block_t *block,
//                free_block_t *next_block)
//   coalesces the middle block with the adjacent memory-allocated free blocks.
//   This function has no heap boundary check. And will assume both prev, next
//   and current block are not NULL.
__INTERNAL_FUNC void coalescing_mid(free_block_t *prev_block,
                                    free_block_t *block,
                                    free_block_t *next_block) {
  // no coalescing is needed.
  if (prev_block->header.alloc && next_block->header.alloc) {
    write_meta((block_t *)block, block->header.sz, false);
    insert_block(block, get_bucket_idx(block->header.sz));
    return;
  }

  // coalescing the next block with the current block.
  if (prev_block->header.alloc && !next_block->header.alloc) {
    size_t newsz = block->header.sz + next_block->header.sz;
    remove_block(next_block, get_bucket_idx(next_block->header.sz));
    write_meta((block_t *)block, newsz, false);
    insert_block(block, get_bucket_idx(newsz));
    return;
  }

  // coalescing the previous block with the current block.
  if (!prev_block->header.alloc && next_block->header.alloc) {
    size_t newsz = block->header.sz + prev_block->header.sz;
    remove_block(prev_block, get_bucket_idx(prev_block->header.sz));
    write_meta((block_t *)prev_block, newsz, false);
    insert_block(prev_block, get_bucket_idx(newsz));
    return;
  }

  // if both the previous and next blocks are free, coalese the previous block
  // and next block with the current block.
  if (!prev_block->header.alloc && !next_block->header.alloc) {
    size_t newsz =
        prev_block->header.sz + block->header.sz + next_block->header.sz;
    remove_block(next_block, get_bucket_idx(next_block->header.sz));
    remove_block(prev_block, get_bucket_idx(prev_block->header.sz));
    write_meta((block_t *)prev_block, newsz, false);
    insert_block(prev_block, get_bucket_idx(newsz));
    return;
  }
}

// coalescing(free_block_t *block)
//   coalesces the block with the adjacent memory-allocated free blocks.
__INTERNAL_FUNC void coalescing(free_block_t *block) {
  // the coalescing is based on the adjacent heap memory blocks.
  bool is_first_block = ((unsigned char *)block == heap.heap_start);
  bool is_last_block = ((unsigned char *)((unsigned char *)block +
                                          block->header.sz) == heap.heap_end);
  block_t *next_block, *prev_block;
  footer_t *prev_block_footer;

  // if the current block is the first block in the heap, coalescing the next
  // is needed.
  if (is_first_block) {
    next_block = (block_t *)((unsigned char *)block + block->header.sz);
    if (!is_last_block && !next_block->header.alloc) {
      size_t newsz = block->header.sz + next_block->header.sz;
      remove_block((free_block_t *)next_block,
                   get_bucket_idx(next_block->header.sz));
      write_meta((block_t *)block, newsz, false);
      insert_block(block, get_bucket_idx(newsz));
    } else {
      write_meta((block_t *)block, block->header.sz, false);
      insert_block(block, get_bucket_idx(block->header.sz));
    }
    return;
  }

  prev_block_footer = (footer_t *)((unsigned char *)block - sizeof(footer_t));
  prev_block = (block_t *)((unsigned char *)block - prev_block_footer->sz);

  // if the current block is the last block in the heap, coalescing the previous
  // is needed.
  if (is_last_block) {
    if (!prev_block->header.alloc) {
      size_t newsz = block->header.sz + prev_block->header.sz;
      remove_block((free_block_t *)prev_block,
                   get_bucket_idx(prev_block->header.sz));
      write_meta((block_t *)prev_block, newsz, false);
      insert_block((free_block_t *)prev_block, get_bucket_idx(newsz));
    } else {
      write_meta((block_t *)block, block->header.sz, false);
      insert_block(block, get_bucket_idx(block->header.sz));
    }
    return;
  }

  next_block = (block_t *)((unsigned char *)block + block->header.sz);
  coalescing_mid((free_block_t *)prev_block, block, (free_block_t *)next_block);
}

/*
 * mm_init - initialize the malloc package.
 */
int mm_init(void) {
  // initialize the free buckets
  memset(heap.free_buckets, 0, sizeof(heap.free_buckets));
  heap.heap_start = (unsigned char *)mem_heap_lo();
  heap.heap_end = (unsigned char *)mem_heap_hi() + 1;
  return 0;
}

/*
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size) {
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

  // no free block is found, request more memory
  size_t refillsz = MAX(block_sz, PAGE_SIZE);
  if (refill(refillsz) == -1)
    return NULL;
  return best_fit(block_sz, get_bucket_idx(refillsz));
}

/*
 * mm_free - Freeing a block coalesces the block with the adjacent
 * memory-allocated free blocks.
 */
void mm_free(void *ptr) {
  if (!ptr)
    return;
  coalescing((free_block_t *)((unsigned char *)ptr - sizeof(header_t)));
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size) {
  // realloc(NULL, size) is equivalent to malloc(size)
  if (!ptr)
    return mm_malloc(size);
  // realloc(ptr, 0) is equivalent to free(ptr)
  if (!size) {
    mm_free(ptr);
    return NULL;
  }
  block_t *block = (block_t *)((unsigned char *)ptr - sizeof(header_t));
  size_t old_payloadsz = block->header.sz - sizeof(header_t) - sizeof(footer_t);
  // if the payload size is large enough, return the pointer to the old block
  if (old_payloadsz >= size)
    return ptr;

  // optimize with in-place explansion
  size_t required_sz = calc_block_sz(size);
  block_t *next_block = (block_t *)((unsigned char *)block + block->header.sz);
  bool is_last_block = ((unsigned char *)next_block >= heap.heap_end);

  if (!is_last_block && !next_block->header.alloc) {
    size_t newsz = block->header.sz + next_block->header.sz;
    if (newsz >= required_sz) {
      remove_block((free_block_t *)next_block,
                   get_bucket_idx(next_block->header.sz));
      size_t leftsz = newsz - required_sz;

      // if the left size is less than the minimum block size, return the whole
      if (leftsz < MINIMUM_BLOCKSZ) {
        write_meta((block_t *)block, newsz, true);
      } else {
        free_block_t *remaining_block =
            (free_block_t *)((unsigned char *)block + required_sz);
        write_meta((block_t *)block, required_sz, true);
        write_meta((block_t *)remaining_block, leftsz, false);
        insert_block(remaining_block, get_bucket_idx(leftsz));
      }

      return ptr;
    }
  }

  // fallback to malloc, copy and free case, CPU intensive case.
  void *new_ptr = mm_malloc(size);
  if (!new_ptr)
    return NULL;
  // copy the data from the old block to the new block
  memcpy(new_ptr, ptr, MIN(old_payloadsz, size));
  mm_free(ptr);
  return new_ptr;
}
