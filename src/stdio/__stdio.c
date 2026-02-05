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
#include <fcntl.h>
#include <stdlib.h>

// global pointer to the head of the file stream list
FILE *__stdio_head = NULL;

// __mode_to_flags(__mode)
//    Convert the mode to the flags.
//
//    This function will always succeed.

static int __mode_to_flags(int __mode) {
  int flags = 0;
  int access = __mode & O_ACCMODE;

  if (access == O_RDONLY || access == O_RDWR)
    flags |= F_READ;
  if (access == O_WRONLY || access == O_RDWR)
    flags |= F_WRITE;
  if (__mode & O_APPEND)
    flags |= F_APPEND;

  return flags;
}

// __finit(__stream, __fd, __flags, __bufmode)
//    Initialize a file stream, all the fields are initialized to zero or NULL.
//    Return the initialized stream.
//
//    This function will always succeed.

FILE *__finit(FILE *__stream, int __fd, int __mode, int __bufmode) {
  // init file descriptor and mode
  __stream->fd = __fd;
  __stream->flags = __mode_to_flags(__mode);
  __stream->mode = __mode;
  __stream->bufmode = __bufmode;

  // init error and EOF flags
  __stream->eof = 0;
  __stream->error = 0;
  __stream->offset = 0;

  // init buffer
  __stream->buf = NULL;
  __stream->bufsz = 0;
  __stream->rpos = __stream->rend = NULL;
  __stream->wpos = __stream->wbase = __stream->wend = NULL;

  // init pushback buffer
  __stream->shbuf = NULL;
  __stream->shlim = UNGET;
  __stream->shcnt = 0;

  // init next and previous file for fflush(NULL) support
  __stream->next = __stdio_head;
  __stream->prev = NULL;
  if (__stdio_head) {
    __stdio_head->prev = __stream;
  }
  __stdio_head = __stream;

  return __stream;
}

// __allocbuf(__stream)
//    Allocate a buffer for the file stream.
//    Return 0 on success, -1 on failure.
//

int __allocbuf(FILE *__stream) {
  size_t sz;

  if (__stream->buf)
    return 0;

  // even the buffer mode is _IONBF, the buffer size is still 1
  if (__stream->bufmode == _IONBF)
    sz = 1;
  else
    sz = BUFSIZ;

  __stream->buf = malloc(sz);
  if (!__stream->buf) {
    __stream->flags |= F_ERR;
    return -1;
  }

  __stream->bufsz = sz;
  __stream->flags |= F_MYBUF;

  if (__FILE_IS_WRITE(__stream)) {
    __stream->wbase = __stream->wpos = __stream->buf;
    __stream->wend = __stream->buf + sz;
  }
  if (__FILE_IS_READ(__stream)) {
    __stream->rpos = __stream->rend = __stream->buf;
  }

  return 0;
}