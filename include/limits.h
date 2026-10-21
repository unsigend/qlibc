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

#ifndef _QLIBC_LIMITS_H_
#define _QLIBC_LIMITS_H_

#include <feature.h>

#if __STDC_VERSION__ >= __ISO_C23
#define __STDC_VERSION_LIMITS_H__ 202311L
#ifdef __BITINT_MAXWIDTH__
#define BITINT_MAXWIDTH __BITINT_MAXWIDTH__
#endif
#define BOOL_MAX 1
#define BOOL_WIDTH __BOOL_WIDTH__
#define CHAR_WIDTH __CHAR_BIT__
#define INT_WIDTH __INT_WIDTH__
#define LLONG_WIDTH __LLONG_WIDTH__
#define LONG_WIDTH __LONG_WIDTH__
#define SCHAR_WIDTH __CHAR_BIT__
#define SHRT_WIDTH __SHRT_WIDTH__
#define UCHAR_WIDTH __CHAR_BIT__
#define UINT_WIDTH __INT_WIDTH__
#define ULLONG_WIDTH __LLONG_WIDTH__
#define ULONG_WIDTH __LONG_WIDTH__
#define USHRT_WIDTH __SHRT_WIDTH__
#endif

#define CHAR_BIT __CHAR_BIT__
#ifdef __CHAR_UNSIGNED__
#define CHAR_MAX (__SCHAR_MAX__ * 2 + 1)
#define CHAR_MIN 0
#else
#define CHAR_MAX __SCHAR_MAX__
#define CHAR_MIN (-__SCHAR_MAX__ - 1)
#endif
#define INT_MAX __INT_MAX__
#define INT_MIN (-__INT_MAX__ - 1)
#define LLONG_MAX __LONG_LONG_MAX__
#define LLONG_MIN (-__LONG_LONG_MAX__ - 1)
#define LONG_MAX __LONG_MAX__
#define LONG_MIN (-__LONG_MAX__ - 1)
#define MB_LEN_MAX 1
#define SCHAR_MAX __SCHAR_MAX__
#define SCHAR_MIN (-__SCHAR_MAX__ - 1)
#define SHRT_MAX __SHRT_MAX__
#define SHRT_MIN (-__SHRT_MAX__ - 1)
#define UCHAR_MAX (__SCHAR_MAX__ * 2 + 1)
#define UINT_MAX (__INT_MAX__ * 2U + 1U)
#define ULLONG_MAX (__LONG_LONG_MAX__ * 2ULL + 1ULL)
#define ULONG_MAX (__LONG_MAX__ * 2UL + 1UL)
#define USHRT_MAX (__SHRT_MAX__ * 2 + 1)

#endif /* _QLIBC_LIMITS_H_ */
