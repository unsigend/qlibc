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

#ifndef _QLIBC_SIGNAL_H_
#define _QLIBC_SIGNAL_H_

#include <feature.h>
#include <sys/types.h>

/* Type of a signal handler. */
typedef void (*sighandler_t)(int);

__BEGIN_DECLS

/* Sends a signal to the process specified by pid. If pid>0, then sends to
   the process with the given process ID. If pid=0, then sends to the current
   process group. If pid=-1, then sends to all processes in the current process
   group. */
extern int kill(pid_t pid, int sig);

/* Sets the signal handler for the signal specified by signum to the function
   specified by handler. Returns the previous signal handler for the signal.

   NOTE: This function has compatibility issues with different UNIX
   implementations. Use sigaction instead. */
extern sighandler_t signal(int signum, sighandler_t handler);

__END_DECLS

#endif