/* qlibc - A light-weight and portable C standard library
 * Copyright (C) 2025-2027 Yixiang Qiu
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

#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

/*
 * User-space allocator.
 *
 * A simple segregated best fit implementation. Each block carries a header and
 * a matching footer. The size is the whole block. One bit records whether it
 * is allocated, another whether it came from mmap. Free blocks are kept in
 * size-class buckets and inserted at the head. The link pointers live in the
 * free payload.
 *
 * Invariants:
 *
 *  - Heap blocks form a half-open range [heap.start, heap.end) grown with
 *    sbrk. Neighbours of a free block are coalesced only inside that range.
 *  - The footer repeats the header. Allocated heap blocks are not on a bucket.
 *  - Requests at or above MMAP_THRESHOLD use mmap and skip the buckets.
 *
 * A zero-size malloc returns NULL. calloc zeros only the sbrk path; mmap
 * anonymous pages are already zero. No locking.
 */

#define ALIGNMENT _Alignof(max_align_t)
#define BUCKET_COUNT 64
#define PAGE_SIZE 4096
#define MMAP_THRESHOLD (4096 * 128)
#define MAX_BLOCK_SIZE (((size_t)1 << 29) - 1) /* fits header.sz : 29 */

#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))
#define ALIGN_PAGE(size) (((size) + (PAGE_SIZE - 1)) & ~(PAGE_SIZE - 1))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* Meta data type: used for both header and footer. 32 bits are used on both
 * widths. 29 bits hold the block size, the low bits hold status. The maximum
 * block size is 512 MiB. */
typedef uint32_t nmeta_t;

/* Design of the meta data: The first 29 bits store the size of the block:
 * payload + meta data (header + footer). The LSB is the allocation status.
 * 0 means free, 1 means allocated. The next bit marks an mmap block.
 *
 * After alignment, the current implementation has some extra metadata
 * overhead, since padding is added so the payload meets ANSI/ISO C alignment.
 */
typedef struct meta {
    nmeta_t alloc : 1;  /* allocation status */
    nmeta_t ismmap : 1; /* allocated by mmap */
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
    free_block_t *buckets[BUCKET_COUNT];
    unsigned char *start;
    unsigned char *end;
    bool init;
} heap_t;

#define MINIMUM_THRESHOLD                                                      \
    (sizeof(header_t) + sizeof(footer_t) + 2 * sizeof(uintptr_t))

static heap_t heap = {.init = false};

/* Bucket size lookup table. Base thresholds: MINIMUM_THRESHOLD 24 on 32-bit,
   48 on 64-bit */
