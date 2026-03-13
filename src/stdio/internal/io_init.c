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

static FILE __stdin_stream;
static FILE __stdout_stream;
static FILE __stderr_stream;

FILE *stdin = NULL;
FILE *stdout = NULL;
FILE *stderr = NULL;

void __qlibc_stdio_init(void)
{
  if (isatty(STDIN_FILENO))
    stdin = __inits(&__stdin_stream, STDIN_FILENO, O_RDONLY, _IOLBF);
  else
    stdin = __inits(&__stdin_stream, STDIN_FILENO, O_RDONLY, _IOFBF);
  if (isatty(STDOUT_FILENO))
    stdout = __inits(&__stdout_stream, STDOUT_FILENO, O_WRONLY, _IOLBF);
  else
    stdout = __inits(&__stdout_stream, STDOUT_FILENO, O_WRONLY, _IOFBF);

  /* Based on ANSI/ISO C standard, stderr is always unbuffered */
  stderr = __inits(&__stderr_stream, STDERR_FILENO, O_WRONLY, _IONBF);
  stdin->flags |= S_STATIC;
  stdout->flags |= S_STATIC;
  stderr->flags |= S_STATIC;
}