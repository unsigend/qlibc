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
#include <unistd.h>

#ifndef SYS_alarm
struct timeval {
    time_t tv_sec;
    suseconds_t tv_usec;
};

struct itimerval {
    struct timeval it_interval;
    struct timeval it_value;
};
#endif

unsigned int alarm(unsigned int seconds)
{
#ifdef SYS_alarm
    return __syscall(SYS_alarm, (long)seconds);
#else
    struct itimerval neu, old;

    neu.it_interval.tv_sec = 0;
    neu.it_interval.tv_usec = 0;
    neu.it_value.tv_sec = seconds;
    neu.it_value.tv_usec = 0;
    if (__syscall(SYS_setitimer, 0L, (long)&neu, (long)&old) < 0)
        return 0;
    return (unsigned int)old.it_value.tv_sec + (old.it_value.tv_usec ? 1u : 0u);
#endif
}
