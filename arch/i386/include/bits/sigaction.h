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

#ifndef _BITS_SIGACTION_H_
#define _BITS_SIGACTION_H_ 1

#include <bits/types.h>

#define SA_NOCLDSTOP 1 /* Don't send SIGCHLD when children stop.  */
#define SA_NOCLDWAIT 2 /* Don't create zombie on child death.  */
#define SA_SIGINFO                                                            \
  4 /* Invoke signal-catching function with three arguments instead of one.   \
     */
#define SA_RESETHAND 0x80000000 /* Reset to SIG_DFL when entry to handler. */
#define SA_RESTART 0x10000000   /* Restart system calls on signal return. */
#define SA_NODEFER                                                            \
  0x40000000 /* Don't automatically block the signal when it's handler is     \
                being executed. */

/* Structure describing the action to be taken when a signal arrives. */
struct sigaction
{
  void (*sa_handler)(int);   /* Address of handler */
  __sigset_t sa_mask;        /* Signals blocked during handler invocation */
  int sa_flags;              /* Flags controlling handler invocation */
  void (*sa_restorer)(void); /* Restore handler. (Not for application use.)*/
};

/* Values for the HOW argument to `sigprocmask'.  */
#define SIG_BLOCK 0   /* Block signals.  */
#define SIG_UNBLOCK 1 /* Unblock signals.  */
#define SIG_SETMASK 2 /* Set the set of blocked signals.  */

#endif