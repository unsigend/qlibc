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

#ifndef _QLIBC_X86_64_SYSDEP_TERMIOS_H_
#define _QLIBC_X86_64_SYSDEP_TERMIOS_H_

typedef unsigned char __cc_t;
typedef unsigned int __tcflag_t;
typedef unsigned int __speed_t;

#define __NCCS 32

struct termios {
  __tcflag_t c_iflag;  /* input mode flags */
  __tcflag_t c_oflag;  /* output mode flags */
  __tcflag_t c_cflag;  /* control mode flags */
  __tcflag_t c_lflag;  /* local mode flags */
  __cc_t c_line;       /* line discipline */
  __cc_t c_cc[__NCCS]; /* character class */
  __speed_t c_ispeed;  /* input speed */
  __speed_t c_ospeed;  /* output speed */
};

#endif