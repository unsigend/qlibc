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

#include "internal/io.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define PERM (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
FILE *tmpfile(void)
{
  int fd = open("/tmp", O_TMPFILE | O_RDWR, PERM);
  if (fd == -1)
    return NULL;

  FILE *stream = malloc(sizeof(FILE));
  if (!stream) {
    close(fd);
    return NULL;
  }

  __inits(stream, fd, O_RDWR, _IOFBF);
  return stream;
}