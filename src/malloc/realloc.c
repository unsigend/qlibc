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

void *realloc(void *ptr, size_t new_size) {
  /* realloc(NULL, size) is equivalent to malloc(size) */
  if (!ptr)
    return malloc(new_size);
  /* realloc(ptr, 0) is equivalent to free(ptr) */
  if (!new_size) {
    free(ptr);
    return NULL;
  }
  block_t *block = (block_t *)((unsigned char *)ptr - sizeof(header_t));
  size_t old_payloadsz;

  /* If the block is allocated by mmap, use mremap to resize the block */
  if (IS_MMAP(block)) {
    old_payloadsz = block->header.sz - sizeof(header_t);
  } else {
    old_payloadsz = block->header.sz - sizeof(header_t) - sizeof(footer_t);
  }

  /* If the payload size is large enough, return the pointer to the old block */
  if (old_payloadsz >= new_size)
    return ptr;

  /* If the block is allocated by mmap, use mremap to resize the block */
  if (IS_MMAP(block)) {
    size_t newsz = ALIGN_PAGE(new_size + sizeof(header_t));
    void *new_ptr =
        mremap((unsigned char *)block, block->header.sz, newsz, MREMAP_MAYMOVE);
    if (new_ptr == MAP_FAILED) {
      errno = ENOMEM;
      return NULL;
    }
    write_meta((block_t *)new_ptr, newsz, true, true);
    return (void *)((unsigned char *)new_ptr + sizeof(header_t));
  }

  /* Optimize with in-place expansion */
  size_t required_sz = calc_block_sz(new_size);
  block_t *next_block = (block_t *)((unsigned char *)block + block->header.sz);
  bool is_last_block = ((unsigned char *)next_block >= __heap.heap_end);

  if (!is_last_block && !next_block->header.alloc) {
    size_t newsz = block->header.sz + next_block->header.sz;
    if (newsz >= required_sz) {
      remove_block((free_block_t *)next_block,
                   get_bucket_idx(next_block->header.sz));
      size_t leftsz = newsz - required_sz;

      /* If the left size is less than the minimum block size, return the whole
         block */
      if (leftsz < MINIMUM_BLOCKSZ) {
        write_meta((block_t *)block, newsz, true, false);
      } else {
        free_block_t *remaining_block =
            (free_block_t *)((unsigned char *)block + required_sz);
        write_meta((block_t *)block, required_sz, true, false);
        write_meta((block_t *)remaining_block, leftsz, false, false);
        insert_block(remaining_block, get_bucket_idx(leftsz));
      }

      return ptr;
    }
  }

  /* Fallback to malloc, copy and free case, CPU intensive case. */
  void *new_ptr = malloc(new_size);
  if (!new_ptr)
    return NULL;
  /* Copy the data from the old block to the new block */
  memcpy(new_ptr, ptr, MIN(old_payloadsz, new_size));
  free(ptr);
  return new_ptr;
}
