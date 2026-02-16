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

int ungetc(int ch, FILE *stream) {
  if (!stream || ch == EOF || __FILE_IS_ERR(stream))
    return EOF;

  if (!stream->shbuf) {
    stream->shbuf = malloc(UNGET);
    if (!stream->shbuf) {
      __FILE_SET_ERR(stream);
      return EOF;
    }
    stream->shlim = UNGET;
    stream->shcnt = 0;
  }

  if (stream->shcnt >= stream->shlim) {
    __FILE_SET_ERR(stream);
    return EOF;
  }

  stream->shbuf[stream->shcnt++] = (unsigned char)ch;
  __FILE_CLEAR_EOF(stream);
  return ch;
}