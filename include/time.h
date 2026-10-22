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

#ifndef _QLIBC_TIME_H_
#define _QLIBC_TIME_H_

#include <sys/types.h>

#define CLOCK_REALTIME 0
#define CLOCK_MONOTONIC 1
#define CLOCK_PROCESS_CPUTIME_ID 2
#define CLOCK_THREAD_CPUTIME_ID 3
#define CLOCK_MONOTONIC_RAW 4
#define CLOCK_REALTIME_COARSE 5
#define CLOCK_MONOTONIC_COARSE 6
#define CLOCK_BOOTTIME 7

#define TIMER_ABSTIME 1

struct timespec {
    time_t tv_sec;
    long tv_nsec;
};

#ifdef __cplusplus
extern "C" {
#endif

extern int nanosleep(const struct timespec *__restrict req,
                     struct timespec *__restrict rem);
extern int clock_gettime(clockid_t clk, struct timespec *ts);
extern int clock_settime(clockid_t clk, const struct timespec *ts);
extern int clock_getres(clockid_t clk, struct timespec *ts);
extern int clock_nanosleep(clockid_t clk, int flags,
                           const struct timespec *__restrict req,
                           struct timespec *__restrict rem);

#ifdef __cplusplus
}
#endif

#endif /* _QLIBC_TIME_H_ */
