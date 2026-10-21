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

#ifdef assert
#undef assert
#endif

#ifdef NDEBUG
#define assert(expr) ((void)0)
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define assert(expr)                                                           \
    (void)((expr) || (__assert_fail(#expr, __func__, __FILE__, __LINE__), 0))
#else
#define assert(expr)                                                           \
    (void)((expr) ||                                                           \
           (__assert_fail(#expr, __FUNCTION__, __FILE__, __LINE__), 0))
#endif

#ifndef _QLIBC_ASSERT_H_
#define _QLIBC_ASSERT_H_

#ifdef __cplusplus
extern "C" {
#endif

extern void __assert_fail(const char *msg, const char *func, const char *file,
                          int line);

#ifdef __cplusplus
}
#endif

#endif /* _QLIBC_ASSERT_H_ */
