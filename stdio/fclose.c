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
#include <stdlib.h>
#include <unistd.h>

// fclose(stream)
//    Implementation:
//    1. Flush the buffered write data
//    2. Remove the stream from global stream list
//    3. Free the buffer (if managed by qlibc)
//    4. Close the file descriptor
//    5. Free FILE structure

int fclose(FILE *stream) {
  if (!stream)
    return EOF;

  // flush the buffered write data
  if (fflush(stream) == EOF)
    return EOF;

  if (stream->prev)
    stream->prev->next = stream->next;
  else
    __stdio_head = stream->next;

  if (stream->next)
    stream->next->prev = stream->prev;

  if (__FILE_IS_MYBUF(stream) && stream->buf) {
    free(stream->buf);
    stream->buf = NULL;
  }

  if (stream->shbuf) {
    free(stream->shbuf);
    stream->shbuf = NULL;
  }

  if (close(stream->fd) == -1) {
    __FILE_SET_ERR(stream);
    free(stream);
    return EOF;
  }

  free(stream);
  return 0;
}