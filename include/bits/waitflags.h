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

#ifndef _BITS_WAITFLAGS_H_
#define _BITS_WAITFLAGS_H_ 1

#define WNOHANG 1    /* Don't block waiting. */
#define WUNTRACED 2  /* Report status of stopped children. */
#define WCONTINUED 8 /* Report continued child. */

#define __W_CONTINUED 0xffff /* Continued child */
#define __WCOREFLAG 0x80     /* Core dump flag */
#define __WTERMSIG(status)                                                    \
  ((status) & 0x7f) /* Get the signal number that killed the process */

#define WIFEXITED(status)                                                     \
  (__WTERMSIG(status) == 0) /* If the process exited normally */
#define WEXITSTATUS(status)                                                   \
  (((status) & 0xff00) >> 8) /* Get the exit status of the process */

#define WIFSIGNALED(status)                                                   \
  (((signed char)(((status) & 0x7f) + 1) >> 1)                                \
   > 0) /* If the process was terminated by a signal */
#define WTERMSIG(status)                                                      \
  __WTERMSIG(status) /* Get the signal number that killed the process */
#define WCOREDUMP(status)                                                     \
  ((status) & __WCOREFLAG) /* If the process dumped core */

#define WIFSTOPPED(status)                                                    \
  (((status) & 0xff) == 0x7f) /* If the process was stopped */
#define WSTOPSIG(status)                                                      \
  WEXITSTATUS(status) /* Get the signal number that stopped the process */

#define WIFCONTINUED(status)                                                  \
  ((status) == __W_CONTINUED) /* If the process was continued */

#endif