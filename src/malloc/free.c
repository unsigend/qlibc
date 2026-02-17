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
#include "mm/coalescing.h"
#include <sys/mman.h>

/* Free memory allocated by malloc */
void free(void *ptr) {
  if (!ptr)
    return;

  block_t *block = (block_t *)((unsigned char *)ptr - sizeof(header_t));
  if (IS_MMAP(block)) {
    munmap((void *)block, block->header.sz);
    return;
  }
  if (!__heap.init)
    return;

  coalescing((free_block_t *)block);
}
