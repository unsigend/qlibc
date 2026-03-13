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

__hidden FILE *__stdio_head = NULL;

__hidden FILE *__inits(FILE *stream, int fd, int mode, int bufmode)
{
  memset(stream, 0, sizeof(FILE));
  stream->fd = fd;
  stream->mode = mode;
  stream->bufmode = bufmode;
  stream->next = __stdio_head;
  if (__stdio_head)
    __stdio_head->prev = stream;
  __stdio_head = stream;

  return stream;
}

__hidden void __resetbufp(FILE *stream, unsigned char *buf, size_t sz)
{
  stream->wbase = stream->wpos = buf;
  stream->wend = buf + sz;
  stream->rpos = stream->rend = buf;
}

__hidden int __allocbuf(FILE *stream)
{
  size_t sz;
  if (stream->buf) {
    __resetbufp(stream, stream->buf, stream->bufsz);
    return 0;
  }
  /* minimum buffer size is 1 */
  sz = stream->bufmode == _IONBF ? 1 : BUFSIZ;
  stream->buf = malloc(sz);
  if (!stream->buf) {
    stream->error = 1;
    return EOF;
  }

  stream->bufsz = sz;
  stream->flags |= S_MYBUF;
  __resetbufp(stream, stream->buf, sz);

  return 0;
}

__hidden int __refill(FILE *stream)
{
  off_t cur = lseek(stream->fd, 0, SEEK_CUR);
  if (cur == -1) {
    stream->error = 1;
    return EOF;
  }
  stream->offset = cur;
  ssize_t n = read(stream->fd, stream->buf, stream->bufsz);
  if (n == -1) {
    stream->error = 1;
    return EOF;
  }
  if (n == 0) {
    stream->eof = 1;
    return EOF;
  }
  stream->rpos = stream->buf;
  stream->rend = stream->buf + n;
  return n;
}

__hidden int __writeall(int fd, const unsigned char *buf, ssize_t n)
{
  ssize_t nbytes = 0;
  errno = 0;
  while (nbytes < n) {
    ssize_t wn = write(fd, buf + nbytes, n - nbytes);
    if (wn == -1) {
      if (errno == EINTR || errno == EAGAIN)
        continue;
      return -1;
    }
    nbytes += wn;
  }
  return nbytes;
}

__hidden int __readall(int fd, unsigned char *buf, ssize_t n)
{
  ssize_t nbytes = 0;
  errno = 0;
  while (nbytes < n) {
    ssize_t rn = read(fd, buf + nbytes, n - nbytes);
    if (rn == -1) {
      if (errno == EINTR || errno == EAGAIN)
        continue;
      return -1;
    }
    if (rn == 0) {
      return nbytes;
    }
    nbytes += rn;
  }
  return nbytes;
}

__hidden int __flushbuf(FILE *stream)
{
  if (stream->flags & D_WRITE && !OBUF_EMPTY(stream)) {
    ssize_t wn = stream->wpos - stream->wbase;
    if (__writeall(stream->fd, stream->wbase, wn) == -1) {
      stream->error = 1;
      return EOF;
    }
    OBUF_DROP(stream);
    stream->offset += wn;
  }
  return 0;
}

__hidden int __toin(FILE *stream)
{
  if (stream->flags & D_WRITE) {
    if (__flushbuf(stream) == EOF)
      return EOF;
    stream->flags &= ~D_WRITE;
  }
  stream->flags |= D_READ;
  return 0;
}

__hidden void __toout(FILE *stream)
{
  if (stream->flags & D_READ) {
    IBUF_DROP(stream);
    stream->flags &= ~D_READ;
    stream->shcnt = 0;
  }
  stream->flags |= D_WRITE;
}

__hidden void __unlinks(FILE *stream)
{
  if (stream->prev)
    stream->prev->next = stream->next;
  else
    __stdio_head = stream->next;

  if (stream->next)
    stream->next->prev = stream->prev;
}