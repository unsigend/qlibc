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

#include "env.h"

#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int unsetenv(const char *name)
{
    size_t namelen;
    char **newenviron;
    int inplace;

    if (!name || !name[0] || strchr(name, '=')) {
        errno = EINVAL;
        return -1;
    }
    if (!environ)
        return 0;

    inplace = 0;
    newenviron = NULL;
    namelen = strlen(name);

    for (size_t i = 0; environ[i]; i++) {
        if (!strncmp(environ[i], name, namelen) && environ[i][namelen] == '=') {
            newenviron = env_remove(environ, i, &inplace);
            if (!newenviron)
                return -1;
            break;
        }
    }

    if (!newenviron || inplace)
        return 0;
    if (__heap_environ)
        free(__heap_environ);
    environ = __heap_environ = newenviron;
    return 0;
}
