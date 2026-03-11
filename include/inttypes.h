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

#ifndef _INTTYPES_H_
#define _INTTYPES_H_ 1

#include <feature.h>

#if __USE_ISO_C99
#include <stdint.h>

/* Returned by imaxdiv */
typedef struct
{
  intmax_t quot;
  intmax_t rem;
} imaxdiv_t;

__BEGIN_DECLS
/* Compute the absolute value of an intmax_t integer */
extern intmax_t imaxabs(intmax_t n);

/* Compute the division of two intmax_t integers */
extern imaxdiv_t imaxdiv(intmax_t x, intmax_t y);

/* Convert a string to an integer */
extern intmax_t strtoimax(const char *restrict str, char **restrict str_end,
                          int base);
extern uintmax_t strtoumax(const char *restrict str, char **restrict str_end,
                           int base);

__END_DECLS
#endif

#endif