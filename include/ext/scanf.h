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

#ifndef _EXT_SCANF_H_
#define _EXT_SCANF_H_ 1

#include <feature.h>
#include <stdarg.h>

/* This is not part of ANSI/ISO C Standard header file, it is part of qlibc
   header extensions. This header just provide pure formatted input functions
   for kernel use. */

__BEGIN_DECLS

/* Read formatted data from a buffer */
extern int sscanf(const char *restrict buffer, const char *restrict format,
                  ...);

/* Read formatted data from a buffer using a variable argument list */
extern int vsscanf(const char *restrict buffer, const char *restrict format,
                   va_list vlist);

__END_DECLS

#endif