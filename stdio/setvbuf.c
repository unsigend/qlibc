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

int setvbuf(FILE *restrict stream, char *restrict buffer, int mode,
            size_t size) {
  if (!stream || (mode != _IONBF && mode != _IOLBF && mode != _IOFBF))
    return EOF;

  if (stream->buf)
    return EOF;

  // user provided buffer
  if (buffer) {
    stream->buf = (unsigned char *)buffer;
    stream->bufmode = mode;
    stream->bufsz = size;

    __init_buf_pointers(stream, stream->buf, size);
  } else {
    // allocate buffer
    stream->bufmode = mode;
    if (__allocbuf(stream) == EOF)
      return EOF;
  }
  return 0;
}