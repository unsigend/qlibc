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

static inline long __syscall0_raw(uint64_t __num) {
  uint64_t ret;
  __asm__ volatile("syscall" : "=a"(ret) : "a"(__num) : "rcx", "r11", "memory");
  return ret;
}
static inline long __syscall1_raw(uint64_t __num, uint64_t __arg1) {
  uint64_t ret;
  __asm__ volatile("syscall"
                   : "=a"(ret)
                   : "a"(__num), "D"(__arg1)
                   : "rcx", "r11", "memory");
  return ret;
}
static inline long __syscall2_raw(uint64_t __num, uint64_t __arg1,
                                  uint64_t __arg2) {
  uint64_t ret;
  __asm__ volatile("syscall"
                   : "=a"(ret)
                   : "a"(__num), "D"(__arg1), "S"(__arg2)
                   : "rcx", "r11", "memory");
  return ret;
}
static inline long __syscall3_raw(uint64_t __num, uint64_t __arg1,
                                  uint64_t __arg2, uint64_t __arg3) {
  uint64_t ret;
  __asm__ volatile("syscall"
                   : "=a"(ret)
                   : "a"(__num), "D"(__arg1), "S"(__arg2), "d"(__arg3)
                   : "rcx", "r11", "memory");
  return ret;
}
static inline long __syscall4_raw(uint64_t __num, uint64_t __arg1,
                                  uint64_t __arg2, uint64_t __arg3,
                                  uint64_t __arg4) {
  uint64_t ret;
  register uint64_t r10 __asm__("r10") = __arg4;
  __asm__ volatile("syscall"
                   : "=a"(ret)
                   : "a"(__num), "D"(__arg1), "S"(__arg2), "d"(__arg3), "r"(r10)
                   : "rcx", "r11", "memory");
  return ret;
}
static inline long __syscall5_raw(uint64_t __num, uint64_t __arg1,
                                  uint64_t __arg2, uint64_t __arg3,
                                  uint64_t __arg4, uint64_t __arg5) {
  uint64_t ret;
  register uint64_t r10 __asm__("r10") = __arg4;
  register uint64_t r8 __asm__("r8") = __arg5;
  __asm__ volatile("syscall"
                   : "=a"(ret)
                   : "a"(__num), "D"(__arg1), "S"(__arg2), "d"(__arg3),
                     "r"(r10), "r"(r8)
                   : "rcx", "r11", "memory");
  return ret;
}
static inline long __syscall6_raw(uint64_t __num, uint64_t __arg1,
                                  uint64_t __arg2, uint64_t __arg3,
                                  uint64_t __arg4, uint64_t __arg5,
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
  return ret;
}

// __syscall just a wrapper for the raw syscall functions
#define __syscall0(NUM) __syscall_ret(__syscall0_raw(NUM))
#define __syscall1(NUM, ARG1) __syscall_ret(__syscall1_raw(NUM, ARG1))
#define __syscall2(NUM, ARG1, ARG2)                                            \
  __syscall_ret(__syscall2_raw(NUM, ARG1, ARG2))
#define __syscall3(NUM, ARG1, ARG2, ARG3)                                      \
  __syscall_ret(__syscall3_raw(NUM, ARG1, ARG2, ARG3))
#define __syscall4(NUM, ARG1, ARG2, ARG3, ARG4)                                \
  __syscall_ret(__syscall4_raw(NUM, ARG1, ARG2, ARG3, ARG4))
#define __syscall5(NUM, ARG1, ARG2, ARG3, ARG4, ARG5)                          \
  __syscall_ret(__syscall5_raw(NUM, ARG1, ARG2, ARG3, ARG4, ARG5))
#define __syscall6(NUM, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6)                    \
  __syscall_ret(__syscall6_raw(NUM, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6))

#include <bits/NR.h>
#endif