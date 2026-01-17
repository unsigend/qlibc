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

#ifndef _QLIBC_AARCH64_SYSDEP_SYSCALL_H_
#define _QLIBC_AARCH64_SYSDEP_SYSCALL_H_

#include <stdint.h>
#include <errno.h>

#undef __syscall0
#undef __syscall1
#undef __syscall2
#undef __syscall3
#undef __syscall4
#undef __syscall5
#undef __syscall6

static inline long __syscall_ret(uint64_t __ret){
    if (__ret >= -4096UL){
        errno = -__ret;
        return -1;
    }
    return __ret;
}

static inline long __syscall0(uint64_t __num){
    register uint64_t x8 __asm__("x8") = __num;
    register uint64_t x0 __asm__("x0");
    __asm__ volatile (
        "svc #0"
        : "=r" (x0)
        : "r" (x8)
        : "memory"
    );
    return __syscall_ret(x0);
}

static inline long __syscall1(uint64_t __num, uint64_t __arg1){
    register uint64_t x8 __asm__("x8") = __num;
    register uint64_t x0 __asm__("x0") = __arg1;
    __asm__ volatile (
        "svc #0"
        : "+r" (x0)
        : "r" (x8)
        : "memory"
    );
    return __syscall_ret(x0);
}

static inline long __syscall2(uint64_t __num, uint64_t __arg1, uint64_t __arg2){
    register uint64_t x8 __asm__("x8") = __num;
    register uint64_t x0 __asm__("x0") = __arg1;
    register uint64_t x1 __asm__("x1") = __arg2;
    __asm__ volatile (
        "svc #0"
        : "+r" (x0)
        : "r" (x8), "r" (x1)
        : "memory"
    );
    return __syscall_ret(x0);
}

static inline long __syscall3(uint64_t __num, uint64_t __arg1, uint64_t __arg2, uint64_t __arg3){
    register uint64_t x8 __asm__("x8") = __num;
    register uint64_t x0 __asm__("x0") = __arg1;
    register uint64_t x1 __asm__("x1") = __arg2;
    register uint64_t x2 __asm__("x2") = __arg3;
    __asm__ volatile (
        "svc #0"
        : "+r" (x0)
        : "r" (x8), "r" (x1), "r" (x2)
        : "memory"
    );
    return __syscall_ret(x0);
}

static inline long __syscall4(uint64_t __num, uint64_t __arg1, uint64_t __arg2, uint64_t __arg3, uint64_t __arg4){
    register uint64_t x8 __asm__("x8") = __num;
    register uint64_t x0 __asm__("x0") = __arg1;
    register uint64_t x1 __asm__("x1") = __arg2;
    register uint64_t x2 __asm__("x2") = __arg3;
    register uint64_t x3 __asm__("x3") = __arg4;
    __asm__ volatile (
        "svc #0"
        : "+r" (x0)
        : "r" (x8), "r" (x1), "r" (x2), "r" (x3)
        : "memory"
    );
    return __syscall_ret(x0);
}

static inline long __syscall5(uint64_t __num, uint64_t __arg1, uint64_t __arg2, uint64_t __arg3, uint64_t __arg4, uint64_t __arg5){
    register uint64_t x8 __asm__("x8") = __num;
    register uint64_t x0 __asm__("x0") = __arg1;
    register uint64_t x1 __asm__("x1") = __arg2;
    register uint64_t x2 __asm__("x2") = __arg3;
    register uint64_t x3 __asm__("x3") = __arg4;
    register uint64_t x4 __asm__("x4") = __arg5;
    __asm__ volatile (
        "svc #0"
        : "+r" (x0)
        : "r" (x8), "r" (x1), "r" (x2), "r" (x3), "r" (x4)
        : "memory"
    );
    return __syscall_ret(x0);
}

static inline long __syscall6(uint64_t __num, uint64_t __arg1, uint64_t __arg2, uint64_t __arg3, uint64_t __arg4, uint64_t __arg5, uint64_t __arg6){
    register uint64_t x8 __asm__("x8") = __num;
    register uint64_t x0 __asm__("x0") = __arg1;
    register uint64_t x1 __asm__("x1") = __arg2;
    register uint64_t x2 __asm__("x2") = __arg3;
    register uint64_t x3 __asm__("x3") = __arg4;
    register uint64_t x4 __asm__("x4") = __arg5;
    register uint64_t x5 __asm__("x5") = __arg6;
    __asm__ volatile (
        "svc #0"
        : "+r" (x0)
        : "r" (x8), "r" (x1), "r" (x2), "r" (x3), "r" (x4), "r" (x5)
        : "memory"
    );
    return __syscall_ret(x0);
}

#include <sysdep/NR.h>
#endif