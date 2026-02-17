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

#ifndef _QLIBC_SYS_UIO_H_
#define _QLIBC_SYS_UIO_H_

#include <feature.h>
#include <stddef.h>
#include <sys/types.h>

struct iovec {
  void *iov_base; /* Base address of the memory area */
  size_t iov_len; /* Length of the memory area */
};

__BEGIN_DECLS
/* Read data from the file referred to by the file descriptor fd into the
   memory areas specified by the iovec array. */
extern ssize_t readv(int fd, const struct iovec *iov, int iovcnt);

/* Write data to the file referred to by the file descriptor fd from the
   memory areas specified by the iovec array. */
extern ssize_t writev(int fd, const struct iovec *iov, int iovcnt);

#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
/* Read data from the file referred to by the file descriptor fd into the
   memory areas specified by the iovec array at the specified offset. The file
   position is not changed. */
extern ssize_t preadv(int fd, const struct iovec *iov, int iovcnt,
                      off_t offset);

/* Write data to the file referred to by the file descriptor fd from the
   memory areas specified by the iovec array at the specified offset. The file
   position is not changed. */
extern ssize_t pwritev(int fd, const struct iovec *iov, int iovcnt,
                       off_t offset);
#endif

__END_DECLS

#endif