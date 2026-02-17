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
#include <errno.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <unistd.h>

#define OFF_MASK ((-0x2000ULL << (8 * sizeof(long) - 1)) | 0xfff)
#define PAGEBITS 12

void *mmap(void *addr, size_t length, int prot, int flags, int fd,
           off_t offset) {
  long ret = 0;
  if (offset & OFF_MASK) {
    errno = EINVAL;
    return MAP_FAILED;
  }
  if (length >= PTRDIFF_MAX) {
    errno = ENOMEM;
    return MAP_FAILED;
  }

#ifdef SYS_mmap2
  ret = __syscall6_raw(SYS_mmap2, (uintptr_t)addr, length, prot, flags, fd,
                       offset >> PAGEBITS);
#else
  ret = __syscall6_raw(SYS_mmap, (uintptr_t)addr, length, prot, flags, fd,
                       offset);
#endif
  if (ret == -EPERM && !addr && (flags & MAP_ANONYMOUS) && !(flags & MAP_FIXED))
    ret = -ENOMEM;
  return (void *)__syscall_ret(ret);
}