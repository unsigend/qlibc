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

#ifndef _QLIBC_SIGNAL_H_
#define _QLIBC_SIGNAL_H_

#include <feature.h>
#include <sys/types.h>

typedef void (*sighandler_t)(int);
typedef __sig_atomic_t sig_atomic_t;
typedef __sigset_t sigset_t;

#define SIG_ERR ((sighandler_t) - 1) /* error */
#define SIG_DFL ((sighandler_t)0)    /* default */
#define SIG_IGN ((sighandler_t)1)    /* ignore */

#define SIGHUP 1  /* hangup */
#define SIGINT 2  /* interrupt */
#define SIGQUIT 3 /* quit */
#define SIGILL 4  /* illegal instruction */
#define SIGTRAP 5 /* trace/breakpoint */
#define SIGABRT 6 /* abort */
#define SIGIOT SIGABRT
#define SIGBUS 7     /* bus error */
#define SIGFPE 8     /* arithmetic error */
#define SIGKILL 9    /* kill */
#define SIGUSR1 10   /* user signal 1 */
#define SIGSEGV 11   /* invalid memory access */
#define SIGUSR2 12   /* user signal 2 */
#define SIGPIPE 13   /* broken pipe */
#define SIGALRM 14   /* alarm */
#define SIGTERM 15   /* termination */
#define SIGSTKFLT 16 /* stack fault */
#define SIGCHLD 17   /* child status */
#define SIGCLD SIGCHLD
#define SIGCONT 18   /* continue */
#define SIGSTOP 19   /* stop (unblockable) */
#define SIGTSTP 20   /* terminal stop */
#define SIGTTIN 21   /* background read */
#define SIGTTOU 22   /* background write */
#define SIGURG 23    /* socket urgent data */
#define SIGXCPU 24   /* CPU time limit */
#define SIGXFSZ 25   /* file size limit */
#define SIGVTALRM 26 /* virtual alarm */
#define SIGPROF 27   /* profiling alarm */
#define SIGWINCH 28  /* window size */
#define SIGPOLL 29   /* pollable event */
#define SIGIO SIGPOLL
#define SIGPWR 30 /* power fail */
#define SIGSYS 31 /* bad syscall */

#define _NSIG 65
#define NSIG _NSIG

#define SA_NOCLDSTOP 1          /* no SIGCHLD on child stop */
#define SA_NOCLDWAIT 2          /* no zombies */
#define SA_SIGINFO 4            /* three-argument handler */
#define SA_ONSTACK 0x08000000   /* use alternate stack */
#define SA_RESTART 0x10000000   /* restart syscalls */
#define SA_NODEFER 0x40000000   /* do not block this signal */
#define SA_RESETHAND 0x80000000 /* reset to SIG_DFL */
#define SA_RESTORER 0x04000000  /* sa_restorer is valid */

#define SIG_BLOCK 0   /* block extra signals */
#define SIG_UNBLOCK 1 /* unblock signals */
#define SIG_SETMASK 2 /* set mask */

struct sigaction {
    void (*sa_handler)(int);
    sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer)(void);
};

#ifdef __cplusplus
extern "C" {
#endif

extern int kill(pid_t pid, int sig);
extern int killpg(int pgrp, int sig);
extern int raise(int sig);
extern sighandler_t signal(int signum, sighandler_t handler);
extern int sigaction(int signum, const struct sigaction *__restrict act,
                     struct sigaction *__restrict oldact);
extern int sigprocmask(int how, const sigset_t *__restrict set,
                       sigset_t *__restrict oldset);
extern int sigsuspend(const sigset_t *mask);
extern int tgkill(int tgid, int tid, int sig);
extern int sigpending(sigset_t *set);
extern int sigemptyset(sigset_t *set);
extern int sigfillset(sigset_t *set);
extern int sigaddset(sigset_t *set, int signum);
extern int sigdelset(sigset_t *set, int signum);
extern int sigismember(const sigset_t *set, int signum);
extern char *strsignal(int sig);
extern void psignal(int sig, const char *msg);
extern int sigandset(sigset_t *dest, const sigset_t *left,
                     const sigset_t *right);
extern int sigorset(sigset_t *dest, const sigset_t *left,
                    const sigset_t *right);
extern int sigisemptyset(const sigset_t *set);

#ifdef __cplusplus
}
#endif

#endif /* _QLIBC_SIGNAL_H_ */
