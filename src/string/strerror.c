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

#include <errno.h>
#include <string.h>

/**
 * Map the error number to the error string
 */
#define ERROR(errnum, errstr) errnum
static unsigned char __strerror_id[] = {
#include <bits/strerror.h>
};

#undef ERROR
#define ERROR(errnum, errstr) errstr
static const char *__strerror_str[] = {
#include <bits/strerror.h>
};

#define _ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
char *strerror(int errnum) {
  if (errnum < 0) {
    return (char *)"Unknown error";
  }
  unsigned long i;
  for (i = 0; i < _ARRAY_SIZE(__strerror_id); i++) {
    if (__strerror_id[i] == errnum) {
      return (char *)__strerror_str[i];
    }
  }
  return (char *)"Unknown error";
}