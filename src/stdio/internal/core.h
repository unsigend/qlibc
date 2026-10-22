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

#ifndef _STDIO_CORE_H_
#define _STDIO_CORE_H_

#include <stdarg.h>
#include <stddef.h>

/* Reader for scanf core, it is a thin wrapper that custom the behaviour of
 * scanf core, scanf will call readc and unreadc to read and unread characters.
 */
struct reader {
    int (*readc)(void *ctx);          /* read a character */
    int (*unreadc)(int c, void *ctx); /* unread a character */
    void *ctx;                        /* opaque context pointer*/
};

extern int printf_core(char *restrict buf, size_t bufsz,
                       const char *restrict fmt, va_list vlist);
extern int scanf_core(struct reader *reader, const char *restrict fmt,
                      va_list vlist);

#endif