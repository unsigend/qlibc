/* qlibc - A light-weight and portable C standard library
 * Copyright (C) 2025 Qiu Yixiang
 *
 * This program is free software: you can redistribute it and and/or modify
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
#include <string.h>

void *memmove(void *dest, const void *src, size_t count) {
  unsigned char *dest_ptr = (unsigned char *)dest;
  const unsigned char *src_ptr = (const unsigned char *)src;
  if (dest_ptr == src_ptr || count == 0) {
    return dest;
  }
  if (dest_ptr < src_ptr || src_ptr + count <= dest_ptr) {
    return memcpy(dest, src, count);
  } else {
    dest_ptr += count;
    src_ptr += count;
    while (count--) {
      dest_ptr--;
      src_ptr--;
      *dest_ptr = *src_ptr;
    }
  }
  return dest;
}