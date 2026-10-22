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

#include <stdlib.h>

void (*__exit_funcs[ATEXIT_MAX])(void);
size_t __exit_func_count = 0;

int atexit(void (*func)(void))
{
    if (!func || __exit_func_count >= ATEXIT_MAX)
        return -1;
    __exit_funcs[__exit_func_count++] = func;
    return 0;
}
