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
#include <stdarg.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/syscall.h>

void *mremap(void *old_addr, size_t old_len, size_t new_len, int flags, ...) {
  va_list ap;
  void *new_addr = NULL;

  if (new_len >= PTRDIFF_MAX) {
    errno = ENOMEM;
    return MAP_FAILED;
  }

  if (flags & MREMAP_FIXED) {
    va_start(ap, flags);
    new_addr = va_arg(ap, void *);
    va_end(ap);
  }

  return (void *)__syscall(SYS_mremap, (long)old_addr, old_len, new_len, flags,
                           (long)new_addr);
}