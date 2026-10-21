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

#ifndef _QLIBC_STDINT_H_
#define _QLIBC_STDINT_H_

#include <feature.h>

#ifdef __INT8_TYPE__
typedef __INT8_TYPE__ int8_t;
typedef __UINT8_TYPE__ uint8_t;
#define INT8_MAX __INT8_MAX__
#define INT8_MIN (-__INT8_MAX__ - 1)
#define UINT8_MAX __UINT8_MAX__
#define INT8_C(v) __INT8_C(v)
#define UINT8_C(v) __UINT8_C(v)
#endif

#ifdef __INT16_TYPE__
typedef __INT16_TYPE__ int16_t;
typedef __UINT16_TYPE__ uint16_t;
#define INT16_MAX __INT16_MAX__
#define INT16_MIN (-__INT16_MAX__ - 1)
#define UINT16_MAX __UINT16_MAX__
#define INT16_C(v) __INT16_C(v)
#define UINT16_C(v) __UINT16_C(v)
#endif

#ifdef __INT32_TYPE__
typedef __INT32_TYPE__ int32_t;
typedef __UINT32_TYPE__ uint32_t;
#define INT32_MAX __INT32_MAX__
#define INT32_MIN (-__INT32_MAX__ - 1)
#define UINT32_MAX __UINT32_MAX__
#define INT32_C(v) __INT32_C(v)
#define UINT32_C(v) __UINT32_C(v)
#endif

#ifdef __INT64_TYPE__
typedef __INT64_TYPE__ int64_t;
typedef __UINT64_TYPE__ uint64_t;
#define INT64_MAX __INT64_MAX__
#define INT64_MIN (-__INT64_MAX__ - 1)
#define UINT64_MAX __UINT64_MAX__
#define INT64_C(v) __INT64_C(v)
#define UINT64_C(v) __UINT64_C(v)
#endif

typedef __INT_LEAST8_TYPE__ int_least8_t;
typedef __INT_LEAST16_TYPE__ int_least16_t;
typedef __INT_LEAST32_TYPE__ int_least32_t;
typedef __INT_LEAST64_TYPE__ int_least64_t;
typedef __UINT_LEAST8_TYPE__ uint_least8_t;
typedef __UINT_LEAST16_TYPE__ uint_least16_t;
typedef __UINT_LEAST32_TYPE__ uint_least32_t;
typedef __UINT_LEAST64_TYPE__ uint_least64_t;

#define INT_LEAST8_MAX __INT_LEAST8_MAX__
#define INT_LEAST8_MIN (-__INT_LEAST8_MAX__ - 1)
#define UINT_LEAST8_MAX __UINT_LEAST8_MAX__
#define INT_LEAST16_MAX __INT_LEAST16_MAX__
#define INT_LEAST16_MIN (-__INT_LEAST16_MAX__ - 1)
#define UINT_LEAST16_MAX __UINT_LEAST16_MAX__
#define INT_LEAST32_MAX __INT_LEAST32_MAX__
#define INT_LEAST32_MIN (-__INT_LEAST32_MAX__ - 1)
#define UINT_LEAST32_MAX __UINT_LEAST32_MAX__
#define INT_LEAST64_MAX __INT_LEAST64_MAX__
#define INT_LEAST64_MIN (-__INT_LEAST64_MAX__ - 1)
#define UINT_LEAST64_MAX __UINT_LEAST64_MAX__

typedef __INT_FAST8_TYPE__ int_fast8_t;
typedef __INT_FAST16_TYPE__ int_fast16_t;
typedef __INT_FAST32_TYPE__ int_fast32_t;
typedef __INT_FAST64_TYPE__ int_fast64_t;
typedef __UINT_FAST8_TYPE__ uint_fast8_t;
typedef __UINT_FAST16_TYPE__ uint_fast16_t;
typedef __UINT_FAST32_TYPE__ uint_fast32_t;
typedef __UINT_FAST64_TYPE__ uint_fast64_t;

#define INT_FAST8_MAX __INT_FAST8_MAX__
#define INT_FAST8_MIN (-__INT_FAST8_MAX__ - 1)
#define UINT_FAST8_MAX __UINT_FAST8_MAX__
#define INT_FAST16_MAX __INT_FAST16_MAX__
#define INT_FAST16_MIN (-__INT_FAST16_MAX__ - 1)
#define UINT_FAST16_MAX __UINT_FAST16_MAX__
#define INT_FAST32_MAX __INT_FAST32_MAX__
#define INT_FAST32_MIN (-__INT_FAST32_MAX__ - 1)
#define UINT_FAST32_MAX __UINT_FAST32_MAX__
#define INT_FAST64_MAX __INT_FAST64_MAX__
#define INT_FAST64_MIN (-__INT_FAST64_MAX__ - 1)
#define UINT_FAST64_MAX __UINT_FAST64_MAX__

