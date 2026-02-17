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

#include <stdint.h>
#include <sys/syscall.h>

/* __brk is a wrapper for the Linux kernel brk system call, this function is
   used to get the heap top address, and this function implementation is not
   part of POSIX standard. It will always return the previous heap address and
   ignore the errno. */

void *__brk(void *addr) {
  return (void *)__syscall1_raw(SYS_brk, (uintptr_t)addr);
}
