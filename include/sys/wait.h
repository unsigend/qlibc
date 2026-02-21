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

#ifndef _QLIBC_SYS_WAIT_H_
#define _QLIBC_SYS_WAIT_H_

#include "sys/types.h"
#include <feature.h>

#define WNOHANG 1    /* Don't block waiting. */
#define WUNTRACED 2  /* Report status of stopped children. */
#define WCONTINUED 8 /* Report continued child. */

__BEGIN_DECLS

/* Waits for a child process to exit or stop. If pid > 0, wait for the child
   with the given process ID. If pid == -1, wait for any child. If the process
   has no child, return -1 and set errno to ECHILD.*/
extern pid_t waitpid(pid_t pid, int *status, int options);

/* Waits for any child process to exit or stop. If the process has no child,
   return -1 and set errno to ECHILD. Equivalent to waitpid(-1, status, 0).*/
extern pid_t wait(int *status);

__END_DECLS

#endif