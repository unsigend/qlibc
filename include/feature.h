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

#ifndef _QLIBC_FEATURE_H_
#define _QLIBC_FEATURE_H_

/* Version macros */
#define QLIBC_VERSION_MAJOR 0
#define QLIBC_VERSION_MINOR 1
#define QLIBC_VERSION_PATCH 0

#define QLIBC_VERSION_STRING "0.1.0"

/* ISO C Standard macros */
#define ISO_C_STANDARD_C99 199901L
#define ISO_C_STANDARD_C11 201112L
#define ISO_C_STANDARD_C17 201710L
#define ISO_C_STANDARD_C23 202311L

/* QLIBC specific macros */
#define QLIBC_ISO_C_VERSION __STDC_VERSION__ /* ISO C Standard version */
#define QLIBC_SUPPORT_MB_STRING 0            /* Multi-byte string support */
#define QLIBC_SUPPORT_FLOATING_POINT 0       /* Floating-point support */
#define _QLIBC_SOURCE 1                      /* QLIBC source */
#define _QLIBC 1                             /* QLIBC */

/* C++ specific macros */
#ifdef __cplusplus
#define __BEGIN_DECLS extern "C" {
#define __END_DECLS }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif

#endif