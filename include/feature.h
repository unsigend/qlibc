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

#ifndef _QLIBC_FEATURE_H_
#define _QLIBC_FEATURE_H_

#define __ISO_C23 202311L
#define __ISO_C17 201710L
#define __ISO_C11 201112L
#define __ISO_C99 199901L
#define __ISO_C94 199409L
#define __ISO_C89 0

#ifndef __STDC_VERSION__
#define __STDC_VERSION__ __ISO_C89
#endif

#ifndef __GNUC__
#error "qlibc: missing GNU C compiler"
#endif

#define __WORD_SIZE __SIZEOF_LONG__

#endif /* _QLIBC_FEATURE_H_ */
