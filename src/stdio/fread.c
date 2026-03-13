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
#include <stddef.h>
#include <string.h>

size_t fread(void *restrict ptr, size_t size, size_t count,
             FILE *restrict stream)
{
  if (!ptr || !size || !count || !stream || stream->error || stream->eof)
    return 0;

  if (count > SIZE_MAX / size) {
    stream->error = 1;
    return 0;
  }

  size_t nbytes = size * count;
  size_t nread = 0;

  if (__toin(stream) == EOF) {
    stream->error = 1;
    return 0;
  }

  if (!stream->buf && __allocbuf(stream) == EOF) {
    stream->error = 1;
    return 0;
  }

  /* fread is designed as slow path read from buffer and slow path read from
     system call*/
  if (nbytes <= stream->bufsz) {
    while (nread < nbytes && stream->shcnt > 0) {
      *(unsigned char *)ptr = fgetc(stream);
      ptr = (unsigned char *)ptr + 1;
      nread++;
    }

    while (nread < nbytes) {
      if (IBUF_EXHAUSTED(stream) && __refill(stream) == EOF)
        return nread / size;

      size_t n = MIN((size_t)(stream->rend - stream->rpos), nbytes - nread);
      memcpy(ptr, stream->rpos, n);
      ptr = (unsigned char *)ptr + n;
      nread += n;
      stream->rpos += n;
    }
  } else {
    while (nread < nbytes && stream->shcnt > 0) {
      *(unsigned char *)ptr = fgetc(stream);
      ptr = (unsigned char *)ptr + 1;
      nread++;
    }
    if (nread == nbytes)
      return nread / size;

    size_t leftn = nbytes - nread;
    size_t avail = stream->rend - stream->rpos;
    size_t oldbuffsz = stream->rend - stream->buf;

    if (avail >= leftn) {
      memcpy(ptr, stream->rpos, leftn);
      ptr = (unsigned char *)ptr + leftn;
      nread += leftn;
      stream->rpos += leftn;

      return nread / size;
    } else {
      memcpy(ptr, stream->rpos, avail);
      ptr = (unsigned char *)ptr + avail;
      nread += avail;
      IBUF_DROP(stream);
    }

    /* Read rest */
    ssize_t rn = __readall(stream->fd, ptr, nbytes - nread);
    if (rn == EOF) {
      stream->error = 1;
      return nread / size;
    }
    if (rn < (ssize_t)(nbytes - nread))
      stream->eof = 1;

    nread += rn;
    stream->offset += rn + oldbuffsz;
  }

  return nread / size;
}