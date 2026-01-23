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
#include <sys/syscall.h>
#include <unistd.h>

long syscall(long __number, ...) {
  va_list args;
  va_start(args, __number);

  long arg1 = va_arg(args, long);
  long arg2 = va_arg(args, long);
  long arg3 = va_arg(args, long);
  long arg4 = va_arg(args, long);
  long arg5 = va_arg(args, long);
  long arg6 = va_arg(args, long);

  va_end(args);

  return __syscall6(__number, arg1, arg2, arg3, arg4, arg5, arg6);
}