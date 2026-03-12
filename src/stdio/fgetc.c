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

int fgetc(FILE *stream)
{
  if (!stream || stream->error || stream->eof)
    return EOF;

  if (toin(stream) == EOF) {
    stream->error = 1;
    return EOF;
  }

  if (stream->shcnt > 0)
    return stream->shbuf[--stream->shcnt];
  if (IBUF_FULL(stream)) {
    if (!stream->buf && allocbuf(stream) == EOF)
      return EOF;
    if (refill(stream) == EOF)
      return EOF;
  }

  return *stream->rpos++;
}