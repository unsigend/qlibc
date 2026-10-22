/* qlibc - A light-weight and portable C standard library
 * Copyright (C) 2025-2027 Yixiang Qiu
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

#if !defined(_POSIX_SOURCE) && !defined(_POSIX_C_SOURCE) &&                    \
    !defined(_XOPEN_SOURCE) && !defined(_GNU_SOURCE) && !defined(_BSD_SOURCE)
int setenv(const char *name, const char *val, int overwrite);
#endif

#include "env.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>

int setenv(const char *name, const char *val, int overwrite)
{
    size_t namelen;
    size_t vallen;
    char **newenviron;

    if (!name || !name[0] || strchr(name, '=') || !val) {
        errno = EINVAL;
        return -1;
    }

    namelen = strlen(name);
    vallen = strlen(val);

    if (environ) {
        for (size_t i = 0; environ[i]; i++) {
            if (!strncmp(environ[i], name, namelen) &&
                environ[i][namelen] == '=') {
                char *repl;

                if (!overwrite)
                    return 0;
                repl = malloc(namelen + vallen + 2);
                if (!repl) {
                    errno = ENOMEM;
                    return -1;
                }
                memcpy(repl, name, namelen);
                repl[namelen] = '=';
                memcpy(repl + namelen + 1, val, vallen);
                repl[namelen + vallen + 1] = '\0';
                environ[i] = repl;
                return 0;
            }
        }
    }

    char *newstr = (char *)malloc(namelen + vallen + 2);
    if (!newstr) {
        errno = ENOMEM;
        return -1;
    }

    memcpy(newstr, name, namelen);
    newstr[namelen] = '=';
    memcpy(newstr + namelen + 1, val, vallen);
    newstr[namelen + vallen + 1] = '\0';

    newenviron = env_expand(environ, newstr);
    if (!newenviron) {
        free(newstr);
        return -1; /* errno is set by env_expand */
    }

    if (__heap_environ)
        free(__heap_environ);
    environ = __heap_environ = newenviron;
    return 0;
}
