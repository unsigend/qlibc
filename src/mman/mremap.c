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

#include <stdarg.h>
#include <sys/mman.h>
#include <syscall.h>
#include <syscall_arch.h>

void *mremap(void *old_addr, size_t old_len, size_t new_len, int flags, ...)
{
    void *new_addr = NULL;

    if (flags & MREMAP_FIXED) {
        va_list ap;

        va_start(ap, flags);
        new_addr = va_arg(ap, void *);
        va_end(ap);
    }

    return (void *)__syscall(SYS_mremap, (long)old_addr, (long)old_len,
                             (long)new_len, (long)flags, (long)new_addr);
}
