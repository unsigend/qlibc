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
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

/* stdio internal I/O utilities helper functions. */

FILE *stdio_head = NULL;

FILE *
inits(FILE *stream, int fd, int mode, int bufmode)
{
  memset(stream, 0, sizeof(FILE));
  stream->fd = fd;
  stream->mode = mode;
  stream->bufmode = bufmode;
  stream->next = stdio_head;
  if (stdio_head) stdio_head->prev = stream;
  stdio_head = stream;

  return stream;
}

void
resetbufp(FILE *stream, unsigned char *buf, size_t sz)
{
  stream->wbase = stream->wpos = buf;
  stream->wend = buf + sz;
  stream->rpos = stream->rend = buf;
}

int
allocbuf(FILE *stream)
{
  size_t sz;
  if (stream->buf)
    {
      resetbufp(stream, stream->buf, stream->bufsz);
      return 0;
    }
  /* minimum buffer size is 1 */
  sz = stream->bufmode == _IONBF ? 1 : BUFSIZ;
  stream->buf = malloc(sz);
  if (!stream->buf)
    {
      stream->error = 1;
      return EOF;
    }

  stream->bufsz = sz;
  stream->flags |= S_MYBUF;
  resetbufp(stream, stream->buf, sz);

  return 0;
}

int
refill(FILE *stream)
{
  off_t cur = lseek(stream->fd, 0, SEEK_CUR);
  if (cur == -1)
    {
      stream->error = 1;
      return EOF;
    }
  stream->offset = cur;
  ssize_t n = read(stream->fd, stream->buf, stream->bufsz);
  if (n == -1)
    {
      stream->error = 1;
      return EOF;
    }
  if (n == 0)
    {
      stream->eof = 1;
      return EOF;
    }
  stream->rpos = stream->buf;
  stream->rend = stream->buf + n;
  return n;
}

int
writeall(int fd, const unsigned char *buf, ssize_t n)
{
  ssize_t total = 0;
  errno = 0;
  while (total < n)
    {
      ssize_t wn = write(fd, buf + total, n - total);
      if (wn == -1)
        {
          if (errno == EINTR || errno == EAGAIN) continue;
          return -1;
        }
      total += wn;
    }
  return total;
}

int
flushbuf(FILE *stream)
{
  if (stream->flags & D_WRITE && !OBUF_EMPTY(stream))
    {
      ssize_t wn = stream->wpos - stream->wbase;
      if (writeall(stream->fd, stream->wbase, wn) == -1)
        {
          stream->error = 1;
          return EOF;
        }
      OBUF_DROP(stream);
      stream->offset += wn;
    }
  return 0;
}

int
toin(FILE *stream)
{
  if (stream->flags & D_WRITE)
    {
      if (flushbuf(stream) == EOF) return EOF;
      stream->flags &= ~D_WRITE;
    }
  stream->flags |= D_READ;
  return 0;
}

void
toout(FILE *stream)
{
  if (stream->flags & D_READ)
    {
      IBUF_DROP(stream);
      stream->flags &= ~D_READ;
      stream->shcnt = 0;
    }
  stream->flags |= D_WRITE;
}