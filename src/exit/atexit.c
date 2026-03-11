/* qlibc - A light-weight and portable C standard library
 * Copyright (C) 2025 Qiu Yixiang
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

/* For simplicity, the exit functions are stored in a static array. Without
   dynamically growing in the heap.*/

void (*__exit_funcs[ATEXIT_MAX])(void);
size_t __exit_func_count = 0;

int
atexit(void (*func)(void))
{
  if (__exit_func_count >= ATEXIT_MAX || ATEXIT_LOCKED())
    return -1;
  __exit_funcs[__exit_func_count++] = func;
  return 0;
}