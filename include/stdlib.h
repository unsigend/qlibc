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

#ifndef _QLIBC_STDLIB_H_
#define _QLIBC_STDLIB_H_

#include <feature.h>
#include <stddef.h>

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

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#ifdef __cplusplus
extern "C" {
#endif

extern int atoi(const char *str);
extern long atol(const char *str);
extern long long atoll(const char *str);

extern long strtol(const char *__restrict str, char **__restrict str_end,
                   int base);
extern long long strtoll(const char *__restrict str, char **__restrict str_end,
                         int base);
extern unsigned long strtoul(const char *__restrict str,
                             char **__restrict str_end, int base);
extern unsigned long long strtoull(const char *__restrict str,
                                   char **__restrict str_end, int base);

#if __STDC_VERSION__ >= __ISO_C11
extern _Noreturn void abort(void);
extern _Noreturn void exit(int status);
extern _Noreturn void _Exit(int status);
#else
extern void abort(void) __attribute__((__noreturn__));
extern void exit(int status) __attribute__((__noreturn__));
extern void _Exit(int status) __attribute__((__noreturn__));
#endif

extern int atexit(void (*func)(void));

extern void *malloc(size_t size);
extern void free(void *ptr);
extern void *calloc(size_t num, size_t size);
extern void *realloc(void *ptr, size_t new_size);

extern void *bsearch(const void *key, const void *ptr, size_t n, size_t size,
                     int (*comp)(const void *, const void *));
extern void qsort(void *ptr, size_t n, size_t size,
                  int (*comp)(const void *, const void *));

extern int abs(int n);
extern long labs(long n);
extern long long llabs(long long n);

extern div_t div(int x, int y);
extern ldiv_t ldiv(long x, long y);
extern lldiv_t lldiv(long long x, long long y);

extern char *getenv(const char *name);

#if defined(_POSIX_SOURCE) || defined(_POSIX_C_SOURCE) ||                      \
    defined(_XOPEN_SOURCE) || defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
extern int putenv(char *string);
extern int setenv(const char *name, const char *value, int overwrite);
extern int unsetenv(const char *name);
#endif

#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
extern int clearenv(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _QLIBC_STDLIB_H_ */