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

#ifndef _SYS_MMAN_H_
#define _SYS_MMAN_H_ 1

#include <bits/mmanflags.h>
#include <stddef.h>
#include <sys/types.h>

__BEGIN_DECLS

/* Map a new mapping in the virtual address space of the calling process. The
   starting address for the new mapping is specified in addr. The length
   argument specifies the length of the mapping */
extern void *mmap(void *addr, size_t length, int prot, int flags, int fd,
                  off_t offset);

/* Unmap a mapping from the virtual address space of the calling process. */
extern int munmap(void *addr, size_t length);

/* Remap a mapping in the virtual address space of the calling process. */
extern void *mremap(void *old_addr, size_t old_len, size_t new_len, int flags,
                    ...);

__END_DECLS

#endif