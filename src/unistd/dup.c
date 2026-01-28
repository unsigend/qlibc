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

#include <syscall.h>
#include <unistd.h>

int dup(int fd) { return __syscall(SYS_dup, (long)fd); }
int dup2(int fd, int fd2) { return __syscall(SYS_dup2, (long)fd, (long)fd2); }
int dup3(int fd, int fd2, int flags) {
  return __syscall(SYS_dup3, (long)fd, (long)fd2, (long)flags);
}