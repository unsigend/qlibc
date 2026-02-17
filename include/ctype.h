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

#ifndef _QLIBC_CTYPE_H_
#define _QLIBC_CTYPE_H_

#include <feature.h>

__BEGIN_DECLS

/* Check if a character is alphanumeric (a-z, A-Z, 0-9) */
extern int isalnum(int c);
/* Check if a character is alphabetic (a-z, A-Z) */
extern int isalpha(int c);
/* Check if a character is a digit (0-9) */
extern int isdigit(int c);
/* Check if a character is a hexadecimal digit (0-9, a-f, A-F) */
extern int isxdigit(int c);

/* Check if a character is a blank character */
extern int isblank(int c);
/* Check if a character is a control character */
extern int iscntrl(int c);
/* Check if a character is a space character */
extern int isspace(int c);
/* Check if a character is a punctuation character */
extern int ispunct(int c);

/* Check if a character is a lowercase letter */
extern int islower(int c);
/* Check if a character is an uppercase letter */
extern int isupper(int c);

/* Check if a character is a graphical character */
extern int isgraph(int c);
/* Check if a character is a printable character */
extern int isprint(int c);

/* Convert a character to lowercase */
extern int tolower(int c);
/* Convert a character to uppercase */
extern int toupper(int c);

__END_DECLS

#endif