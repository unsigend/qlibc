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

#ifndef _QLIBC_STRING_H_
#define _QLIBC_STRING_H_

#include <feature.h>
#include <stddef.h>

__BEGIN_DECLS
/* Search the memory area for the first occurrence of the character ch */
extern void *memchr(const void *ptr, int ch, size_t count);

/* Compare the memory areas */
extern int memcmp(const void *lhs, const void *rhs, size_t count);

/* Fill the memory area with the specified value */
extern void *memset(void *dest, int ch, size_t count);

/* Copy from SRC to DEST*/
extern void *memcpy(void *restrict dest, const void *restrict src,
                    size_t count);

/* Copy from SRC to DEST, but the memory areas may overlap */
extern void *memmove(void *dest, const void *src, size_t count);

/* Get the length of the string */
extern size_t strlen(const char *str);

/* Compare the strings */
extern int strcmp(const char *lhs, const char *rhs);

/* Compare the strings, but the memory areas may overlap */
extern int strncmp(const char *lhs, const char *rhs, size_t count);

/* Compare the strings, but the memory areas may overlap */
extern int strcoll(const char *lhs, const char *rhs);

/* Search the string for the first occurrence of the character ch */
extern char *strchr(const char *str, int ch);

/* Search the string for the last occurrence of the character ch */
extern char *strrchr(const char *str, int ch);

/* Get the length of the initial segment of the string that consists of only the
   characters in the charset */
extern size_t strspn(const char *str, const char *charset);

/* Get the length of the initial segment of the string that consists of only the
   characters not in the charset */
extern size_t strcspn(const char *str, const char *charset);

/* Search the string for the first occurrence of any character in the charset */
extern char *strpbrk(const char *str, const char *charset);

/* Search the string for the first occurrence of the substring */
extern char *strstr(const char *str, const char *substr);

/* Tokenize the string */
extern char *strtok(char *restrict str, const char *restrict delim);

/* Copy the string from SRC to DEST */
extern char *strcpy(char *restrict dest, const char *restrict src);

/* Copy from SRC to DEST, but the memory areas may overlap */
extern char *strncpy(char *restrict dest, const char *restrict src,
                     size_t count);

/* Concatenate the string from SRC to DEST */
extern char *strcat(char *restrict dest, const char *restrict src);

/* Concatenate from SRC to DEST, but the memory areas may overlap */
extern char *strncat(char *restrict dest, const char *restrict src,
                     size_t count);

/* Transform the string from SRC to DEST */
extern size_t strxfrm(char *restrict dest, const char *restrict src,
                      size_t count);

/* Duplicate the string */
extern char *strdup(const char *src);

/* Get the error message for the error number */
extern char *strerror(int errnum);

__END_DECLS

#endif // _QLIBC_STRING_H_