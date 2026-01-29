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

#ifndef _QLIBC_X86_64_BITS_STAT_H_
#define _QLIBC_X86_64_BITS_STAT_H_

#include <bits/types.h>
#include <time.h>

/*
 * The stat structure for x64 architecture is based on GNU glibc.
 */
struct stat {
  __dev_t st_dev;           /* ID of device containing file */
  __ino_t st_ino;           /* inode number */
  __nlink_t st_nlink;       /* number of hard links */
  __mode_t st_mode;         /* file type and mode */
  __uid_t st_uid;           /* user ID of owner */
  __gid_t st_gid;           /* group ID of owner */
  unsigned int __padding;   /* padding */
  __dev_t st_rdev;          /* device ID (if special file) */
  __off_t st_size;          /* total size, in bytes */
  __blksize_t st_blksize;   /* block size for filesystem I/O */
  __blkcnt_t st_blocks;     /* number of 512B blocks allocated */
  struct timespec st_atime; /* time of last access */
  struct timespec st_mtime; /* time of last modification */
  struct timespec st_ctime; /* time of last status change */
  long __unused[3];         /* backwards compatibility */
};

#define st_atime st_atime.tv_sec
#define st_mtime st_mtime.tv_sec
#define st_ctime st_ctime.tv_sec

#endif