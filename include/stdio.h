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

#ifndef _QLIBC_STDIO_H_
#define _QLIBC_STDIO_H_

#include <feature.h>
#include <stdarg.h>
#include <stddef.h>
#include <sys/types.h>

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define _IOFBF 0
#define _IOLBF 1
#define _IONBF 2

#define EOF (-1)          /* end of file */
#define BUFSIZ 8192       /* buffer size */
#define FILENAME_MAX 4096 /* maximum file name length */
#define FOPEN_MAX 1000    /* maximum number of open files */
#define TMP_MAX 10000     /* maximum number of temporary files */

struct _FILE_IO;
typedef struct _FILE_IO FILE;

typedef struct _fpos {
    off_t pos; /* file position */
} fpos_t;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

#define stdin stdin
#define stdout stdout
#define stderr stderr

#ifdef __cplusplus
extern "C" {
#endif

extern FILE *fopen(const char *__restrict filename,
                   const char *__restrict mode);
extern FILE *freopen(const char *__restrict filename,
                     const char *__restrict mode, FILE *__restrict stream);
extern int fclose(FILE *stream);
extern int fflush(FILE *stream);
extern void setbuf(FILE *__restrict stream, char *__restrict buf);
extern int setvbuf(FILE *__restrict stream, char *__restrict buf, int mode,
                   size_t size);

extern size_t fread(void *__restrict buf, size_t size, size_t count,
                    FILE *__restrict stream);
extern size_t fwrite(const void *__restrict buf, size_t size, size_t count,
                     FILE *__restrict stream);

extern int fgetc(FILE *stream);
extern int getc(FILE *stream);
extern char *fgets(char *__restrict str, int count, FILE *__restrict stream);
extern int fputc(int ch, FILE *stream);
extern int putc(int ch, FILE *stream);
extern int fputs(const char *__restrict str, FILE *__restrict stream);
extern int getchar(void);
extern int putchar(int ch);
extern int puts(const char *str);
extern int ungetc(int ch, FILE *stream);

extern int scanf(const char *__restrict fmt, ...);
extern int fscanf(FILE *__restrict stream, const char *__restrict fmt, ...);
extern int sscanf(const char *__restrict buf, const char *__restrict fmt, ...);
extern int vscanf(const char *__restrict fmt, va_list vlist);
extern int vfscanf(FILE *__restrict stream, const char *__restrict fmt,
                   va_list vlist);
extern int vsscanf(const char *__restrict buf, const char *__restrict fmt,
                   va_list vlist);

extern int printf(const char *__restrict fmt, ...);
extern int fprintf(FILE *__restrict stream, const char *__restrict fmt, ...);
extern int sprintf(char *__restrict buf, const char *__restrict fmt, ...);
extern int snprintf(char *__restrict buf, size_t bufsz,
                    const char *__restrict fmt, ...);
extern int vprintf(const char *__restrict fmt, va_list vlist);
extern int vfprintf(FILE *__restrict stream, const char *__restrict fmt,
                    va_list vlist);
extern int vsprintf(char *__restrict buf, const char *__restrict fmt,
                    va_list vlist);
extern int vsnprintf(char *__restrict buf, size_t bufsz,
                     const char *__restrict fmt, va_list vlist);

extern long ftell(FILE *stream);
extern int fgetpos(FILE *__restrict stream, fpos_t *__restrict pos);
extern int fseek(FILE *stream, long offset, int origin);
extern int fsetpos(FILE *__restrict stream, const fpos_t *__restrict pos);
extern void rewind(FILE *stream);

extern void clearerr(FILE *stream);
extern int feof(FILE *stream);
extern int ferror(FILE *stream);
extern void perror(const char *s);

extern int remove(const char *pathname);
extern int rename(const char *oldpath, const char *newpath);
extern FILE *tmpfile(void);

#ifdef __cplusplus
}
#endif

#endif /* _QLIBC_STDIO_H_ */