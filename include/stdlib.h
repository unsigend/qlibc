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

#ifndef _QLIBC_STDLIB_H_
#define _QLIBC_STDLIB_H_

#include <feature.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Conversions to and from numeric formats
extern double atof(const char* str);

extern int atoi(const char *str);
extern long atol(const char *str);
extern long long atoll(const char *str);

extern long strtol(const char* restrict str, char** restrict str_end, int base);
extern long long strtoll(const char* restrict str, char** restrict str_end, int base);

extern unsigned long strtoul(const char* restrict str, char** restrict str_end, int base);
extern unsigned long long strtoull(const char* restrict str, char** restrict str_end, int base);

extern float strtof(const char* restrict str, char** restrict str_end);
extern double strtod(const char* restrict str, char** restrict str_end);
extern long double strtold(const char* restrict str, char** restrict str_end);

extern intmax_t strtoimax(const char* restrict str, char** restrict str_end, int base);
extern uintmax_t strtoumax(const char* restrict str, char** restrict str_end, int base);

// Program termination
#if QLIBC_ISO_C_VERSION < ISO_C_STANDARD_C11
extern void abort(void);
#else
#include <noreturn.h>
extern noreturn void abort(void);
#endif


// Memory management
extern void* malloc(size_t size);
extern void free(void* ptr);
extern void* calloc(size_t num, size_t size);
extern void* realloc(void* ptr, size_t new_size);

#ifdef __cplusplus
}
#endif

#endif // _QLIBC_STDLIB_H_