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

#ifndef _IO_H_
#define _IO_H_ 1

/* Standard I/O internal implementation. For now the IO use a simple buffer
   model which is 8192 bytes. No lock protection and thread safety is supported
   yet. */
#include <fcntl.h>
#include <feature.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define UNGET 8 /* pushback buffer limit */

#define D_READ 0x01   /* read direction */
#define D_WRITE 0x02  /* write direction */
#define S_MYBUF 0x04  /* qlibc buffer */
#define S_STATIC 0x08 /* FILE is static */

#define IBUF_EXHAUSTED(s)                                                      \
  ((s)->rpos == (s)->rend) /* input buffer is exhausted */
#define IBUF_DROP(s)                                                           \
  ((s)->rpos = (s)->rend = (s)->buf)            /* drop input buffer           \
                                                 */
#define OBUF_FULL(s) ((s)->wpos == (s)->wend)   /* output buffer is full */
#define OBUF_EMPTY(s) ((s)->wpos == (s)->wbase) /* output buffer is empty */
#define OBUF_DROP(s) ((s)->wpos = (s)->wbase)   /* drop output buffer */

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/* global pointer to the head of the file stream list */
extern __hidden FILE *__stdio_head;

/* Initialize a file stream, all the fields are initialized to zero or NULL.
 * Return the initialized stream. Always succeed.*/
extern __hidden FILE *__inits(FILE *stream, int fd, int mode, int bufmode);

/* Allocate memory for buffer if F_MYBUF is set, or reset buffer pointer if it
   is maintained by user. Return 0 on success, EOF on failure. */
extern __hidden int __allocbuf(FILE *stream);

/* Refill the read buffer. Return the number of bytes read on success, EOF on
   failure. */
extern __hidden int __refill(FILE *stream);

/* Flush the write buffer. Return 0 on success, EOF on failure. */
extern __hidden int __flushbuf(FILE *stream);

/* Write all the data to the file descriptor. Return the number of bytes
   written on success, -1 on failure. */
extern __hidden int __writeall(int fd, const unsigned char *buf, ssize_t n);

/* Read all the data from the file descriptor. Return the number of bytes
   read on success, 0 on EOF, -1 on failure. */
extern __hidden int __readall(int fd, unsigned char *buf, ssize_t n);

/* Reset the buffer pointers to initial state. */
extern __hidden void __resetbufp(FILE *stream, unsigned char *buf, size_t sz);

/* Switch a stream status to read direction or write direction. When switching
   to read direction, return EOF on failure. Switch to out direction is always
   succeed. */
extern __hidden int __toin(FILE *stream);
extern __hidden void __toout(FILE *stream);

/* Unlink a stream from the global stream list. */
extern __hidden void __unlinks(FILE *stream);

#endif