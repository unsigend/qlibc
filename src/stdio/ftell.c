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
#include <unistd.h>

long ftell(FILE *stream) {
  if (!stream)
    return -1;

  // TODO: optimize the offset by replacing lseek with maintained offset field
  off_t pos = lseek(stream->fd, 0, SEEK_CUR);
  if (pos == -1)
    return -1;

  if (stream->flags & S_READ)
    pos -= (stream->rend - stream->rpos);
  if (stream->flags & S_WRITE)
    pos += (stream->wpos - stream->wbase);

  return pos;
}