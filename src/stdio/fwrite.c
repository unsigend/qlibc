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
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

size_t fwrite(const void *restrict ptr, size_t size, size_t count,
              FILE *restrict stream) {
  if (!ptr || !size || !count || !stream)
    return 0;
  if (__FILE_IS_ERR(stream) || __FILE_IS_EOF(stream))
    return 0;

  if (!stream->buf)
    if (__allocbuf(stream) == EOF)
      return 0;

  size_t nreq = size * count;
  size_t wn = 0;

  // fast path
  //   For fast path just write to buffer or flush buffer if needed
  if (nreq <= stream->bufsz) {
    // line buffered, flush when '\n'
    if (__FILE_IS_LINEBUF(stream)) {
      while (wn < nreq) {
        int r = fputc(((unsigned char *)ptr)[wn], stream);
        if (r == EOF)
          return wn / size;
        wn++;
      }
    }
    // full buffered, flush when buffer is full
    else {
      while (wn < nreq) {
        if (__IO_WBUF_FULL(stream)) {
          if (__flushbuf(stream) == EOF)
            return wn / size;
        }
        size_t __n = MIN((size_t)(stream->wend - stream->wpos), nreq - wn);
        memcpy(stream->wpos, (unsigned char *)ptr + wn, __n);
        stream->wpos += __n;
        wn += __n;
      }
    }
  }

  // slow path
  //   For slow path just write to file descriptor directly
  else {
    // flush the buffer first
    if (__flushbuf(stream) == EOF)
      return 0;

    // write the rest from system call
    ssize_t __w = __writeall(stream->fd, (unsigned char *)ptr, nreq);
    if (__w == -1) {
      __FILE_SET_ERR(stream);
      return wn / size;
    }
    wn += __w;
  }

  return wn / size;
}