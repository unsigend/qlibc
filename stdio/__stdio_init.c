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

#include "__stdio.h"
#include <stdio.h>

static FILE __stdin_stream;
static FILE __stdout_stream;
static FILE __stderr_stream;

FILE *__stdin = NULL;
FILE *__stdout = NULL;
FILE *__stderr = NULL;

// __stdio_init(void)
//    stdio module initialization function.

__attribute__((constructor)) void __stdio_init(void) {
  __stdin = __finit(&__stdin_stream, STDIN_FILENO, O_RDONLY, _IOLBF);
  __stdout = __finit(&__stdout_stream, STDOUT_FILENO, O_WRONLY, _IOLBF);
  __stderr = __finit(&__stderr_stream, STDERR_FILENO, O_WRONLY, _IONBF);
}