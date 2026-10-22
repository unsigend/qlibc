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

#include "xtoa.h"

#include <errno.h>

char *xtoa(unsigned long long val, char *buf, int base)
{
    char *p;
    const char *d = "0123456789abcdefghijklmnopqrstuvwxyz";

    if (base < 2 || base > 36) {
        errno = EINVAL;
        return buf;
    }

    p = buf;
    do {
        *p++ = d[val % base];
        val /= base;
    } while (val);

    for (char *l = buf, *r = p - 1; l < r; l++, r--) {
        char tmp = *l;
        *l = *r;
        *r = tmp;
    }

    *p = '\0';
    return buf;
}