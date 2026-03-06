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

#ifndef _BITS_MMANFLAGS_H_
#define _BITS_MMANFLAGS_H_ 1

#define PROT_NONE 0x00            /* No permissions */
#define PROT_READ 0x01            /* Read permissions */
#define PROT_WRITE 0x02           /* Write permissions */
#define PROT_EXEC 0x04            /* Execute permissions */
#define PROT_GROWSDOWN 0x01000000 /* Grow down */
#define PROT_GROWSUP 0x02000000   /* Grow up */

#define MAP_SHARED 0x01          /* Shared mapping */
#define MAP_PRIVATE 0x02         /* Private mapping */
#define MAP_SHARED_VALIDATE 0x03 /* Shared mapping with validation */
#define MAP_TYPE 0x0f            /* Type of mapping */
#define MAP_FIXED 0x10           /* Fixed mapping */
#define MAP_FILE 0               /* File mapping */
#define MAP_ANONYMOUS 0x20       /* Anonymous mapping */
#define MAP_ANON MAP_ANONYMOUS   /* Anonymous mapping */
#define MAP_HUGE_SHIFT 26        /* Huge shift */
#define MAP_HUGE_MASK 0x3f       /* Huge mask */
#define MAP_FAILED ((void *)-1)  /* Failed mapping */

#define MREMAP_MAYMOVE 0x01   /* May move the mapping */
#define MREMAP_FIXED 0x02     /* Fixed mapping */
#define MREMAP_DONTUNMAP 0x04 /* Don't unmap the mapping */

#endif