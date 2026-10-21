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

#ifndef _QLIBC_SYS_STAT_H_
#define _QLIBC_SYS_STAT_H_

#include <bits/stat.h>
#include <feature.h>
#include <sys/types.h>

#define S_IRUSR 00400 /* user read */
#define S_IWUSR 00200 /* user write */
#define S_IXUSR 00100 /* user execute */
#define S_IRWXU (S_IRUSR | S_IWUSR | S_IXUSR)
#define S_IRGRP 00040 /* group read */
#define S_IWGRP 00020 /* group write */
#define S_IXGRP 00010 /* group execute */
#define S_IRWXG (S_IRGRP | S_IWGRP | S_IXGRP)
#define S_IROTH 00004 /* other read */
#define S_IWOTH 00002 /* other write */
#define S_IXOTH 00001 /* other execute */
#define S_IRWXO (S_IROTH | S_IWOTH | S_IXOTH)

#define S_ISUID 04000 /* set-user-ID */
#define S_ISGID 02000 /* set-group-ID */
#define S_ISVTX 01000 /* sticky */

#define S_IFMT 0170000   /* type mask */
#define S_IFIFO 0010000  /* FIFO */
#define S_IFCHR 0020000  /* character device */
#define S_IFDIR 0040000  /* directory */
#define S_IFBLK 0060000  /* block device */
#define S_IFREG 0100000  /* regular file */
#define S_IFLNK 0120000  /* symlink */
#define S_IFSOCK 0140000 /* socket */

#define S_ISFIFO(m) (((m) & S_IFMT) == S_IFIFO)
#define S_ISCHR(m) (((m) & S_IFMT) == S_IFCHR)
#define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#define S_ISBLK(m) (((m) & S_IFMT) == S_IFBLK)
#define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#define S_ISLNK(m) (((m) & S_IFMT) == S_IFLNK)
#define S_ISSOCK(m) (((m) & S_IFMT) == S_IFSOCK)

#ifdef __cplusplus
extern "C" {
#endif

extern int stat(const char *__restrict path, struct stat *__restrict buf);
extern int fstat(int fd, struct stat *__restrict buf);
extern int lstat(const char *__restrict path, struct stat *__restrict buf);

#ifdef __cplusplus
}
#endif

#endif /* _QLIBC_SYS_STAT_H_ */
