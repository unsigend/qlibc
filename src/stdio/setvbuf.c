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

#define VMODE(mode) ((mode) == _IONBF || (mode) == _IOLBF || (mode) == _IOFBF)

int
setvbuf(FILE *restrict stream, char *restrict buffer, int mode, size_t size)
{
  if (!stream || !VMODE(mode) || stream->buf)
    return EOF;

  if (buffer)
    {
      stream->buf = (unsigned char *)buffer;
      stream->bufmode = mode;
      stream->bufsz = size;

      resetbufp(stream, stream->buf, size);
    }
  else
    {
      stream->bufmode = mode;
      if (allocbuf(stream) == EOF)
        return EOF;
    }
  return 0;
}