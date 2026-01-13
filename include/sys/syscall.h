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

#ifndef _QLIBC_SYS_SYSCALL_H_
#define _QLIBC_SYS_SYSCALL_H_

/**
 * @brief: Macros for syscall
 * Generic syscall macros provide a common interface for different architectures.
 */
#define __syscall0(NUM)
#define __syscall1(NUM, ARG1)
#define __syscall2(NUM, ARG1, ARG2)
#define __syscall3(NUM, ARG1, ARG2, ARG3)
#define __syscall4(NUM, ARG1, ARG2, ARG3, ARG4)
#define __syscall5(NUM, ARG1, ARG2, ARG3, ARG4, ARG5)
#define __syscall6(NUM, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6)

#include <sysdep/syscall.h>

#endif