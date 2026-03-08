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

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define UNGET 8 /* pushback buffer limit */

#define S_READ 0x01    /* open for reading */
#define S_WRITE 0x02   /* open for writing */
#define S_APPEND 0x04  /* append mode */
#define S_MYBUF 0x08   /* qlibc buffer */
#define S_LINEBUF 0x10 /* line buffered */

#define IBUF_FULL(s) ((s)->rpos == (s)->rend) /* input buffer is full */
#define IBUF_EMPTY(s) ((s)->rpos == (s)->buf) /* input buffer is empty */
#define IBUF_DROP(s)                                                           \
  ((s)->rpos = (s)->rend = (s)->buf)            /* drop input buffer           \
                                                 */
#define OBUF_FULL(s) ((s)->wpos == (s)->wend)   /* output buffer is full */
#define OBUF_EMPTY(s) ((s)->wpos == (s)->wbase) /* output buffer is empty */
#define OBUF_DROP(s) ((s)->wpos = (s)->wbase)   /* drop output buffer */

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/* global pointer to the head of the file stream list */
extern FILE *stdio_head;

/* Initialize a file stream, all the fields are initialized to zero or NULL.
 * Return the initialized stream. Always succeed.*/
extern FILE *inits(FILE *stream, int fd, int mode, int bufmode);

/* Allocate memory for buffer if F_MYBUF is set, or reset buffer pointer if it
   is maintained by user. Return 0 on success, EOF on failure. */
extern int allocbuf(FILE *stream);

/* Refill the read buffer. Return the number of bytes read on success, EOF on
   failure. */
extern int refill(FILE *stream);

/* Flush the write buffer. Return 0 on success, EOF on failure. */
extern int flushbuf(FILE *stream);

/* Write all the data to the file descriptor. Return the number of bytes written
   on success, -1 on failure. */
extern int writeall(int fd, const unsigned char *buf, ssize_t n);

/* Reset the buffer pointers to initial state. */
extern void resetbufp(FILE *stream, unsigned char *buf, size_t sz);

/* Convert the open mode to internal flags*/
extern int mtoflags(int mode);

#endif