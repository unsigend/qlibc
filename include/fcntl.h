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

/* Based on the Unix conversion, the macros here are kernel open file table
   related. */

#define O_RDONLY 0          /* Read only */
#define O_WRONLY 1          /* Write only */
#define O_RDWR 2            /* Read and write */
#define O_CLOEXEC 02000000  /* Close on exec */
#define O_CREAT 0100        /* Create */
#define O_DIRECTORY 0200000 /* Directory */
#define O_EXCL 0200         /* Exclusive creation */
#define O_LARGEFILE 0       /* Large file */
#ifdef __i386__
#undef O_LARGEFILE
#define O_LARGEFILE 0100000 /* Large file */
#endif
#define O_NOCTTY 0400      /* No control tty */
#define O_NOFOLLOW 0400000 /* No follow */
#define O_TRUNC 01000      /* Truncate */
#define O_APPEND 02000     /* Append */
#define O_ASYNC 020000     /* Async */
#define O_DIRECT 040000    /* Direct */
#define O_DSYNC 010000     /* Data sync */
#define O_NOATIME 01000000 /* No atime */
#define O_NONBLOCK 04000   /* Non-blocking */
#define O_SYNC 04010000    /* Sync */
#define O_ACCMODE 0x03     /* Access mode mask */

#define F_GETFL 3 /* Get file status flags */
#define F_SETFL 4 /* Set file status flags */

__BEGIN_DECLS

/* Opens the file specified by pathname with the specified flags and mode. */
extern int open(const char *pathname, int flags, ...);

/* Creates a new file with the specified name and permissions. This function is
   equivalent to open(pathname, O_CREAT | O_WRONLY | O_TRUNC, mode). And is a
   POSIX extension.*/
extern int creat(const char *pathname, mode_t mode);

/* Controls the file descriptor fd. */
extern int fcntl(int fd, int cmd, ...);

__END_DECLS

#endif