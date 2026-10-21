/* qlibc - A light-weight and portable C standard library
 * Copyright (C) 2025-2027 Yixiang Qiu
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

#ifndef _QLIBC_EXT_STRTOL_H_
#define _QLIBC_EXT_STRTOL_H_

#ifdef __cplusplus
extern "C" {
#endif

extern long strtol(const char *__restrict str, char **__restrict str_end,
                   int base);
extern long long strtoll(const char *__restrict str, char **__restrict str_end,
                         int base);
extern unsigned long strtoul(const char *__restrict str,
                             char **__restrict str_end, int base);
extern unsigned long long strtoull(const char *__restrict str,
                                   char **__restrict str_end, int base);

#ifdef __cplusplus
}
#endif

#endif /* _QLIBC_EXT_STRTOL_H_ */