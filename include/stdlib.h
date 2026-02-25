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

/* Returned by div */
typedef struct {
  int quot;
  int rem;
} div_t;

/* Returned by ldiv */
typedef struct {
  long quot;
  long rem;
} ldiv_t;

/* Returned by lldiv */
typedef struct {
  long long quot;
  long long rem;
} lldiv_t;

__BEGIN_DECLS

/* Convert a ASCII to an integer */
extern int atoi(const char *str);
extern long atol(const char *str);
extern long long atoll(const char *str);

/* Convert a string to an integer with a specified base, and move forward the
   pointer str_end to the last converted character */
extern long strtol(const char *restrict str, char **restrict str_end, int base);
extern long long strtoll(const char *restrict str, char **restrict str_end,
                         int base);
extern unsigned long strtoul(const char *restrict str, char **restrict str_end,
                             int base);
extern unsigned long long strtoull(const char *restrict str,
                                   char **restrict str_end, int base);

#if defined(QLIBC_ISO_C_VERSION) && QLIBC_ISO_C_VERSION < ISO_C_STANDARD_C11
/* Causes abnormal program termination without cleaning up */
extern void abort(void);

/* Program termination with status code, exit terminates the program with
   cleanup, _Exit terminates the program without cleanup */
extern void exit(int status);
extern void _Exit(int status);
#else
#include <stdnoreturn.h>
/* Causes abnormal program termination without cleaning up */
extern noreturn void abort(void);

/* Program termination with status code, exit terminates the program with
   cleanup, _Exit terminates the program without cleanup */
extern noreturn void exit(int status);
extern noreturn void _Exit(int status);
#endif

/* Allocate SIZE bytes of uninitialized memory, the allocated memory is
  always aligned with the max_align_t. */
extern void *malloc(size_t size);
/* Free memory allocated by malloc, recalloc and calloc */
extern void free(void *ptr);
/* Allocate memory for an array of NUM elements, each of which is SIZE
   bytes, the memory is always initialized to 0 */
extern void *calloc(size_t num, size_t size);
/* Reallocate memory and invalidate the old memory */
extern void *realloc(void *ptr, size_t new_size);

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= ISO_C_STANDARD_C11
/* Allocate memory with a specific ALIGNMENT bytes */
extern void *aligned_alloc(size_t alignment, size_t size);
#endif

/* Search the array for an element that matches the key, the underlying
   search algorithm is implementation-defined. */
extern void *bsearch(const void *key, const void *ptr, size_t count,
                     size_t size, int (*comp)(const void *, const void *));
/* Sort the array, the underlying sort algorithm is
 * implementation-defined.*/
extern void qsort(void *ptr, size_t count, size_t size,
                  int (*comp)(const void *, const void *));

/* Compute the absolute value of an integer N */
extern int abs(int n);
extern long labs(long n);
extern long long llabs(long long n);

/* Compute the division of two integers */
extern div_t div(int x, int y);
extern ldiv_t ldiv(long x, long y);
extern lldiv_t lldiv(long long x, long long y);

/* Returns the value of the environment variable specified by name. */
extern char *getenv(const char *name);

/* Sets the value of the environment variable specified by name to value.
 * If name does exist in the environment, then its value is changed to
 * value if overwrite is nonzero. */
extern int setenv(const char *name, const char *value, int overwrite);

/* Removes the environment variable specified by name. If name does not
   exist in the environment, then the function succeeds, and the
   environment is unchanged. */
extern int unsetenv(const char *name);

__END_DECLS

#if defined(__USE_QLIBC_EXTENDED)
#include <ext/itoa.h>
#endif

#endif // _QLIBC_STDLIB_H_