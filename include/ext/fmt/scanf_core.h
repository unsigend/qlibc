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

#ifndef _SCANF_CORE_H_
#define _SCANF_CORE_H_ 1

/* Not part of ANSI/ISO C Standard, it include implementation details of scanf,
   just for freestanding kernel use. */

#include <feature.h>
#include <stdarg.h>

__BEGIN_DECLS

/* Formatted core input function */
extern int scanf_core(const char *restrict buff, const char *restrict fmt,
                      va_list vlist);

__END_DECLS

#endif