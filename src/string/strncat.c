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

#include <string.h>

char* strncat(char* restrict dest, const char* restrict src, size_t count){
    size_t len_dest = strlen(dest);
    size_t len_src = strlen(src);
    if (len_src < count){
        memcpy(dest + len_dest, src, len_src + 1);
    }else{
        memcpy(dest + len_dest, src, count);
        dest[len_dest + count] = '\0';
    }
    return dest;
}