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

#include <sys/stat.h>
#include <syscall.h>
#include <syscall_arch.h>

int fstatat(int fd, const char *__restrict path, struct stat *__restrict buf,
            int flag)
{
#ifdef SYS_fstatat64
    return __syscall(SYS_fstatat64, (long)fd, (long)path, (long)buf, (long)flag);
#else
    return __syscall(SYS_newfstatat, (long)fd, (long)path, (long)buf,
                     (long)flag);
#endif
}
