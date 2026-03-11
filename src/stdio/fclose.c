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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
fclose(FILE *stream)
{
  if (!stream)
    return EOF;

  int fd;
  fd = stream->fd;

  /* flush the buffered write data */
  if (fflush(stream) == EOF)
    return EOF;

  /* remove the stream from global stream list */
  if (stream->prev)
    stream->prev->next = stream->next;
  else
    stdio_head = stream->next;

  if (stream->next)
    stream->next->prev = stream->prev;

  /* free the buffer if not managed by user */
  if (stream->flags & S_MYBUF && stream->buf)
    {
      free(stream->buf);
      stream->buf = NULL;
    }

  if (stream->shbuf)
    {
      free(stream->shbuf);
      stream->shbuf = NULL;
    }

  /* close the file descriptor */
  if (close(fd) == -1)
    {
      stream->error = 1;
      return EOF;
    }

  if (!(stream->flags & S_STATIC))
    free(stream);
  else
    memset(stream, 0, sizeof(FILE));

  return 0;
}