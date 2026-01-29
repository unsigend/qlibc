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

#ifndef _QLIBC_FNCNTL_H_
#define _QLIBC_FNCNTL_H_

#include <feature.h>
#include <sys/types.h>

/*
 * Based on the Unix conversion, the macros here are kernel open file table
 * related
 */

/* file access mode flags */
#define O_RDONLY 0
#define O_WRONLY 1
#define O_RDWR 2

/* file creation flags */
#define O_CLOEXEC 02000000
#define O_CREAT 0100
#define O_DIRECTORY 0200000
#define O_EXCL 0200

#define O_LARGEFILE 0
#ifdef __i386__
#undef O_LARGEFILE
#define O_LARGEFILE 0100000
#endif

#define O_NOCTTY 0400
#define O_NOFOLLOW 0400000
#define O_TRUNC 01000

/* file open flags */
#define O_APPEND 02000
#define O_ASYNC 020000
#define O_DIRECT 040000
#define O_DSYNC 010000
#define O_NOATIME 01000000
#define O_NONBLOCK 04000
#define O_SYNC 04010000
#define O_ACCMODE 0x03

/* fcntl flags */
#define F_GETFL 3
#define F_SETFL 4

#ifdef __cplusplus
extern "C" {
#endif

extern int open(const char *pathname, int flags, ...);
extern int creat(const char *pathname, mode_t mode);
extern int fcntl(int fd, int cmd, ...);

#ifdef __cplusplus
}
#endif

#endif