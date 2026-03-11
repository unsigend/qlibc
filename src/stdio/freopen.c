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
#include <string.h>

#define PERM (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

FILE *
freopen(const char *restrict filename, const char *restrict mode,
        FILE *restrict stream)
{
  int fd, oflags;

  if (!filename || !mode || !stream) return NULL;

  /* flush the buffered write data */
  if (fflush(stream) == EOF) return NULL;

  if (close(stream->fd) == -1)
    {
      stream->error = 1;
      return NULL;
    }

  if (stream->flags & S_MYBUF && stream->buf) free(stream->buf);
  if (stream->shbuf) free(stream->shbuf);

  switch (mode[0])
    {
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

  if ((fd = open(filename, oflags, PERM)) == -1) return NULL;

  FILE *prev = stream->prev;
  FILE *next = stream->next;
  memset(stream, 0, sizeof(FILE));

  stream->fd = fd;
  stream->mode = oflags;
  stream->bufmode = isatty(fd) ? _IOLBF : _IOFBF;
  stream->prev = prev;
  stream->next = next;

  return stream;
}