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

#include "_stat.h"
#include <bits/NR.h>
#include <bits/stat.h>
#include <bits/syscall.h>

int stat(const char *restrict path, struct stat *restrict buf) {
  struct __stat64 st64buf;
  int ret = __syscall2(__NR_stat64, (long)path, (long)&st64buf);
  if (ret < 0) {
    return ret;
  }
  _stat64_to_stat(&st64buf, buf);
  return 0;
}