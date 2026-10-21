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

#ifndef _QLIBC_FCNTL_H_
#define _QLIBC_FCNTL_H_

#include <bits/fcntl.h>
#include <feature.h>
#include <sys/types.h>

#define O_RDONLY 0  /* read only */
#define O_WRONLY 1  /* write only */
#define O_RDWR 2    /* read and write */
#define O_ACCMODE 3 /* access mode mask */

#define O_CREAT 0100                        /* create if missing */
#define O_EXCL 0200                         /* fail if exists with O_CREAT */
#define O_NOCTTY 0400                       /* do not assign controlling tty */
#define O_TRUNC 01000                       /* truncate to 0 */
#define O_APPEND 02000                      /* append on write */
#define O_NONBLOCK 04000                    /* do not block */
#define O_DSYNC 010000                      /* sync data */
#define O_ASYNC 020000                      /* SIGIO on I/O */
#define O_DIRECT 040000                     /* direct I/O */
#define O_DIRECTORY 0200000                 /* must be a directory */
#define O_NOFOLLOW 0400000                  /* do not follow symlinks */
#define O_NOATIME 01000000                  /* do not update atime */
#define O_CLOEXEC 02000000                  /* close on exec */
#define O_SYNC 04010000                     /* sync data and metadata */
#define O_PATH 010000000                    /* path-only fd */
#define O_TMPFILE (020000000 | O_DIRECTORY) /* unnamed temporary file */

#define F_DUPFD 0 /* duplicate fd */
#define F_GETFD 1 /* get fd flags */
#define F_SETFD 2 /* set fd flags */
#define F_GETFL 3 /* get status flags */
#define F_SETFL 4 /* set status flags */

#define FD_CLOEXEC 1 /* close-on-exec fd flag */

#ifdef __cplusplus
extern "C" {
#endif

extern int open(const char *path, int flags, ...);
extern int creat(const char *path, mode_t mode);
extern int fcntl(int fd, int cmd, ...);

#ifdef __cplusplus
}
#endif

#endif /* _QLIBC_FCNTL_H_ */
