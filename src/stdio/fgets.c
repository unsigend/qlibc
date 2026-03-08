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

#include <stdio.h>

char *fgets(char *restrict str, int count, FILE *stream) {
  if (!str || count <= 0 || !stream)
    return NULL;

  size_t rn = count - 1;
  size_t total = 0;

  while (total < rn) {
    int ch = fgetc(stream);
    if (ch == EOF)
      break;
    str[total++] = ch;
    if (ch == '\n')
      break;
  }

  str[total] = '\0';
  return total ? str : NULL;
}