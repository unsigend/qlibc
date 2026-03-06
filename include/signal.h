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

typedef void (*__sighandler_t)(int);

/* An integral type that can be modified atomically, without the
   possibility of a signal arriving in the middle of the operation.  */
typedef __sig_atomic_t sig_atomic_t;

typedef __sigset_t sigset_t;
typedef __sighandler_t sighandler_t;

#include <bits/signum-generic.h> /* Generic signals numbers */

__BEGIN_DECLS

/* Sends a signal to the process specified by pid. If pid>0, then sends to
   the process with the given process ID. If pid=0, then sends to the current
   process group. If pid<-1, then sends to all processes in the pid group
   specified by pid. If pid=-1, send to every process the calling process have
   permission to send signals to. */
extern int kill(pid_t pid, int sig);

/* Sets the signal handler for the signal specified by signum to the function
   specified by handler. Returns the previous signal handler for the signal.

   NOTE: This function implementation is layer on top of the sigaction function.
   So it is compatible with different UNIX implementations. */
extern sighandler_t signal(int signum, sighandler_t handler);

/* Raises a signal to the current process or thread. */
extern int raise(int sig);

/* Send a signal to all of the members of a process group. */
extern int killpg(int pgrp, int sig);

/* Returns a string or print the signal description specified by sig. */
extern char *strsignal(int sig);
extern void psignal(int sig, const char *msg);

/* Clear or set all signals in the set. */
extern int sigemptyset(sigset_t *set);
extern int sigfillset(sigset_t *set);

/* Add or delete a signal from the set. */
extern int sigaddset(sigset_t *set, int signum);
extern int sigdelset(sigset_t *set, int signum);

/* Check if a signal is a member of the set. */
extern int sigismember(const sigset_t *set, int signum);

#if defined(_QLIBC_SOURCE) || defined(_GNU_SOURCE)
/* Set the intersection or union of two sets. */
extern int sigandset(sigset_t *dest, const sigset_t *left,
                     const sigset_t *right);
extern int sigorset(sigset_t *dest, const sigset_t *left,
                    const sigset_t *right);

/* Check if the set is empty. */
extern int sigisemptyset(const sigset_t *set);
#endif

/* Get and/or change the signal mask of the calling thread. */
extern int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);

/* Get the set of pending signals for the calling thread or process. */
extern int sigpending(sigset_t *set);

#include <bits/sigaction.h>

/* Set the action for a signal. */
extern int sigaction(int signum, const struct sigaction *act,
                     struct sigaction *oldact);

__END_DECLS

#endif