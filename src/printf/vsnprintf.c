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

#include <stdarg.h>
#include <stddef.h>

extern int printf_core(char *restrict __buffer, size_t __bufsz,
                       const char *restrict __format, va_list __vlist);

/* vsnprintf just a wrapper of __printf_core */
int vsnprintf(char *restrict __buffer, size_t __bufsz,
              const char *restrict __format, va_list __vlist) {
  return printf_core(__buffer, __bufsz, __format, __vlist);
}