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

#include "exit_funcs.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#if __STDC_VERSION__ >= __ISO_C11
_Noreturn void exit(int status)
#else
void exit(int status)
#endif
{
    while (__exit_func_count)
        __exit_funcs[--__exit_func_count]();
    fflush(NULL);
    _exit(status);
}
