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
#include <stddef.h>
#include <stdint.h>

__BEGIN_DECLS
/* Convert a string to an integer */
extern int atoi(const char *str);
/* Convert a string to a long integer */
extern long atol(const char *str);
/* Convert a string to a long long integer */
extern long long atoll(const char *str);

/* Convert a string to a long integer */
extern long strtol(const char *restrict str, char **restrict str_end, int base);
/* Convert a string to a long long integer */
extern long long strtoll(const char *restrict str, char **restrict str_end,
                         int base);
/* Convert a string to an unsigned long integer */
extern unsigned long strtoul(const char *restrict str, char **restrict str_end,
                             int base);
/* Convert a string to an unsigned long long integer */
extern unsigned long long strtoull(const char *restrict str,
                                   char **restrict str_end, int base);
/* Convert a string to an intmax_t integer */
extern intmax_t strtoimax(const char *restrict str, char **restrict str_end,
                          int base);
/* Convert a string to an uintmax_t integer */
extern uintmax_t strtoumax(const char *restrict str, char **restrict str_end,
                           int base);

#if defined(QLIBC_SUPPORT_FLOATING_POINT) && QLIBC_SUPPORT_FLOATING_POINT == 1
/* Convert a string to a double precision floating point number */
extern double atof(const char *str);

/* Convert a string to a float precision floating point number */
extern float strtof(const char *restrict str, char **restrict str_end);

/* Convert a string to a double precision floating point number */
extern double strtod(const char *restrict str, char **restrict str_end);

/* Convert a string to a long double precision floating point number */
extern long double strtold(const char *restrict str, char **restrict str_end);
#endif

// program termination
#if QLIBC_ISO_C_VERSION < ISO_C_STANDARD_C11
/* Causes abnormal program termination without cleaning up */
extern void abort(void);
/* Causes normal program termination with cleaning up */
extern void exit(int status);
/* Causes normal program termination without cleaning up */
extern void _Exit(int status);
#else
#include <stdnoreturn.h>
/* Causes abnormal program termination without cleaning up */
extern noreturn void abort(void);
/* Causes normal program termination with cleaning up */
extern noreturn void exit(int status);
/* Causes normal program termination without cleaning up */
extern noreturn void _Exit(int status);
#endif

/* Allocate size bytes of uninitialized memory */
extern void *malloc(size_t size);
/* Free memory allocated by malloc */
extern void free(void *ptr);
/* Allocate memory for an array of num elements, each of which is size bytes */
extern void *calloc(size_t num, size_t size);
/* Reallocate memory and invalidate the old memory */
extern void *realloc(void *ptr, size_t new_size);

#if QLIBC_ISO_C_VERSION >= ISO_C_STANDARD_C11
/* Allocate memory with a specific alignment */
extern void *aligned_alloc(size_t alignment, size_t size);
#endif

/* Search the array for an element that matches the key, the underlying search
   algorithm is implementation-defined. */
extern void *bsearch(const void *key, const void *ptr, size_t count,
                     size_t size, int (*comp)(const void *, const void *));
/* Sort the array, the underlying sort algorithm is implementation-defined.*/
extern void qsort(void *ptr, size_t count, size_t size,
                  int (*comp)(const void *, const void *));

/* Compute the absolute value of an integer */
extern int abs(int n);
/* Compute the absolute value of a long integer */
extern long labs(long n);
/* Compute the absolute value of a long long integer */
extern long long llabs(long long n);
/* Compute the absolute value of an intmax_t integer */
extern intmax_t imaxabs(intmax_t n);

__END_DECLS

#endif // _QLIBC_STDLIB_H_