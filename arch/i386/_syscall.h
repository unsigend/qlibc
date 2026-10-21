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

#ifndef _QLIBC_I386__SYSCALL_H_
#define _QLIBC_I386__SYSCALL_H_

#include <errno.h>
#include <stdint.h>

static inline long syscall_ret(uint32_t ret)
{
    if (ret >= -4096U) {
        errno = -ret;
        return -1;
    }
    return ret;
}

static inline long syscall0_raw(uint32_t num)
{
    uint32_t ret;
    __asm__ volatile("int $0x80" : "=a"(ret) : "a"(num) : "memory");
    return ret;
}

static inline long syscall1_raw(uint32_t num, uint32_t arg1)
{
    uint32_t ret;
    __asm__ volatile("int $0x80" : "=a"(ret) : "a"(num), "b"(arg1) : "memory");
    return ret;
}

static inline long syscall2_raw(uint32_t num, uint32_t arg1, uint32_t arg2)
{
    uint32_t ret;
    __asm__ volatile("int $0x80"
                     : "=a"(ret)
                     : "a"(num), "b"(arg1), "c"(arg2)
                     : "memory");
    return ret;
}

static inline long syscall3_raw(uint32_t num, uint32_t arg1, uint32_t arg2,
                                uint32_t arg3)
{
    uint32_t ret;
    __asm__ volatile("int $0x80"
                     : "=a"(ret)
                     : "a"(num), "b"(arg1), "c"(arg2), "d"(arg3)
                     : "memory");
    return ret;
}

static inline long syscall4_raw(uint32_t num, uint32_t arg1, uint32_t arg2,
                                uint32_t arg3, uint32_t arg4)
{
    uint32_t ret;
    __asm__ volatile("int $0x80"
                     : "=a"(ret)
                     : "a"(num), "b"(arg1), "c"(arg2), "d"(arg3), "S"(arg4)
                     : "memory");
    return ret;
}

static inline long syscall5_raw(uint32_t num, uint32_t arg1, uint32_t arg2,
                                uint32_t arg3, uint32_t arg4, uint32_t arg5)
{
    uint32_t ret;
    __asm__ volatile("int $0x80"
                     : "=a"(ret)
                     : "a"(num), "b"(arg1), "c"(arg2), "d"(arg3), "S"(arg4),
                       "D"(arg5)
                     : "memory");
    return ret;
}

static inline long syscall6_raw(uint32_t num, uint32_t arg1, uint32_t arg2,
                                uint32_t arg3, uint32_t arg4, uint32_t arg5,
                                uint32_t arg6)
{
    uint32_t ret;
    __asm__ volatile("pushl %7\n\t"
                     "pushl %%ebp\n\t"
                     "movl 4(%%esp), %%ebp\n\t"
                     "int $0x80\n\t"
                     "popl %%ebp\n\t"
                     "addl $4, %%esp"
                     : "=a"(ret)
                     : "a"(num), "b"(arg1), "c"(arg2), "d"(arg3), "S"(arg4),
                       "D"(arg5), "g"(arg6)
                     : "memory");
    return ret;
}

#define syscall0(nr) syscall_ret(syscall0_raw(nr))
#define syscall1(nr, arg1) syscall_ret(syscall1_raw(nr, arg1))
#define syscall2(nr, arg1, arg2) syscall_ret(syscall2_raw(nr, arg1, arg2))
#define syscall3(nr, arg1, arg2, arg3)                                         \
    syscall_ret(syscall3_raw(nr, arg1, arg2, arg3))
#define syscall4(nr, arg1, arg2, arg3, arg4)                                   \
    syscall_ret(syscall4_raw(nr, arg1, arg2, arg3, arg4))
#define syscall5(nr, arg1, arg2, arg3, arg4, arg5)                             \
    syscall_ret(syscall5_raw(nr, arg1, arg2, arg3, arg4, arg5))
#define syscall6(nr, arg1, arg2, arg3, arg4, arg5, arg6)                       \
    syscall_ret(syscall6_raw(nr, arg1, arg2, arg3, arg4, arg5, arg6))

#endif /* _QLIBC_I386__SYSCALL_H_ */