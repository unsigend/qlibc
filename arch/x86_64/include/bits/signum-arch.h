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

#ifndef _QLIBC_X86_64_BITS_SIGNUM_ARCH_H_
#define _QLIBC_X86_64_BITS_SIGNUM_ARCH_H_

#define SIGSTKFLT 16 /* Stack fault (obsolete).  */
#define SIGPWR 30    /* Power failure imminent.  */

/* Historical signals specified by POSIX. */
#define SIGBUS 7  /* Bus error.  */
#define SIGSYS 31 /* Bad system call.  */

/* New POSIX signals.  */
#define SIGURG 23    /* Urgent data is available at a socket.  */
#define SIGSTOP 19   /* Stop, unblockable.  */
#define SIGTSTP 20   /* Keyboard stop.  */
#define SIGCONT 18   /* Continue.  */
#define SIGCHLD 17   /* Child terminated or stopped.  */
#define SIGTTIN 21   /* Background read from control terminal.  */
#define SIGTTOU 22   /* Background write to control terminal.  */
#define SIGPOLL 29   /* Pollable event occurred (System V).  */
#define SIGXFSZ 25   /* File size limit exceeded.  */
#define SIGXCPU 24   /* CPU time limit exceeded.  */
#define SIGVTALRM 26 /* Virtual timer expired.  */
#define SIGPROF 27   /* Profiling timer expired.  */
#define SIGUSR1 10   /* User-defined signal 1.  */
#define SIGUSR2 12   /* User-defined signal 2.  */

/* Nonstandard signals found in all modern POSIX systems
   (including both BSD and Linux).  */
#define SIGWINCH 28 /* Window size change.  */

/* Archaic names for compatibility.  */
#define SIGIO SIGPOLL  /* I/O now possible (4.2 BSD).  */
#define SIGIOT SIGABRT /* IOT instruction, abort() on a PDP-11.  */
#define SIGCLD SIGCHLD /* Old System V name */

#endif