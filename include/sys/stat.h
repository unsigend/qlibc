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

#ifndef _QLIBC_SYS_STAT_H_
#define _QLIBC_SYS_STAT_H_

#include <bits/stat.h>
#include <sys/types.h>

/*
 * Based on the Unix conversion, the macros here are kernel I-node table related
 */

/* file permission flags */
#define S_IRUSR 00400
#define S_IWUSR 00200
#define S_IXUSR 00100
#define S_IRWXU (S_IRUSR | S_IWUSR | S_IXUSR)
#define S_IRGRP 00040
#define S_IWGRP 00020
#define S_IXGRP 00010
#define S_IRWXG (S_IRGRP | S_IWGRP | S_IXGRP)
#define S_IROTH 00004
#define S_IWOTH 00002
#define S_IXOTH 00001
#define S_IRWXO (S_IROTH | S_IWOTH | S_IXOTH)

/* file type flags */
#define S_IFMT 0170000
#define S_IFDIR 0040000
#define S_IFCHR 0020000
#define S_IFBLK 0060000
#define S_IFREG 0100000
#define S_IFIFO 0010000
#define S_IFLNK 0120000
#define S_IFSOCK 0140000

#define S_ISDIR(mode) (((mode) & S_IFMT) == S_IFDIR)
#define S_ISCHR(mode) (((mode) & S_IFMT) == S_IFCHR)
#define S_ISBLK(mode) (((mode) & S_IFMT) == S_IFBLK)
#define S_ISREG(mode) (((mode) & S_IFMT) == S_IFREG)
#define S_ISFIFO(mode) (((mode) & S_IFMT) == S_IFIFO)
#define S_ISLNK(mode) (((mode) & S_IFMT) == S_IFLNK)
#define S_ISSOCK(mode) (((mode) & S_IFMT) == S_IFSOCK)

#ifdef __cplusplus
extern "C" {
#endif

extern int stat(const char *restrict path, struct stat *restrict buf);
extern int fstat(int fd, struct stat *restrict buf);
extern int lstat(const char *restrict path, struct stat *restrict buf);

#ifdef __cplusplus
}
#endif

#endif