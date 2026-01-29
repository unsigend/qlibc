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
#include <bits/stat.h>
#include <bits/types.h>

/* Backward compatibility for old stat structure in system calls */
static inline void _stat64_to_stat(const struct __stat64 *restrict src,
                                   struct stat *restrict dst) {
  dst->st_dev = (__dev_t)(src->st_dev);
  dst->__pad0 = src->__pad0;
  dst->st_ino = (__ino_t)(src->__st_ino);
  dst->st_mode = src->st_mode;
  dst->st_nlink = src->st_nlink;
  dst->st_uid = src->st_uid;
  dst->st_gid = src->st_gid;
  dst->st_rdev = (__dev_t)(src->st_rdev);
  dst->__pad1 = src->__pad1;
  dst->st_size = (__off_t)(src->st_size);
  dst->st_blksize = src->st_blksize;
  dst->st_blocks = (__blkcnt_t)(src->st_blocks);

  /* copy timespec */
  dst->st_atime = src->st_atime;
  dst->st_mtime = src->st_mtime;
  dst->st_ctime = src->st_ctime;

  /* clear unused fields */
  dst->__unused[0] = 0;
  dst->__unused[1] = 0;
}