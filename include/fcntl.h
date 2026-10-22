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

#define F_DUPFD_CLOEXEC 1030 /* dup and set FD_CLOEXEC */
#define FD_CLOEXEC 1         /* close-on-exec */

#define AT_FDCWD (-100)           /* openat cwd */
#define AT_SYMLINK_NOFOLLOW 0x100 /* do not follow symlink */
#define AT_REMOVEDIR 0x200        /* unlinkat directory */
#define AT_SYMLINK_FOLLOW 0x400   /* follow symlink */

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
