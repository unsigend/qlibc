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

#ifndef _QLIBC_AARCH64__SYSCALL_H_
#define _QLIBC_AARCH64__SYSCALL_H_

#include <errno.h>
#include <stdint.h>

static inline long syscall_ret(uint64_t ret)
{
    if (ret >= -4096UL) {
        errno = -ret;
        return -1;
    }
    return ret;
}

static inline long syscall0_raw(uint64_t num)
{
    register uint64_t x8 __asm__("x8") = num;
    register uint64_t x0 __asm__("x0");

    __asm__ volatile("svc 0" : "=r"(x0) : "r"(x8) : "memory", "cc");
    return x0;
}

static inline long syscall1_raw(uint64_t num, uint64_t arg1)
{
    register uint64_t x8 __asm__("x8") = num;
    register uint64_t x0 __asm__("x0") = arg1;

    __asm__ volatile("svc 0" : "+r"(x0) : "r"(x8) : "memory", "cc");
    return x0;
}

static inline long syscall2_raw(uint64_t num, uint64_t arg1, uint64_t arg2)
{
    register uint64_t x8 __asm__("x8") = num;
    register uint64_t x0 __asm__("x0") = arg1;
    register uint64_t x1 __asm__("x1") = arg2;

    __asm__ volatile("svc 0" : "+r"(x0) : "r"(x8), "r"(x1) : "memory", "cc");
    return x0;
}

static inline long syscall3_raw(uint64_t num, uint64_t arg1, uint64_t arg2,
                                uint64_t arg3)
{
    register uint64_t x8 __asm__("x8") = num;
    register uint64_t x0 __asm__("x0") = arg1;
    register uint64_t x1 __asm__("x1") = arg2;
    register uint64_t x2 __asm__("x2") = arg3;

    __asm__ volatile("svc 0"
                     : "+r"(x0)
                     : "r"(x8), "r"(x1), "r"(x2)
                     : "memory", "cc");
    return x0;
}

static inline long syscall4_raw(uint64_t num, uint64_t arg1, uint64_t arg2,
                                uint64_t arg3, uint64_t arg4)
{
    register uint64_t x8 __asm__("x8") = num;
    register uint64_t x0 __asm__("x0") = arg1;
    register uint64_t x1 __asm__("x1") = arg2;
    register uint64_t x2 __asm__("x2") = arg3;
    register uint64_t x3 __asm__("x3") = arg4;

    __asm__ volatile("svc 0"
                     : "+r"(x0)
                     : "r"(x8), "r"(x1), "r"(x2), "r"(x3)
                     : "memory", "cc");
    return x0;
}

static inline long syscall5_raw(uint64_t num, uint64_t arg1, uint64_t arg2,
                                uint64_t arg3, uint64_t arg4, uint64_t arg5)
{
    register uint64_t x8 __asm__("x8") = num;
    register uint64_t x0 __asm__("x0") = arg1;
    register uint64_t x1 __asm__("x1") = arg2;
    register uint64_t x2 __asm__("x2") = arg3;
    register uint64_t x3 __asm__("x3") = arg4;
    register uint64_t x4 __asm__("x4") = arg5;

    __asm__ volatile("svc 0"
                     : "+r"(x0)
                     : "r"(x8), "r"(x1), "r"(x2), "r"(x3), "r"(x4)
                     : "memory", "cc");
    return x0;
}

static inline long syscall6_raw(uint64_t num, uint64_t arg1, uint64_t arg2,
                                uint64_t arg3, uint64_t arg4, uint64_t arg5,
                                uint64_t arg6)
{
    register uint64_t x8 __asm__("x8") = num;
    register uint64_t x0 __asm__("x0") = arg1;
    register uint64_t x1 __asm__("x1") = arg2;
    register uint64_t x2 __asm__("x2") = arg3;
    register uint64_t x3 __asm__("x3") = arg4;
    register uint64_t x4 __asm__("x4") = arg5;
    register uint64_t x5 __asm__("x5") = arg6;

    __asm__ volatile("svc 0"
                     : "+r"(x0)
                     : "r"(x8), "r"(x1), "r"(x2), "r"(x3), "r"(x4), "r"(x5)
                     : "memory", "cc");
    return x0;
}

#define __syscall0(nr) syscall_ret(syscall0_raw(nr))
#define __syscall1(nr, arg1) syscall_ret(syscall1_raw(nr, arg1))
#define __syscall2(nr, arg1, arg2) syscall_ret(syscall2_raw(nr, arg1, arg2))
#define __syscall3(nr, arg1, arg2, arg3)                                       \
    syscall_ret(syscall3_raw(nr, arg1, arg2, arg3))
#define __syscall4(nr, arg1, arg2, arg3, arg4)                                 \
    syscall_ret(syscall4_raw(nr, arg1, arg2, arg3, arg4))
#define __syscall5(nr, arg1, arg2, arg3, arg4, arg5)                           \
    syscall_ret(syscall5_raw(nr, arg1, arg2, arg3, arg4, arg5))
#define __syscall6(nr, arg1, arg2, arg3, arg4, arg5, arg6)                     \
    syscall_ret(syscall6_raw(nr, arg1, arg2, arg3, arg4, arg5, arg6))

#endif /* _QLIBC_AARCH64__SYSCALL_H_ */
