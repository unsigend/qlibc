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

#ifndef _QLIBC_EXT_ITOA_H_
#define _QLIBC_EXT_ITOA_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Write value into buf in the given base and return buf. Base 10 prefixes '-'
 * when value is negative; other bases are unsigned. */
extern char *itoa(int val, char *buf, int base);
extern char *ltoa(long val, char *buf, int base);
extern char *lltoa(long long val, char *buf, int base);

/* Write an unsigned value into buf in the given base and return buf. */
extern char *utoa(unsigned int val, char *buf, int base);
extern char *ultoa(unsigned long val, char *buf, int base);
extern char *ulltoa(unsigned long long val, char *buf, int base);

#ifdef __cplusplus
}
#endif

#endif /* _QLIBC_EXT_ITOA_H_ */
