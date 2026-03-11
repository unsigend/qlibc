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
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int setenv(const char *name, const char *value, int overwrite)
{
  if (!name || !value)
    return -1;

  size_t namelen = strlen(name);
  size_t valuelen = strlen(value);
  if (!namelen)
    return -1;

  /* Required size for name=value pair: namelen + '=' + valuelen + '\0' */
  if (environ) {
    for (size_t i = 0; environ[i]; i++) {
      if (!strncmp(environ[i], name, namelen) && environ[i][namelen] == '=') {
        if (!overwrite)
          return 0;
        environ[i] = malloc(namelen + valuelen + 2);
        if (!environ[i]) {
          errno = ENOMEM;
          return -1;
        }
        memcpy(environ[i], name, namelen);
        environ[i][namelen] = '=';
        memcpy(environ[i] + namelen + 1, value, valuelen);
        environ[i][namelen + valuelen + 1] = '\0';
        return 0;
      }
    }
  }

  char *newstr = (char *)malloc(namelen + valuelen + 2);
  if (!newstr) {
    errno = ENOMEM;
    return -1;
  }

  memcpy(newstr, name, namelen);
  newstr[namelen] = '=';
  memcpy(newstr + namelen + 1, value, valuelen);
  newstr[namelen + valuelen + 1] = '\0';

  char **newenviron = env_expand(environ, newstr);
  if (!newenviron) {
    free(newstr);
    return -1; /* errno is set by env_expand */
  }

  if (__heap_environ)
    free(__heap_environ);
  environ = __heap_environ = newenviron;
  return 0;
}