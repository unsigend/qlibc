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
#include <unistd.h>

/* The current implementation of sbrk is not thread-safe, it has no lock
   protection and it is not recommend for user to call this function to break
   the heap state that malloc will use. */

void *sbrk(intptr_t increment) {
  static void *__addr;
  if (!__addr) {
    __addr = __brk(0);
  }
  void *oldaddr = __addr;
  if (increment) {
    void *retaddr = __brk((unsigned char *)__addr + increment);
    if ((increment > 0 && retaddr < __addr) ||
        (increment < 0 && retaddr >= __addr)) {
      errno = ENOMEM;
      return (void *)-1;
    }
    __addr = retaddr;
  }
  return oldaddr;
}