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

#include <fcntl.h>
#include <syscall.h>
#include <syscall_arch.h>
#include <unistd.h>

int symlink(const char *target, const char *linkpath)
{
#ifdef SYS_symlink
    return __syscall(SYS_symlink, (long)target, (long)linkpath);
#else
    return __syscall(SYS_symlinkat, (long)target, (long)AT_FDCWD, (long)linkpath);
#endif
}
