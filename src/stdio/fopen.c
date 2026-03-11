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
#include <stdlib.h>

#define PERM (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

FILE *fopen(const char *restrict filename, const char *restrict mode)
{
  int fd;
  int oflags;
  int bufmode;
  FILE *stream;

  if (!filename || !mode)
    return NULL;

  switch (mode[0]) {
  case 'r':
    oflags = O_RDONLY;
    break;
  case 'w':
    oflags = O_WRONLY | O_CREAT | O_TRUNC;
    break;
  case 'a':
    oflags = O_WRONLY | O_CREAT | O_APPEND;
    break;
  default:
    return NULL;
  }

  if (mode[1] == '+' || (mode[1] && mode[2] == '+'))
    oflags = (oflags & ~O_ACCMODE) | O_RDWR;

  fd = open(filename, oflags, PERM);
  if (fd == -1)
    return NULL;

  stream = malloc(sizeof(FILE));
  if (!stream) {
    close(fd);
    return NULL;
  }

  bufmode = isatty(fd) ? _IOLBF : _IOFBF;

  inits(stream, fd, oflags, bufmode);
  return stream;
}