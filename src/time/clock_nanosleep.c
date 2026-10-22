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

#include <syscall.h>
#include <syscall_arch.h>
#include <time.h>

int clock_nanosleep(clockid_t clk, int flags,
                    const struct timespec *__restrict req,
                    struct timespec *__restrict rem)
{
#ifdef SYS_clock_nanosleep
    return __syscall(SYS_clock_nanosleep, (long)clk, (long)flags, (long)req,
                     (long)rem);
#elif defined(SYS_clock_nanosleep_time32)
    return __syscall(SYS_clock_nanosleep_time32, (long)clk, (long)flags,
                     (long)req, (long)rem);
#else
    return __syscall(SYS_clock_nanosleep_time64, (long)clk, (long)flags,
                     (long)req, (long)rem);
#endif
}
