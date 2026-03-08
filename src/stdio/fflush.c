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

static int flushall(void) {
  FILE *cur = stdio_head;
  while (cur) {
    /* flush the write buffer */
    if (flushbuf(cur) == EOF)
      return EOF;
    if (cur->flags & S_READ)
      IBUF_DROP(cur);
    cur = cur->next;
  }
  return 0;
}

int fflush(FILE *stream) {
  if (!stream)
    return flushall();

  if (stream->error || flushbuf(stream) == EOF)
    return EOF;

  if (stream->flags & S_READ)
    IBUF_DROP(stream);

  return 0;
}