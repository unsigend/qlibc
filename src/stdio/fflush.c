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

static int __flushall(void) {
  FILE *__c = __stdio_head;
  while (__c) {
    if (__FILE_IS_WRITE(__c) && !__IO_WBUF_EMPTY(__c)) {
      if (__flushbuf(__c) == EOF)
        return EOF;
    }
    if (__FILE_IS_READ(__c))
      __IO_RBUF_DROP(__c);
    __c = __c->next;
  }
  return 0;
}

int fflush(FILE *stream) {
  if (!stream)
    return __flushall();
  if (__FILE_IS_ERR(stream))
    return EOF;
  if (__FILE_IS_WRITE(stream) && !__IO_WBUF_EMPTY(stream)) {
    if (__flushbuf(stream) == EOF)
      return EOF;
  }
  if (__FILE_IS_READ(stream))
    __IO_RBUF_DROP(stream);
  return 0;
}