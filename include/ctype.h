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

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Check if a character is alphanumeric.
 */
int isalnum(int c);

/**
 * @brief Check if a character is alphabetic.
 */
int isalpha(int c);

/**
 * @brief Check if a character is a blank character.
 */
int isblank(int c);

/**
 * @brief Check if a character is a control character.
 */
int iscntrl(int c);

/**
 * @brief Check if a character is a digit.
 */
int isdigit(int c);

/**
 * @brief Check if a character is a graphical character.
 */
int isgraph(int c);

/**
 * @brief Check if a character is a lowercase letter.
 */
int islower(int c);

/**
 * @brief Check if a character is a printable character.
 */
int isprint(int c);

/**
 * @brief Check if a character is a punctuation character.
 */
int ispunct(int c);

/**
 * @brief Check if a character is a space character.
 */
int isspace(int c);

/**
 * @brief Check if a character is an uppercase letter.
 */
int isupper(int c);

/**
 * @brief Check if a character is a hexadecimal digit.
 */
int isxdigit(int c);

/**
 * @brief Convert a character to lowercase.
 */
int tolower(int c);

/**
 * @brief Convert a character to uppercase.
 */
int toupper(int c);

#ifdef __cplusplus
}
#endif

#endif 