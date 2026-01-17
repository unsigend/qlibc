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

#ifndef _QLIBC_I386_SYSDEP_SYSCALL_H_
#define _QLIBC_I386_SYSDEP_SYSCALL_H_

#include <errno.h>
#include <stdint.h>

#undef __syscall0
#undef __syscall1
#undef __syscall2
#undef __syscall3
#undef __syscall4
#undef __syscall5
#undef __syscall6

static inline long __syscall_ret(uint32_t __ret){
    if (__ret >= -4096U){
        errno = -__ret;
        return -1;
    }
    return __ret;
}

static inline long __syscall0(uint32_t __num){
    uint32_t ret;
    __asm__ volatile (
        "int $0x80"
        : "=a" (ret)
        : "a" (__num)
        : "memory"
    );
    return __syscall_ret(ret);
}

static inline long __syscall1(uint32_t __num, uint32_t __arg1){
    uint32_t ret;
    __asm__ volatile (
        "int $0x80"
        : "=a" (ret)
        : "a" (__num), "b" (__arg1)
        : "memory"
    );
    return __syscall_ret(ret);
}
static inline long __syscall2(uint32_t __num, uint32_t __arg1, uint32_t __arg2){
    uint32_t ret;
    __asm__ volatile (
        "int $0x80"
        : "=a" (ret)
        : "a" (__num), "b" (__arg1), "c" (__arg2)
        : "memory"
    );
    return __syscall_ret(ret);
}
static inline long __syscall3(uint32_t __num, uint32_t __arg1, uint32_t __arg2, uint32_t __arg3){
    uint32_t ret;
    __asm__ volatile (
        "int $0x80"
        : "=a" (ret)
        : "a" (__num), "b" (__arg1), "c" (__arg2), "d" (__arg3)
        : "memory"
    );
    return __syscall_ret(ret);
}
static inline long __syscall4(uint32_t __num, uint32_t __arg1, uint32_t __arg2, uint32_t __arg3, uint32_t __arg4){
    uint32_t ret;
    __asm__ volatile (
        "int $0x80"
        : "=a" (ret)
        : "a" (__num), "b" (__arg1), "c" (__arg2), "d" (__arg3), "S" (__arg4)
        : "memory"
    );
    return __syscall_ret(ret);
}
static inline long __syscall5(uint32_t __num, uint32_t __arg1, uint32_t __arg2, uint32_t __arg3, uint32_t __arg4, uint32_t __arg5){
    uint32_t ret;
    __asm__ volatile (
        "int $0x80"
        : "=a" (ret)
        : "a" (__num), "b" (__arg1), "c" (__arg2), "d" (__arg3), "S" (__arg4), "D" (__arg5)
        : "memory"
    );
    return __syscall_ret(ret);
}
static inline long __syscall6(uint32_t __num, uint32_t __arg1, uint32_t __arg2, uint32_t __arg3, uint32_t __arg4, uint32_t __arg5, uint32_t __arg6){
    uint32_t ret;
    register uint32_t ebp __asm__("ebp") = __arg6;
    __asm__ volatile (
        "int $0x80"
        : "=a" (ret)
        : "a" (__num), "b" (__arg1), "c" (__arg2), "d" (__arg3), "S" (__arg4), "D" (__arg5), "r" (ebp)
        : "memory"
    );
    return __syscall_ret(ret);
}

#include <sysdep/NR.h>
#endif