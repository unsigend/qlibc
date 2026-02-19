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

/* Internal implementation of printf family of functions. This source file
   should be a freestanding implementation of the core printf, which is
   independent of the standard library and no buffer related manipulation. */

#include <stdarg.h>
#include <string.h>

/* Features supported:
   Specifiers: %c, %s, %d, %i, %o, %x, %X, %u, %p
   Flags:
      - left alignment: -
      - zero padding:   0
      - 0x prefix:      # (%x, %X, %o)
   Width:      fixed %Nd, dynamic %*d
   Precision:  fixed %.Nd, dynamic %.*d
   Length:     l (long), ll (long long), z (size_t), h (short)
*/