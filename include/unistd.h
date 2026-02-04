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

#ifndef _QLIBC_UNISTD_H_
#define _QLIBC_UNISTD_H_

#include <feature.h>
#include <stddef.h>
#include <sys/types.h>

/* standard file descriptors */
#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

/* seek flags */
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#ifdef __cplusplus
extern "C" {
#endif

extern int close(int fd);
extern off_t lseek(int fd, off_t offset, int whence);
extern off_t tell(int fd);
extern ssize_t read(int fd, void *buf, size_t count);
extern ssize_t write(int fd, const void *buf, size_t count);
extern int dup(int fd);
extern int dup2(int fd, int fd2);
extern int dup3(int fd, int fd2, int flags);
extern ssize_t pread(int fd, void *buf, size_t count, off_t offset);
extern ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset);
extern int truncate(const char *path, off_t length);
extern int ftruncate(int fd, off_t length);
extern long syscall(long __number, ...);
extern int fsync(int fd);
extern int fdatasync(int fd);
extern int sync(void);

#ifdef __cplusplus
}
#endif

#endif