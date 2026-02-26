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
#include "env.h"
#include <stdlib.h>
#include <string.h>

/* Based on ANSI/ISO C standard, putenv() function will not copy the string to a
   buffer. Return 0 if success, otherwise return -1. */

int putenv(char *string) {
  if (!string)
    return -1;
  size_t len = strlen(string);
  char *eq = strchr(string, '=');
  if (!len || !eq)
    return -1;
  size_t namelen = eq - string;

  if (environ) {
    for (size_t i = 0; environ[i]; i++) {
      if (!strncmp(environ[i], string, namelen) && environ[i][namelen] == '=') {
        environ[i] = string;
        return 0;
      }
    }
  }
  char **newenviron = env_expand(environ, string);
  if (!newenviron)
    return -1; /* errno is set by env_expand */

  if (__heap_environ)
    free(__heap_environ);

  environ = __heap_environ = newenviron;
  return 0;
}