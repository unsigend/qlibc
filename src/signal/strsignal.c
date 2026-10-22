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

#include <signal.h>
#include <stdio.h>

static const char *const sigdescs[] = {
    0,
    "Hangup",
    "Interrupt",
    "Quit",
    "Illegal instruction",
    "Trace/breakpoint trap",
    "Aborted",
    "Bus error",
    "Floating point exception",
    "Killed",
    "User defined signal 1",
    "Segmentation fault",
    "User defined signal 2",
    "Broken pipe",
    "Alarm clock",
    "Terminated",
    "Stack fault",
    "Child exited",
    "Continued",
    "Stopped (signal)",
    "Stopped",
    "Stopped (tty input)",
    "Stopped (tty output)",
    "Urgent I/O condition",
    "CPU time limit exceeded",
    "File size limit exceeded",
    "Virtual timer expired",
    "Profiling timer expired",
    "Window changed",
    "I/O possible",
    "Power failure",
    "Bad system call",
};

#define BUFSZ 64
static char unknownbuf[BUFSZ];

char *strsignal(int sig)
{
    if (sig <= 0 || sig >= (int)(sizeof sigdescs / sizeof sigdescs[0]) ||
        !sigdescs[sig]) {
        snprintf(unknownbuf, BUFSZ, "Unknown signal %d", sig);
        return unknownbuf;
    }
    return (char *)sigdescs[sig];
}