static const size_t slots[BUCKET_COUNT] = {
    /* Tiny: 8-byte increments */
    MINIMUM_THRESHOLD, 32, 40, 48, 56, 64, 72, 80,
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

static inline size_t calc_needed_size(size_t sz)
{
    return MAX(ALIGN(sz + sizeof(header_t) + sizeof(footer_t)),
               ALIGN(MINIMUM_THRESHOLD));
}

static inline footer_t *get_footer(block_t *block)
{
    return (footer_t *)((char *)block + block->header.sz - sizeof(footer_t));
}

static void write_meta(block_t *block, size_t sz, bool alloc, bool ismmap)
{
    footer_t *footer;

    block->header.sz = sz;
    block->header.alloc = alloc;
    block->header.ismmap = ismmap;
    footer = get_footer(block);
    *footer = block->header;
}

static size_t get_bucket_index(size_t sz)
{
    size_t i;

    for (i = 0; i < BUCKET_COUNT; ++i) {
        if (sz <= slots[i])
            return i;
    }
    return BUCKET_COUNT - 1;
}

/* Insert a new block into the free buckets based on LIFO strategy. */
static void insert(free_block_t *block, size_t index)
{
    free_block_t *freehead;

    freehead = heap.buckets[index];
    block->next = freehead;
    block->prev = NULL;
    if (freehead)
        freehead->prev = block;

    heap.buckets[index] = block;
}

static free_block_t *remove_at(free_block_t *block, size_t index)
{
    free_block_t *prevblk, *nextblk;

    prevblk = block->prev;
    nextblk = block->next;
    if (prevblk)
        prevblk->next = nextblk;
    else
        heap.buckets[index] = nextblk;

    if (nextblk)
        nextblk->prev = prevblk;

    block->next = NULL;
    block->prev = NULL;
    return block;
}

static void *slice(free_block_t *block, size_t sz)
{
    size_t blocksz, leftsz;
    free_block_t *remain;

    blocksz = block->header.sz;
    leftsz = blocksz - sz;

    /* If the left size is less than the minimum block size, return the whole
     * block, since it is not worth splitting and acceptable internal
     * fragmentation. */
    if (leftsz < MINIMUM_THRESHOLD) {
        write_meta((block_t *)block, blocksz, true, false);
        return (void *)((unsigned char *)block + sizeof(header_t));
    }

    /* Otherwise, split the block into two parts: the first part is the
     * requested size, the second part is the remaining block. */
    remain = (free_block_t *)((unsigned char *)block + sz);
    write_meta((block_t *)block, sz, true, false);
    write_meta((block_t *)remain, leftsz, false, false);
    insert(remain, get_bucket_index(leftsz));

    return (void *)((unsigned char *)block + sizeof(header_t));
}

static void coalescing_mid(free_block_t *prev, free_block_t *block,
                           free_block_t *next)
{
    size_t newsz;

    if (prev->header.alloc && next->header.alloc) /* no coalescing needed */
    {
        write_meta((block_t *)block, block->header.sz, false, false);
        insert(block, get_bucket_index(block->header.sz));
        return;
    }

    if (prev->header.alloc &&
        !next->header.alloc) /* coalescing the next block */
    {
        newsz = block->header.sz + next->header.sz;
        remove_at(next, get_bucket_index(next->header.sz));
        write_meta((block_t *)block, newsz, false, false);
        insert(block, get_bucket_index(newsz));
        return;
    }

    if (!prev->header.alloc &&
        next->header.alloc) /* coalescing the previous block */
    {
        newsz = block->header.sz + prev->header.sz;
        remove_at(prev, get_bucket_index(prev->header.sz));
        write_meta((block_t *)prev, newsz, false, false);
        insert(prev, get_bucket_index(newsz));
        return;
    }

    else /* coalescing the previous and next blocks */
    {
        newsz = prev->header.sz + block->header.sz + next->header.sz;
        remove_at(next, get_bucket_index(next->header.sz));
        remove_at(prev, get_bucket_index(prev->header.sz));
        write_meta((block_t *)prev, newsz, false, false);
        insert(prev, get_bucket_index(newsz));
        return;
    }
}

static void coalescing(free_block_t *block)
{
    bool isfirst, islast;
    block_t *next, *prev;
    footer_t *prevfooter;

    isfirst = ((unsigned char *)block == heap.start);
    islast = ((unsigned char *)((unsigned char *)block + block->header.sz) ==
              heap.end);

    /* If the current block is the first block in the heap, coalescing the next
     * block is needed.*/
    if (isfirst) {
        next = (block_t *)((unsigned char *)block + block->header.sz);
        if (!islast && !next->header.alloc) {
            size_t newsz = block->header.sz + next->header.sz;
            remove_at((free_block_t *)next, get_bucket_index(next->header.sz));
            write_meta((block_t *)block, newsz, false, false);
            insert(block, get_bucket_index(newsz));
        } else {
            write_meta((block_t *)block, block->header.sz, false, false);
            insert(block, get_bucket_index(block->header.sz));
        }
        return;
    }

    prevfooter = (footer_t *)((unsigned char *)block - sizeof(footer_t));
    prev = (block_t *)((unsigned char *)block - prevfooter->sz);

    /* If the current block is the last block in the heap, coalescing the
     * previous block is needed.*/
    if (islast) {
        if (!prev->header.alloc) {
            size_t newsz = block->header.sz + prev->header.sz;
            remove_at((free_block_t *)prev, get_bucket_index(prev->header.sz));
            write_meta((block_t *)prev, newsz, false, false);
            insert((free_block_t *)prev, get_bucket_index(newsz));
        } else {
            write_meta((block_t *)block, block->header.sz, false, false);
            insert(block, get_bucket_index(block->header.sz));
        }
        return;
    }

    next = (block_t *)((unsigned char *)block + block->header.sz);
    coalescing_mid((free_block_t *)prev, block, (free_block_t *)next);
}

__attribute__((unused)) static void *firstfit(size_t sz, size_t index)
{
    free_block_t *block;
    void *p;

    block = heap.buckets[index];

    while (block) {
        if (block->header.sz >= sz) {
            remove_at(block, index);
            p = slice(block, sz);
            return p;
        }
        block = block->next;
    }
    return NULL;
}

static void *bestfit(size_t sz, size_t index)
{
    free_block_t *block;
    free_block_t *bestblock;
    void *p;

    block = heap.buckets[index];
    bestblock = NULL;

    while (block) {
        if (block->header.sz >= sz) {
            if (!bestblock || block->header.sz < bestblock->header.sz)
                bestblock = block;
        }
        block = block->next;
    }
    if (bestblock) {
        remove_at(bestblock, index);
        p = slice(bestblock, sz);
        return p;
    }
    return NULL;
}

static int init_heap(void)
{
    memset(heap.buckets, 0, sizeof(heap.buckets));
    heap.start = (unsigned char *)sbrk(0);
    heap.end = heap.start;
    heap.init = true;
    return 0;
}

/* Grow the heap with sbrk and insert the new span as one free block. */
static inline int refill(size_t sz)
{
    void *p;
    free_block_t *block;

    p = sbrk((intptr_t)sz);
    if (p == (void *)-1)
        return -1;

    block = (free_block_t *)p;
    write_meta((block_t *)block, sz, false, false);
    insert(block, get_bucket_index(sz));
    heap.end = (unsigned char *)p + sz;
    return 0;
}

void *malloc(size_t size)
{
    size_t needed;
    size_t index;
    size_t refillsz;
    void *p;

    if (size >= MMAP_THRESHOLD) {
        size_t mmapsz = ALIGN_PAGE(size + sizeof(header_t));

        if (mmapsz > MAX_BLOCK_SIZE) {
            errno = ENOMEM;
            return NULL;
        }
        p = mmap(NULL, mmapsz, PROT_READ | PROT_WRITE,
                 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (p == MAP_FAILED) {
            errno = ENOMEM;
            return NULL;
        }
        write_meta((block_t *)p, mmapsz, true, true);
        return (void *)((unsigned char *)p + sizeof(header_t));
    }

    if (!heap.init) {
        if (init_heap() == -1) {
            errno = ENOMEM;
            return NULL;
        }
    }

    if (!size)
        return NULL;

    needed = calc_needed_size(size);
    index = get_bucket_index(needed);
    while (index < BUCKET_COUNT) {
        p = bestfit(needed, index);
        if (p)
            return p;
        ++index;
    }

    refillsz = MAX(needed, PAGE_SIZE);
    if (refill(refillsz) == -1) {
        errno = ENOMEM;
        return NULL;
    }
    return bestfit(needed, get_bucket_index(refillsz));
}

void free(void *ptr)
{
    block_t *block;

    if (!ptr)
        return;

    block = (block_t *)((unsigned char *)ptr - sizeof(header_t));
    if (block->header.ismmap) {
        munmap((void *)block, block->header.sz);
        return;
    }
    if (!heap.init)
        return;

    coalescing((free_block_t *)block);
}

void *calloc(size_t num, size_t size)
{
    size_t bytes;
    void *p;

    if (!num || !size)
        return NULL;

    if (__builtin_mul_overflow(num, size, &bytes)) {
        errno = ENOMEM;
        return NULL;
    }

    p = malloc(bytes);
    /* mmap anonymous pages are already zero. */
    if (p && bytes < MMAP_THRESHOLD)
        memset(p, 0, bytes);
    return p;
}

void *realloc(void *ptr, size_t new_size)
{
    block_t *block;
    block_t *next;
    size_t oldpayload;
    size_t needed;
    bool islast;

    if (!ptr)
        return malloc(new_size);
    if (!new_size) {
        free(ptr);
        return NULL;
    }

    block = (block_t *)((unsigned char *)ptr - sizeof(header_t));
    if (block->header.ismmap)
        oldpayload = block->header.sz - sizeof(header_t);
    else
        oldpayload = block->header.sz - sizeof(header_t) - sizeof(footer_t);

    /* fast path: return if the old payload is large enough */
    if (oldpayload >= new_size)
        return ptr;

    if (block->header.ismmap) /* if the block is allocated by mmap, use mremap
                                 to resize the block */
    {
        size_t newsz = ALIGN_PAGE(new_size + sizeof(header_t));

        if (newsz > MAX_BLOCK_SIZE) {
            errno = ENOMEM;
            return NULL;
        }
        void *newptr = mremap((unsigned char *)block, block->header.sz, newsz,
                              MREMAP_MAYMOVE);
        if (newptr == MAP_FAILED) {
            errno = ENOMEM;
            return NULL;
        }
        write_meta((block_t *)newptr, newsz, true, true);
        return (void *)((unsigned char *)newptr + sizeof(header_t));
    }

    needed = calc_needed_size(new_size);
    next = (block_t *)((unsigned char *)block + block->header.sz);
    islast = ((unsigned char *)next >= heap.end);

    if (!islast && !next->header.alloc) {
        size_t newsz = block->header.sz + next->header.sz;
        if (newsz >= needed) {
            size_t leftsz;

            remove_at((free_block_t *)next, get_bucket_index(next->header.sz));
            leftsz = newsz - needed;
            if (leftsz < MINIMUM_THRESHOLD) {
                write_meta(block, newsz, true, false);
            } else {
                free_block_t *remain =
                    (free_block_t *)((unsigned char *)block + needed);
                write_meta(block, needed, true, false);
                write_meta((block_t *)remain, leftsz, false, false);
                insert(remain, get_bucket_index(leftsz));
            }
            return ptr;
        }
    }

    {
        /* slow path: allocate a new block and copy the data */
        void *newptr = malloc(new_size);
        if (!newptr)
            return NULL;
        memcpy(newptr, ptr, MIN(oldpayload, new_size));
        free(ptr);
        return newptr;
    }
}
