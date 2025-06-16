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

#ifndef _QLIBC_STDLIB_H_
#define _QLIBC_STDLIB_H_

#include <feature.h>
// #include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Conversions to and from numeric formats
extern int atoi(const char *str);
extern long atol(const char *str);
extern long long atoll(const char *str);

// Program termination
#if QLIBC_ISO_C_VERSION < ISO_C_STANDARD_C11
extern void abort(void);
#else
#include <noreturn.h>
extern noreturn void abort(void);
#endif

#ifdef __cplusplus
}
#endif

#endif // _QLIBC_STDLIB_H_