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

#ifndef _QLIBC_I386_BITS_SIGNAL_H_
#define _QLIBC_I386_BITS_SIGNAL_H_

/* A set of signals to be blocked, unblocked, or waited for.*/
typedef unsigned long long __sigset_t;

/* Structure describing the action to be taken when a signal arrives. */
struct sigaction {
  void (*sa_handler)(int);   /* Address of handler */
  __sigset_t sa_mask;        /* Signals blocked during handler invocation */
  int sa_flags;              /* Flags controlling handler invocation */
  void (*sa_restorer)(void); /* Restore handler. (Not for application use.)*/
};

#endif