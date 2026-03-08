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

int fseek(FILE *stream, long offset, int origin) {
  if (!stream)
    return -1;

  if (origin == SEEK_CUR) {
    if (stream->flags & S_WRITE) {
      offset += (stream->wpos - stream->wbase);
    }
    if (stream->flags & S_READ) {
      offset -= (stream->rend - stream->rpos);
    }
  }

  if (flushbuf(stream) == EOF)
    return -1;

  if (stream->flags & S_READ)
    IBUF_DROP(stream);

  off_t pos = lseek(stream->fd, offset, origin);
  if (pos == -1)
    return -1;

  stream->eof = 0;
  stream->offset = pos;
  return 0;
}