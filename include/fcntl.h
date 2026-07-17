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

#ifndef _FCNTL_H_
#define _FCNTL_H_ 1

#include <feature.h>
#include <sys/types.h>

/* Based on the Unix conversion, the macros here are kernel open file table
   related. */
#include <bits/fcntl.h>

__BEGIN_DECLS

extern int open(const char *pathname, int flags, ...);
extern int creat(const char *pathname, mode_t mode);
extern int fcntl(int fd, int cmd, ...);

__END_DECLS

#endif