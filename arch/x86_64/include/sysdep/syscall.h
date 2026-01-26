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

#ifndef _QLIBC_X86_64_SYSDEP_SYSCALL_H_
#define _QLIBC_X86_64_SYSDEP_SYSCALL_H_

#include <errno.h>
#include <stdint.h>

#undef __syscall0
#undef __syscall1
#undef __syscall2
#undef __syscall3
#undef __syscall4
#undef __syscall5
#undef __syscall6

static inline long __syscall_ret(uint64_t __ret) {
  if (__ret >= -4096UL) {
    errno = -__ret;
    return -1;
  }
  return __ret;
}

static inline long __syscall0(uint64_t __num) {
  uint64_t ret;
  __asm__ volatile("syscall" : "=a"(ret) : "a"(__num) : "rcx", "r11", "memory");
  return __syscall_ret(ret);
}
static inline long __syscall1(uint64_t __num, uint64_t __arg1) {
  uint64_t ret;
  __asm__ volatile("syscall"
                   : "=a"(ret)
                   : "a"(__num), "D"(__arg1)
                   : "rcx", "r11", "memory");
  return __syscall_ret(ret);
}
static inline long __syscall2(uint64_t __num, uint64_t __arg1,
                              uint64_t __arg2) {
  uint64_t ret;
  __asm__ volatile("syscall"
                   : "=a"(ret)
                   : "a"(__num), "D"(__arg1), "S"(__arg2)
                   : "rcx", "r11", "memory");
  return __syscall_ret(ret);
}
static inline long __syscall3(uint64_t __num, uint64_t __arg1, uint64_t __arg2,
                              uint64_t __arg3) {
  uint64_t ret;
  __asm__ volatile("syscall"
                   : "=a"(ret)
                   : "a"(__num), "D"(__arg1), "S"(__arg2), "d"(__arg3)
                   : "rcx", "r11", "memory");
  return __syscall_ret(ret);
}
static inline long __syscall4(uint64_t __num, uint64_t __arg1, uint64_t __arg2,
                              uint64_t __arg3, uint64_t __arg4) {
  uint64_t ret;
  register uint64_t r10 __asm__("r10") = __arg4;
  __asm__ volatile("syscall"
                   : "=a"(ret)
                   : "a"(__num), "D"(__arg1), "S"(__arg2), "d"(__arg3), "r"(r10)
                   : "rcx", "r11", "memory");
  return __syscall_ret(ret);
}
static inline long __syscall5(uint64_t __num, uint64_t __arg1, uint64_t __arg2,
                              uint64_t __arg3, uint64_t __arg4,
                              uint64_t __arg5) {
  uint64_t ret;
  register uint64_t r10 __asm__("r10") = __arg4;
  register uint64_t r8 __asm__("r8") = __arg5;
  __asm__ volatile("syscall"
                   : "=a"(ret)
                   : "a"(__num), "D"(__arg1), "S"(__arg2), "d"(__arg3),
                     "r"(r10), "r"(r8)
                   : "rcx", "r11", "memory");
  return __syscall_ret(ret);
}
static inline long __syscall6(uint64_t __num, uint64_t __arg1, uint64_t __arg2,
                              uint64_t __arg3, uint64_t __arg4, uint64_t __arg5,
                              uint64_t __arg6) {
  uint64_t ret;
  register uint64_t r10 __asm__("r10") = __arg4;
  register uint64_t r8 __asm__("r8") = __arg5;
  register uint64_t r9 __asm__("r9") = __arg6;
  __asm__ volatile("syscall"
                   : "=a"(ret)
                   : "a"(__num), "D"(__arg1), "S"(__arg2), "d"(__arg3),
                     "r"(r10), "r"(r8), "r"(r9)
                   : "rcx", "r11", "memory");
  return __syscall_ret(ret);
}

#include <sysdep/NR.h>
#endif