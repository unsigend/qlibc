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

#ifndef _QLIBC_STDIO_H_
#define _QLIBC_STDIO_H_

/* seek flags */
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#ifndef __cplusplus
#define NULL ((void *)0)
#else
#define NULL nullptr
#endif

typedef struct _FILE_IO {

} FILE;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

/* file access */
extern FILE *fopen(const char *restrict filename, const char *restrict mode);
extern FILE *freopen(const char *restrict filename, const char *restrict mode,
                     FILE *restrict stream);

#endif