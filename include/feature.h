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

/**
 * @brief: Macros for feature
 */

#define QLIBC_VERSION_MAJOR 0
#define QLIBC_VERSION_MINOR 1
#define QLIBC_VERSION_PATCH 0

#define QLIBC_VERSION_STRING "0.1.0"

#define ISO_C_STANDARD_C99   199901L
#define ISO_C_STANDARD_C11   201112L
#define ISO_C_STANDARD_C17   201710L
#define ISO_C_STANDARD_C23   202311L

#define QLIBC_ISO_C_VERSION         __STDC_VERSION__
#define QLIBC_SUPPORT_MB_STRING     0


#endif