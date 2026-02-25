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

#ifndef _QLIBC_MALLOC_H_
#define _QLIBC_MALLOC_H_

/* This header file is not part of ANSI/ISO C standard, it is a extension of
   the malloc API. Which confirms the GNU glibc malloc extension API. It only
   used for debugging and profiling memory allocation statistics purposes.*/

#include <feature.h>
#include <stddef.h>

/* Malloc extension support */
#if defined(__USE_QLIBC_EXTENDED)
struct mallinfo {
  size_t arena;    /* Non-mmapped space allocated (bytes) */
  size_t ordblks;  /* Number of free chunks */
  size_t smblks;   /* Number of free fastbin blocks */
  size_t hblks;    /* Number of mmapped regions */
  size_t hblkhd;   /* Space allocated in mmapped regions (bytes) */
  size_t usmblks;  /* unused and always zero */
  size_t fsmblks;  /* Space in freed fastbin blocks (bytes) */
  size_t uordblks; /* Total allocated space (bytes) */
  size_t fordblks; /* Total free space (bytes) */
  size_t keepcost; /* Top-most, releasable space (bytes) */
};
#endif

__BEGIN_DECLS
/* Allocate size bytes of uninitialized memory */
extern void *malloc(size_t size);
/* Free memory allocated by malloc */
extern void free(void *ptr);
/* Allocate memory for an array of num elements, each of which is size bytes */
extern void *calloc(size_t num, size_t size);
/* Reallocate memory and invalidate the old memory */
extern void *realloc(void *ptr, size_t new_size);

#if QLIBC_ISO_C_VERSION >= ISO_C_STANDARD_C11
/* Allocate memory with a specific alignment */
extern void *aligned_alloc(size_t alignment, size_t size);
#endif

/* Malloc extension support */
#if defined(__USE_QLIBC_EXTENDED)
/* Get memory allocation information, return 0 on success, -1 on failure, note
   that this is not GNU glibc compatible API */

extern int mallinfo(struct mallinfo *info);
#endif

__END_DECLS

#endif