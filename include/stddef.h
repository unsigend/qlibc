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

#ifndef _QLIBC_STDDEF_H_
#define _QLIBC_STDDEF_H_

#include <feature.h>

typedef __PTRDIFF_TYPE__ ptrdiff_t;
typedef __SIZE_TYPE__ size_t;
typedef __WCHAR_TYPE__ wchar_t;

#if __STDC_VERSION__ >= __ISO_C11
typedef struct {
    long long __ll __attribute__((__aligned__(__BIGGEST_ALIGNMENT__)));
    long double __ld __attribute__((__aligned__(__BIGGEST_ALIGNMENT__)));
} max_align_t;
#endif

#if __STDC_VERSION__ >= __ISO_C23
#define __STDC_VERSION_STDDEF_H__ 202311L
typedef __typeof__(nullptr) nullptr_t;
#define unreachable() __builtin_unreachable()
#endif

#define NULL ((void *)0)
#define offsetof(type, member) __builtin_offsetof(type, member)

#endif /* _QLIBC_STDDEF_H_ */
