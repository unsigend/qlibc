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

#ifndef _STDLIB_H_
#define _STDLIB_H_ 1

#include <stddef.h>
#include <stdint.h>

typedef struct {
    int quot;
    int rem;
} div_t;

typedef struct {
    long quot;
    long rem;
} ldiv_t;

typedef struct {
    long long quot;
    long long rem;
} lldiv_t;

__BEGIN_DECLS

extern int atoi(const char *str);
extern long atol(const char *str);
extern long long atoll(const char *str);

extern long strtol(const char *restrict str, char **restrict str_end, int base);
extern long long strtoll(const char *restrict str, char **restrict str_end,
                         int base);
extern unsigned long strtoul(const char *restrict str, char **restrict str_end,
                             int base);
extern unsigned long long strtoull(const char *restrict str,
                                   char **restrict str_end, int base);

#if __USE_ISO_C11
extern void abort(void);
extern void exit(int status);
extern void _Exit(int status);
#else
#include <stdnoreturn.h>
extern noreturn void abort(void);
extern noreturn void exit(int status);
extern noreturn void _Exit(int status);
#endif

extern int atexit(void (*func)(void));

extern void *malloc(size_t size);
extern void free(void *ptr);
extern void *calloc(size_t num, size_t size);
extern void *realloc(void *ptr, size_t new_size);

#if __USE_ISO_C11
extern void *aligned_alloc(size_t alignment, size_t size);
#endif

extern void *bsearch(const void *key, const void *ptr, size_t count,
                     size_t size, int (*comp)(const void *, const void *));
extern void qsort(void *ptr, size_t count, size_t size,
                  int (*comp)(const void *, const void *));

extern int abs(int n);
extern long labs(long n);
extern long long llabs(long long n);

extern div_t div(int x, int y);
extern ldiv_t ldiv(long x, long y);
extern lldiv_t lldiv(long long x, long long y);

extern char *getenv(const char *name);
extern int putenv(char *string);

#if defined(_POSIX_SOURCE) || defined(_POSIX_C_SOURCE) ||                      \
    defined(_XOPEN_SOURCE) || defined(_GNU_SOURCE) || defined(_BSD_SOURCE) ||  \
    defined(_QLIBC_SOURCE)
extern int setenv(const char *name, const char *value, int overwrite);
extern int unsetenv(const char *name);

#endif

#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE) || defined(_QLIBC_SOURCE)
extern void clearenv(void);
#endif

__END_DECLS

#if defined(_QLIBC_SOURCE) || defined(_GNU_SOURCE)
#include <ext/itoa.h>
#endif

#endif