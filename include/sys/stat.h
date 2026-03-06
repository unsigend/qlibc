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

#ifndef _SYS_STAT_H_
#define _SYS_STAT_H_ 1

#include <bits/stat.h>
#include <feature.h>
#include <sys/types.h>

/* Based on the Unix conversion, the macros here are kernel I-node table
   related. And all the macros related to the I-node will be under sys/ */
#include <bits/statflags.h>

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