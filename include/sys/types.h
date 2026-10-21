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

#ifndef _QLIBC_SYS_TYPES_H_
#define _QLIBC_SYS_TYPES_H_

#include <bits/types.h>
#include <bits/typesizes.h>

typedef __pid_t pid_t;
typedef __uid_t uid_t;
typedef __gid_t gid_t;
typedef __id_t id_t;
typedef __mode_t mode_t;
typedef __key_t key_t;
typedef __useconds_t useconds_t;
typedef __suseconds_t suseconds_t;
typedef __clock_t clock_t;
typedef __clockid_t clockid_t;
typedef __timer_t timer_t;
typedef __socklen_t socklen_t;
typedef __sig_atomic_t sig_atomic_t;
typedef __sigset_t sigset_t;

typedef __dev_t dev_t;
typedef __dev64_t dev64_t;

typedef __off_t off_t;
typedef __off64_t off64_t;

typedef __ssize_t ssize_t;
typedef __ssize64_t ssize64_t;

typedef __blksize_t blksize_t;
typedef __blksize64_t blksize64_t;

typedef __blkcnt_t blkcnt_t;
typedef __blkcnt64_t blkcnt64_t;

typedef __time_t time_t;
typedef __time64_t time64_t;

typedef __ino_t ino_t;
typedef __ino64_t ino64_t;

typedef __nlink_t nlink_t;
typedef __nlink64_t nlink64_t;

#endif /* _QLIBC_SYS_TYPES_H_ */
