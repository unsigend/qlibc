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
#include <stdint.h>
#include <sys/types.h>

#define STDIN_FILENO 0  /* Standard input file descriptor */
#define STDOUT_FILENO 1 /* Standard output file descriptor */
#define STDERR_FILENO 2 /* Standard error file descriptor */

#define SEEK_SET 0 /* Set file position to offset */
#define SEEK_CUR 1 /* Set file position to current position + offset */
#define SEEK_END 2 /* Set file position to end of file + offset */

__BEGIN_DECLS

/* Closes the file referred to by the file descriptor fd. */
extern int close(int fd);

/* Sets the file position of the file referred to by the file descriptor fd to
   the specified offset. */
extern off_t lseek(int fd, off_t offset, int whence);

/* Returns the current file position of the file referred to by the file
   descriptor fd. This function is not part of POSIX standard. */
extern off_t tell(int fd);

/* Reads data from the file referred to by the file descriptor fd into the
   buffer buf. */
extern ssize_t read(int fd, void *buf, size_t count);

/* Writes data to the file referred to by the file descriptor fd at the
   specified offset. */
extern ssize_t write(int fd, const void *buf, size_t count);

/* Creates a new file descriptor that is a copy of the file descriptor fd. */
extern int dup(int fd);
extern int dup2(int fd, int fd2);
extern int dup3(int fd, int fd2, int flags);

/* Reads data from the file referred to by the file descriptor fd at the
   specified offset. The file position is not changed. */
extern ssize_t pread(int fd, void *buf, size_t count, off_t offset);

/* Writes data to the file referred to by the file descriptor fd at the
   specified offset. The file position is not changed. */
extern ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset);

/* Truncates the file referred to by the pathname to the specified length. */
extern int truncate(const char *path, off_t length);

/* Truncates the file referred to by the file descriptor fd to the specified
   length. */
extern int ftruncate(int fd, off_t length);

/* Makes a system call with the given number and arguments. */
extern long syscall(long __number, ...);

/* Flushes all modified data of the file referred to by the file descriptor fd
   to the disk device. */
extern int fsync(int fd);

/* Flushes all modified data of the file referred to by the file descriptor fd
   to the disk device, but does not synchronize the filesystem metadata. */
extern int fdatasync(int fd);

/* Synchronizes all pending modifications to filesystem metadata and cached file
   data to be written to the underlying filesystems. */
extern int sync(void);

/* Checks if the file descriptor is associated with a terminal. */
extern int isatty(int fd);

/* Deletes the name and file information associated with pathname from the file
   system. */
extern int unlink(const char *pathname);

/* Sets the end of the data segment to the value specified by addr, when
   that value is reasonable, the system has enough memory, and the process
   does not exceed its maximum data size */
extern int brk(void *addr);

#ifdef _QLIBC_SOURCE
/* This function is not part of POSIX standard, just used for internal use of
   qlibc extension. */
extern void *__brk(void *addr);
#endif

/* Increments the program's data space by increment bytes. Calling sbrk()
   with an increment of 0 can be used to find the current location of the
   program break.*/
extern void *sbrk(intptr_t increment);

__END_DECLS

#endif