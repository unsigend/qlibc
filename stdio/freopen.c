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

#define __DEFAULT_PERM (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

FILE *freopen(const char *restrict filename, const char *restrict mode,
              FILE *restrict stream) {
  if (!filename || !mode || !stream)
    return NULL;

  // flush the buffered write data
  if (fflush(stream) == EOF)
    return NULL;

  // close the file descriptor
  if (close(stream->fd) == -1) {
    __FILE_SET_ERR(stream);
    return NULL;
  }

  if (__FILE_IS_MYBUF(stream) && stream->buf) {
    free(stream->buf);
  }

  int fd, oflags;
  int bufmode;

  switch (mode[0]) {
  case 'r':
    oflags = O_RDONLY;
    break;
  case 'w':
    oflags = O_WRONLY | O_CREAT | O_TRUNC;
    break;
  case 'a':
    oflags = O_WRONLY | O_CREAT | O_APPEND;
    break;
  }

  if (mode[1] == '+' || (mode[1] && mode[2] == '+'))
    oflags = (oflags & ~O_ACCMODE) | O_RDWR;

  fd = open(filename, oflags, __DEFAULT_PERM);
  if (fd == -1)
    return NULL;

  bufmode = isatty(fd) ? _IOLBF : _IOFBF;

  // init strem state
  stream->fd = fd;
  stream->flags = __mode_to_flags(oflags);
  stream->mode = oflags;
  stream->bufmode = bufmode;

  stream->error = 0;
  stream->eof = 0;
  stream->offset = 0;

  stream->buf = NULL;
  stream->bufsz = 0;
  stream->rpos = stream->rend = NULL;
  stream->wpos = stream->wbase = stream->wend = NULL;

  stream->shbuf = NULL;
  stream->shlim = UNGET;
  stream->shcnt = 0;

  return stream;
}