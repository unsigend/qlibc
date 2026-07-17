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

extern int kill(pid_t pid, int sig);
extern sighandler_t signal(int signum, sighandler_t handler);
extern int raise(int sig);
extern int killpg(int pgrp, int sig);
extern char *strsignal(int sig);
extern void psignal(int sig, const char *msg);
extern int sigemptyset(sigset_t *set);
extern int sigfillset(sigset_t *set);
extern int sigaddset(sigset_t *set, int signum);
extern int sigdelset(sigset_t *set, int signum);
extern int sigismember(const sigset_t *set, int signum);

#if defined(_QLIBC_SOURCE) || defined(_GNU_SOURCE)
extern int sigandset(sigset_t *dest, const sigset_t *left,
                     const sigset_t *right);
extern int sigorset(sigset_t *dest, const sigset_t *left,
                    const sigset_t *right);
extern int sigisemptyset(const sigset_t *set);
#endif

extern int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
extern int sigpending(sigset_t *set);

#include <bits/sigaction.h>

extern int sigaction(int signum, const struct sigaction *act,
                     struct sigaction *oldact);

__END_DECLS

#endif