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
#include "sys/types.h"
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

// fread does not distinguish between end-of-file and error, and callers must
// use feof and ferror to determine which occurred.
//
// Note: Based on ANSI/ISO C standard, fread returns the number of items read or
// less than requested count if an error occurs or EOF occurs.

size_t fread(void *restrict ptr, size_t size, size_t count,
             FILE *restrict stream) {
  if (!ptr || !size || !count || !stream)
    return 0;

  if (__FILE_IS_ERR(stream) || __FILE_IS_EOF(stream))
    return 0;

  size_t nreq = size * count;
  size_t rn = 0;

  // if the buffer is not allocated, allocate it
  if (!stream->buf)
    if (__allocbuf(stream) == EOF)
      return 0;

  // fast path
  //   For fast path just read from buffer or refill buffer if needed
  if (nreq <= stream->bufsz) {
    while (rn < nreq) {
      if (__IO_RBUF_FULL(stream) && __refillbuf(stream) == EOF)
        return rn / size;

      size_t __n = MIN((size_t)(stream->rend - stream->rpos), nreq - rn);
      memcpy(ptr, stream->rpos, __n);
      ptr = (unsigned char *)ptr + __n;
      rn += __n;
      stream->rpos += __n;
    }
  }

  // slow path
  //   For slow path just use direct I/O from system call
  else {
    // consume the buffer left first
    size_t bufleftn = stream->rend - stream->rpos;
    if (bufleftn) {
      memcpy(ptr, stream->rpos, bufleftn);
      ptr = (unsigned char *)ptr + bufleftn;
      rn += bufleftn;

      // drop the buffer
      __IO_RBUF_DROP(stream);
    }

    // read the rest from system call
    ssize_t __r = read(stream->fd, ptr, nreq - rn);
    if (__r == -1) {
      __FILE_SET_ERR(stream);
      return rn / size;
    }
    if (__r == 0) {
      __FILE_SET_EOF(stream);
      return rn / size;
    }
    rn += __r;
  }

  return rn / size;
}