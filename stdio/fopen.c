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
#include <stdlib.h>

#define __DEFAULT_PERM (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

// fopen(filename, mode)
//    Open a file and return a stream.
//    Return the stream on success, NULL on failure.
//
//    Note: for lazy loading optimization, the buffer will not allocated until
//    the first read or write operation is performed. So in fopen, it will only
//    deal with the file descriptor and mode.

FILE *fopen(const char *restrict filename, const char *restrict mode) {
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

  fd = open(filename, oflags, __DEFAULT_PERM);
  if (fd == -1)
    return NULL;

  stream = malloc(sizeof(FILE));
  if (!stream) {
    close(fd);
    return NULL;
  }

  // determine the buffer mode
  bufmode = isatty(fd) ? _IOLBF : _IOFBF;

  __finit(stream, fd, oflags, bufmode);
  return stream;
}