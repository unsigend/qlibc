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
#include <string.h>

size_t fwrite(const void *restrict ptr, size_t size, size_t count,
              FILE *restrict stream)
{
  if (!ptr || !size || !count || !stream || stream->error || stream->eof)
    return 0;

  toout(stream);

  if (!stream->buf && allocbuf(stream) == EOF)
    return 0;

  size_t nbytes = size * count;
  size_t total = 0;

  /* fast path, write to buffer if possible */
  if (nbytes <= stream->bufsz && stream->bufmode != _IONBF) {
    /* line buffered, flush when '\n' */
    if (stream->bufmode == _IOLBF) {
      while (total < nbytes) {
        int r = fputc(((unsigned char *)ptr)[total], stream);
        if (r == EOF)
          return total / size;
        total++;
      }
    }
    /* full buffered, flush when buffer is full */
    else {
      while (total < nbytes) {
        if (OBUF_FULL(stream) && flushbuf(stream) == EOF)
          return total / size;
        size_t n = MIN((size_t)(stream->wend - stream->wpos), nbytes - total);
        memcpy(stream->wpos, (unsigned char *)ptr + total, n);
        stream->wpos += n;
        total += n;
      }
    }
  }
  /* slow path, write directly to file descriptor */
  else {
    if (flushbuf(stream) == EOF)
      return 0;
    /* write the rest from system call */
    ssize_t n = writeall(stream->fd, (unsigned char *)ptr, nbytes);
    if (n == -1) {
      stream->error = 1;
      return total / size;
    }
    total += n;
    stream->offset += n;
  }

  return total / size;
}