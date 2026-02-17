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

#ifndef _QLIBC_SYS_IOCTL_H_
#define _QLIBC_SYS_IOCTL_H_

#include <bits/ioctl.h>
#include <feature.h>

__BEGIN_DECLS

/* Manipulates the underlying device parameters of special files, this function
   is used for no-standard I/O operations. The implementation is
   architecture-dependent. */
extern int ioctl(int fd, int request, ...);

__END_DECLS

#endif