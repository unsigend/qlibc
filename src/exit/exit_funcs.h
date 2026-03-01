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

#ifndef _QLIBC_EXIT_FUNCS_H_
#define _QLIBC_EXIT_FUNCS_H_

/* Internal header file for exit functions. */

#include <stddef.h>

/* The minimum number of exit functions is 32. */
#ifdef ATEXIT_MAX
#undef ATEXIT_MAX
#endif
#define ATEXIT_MAX 32

extern int __atexit_lock;
extern void (*__exit_funcs[ATEXIT_MAX])(void);
extern size_t __exit_func_count;

#define LOCK() __atexit_lock = 1;
#define UNLOCK() __atexit_lock = 0;
#define ATEXIT_LOCKED() (__atexit_lock)

#endif