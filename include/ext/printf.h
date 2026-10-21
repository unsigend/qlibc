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

#ifndef _QLIBC_EXT_PRINTF_H_
#define _QLIBC_EXT_PRINTF_H_

#include <feature.h>
#include <stdarg.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

__printf(2, 3) extern int sprintf(char *__restrict buf,
                                  const char *__restrict fmt, ...);
__printf(3, 4) extern int snprintf(char *__restrict buf, size_t bufsz,
                                   const char *__restrict fmt, ...);
__printf(2, 0) extern int vsprintf(char *__restrict buf,
                                   const char *__restrict fmt, va_list vlist);
__printf(3, 0) extern int vsnprintf(char *__restrict buf, size_t bufsz,
                                    const char *__restrict fmt, va_list vlist);

#ifdef __cplusplus
}
#endif

#endif /* _QLIBC_EXT_PRINTF_H_ */