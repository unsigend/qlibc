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

#ifndef _QLIBC_STDARG_H_
#define _QLIBC_STDARG_H_

#include <feature.h>

typedef __builtin_va_list va_list;

#define va_arg(ap, type) __builtin_va_arg(ap, type)
#define va_end(ap) __builtin_va_end(ap)
#define va_start(ap, last) __builtin_va_start(ap, last)

#if __STDC_VERSION__ >= __ISO_C99
#define va_copy(dest, src) __builtin_va_copy(dest, src)
#endif

#if __STDC_VERSION__ >= __ISO_C23
#define __STDC_VERSION_STDARG_H__ 202311L
#endif

#endif /* _QLIBC_STDARG_H_ */
