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

/* An integral type that can be modified atomically, without the
   possibility of a signal arriving in the middle of the operation.  */
typedef __sig_atomic_t sig_atomic_t;

/* Macros for signal() function. */
#define SIG_ERR ((sighandler_t) - 1) /* Error return. */
#define SIG_DFL ((sighandler_t)0)    /* Default action. */
#define SIG_IGN ((sighandler_t)1)    /* Ignore signal. */

/* ISO C99 signals.  */
#define SIGINT 2   /* Interactive attention signal.  */
#define SIGILL 4   /* Illegal instruction.  */
#define SIGABRT 6  /* Abnormal termination.  */
#define SIGFPE 8   /* Erroneous arithmetic operation.  */
#define SIGSEGV 11 /* Invalid access to storage.  */
#define SIGTERM 15 /* Termination request.  */

/* Historical signals specified by POSIX. */
#define SIGHUP 1   /* Hangup.  */
#define SIGQUIT 3  /* Quit.  */
#define SIGTRAP 5  /* Trace/breakpoint trap.  */
#define SIGKILL 9  /* Killed.  */
#define SIGPIPE 13 /* Broken pipe.  */
#define SIGALRM 14 /* Alarm clock.  */

/* Archaic names for compatibility.  */
#define SIGIO SIGPOLL  /* I/O now possible (4.2 BSD).  */
#define SIGIOT SIGABRT /* IOT instruction, abort() on a PDP-11.  */
#define SIGCLD SIGCHLD /* Old System V name */

#include <bits/signum-arch.h>

__BEGIN_DECLS

/* Sends a signal to the process specified by pid. If pid>0, then sends to
   the process with the given process ID. If pid=0, then sends to the current
   process group. If pid=-1, then sends to all processes in the current process
   group. */
extern int kill(pid_t pid, int sig);

/* Sets the signal handler for the signal specified by signum to the function
   specified by handler. Returns the previous signal handler for the signal.

   NOTE: This function implementation is layer on top of the sigaction function.
   So it is compatible with different UNIX implementations. */
extern sighandler_t signal(int signum, sighandler_t handler);

__END_DECLS

#endif