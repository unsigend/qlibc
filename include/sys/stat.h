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
#include <feature.h>
#include <sys/types.h>

/* Based on the Unix conversion, the macros here are kernel I-node table
   related. And all the macors related to the I-node will be under sys/ */

/* file permission flags */
#define S_IRUSR 00400 /* User read permission */
#define S_IWUSR 00200 /* User write permission */
#define S_IXUSR 00100 /* User execute permission */
#define S_IRWXU                                                                \
  (S_IRUSR | S_IWUSR | S_IXUSR) /* User read, write, and execute permission */
#define S_IRGRP 00040           /* Group read permission */
#define S_IWGRP 00020           /* Group write permission */
#define S_IXGRP 00010           /* Group execute permission */
#define S_IRWXG                                                                \
  (S_IRGRP | S_IWGRP | S_IXGRP) /* Group read, write, and execute permission   \
                                 */
#define S_IROTH 00004           /* Other read permission */
#define S_IWOTH 00002           /* Other write permission */
#define S_IXOTH 00001           /* Other execute permission */
#define S_IRWXO                                                                \
  (S_IROTH | S_IWOTH | S_IXOTH) /* Other read, write, and execute permission   \
                                 */

/* file type flags */
#define S_IFMT 0170000   /* File type mask */
#define S_IFDIR 0040000  /* Directory */
#define S_IFCHR 0020000  /* Character device */
#define S_IFBLK 0060000  /* Block device */
#define S_IFREG 0100000  /* Regular file */
#define S_IFIFO 0010000  /* FIFO */
#define S_IFLNK 0120000  /* Symbolic link */
#define S_IFSOCK 0140000 /* Socket */

#define S_ISDIR(mode)                                                          \
  (((mode) & S_IFMT) == S_IFDIR) /* Check if the file is a directory */
#define S_ISCHR(mode)                                                          \
  (((mode) & S_IFMT) == S_IFCHR) /* Check if the file is a character device */
#define S_ISBLK(mode)                                                          \
  (((mode) & S_IFMT) == S_IFBLK) /* Check if the file is a block device */
#define S_ISREG(mode)                                                          \
  (((mode) & S_IFMT) == S_IFREG) /* Check if the file is a regular file */
#define S_ISFIFO(mode)                                                         \
  (((mode) & S_IFMT) == S_IFIFO) /* Check if the file is a FIFO */
#define S_ISLNK(mode)                                                          \
  (((mode) & S_IFMT) == S_IFLNK) /* Check if the file is a symbolic link */
#define S_ISSOCK(mode)                                                         \
  (((mode) & S_IFMT) == S_IFSOCK) /* Check if the file is a socket */

__BEGIN_DECLS

/* Get the metadata of the file */
extern int stat(const char *restrict path, struct stat *restrict buf);

/* Get the metadata of the file associated with the file descriptor */
extern int fstat(int fd, struct stat *restrict buf);

/* Get the metadata of the file, but if the file is a symbolic link, the
   metadata of the link is returned */
extern int lstat(const char *restrict path, struct stat *restrict buf);

__END_DECLS

#endif