typedef __INTMAX_TYPE__ intmax_t;
typedef __UINTMAX_TYPE__ uintmax_t;

#define INTMAX_MAX __INTMAX_MAX__
#define INTMAX_MIN (-__INTMAX_MAX__ - 1)
#define UINTMAX_MAX __UINTMAX_MAX__
#define INTMAX_C(v) __INTMAX_C(v)
#define UINTMAX_C(v) __UINTMAX_C(v)

#ifdef __INTPTR_TYPE__
typedef __INTPTR_TYPE__ intptr_t;
typedef __UINTPTR_TYPE__ uintptr_t;
#define INTPTR_MAX __INTPTR_MAX__
#define INTPTR_MIN (-__INTPTR_MAX__ - 1)
#define UINTPTR_MAX __UINTPTR_MAX__
#endif

#define PTRDIFF_MAX __PTRDIFF_MAX__
#define PTRDIFF_MIN (-__PTRDIFF_MAX__ - 1)
#define SIZE_MAX __SIZE_MAX__

#define SIG_ATOMIC_MAX __SIG_ATOMIC_MAX__
#ifdef __SIG_ATOMIC_MIN__
#define SIG_ATOMIC_MIN __SIG_ATOMIC_MIN__
#else
#define SIG_ATOMIC_MIN (-__SIG_ATOMIC_MAX__ - 1)
#endif

#define WCHAR_MAX __WCHAR_MAX__
#ifdef __WCHAR_MIN__
#define WCHAR_MIN __WCHAR_MIN__
#elif defined(__WCHAR_UNSIGNED__)
#define WCHAR_MIN 0
#else
#define WCHAR_MIN (-__WCHAR_MAX__ - 1)
#endif

#define WINT_MAX __WINT_MAX__
#ifdef __WINT_MIN__
#define WINT_MIN __WINT_MIN__
#elif defined(__WINT_UNSIGNED__)
#define WINT_MIN 0
#else
#define WINT_MIN (-__WINT_MAX__ - 1)
#endif

#if __STDC_VERSION__ >= __ISO_C23
#define __STDC_VERSION_STDINT_H__ 202311L
#ifdef __INT8_TYPE__
#define INT8_WIDTH 8
#define UINT8_WIDTH 8
#endif
#ifdef __INT16_TYPE__
#define INT16_WIDTH 16
#define UINT16_WIDTH 16
#endif
#ifdef __INT32_TYPE__
#define INT32_WIDTH 32
#define UINT32_WIDTH 32
#endif
#ifdef __INT64_TYPE__
#define INT64_WIDTH 64
#define UINT64_WIDTH 64
#endif
#define INT_LEAST8_WIDTH __INT_LEAST8_WIDTH__
#define INT_LEAST16_WIDTH __INT_LEAST16_WIDTH__
#define INT_LEAST32_WIDTH __INT_LEAST32_WIDTH__
#define INT_LEAST64_WIDTH __INT_LEAST64_WIDTH__
#define UINT_LEAST8_WIDTH __INT_LEAST8_WIDTH__
#define UINT_LEAST16_WIDTH __INT_LEAST16_WIDTH__
#define UINT_LEAST32_WIDTH __INT_LEAST32_WIDTH__
#define UINT_LEAST64_WIDTH __INT_LEAST64_WIDTH__
#define INT_FAST8_WIDTH __INT_FAST8_WIDTH__
#define INT_FAST16_WIDTH __INT_FAST16_WIDTH__
#define INT_FAST32_WIDTH __INT_FAST32_WIDTH__
#define INT_FAST64_WIDTH __INT_FAST64_WIDTH__
#define UINT_FAST8_WIDTH __INT_FAST8_WIDTH__
#define UINT_FAST16_WIDTH __INT_FAST16_WIDTH__
#define UINT_FAST32_WIDTH __INT_FAST32_WIDTH__
#define UINT_FAST64_WIDTH __INT_FAST64_WIDTH__
#define INTMAX_WIDTH __INTMAX_WIDTH__
#define UINTMAX_WIDTH __UINTMAX_WIDTH__
#ifdef __INTPTR_TYPE__
#define INTPTR_WIDTH __INTPTR_WIDTH__
#define UINTPTR_WIDTH __UINTPTR_WIDTH__
#endif
#define PTRDIFF_WIDTH __PTRDIFF_WIDTH__
#define SIZE_WIDTH __SIZE_WIDTH__
#define SIG_ATOMIC_WIDTH __SIG_ATOMIC_WIDTH__
#define WCHAR_WIDTH __WCHAR_WIDTH__
#define WINT_WIDTH __WINT_WIDTH__
#endif

#endif /* _QLIBC_STDINT_H_ */
