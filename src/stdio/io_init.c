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

#include "io.h"
#include <stdio.h>

static FILE stdin_stream;
static FILE stdout_stream;
static FILE stderr_stream;

FILE *stdin = NULL;
FILE *stdout = NULL;
FILE *stderr = NULL;

__attribute__((constructor)) void stdio_init(void) {
  stdin = inits(&stdin_stream, STDIN_FILENO, O_RDONLY, _IOLBF);
  stdout = inits(&stdout_stream, STDOUT_FILENO, O_WRONLY, _IOLBF);
  stderr = inits(&stderr_stream, STDERR_FILENO, O_WRONLY, _IONBF);
}