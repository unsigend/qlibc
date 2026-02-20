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

#ifndef _QLIBC_EXT_ITOA_H_
#define _QLIBC_EXT_ITOA_H_

/* This header is not part of ANSI/ISO C Standard header file, it is part of
   qlibc header extensions. This header provides integer to string conversion
   functions. */
#include <feature.h>

#define INT_BUFFSZ                                                             \
  32 /* buffer size for integer conversion, enough for 64-bit integer */

__BEGIN_DECLS

/* Convert an integer to a string. If base is 10 and value is negative, the
   resulting string is preceded with a minus sign (-). With any other base,
   value is always considered unsigned.  Return the pointer to the NULL
   terminated string.*/
extern char *itoa(int value, char *buff, int base);

/* Convert a long integer to a string. If base is 10 and value is negative, the
   resulting string is preceded with a minus sign (-). With any other base,
   value is always considered unsigned.  Return the pointer to the NULL
   terminated string.*/
extern char *ltoa(long value, char *buff, int base);

/* Convert a long long integer to a string. If base is 10 and value is negative,
   the resulting string is preceded with a minus sign (-). With any other base,
   value is always considered unsigned.  Return the pointer to the NULL
   terminated string.*/
extern char *lltoa(long long value, char *buff, int base);

/* Convert an unsigned integer to a string. Return the pointer to the NULL
   terminated string.*/
extern char *utoa(unsigned int value, char *buff, int base);

/* Convert an unsigned long integer to a string. Return the pointer to the NULL
   terminated string.*/
extern char *ultoa(unsigned long value, char *buff, int base);

/* Convert an unsigned long long integer to a string. Return the pointer to the
   NULL terminated string.*/
extern char *ulltoa(unsigned long long value, char *buff, int base);

__END_DECLS

#endif