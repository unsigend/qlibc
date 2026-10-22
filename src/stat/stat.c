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
#include <sys/stat.h>
#include <syscall.h>
#include <syscall_arch.h>

int stat(const char *__restrict path, struct stat *__restrict buf)
{
#ifdef SYS_stat64
    return __syscall(SYS_stat64, (long)path, (long)buf);
#elif defined(SYS_stat)
    return __syscall(SYS_stat, (long)path, (long)buf);
#else
    return __syscall(SYS_newfstatat, (long)AT_FDCWD, (long)path, (long)buf, 0L);
#endif
}
