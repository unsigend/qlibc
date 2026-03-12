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

  size_t nbytes = size * count;
  size_t total = 0;

  if (toin(stream) == EOF) {
    stream->error = 1;
    return 0;
  }

  if (!stream->buf && allocbuf(stream) == EOF) {
    stream->error = 1;
    return 0;
  }

  /* fast path, read from buffer if possible */
  if (nbytes <= stream->bufsz) {
    /* read from pushback buffer */
    while (total < nbytes && stream->shcnt > 0) {
      *(unsigned char *)ptr = fgetc(stream);
      ptr = (unsigned char *)ptr + 1;
      total++;
    }

    while (total < nbytes) {
      if (IBUF_FULL(stream) && refill(stream) == EOF)
        return total / size;

      size_t n = MIN((size_t)(stream->rend - stream->rpos), nbytes - total);
      memcpy(ptr, stream->rpos, n);
      ptr = (unsigned char *)ptr + n;
      total += n;
      stream->rpos += n;
    }
  }

  /* slow path, read directly from system call */
  else {
    /* TODO: potential bugs here */

    /* read from pushback buffer */
    while (total < nbytes && stream->shcnt > 0) {
      *(unsigned char *)ptr = fgetc(stream);
      ptr = (unsigned char *)ptr + 1;
      total++;
    }

    /* consume the buffer left */
    size_t leftn = MIN((size_t)(stream->rend - stream->rpos), nbytes - total);
    size_t oldbuffsz = stream->rend - stream->buf;
    if (leftn) {
      memcpy(ptr, stream->rpos, leftn);
      ptr = (unsigned char *)ptr + leftn;
      total += leftn;
    }
    if (nbytes - total > leftn)
      IBUF_DROP(stream);

    if (total == nbytes) {
      stream->offset += oldbuffsz;
      return total / size;
    }

    /* Read rest */
    ssize_t rn = read(stream->fd, ptr, nbytes - total);
    if (rn == -1) {
      stream->error = 1;
      return total / size;
    }
    if (rn == 0) {
      stream->eof = 1;
      return total / size;
    }
    total += rn;
    stream->offset += rn + oldbuffsz;
  }

  return total / size;
}