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

#ifndef _QLIBC_STDIO__STDIO_H_
#define _QLIBC_STDIO__STDIO_H_

#include <fcntl.h>
#include <stdioo.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define UNGET 8

#define F_EOF 0x01     /* EOF flag */
#define F_ERR 0x02     /* error flag */
#define F_READ 0x04    /* open for reading */
#define F_WRITE 0x08   /* open for writing */
#define F_APPEND 0x10  /* append mode */
#define F_MYBUF 0x20   /* qlibc buffer */
#define F_LINEBUF 0x40 /* line buffered */

#define __FILE_MODE(__F) ((__F)->mode)
#define __FILE_FLAGS(__F) ((__F)->flags)
#define __FILE_BUFMODE(__F) ((__F)->bufmode)

#define __FILE_IS_EOF(__F) (((__FILE_FLAGS(__F)) & F_EOF) != 0)
#define __FILE_IS_ERR(__F) (((__FILE_FLAGS(__F)) & F_ERR) != 0)
#define __FILE_IS_READ(__F) (((__FILE_FLAGS(__F)) & F_READ) != 0)
#define __FILE_IS_WRITE(__F) (((__FILE_FLAGS(__F)) & F_WRITE) != 0)
#define __FILE_IS_APPEND(__F) (((__FILE_FLAGS(__F)) & F_APPEND) != 0)
#define __FILE_IS_MYBUF(__F) (((__FILE_FLAGS(__F)) & F_MYBUF) != 0)
#define __FILE_IS_LINEBUF(__F) (((__FILE_FLAGS(__F)) & F_LINEBUF) != 0)

#define __FILE_SET_EOF(__F) (((__FILE_FLAGS(__F)) |= F_EOF))
#define __FILE_SET_ERR(__F) (((__FILE_FLAGS(__F)) |= F_ERR))
#define __FILE_SET_READ(__F) (((__FILE_FLAGS(__F)) |= F_READ))
#define __FILE_SET_WRITE(__F) (((__FILE_FLAGS(__F)) |= F_WRITE))
#define __FILE_SET_APPEND(__F) (((__FILE_FLAGS(__F)) |= F_APPEND))
#define __FILE_SET_MYBUF(__F) (((__FILE_FLAGS(__F)) |= F_MYBUF))
#define __FILE_SET_LINEBUF(__F) (((__FILE_FLAGS(__F)) |= F_LINEBUF))

#define __FILE_CLEAR_EOF(__F) (((__FILE_FLAGS(__F)) &= ~F_EOF))
#define __FILE_CLEAR_ERR(__F) (((__FILE_FLAGS(__F)) &= ~F_ERR))
#define __FILE_CLEAR_READ(__F) (((__FILE_FLAGS(__F)) &= ~F_READ))
#define __FILE_CLEAR_WRITE(__F) (((__FILE_FLAGS(__F)) &= ~F_WRITE))
#define __FILE_CLEAR_APPEND(__F) (((__FILE_FLAGS(__F)) &= ~F_APPEND))
#define __FILE_CLEAR_MYBUF(__F) (((__FILE_FLAGS(__F)) &= ~F_MYBUF))
#define __FILE_CLEAR_LINEBUF(__F) (((__FILE_FLAGS(__F)) &= ~F_LINEBUF))

extern FILE *__stdio_head;
extern FILE *__finit(FILE *__stream, int __fd, int __mode, int __bufmode);
extern int __allocbuf(FILE *__stream);

#endif