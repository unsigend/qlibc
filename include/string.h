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

#ifndef _QLIBC_STRING_H_
#define _QLIBC_STRING_H_

#include <feature.h>

typedef __SIZE_TYPE__ size_t;
#define NULL ((void *)0)

#ifdef __cplusplus
extern "C" {
#endif

extern void *memchr(const void *ptr, int ch, size_t count);
extern int memcmp(const void *lhs, const void *rhs, size_t count);
extern void *memset(void *dest, int ch, size_t count);
extern void *memcpy(void *__restrict dest, const void *__restrict src,
                    size_t count);
extern void *memmove(void *dest, const void *src, size_t count);

extern size_t strlen(const char *str);
extern int strcmp(const char *lhs, const char *rhs);
extern int strncmp(const char *lhs, const char *rhs, size_t count);
extern char *strchr(const char *str, int ch);
extern char *strrchr(const char *str, int ch);

extern size_t strspn(const char *str, const char *charset);
extern size_t strcspn(const char *str, const char *charset);
extern char *strpbrk(const char *str, const char *charset);
extern char *strstr(const char *str, const char *substr);
extern char *strtok(char *__restrict str, const char *__restrict delim);
extern char *strcpy(char *__restrict dest, const char *__restrict src);
extern char *strncpy(char *__restrict dest, const char *__restrict src,
                     size_t count);
extern char *strcat(char *__restrict dest, const char *__restrict src);
extern char *strncat(char *__restrict dest, const char *__restrict src,
                     size_t count);
extern char *strdup(const char *src);

extern char *strerror(int errnum);
extern char *strsignal(int sig);

#ifdef __cplusplus
}
#endif

#endif /* _QLIBC_STRING_H_ */