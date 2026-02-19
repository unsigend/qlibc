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

#ifndef _QLIBC_PRINTF_H_
#define _QLIBC_PRINTF_H_

#include <feature.h>
#include <stdio.h>

/* This is not part of ANSI/ISO C Standard header file, it is part of qlibc
   header extensions. This header just provide formatted output functions. */

__BEGIN_DECLS

/* Print formatted data to stdout */
extern int printf(const char *restrict format, ...);

/* Print formatted data to a file stream */
extern int fprintf(FILE *restrict stream, const char *restrict format, ...);

/* Format and store data in a buffer */
extern int sprintf(char *restrict buffer, const char *restrict format, ...);

/* Format and store data in a buffer with a maximum length */
extern int snprintf(char *restrict buffer, size_t bufsz,
                    const char *restrict format, ...);

/* Print formatted data to stdout using a variable argument list */
extern int vprintf(const char *restrict format, va_list vlist);

/* Print formatted data to a file stream using a variable argument list */
extern int vfprintf(FILE *restrict stream, const char *restrict format,
                    va_list vlist);

/* Format and store data in a buffer using a variable argument list */
extern int vsprintf(char *restrict buffer, const char *restrict format,
                    va_list vlist);

/* Format and store data in a buffer with a maximum length using a variable
   argument list */
extern int vsnprintf(char *restrict buffer, size_t bufsz,
                     const char *restrict format, va_list vlist);

__END_DECLS

#endif