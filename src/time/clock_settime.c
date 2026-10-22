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

int clock_settime(clockid_t clk, const struct timespec *ts)
{
#ifdef SYS_clock_settime
    return __syscall(SYS_clock_settime, (long)clk, (long)ts);
#elif defined(SYS_clock_settime32)
    return __syscall(SYS_clock_settime32, (long)clk, (long)ts);
#else
    return __syscall(SYS_clock_settime64, (long)clk, (long)ts);
#endif
}
