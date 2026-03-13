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

#include "internal/io.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int fclose(FILE *stream)
{
  if (!stream)
    return EOF;

  int fd;
  int error = 0;
  fd = stream->fd;

  if (fflush(stream) == EOF)
    error = 1;

  unlinks(stream);

  if (stream->flags & S_MYBUF && stream->buf) {
    free(stream->buf);
    stream->buf = NULL;
  }

  if (stream->shbuf) {
    free(stream->shbuf);
    stream->shbuf = NULL;
  }

  if (close(fd) == -1)
    error = 1;

  if (!(stream->flags & S_STATIC))
    free(stream);
  else
    memset(stream, 0, sizeof(FILE));

  return error ? EOF : 0;
}