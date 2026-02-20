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

#ifndef _QLIBC_X86_64_BITS_TYPES_H_
#define _QLIBC_X86_64_BITS_TYPES_H_

typedef unsigned long __dev_t;
typedef __dev_t __dev64_t;

typedef long __off_t;
typedef __off_t __off64_t;

typedef long __ssize_t;
typedef __ssize_t __ssize64_t;

typedef long __blksize_t;
typedef __blksize_t __blksize64_t;

typedef long __blkcnt_t;
typedef __blkcnt_t __blkcnt64_t;

typedef long __time_t;
typedef __time_t __time64_t;

typedef unsigned long __ino_t;
typedef __ino_t __ino64_t;

typedef unsigned long __nlink_t;
typedef __nlink_t __nlink64_t;

typedef unsigned int __mode_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned int __pid_t;

#endif