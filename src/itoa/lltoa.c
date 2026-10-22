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

#include <ext/itoa.h>
#include <limits.h>

char *lltoa(long long val, char *buf, int base)
{
    char *p = buf;
    unsigned long long uval;

    if (base == 10 && val < 0) {
        *p++ = '-';
        uval = (val == LLONG_MIN) ? (unsigned long long)LLONG_MAX + 1
                                  : (unsigned long long)(-val);
    } else
        uval = (unsigned long long)val;

    xtoa(uval, p, base);
    return buf;
}