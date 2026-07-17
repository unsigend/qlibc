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

#ifndef _UNISTD_H_
#define _UNISTD_H_ 1

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

__BEGIN_DECLS

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

extern long syscall(long number, ...);
extern int fsync(int fd);
extern int fdatasync(int fd);
extern int sync(void);

extern int isatty(int fd);
extern int unlink(const char *pathname);

extern int rmdir(const char *pathname);
extern int brk(void *addr);
extern void *sbrk(intptr_t increment);

#ifdef _QLIBC_SOURCE
/* This function is not part of POSIX standard, just used for internal use of
   qlibc extension. */
extern void *__brk(void *addr);
#endif

extern pid_t getpid(void);
extern pid_t getppid(void);
extern pid_t getpgrp(void);
extern int setpgid(pid_t pid, pid_t pgid);
extern pid_t fork(void);
extern unsigned int sleep(unsigned int seconds);
extern int pause(void);
extern unsigned int alarm(unsigned int seconds);
extern int execve(const char *filename, const char *argv[], const char *envp[]);

#if __USE_ISO_C11
#include <stdnoreturn.h>
extern noreturn void _exit(int status);
#else
extern void _exit(int status);
#endif

__END_DECLS

#endif