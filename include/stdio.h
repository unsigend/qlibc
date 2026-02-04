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

#include <stdarg.h>
#include <stddef.h>

/* seek flags */
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

/* buffer mode */
#define _IOFBF 0
#define _IOLBF 1
#define _IONBF 2

#define EOF (-1)
#define BUFSIZ 4096

/* file IO structure */
typedef struct _FILE_IO {
  int fd;             /* file descriptor */
  int oflags;         /* file open flags */
  int flags;          /* file flags */
  int error;          /* error indicator */
  int eof;            /* EOF indicator*/
  long offset;        /* file offset */
  unsigned char *buf; /* buffer */
  size_t bufsz;       /* buffer size */
  size_t bufpos;      /* buffer position */
  size_t bufend;      /* buffer end */
  int bufmode;        /* buffer mode */
} FILE;

/* file access */
extern FILE *fopen(const char *restrict filename, const char *restrict mode);
extern FILE *freopen(const char *restrict filename, const char *restrict mode,
                     FILE *restrict stream);
extern int fclose(FILE *stream);
extern int fflush(FILE *stream);
extern void setbuf(FILE *restrict stream, char *restrict buffer);
extern int setvbuf(FILE *restrict stream, char *restrict buffer, int mode,
                   size_t size);

/* direct I/O */
extern size_t fread(void *restrict buffer, size_t size, size_t count,
                    FILE *restrict stream);
extern size_t fwrite(const void *restrict buffer, size_t size, size_t count,
                     FILE *restrict stream);

/* unformatted I/O */
extern int fgetc(FILE *stream);
extern int getc(FILE *stream);
extern char *fgets(char *restrict str, int count, FILE *restrict stream);
extern int fputc(int ch, FILE *stream);
extern int putc(int ch, FILE *stream);
extern int fputs(const char *restrict str, FILE *restrict stream);
extern int getchar(void);
extern char *gets(char *str);
extern int putchar(int ch);
extern int puts(const char *str);
extern int ungetc(int ch, FILE *stream);

/* formatted I/O */
extern int scanf(const char *restrict format, ...);
extern int fscanf(FILE *restrict stream, const char *restrict format, ...);
extern int sscanf(const char *restrict buffer, const char *restrict format,
                  ...);
extern int vscanf(const char *restrict format, va_list vlist);
extern int vfscanf(FILE *restrict stream, const char *restrict format,
                   va_list vlist);
extern int vsscanf(const char *restrict buffer, const char *restrict format,
                   va_list vlist);
extern int printf(const char *restrict format, ...);
extern int fprintf(FILE *restrict stream, const char *restrict format, ...);
extern int sprintf(char *restrict buffer, const char *restrict format, ...);
extern int snprintf(char *restrict buffer, size_t bufsz,
                    const char *restrict format, ...);
extern int vprintf(const char *restrict format, va_list vlist);
extern int vfprintf(FILE *restrict stream, const char *restrict format,
                    va_list vlist);
extern int vsprintf(char *restrict buffer, const char *restrict format,
                    va_list vlist);
extern int vsnprintf(char *restrict buffer, size_t bufsz,
                     const char *restrict format, va_list vlist);

/* file positioning */
extern long ftell(FILE *stream);
extern int fseek(FILE *stream, long offset, int origin);
extern void rewind(FILE *stream);

/* error handling */
extern void clearerr(FILE *stream);
extern int feof(FILE *stream);
extern int ferror(FILE *stream);
extern void perror(const char *s);

/* file operations */
extern int remove(const char *pathname);
extern int rename(const char *oldpath, const char *newpath);
extern FILE *tmpfile(void);
extern char *tmpnam(char *str);
#endif