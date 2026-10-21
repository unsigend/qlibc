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

#ifndef _QLIBC_SYS_WAIT_H_
#define _QLIBC_SYS_WAIT_H_

#include <feature.h>
#include <sys/types.h>

#define WNOHANG 1    /* do not block */
#define WUNTRACED 2  /* report stopped children */
#define WCONTINUED 8 /* report continued children */

#define __W_CONTINUED 0xffff
#define __WCOREFLAG 0x80
#define __WTERMSIG(status) ((status) & 0x7f)

#define WIFEXITED(status) (__WTERMSIG(status) == 0)
#define WEXITSTATUS(status) (((status) & 0xff00) >> 8)
#define WIFSIGNALED(status) (((signed char)(((status) & 0x7f) + 1) >> 1) > 0)
#define WTERMSIG(status) __WTERMSIG(status)
#define WCOREDUMP(status) ((status) & __WCOREFLAG)
#define WIFSTOPPED(status) (((status) & 0xff) == 0x7f)
#define WSTOPSIG(status) WEXITSTATUS(status)
#define WIFCONTINUED(status) ((status) == __W_CONTINUED)

#ifdef __cplusplus
extern "C" {
#endif

extern pid_t waitpid(pid_t pid, int *status, int options);
extern pid_t wait(int *status);

#ifdef __cplusplus
}
#endif

#endif /* _QLIBC_SYS_WAIT_H_ */