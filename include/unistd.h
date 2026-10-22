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

#ifndef _QLIBC_UNISTD_H_
#define _QLIBC_UNISTD_H_

#include <feature.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define F_OK 0 /* existence */
#define X_OK 1 /* execute */
#define W_OK 2 /* write */
#define R_OK 4 /* read */

#ifdef __cplusplus
extern "C" {
#endif

extern int close(int fd);
extern off_t lseek(int fd, off_t offset, int whence);
extern ssize_t read(int fd, void *buf, size_t count);
extern ssize_t write(int fd, const void *buf, size_t count);
extern int dup(int fd);
extern int dup2(int fd, int fd2);
extern int dup3(int fd, int fd2, int flags);
extern int pipe(int fd[2]);
extern int pipe2(int fd[2], int flags);
extern ssize_t pread(int fd, void *buf, size_t count, off_t offset);
extern ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset);
extern int truncate(const char *path, off_t length);
extern int ftruncate(int fd, off_t length);
extern long syscall(long number, ...);
extern int fsync(int fd);
extern int fdatasync(int fd);
extern void sync(void);
extern int isatty(int fd);
extern int access(const char *pathname, int amode);
extern int chdir(const char *path);
extern int fchdir(int fd);
extern int chown(const char *path, uid_t uid, gid_t gid);
extern int fchown(int fd, uid_t uid, gid_t gid);
extern int lchown(const char *path, uid_t uid, gid_t gid);
extern int fchownat(int fd, const char *path, uid_t uid, gid_t gid, int flag);
extern int link(const char *oldpath, const char *newpath);
extern int linkat(int oldfd, const char *oldpath, int newfd, const char *newpath,
                  int flag);
extern int symlink(const char *target, const char *linkpath);
extern int symlinkat(const char *target, int newfd, const char *linkpath);
extern ssize_t readlink(const char *path, char *buf, size_t bufsize);
extern ssize_t readlinkat(int fd, const char *path, char *buf, size_t bufsize);
extern int unlink(const char *pathname);
extern int unlinkat(int fd, const char *pathname, int flag);
extern int rmdir(const char *pathname);
extern int brk(void *addr);
extern void *sbrk(intptr_t increment);
extern pid_t getpid(void);
extern pid_t getppid(void);
extern pid_t getpgrp(void);
extern pid_t getpgid(pid_t pid);
extern int setpgid(pid_t pid, pid_t pgid);
extern pid_t setsid(void);
extern pid_t getsid(pid_t pid);
extern pid_t fork(void);
extern unsigned int sleep(unsigned int seconds);
extern int pause(void);
extern unsigned int alarm(unsigned int seconds);
extern int execve(const char *filename, char *const argv[], char *const envp[]);
extern uid_t getuid(void);
extern uid_t geteuid(void);
extern gid_t getgid(void);
extern gid_t getegid(void);
extern int getgroups(int size, gid_t list[]);
extern int setuid(uid_t uid);
extern int setgid(gid_t gid);
extern int setreuid(uid_t ruid, uid_t euid);
extern int setregid(gid_t rgid, gid_t egid);
extern int setgroups(size_t size, const gid_t *list);
extern int setresuid(uid_t ruid, uid_t euid, uid_t suid);
extern int setresgid(gid_t rgid, gid_t egid, gid_t sgid);
extern int getresuid(uid_t *ruid, uid_t *euid, uid_t *suid);
extern int getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid);
extern pid_t gettid(void);
extern int sethostname(const char *name, size_t len);

#if __STDC_VERSION__ >= __ISO_C11
extern _Noreturn void _exit(int status);
#else
extern void _exit(int status) __attribute__((__noreturn__));
#endif

#ifdef __cplusplus
}
#endif

#endif /* _QLIBC_UNISTD_H_ */